/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <memory>

#include <ast/all.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{

  namespace
  {

    // Try to cast the type into a nil type.
    // If it's not actually a `type::Nil`, return `nullptr`.
    // This allows us to write more clear code like:
    // if (auto nil = to_nil(e.type_get())
    // ...
    const Nil* to_nil(const Type& type)
    {
      return dynamic_cast<const Nil*>(&type.actual());
    }

  }

  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type*
  TypeChecker::type(ast::Typable& e)
  {
    if(!e.type_get())
      e.accept(*this);
    return e.type_get();
  }

  const Record*
  TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    for (const auto& i : e)
        res->field_add(i->name_get(), *type(i->type_name_get()));

    return res;
  }

  const Record*
  TypeChecker::type(const ast::VarDecs& e)
  {
    auto res = new Record;
    for (const auto& i : e.decs_get())
      res->field_add(i->name_get(), *type(*i));

    return res;
  }

  const misc::error&
  TypeChecker::error_get() const
  {
    return error_;
  }


  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void
  TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type
           << ast.location_get() << ": " << msg << std::endl;
  }

  void
  TypeChecker::type_mismatch(const ast::Ast& ast,
                             const std::string& exp1, const Type& type1,
                             const std::string& exp2, const Type& type2)
  {
    error_ << misc::error::error_type::type
           << ast.location_get() << ": type mismatch" << misc::incendl
           << exp1 << " type: " << type1 << misc::iendl
           << exp2 << " type: " << type2 << misc::decendl;
  }

  void
  TypeChecker::check_types(const ast::Ast& ast,
                           const std::string& exp1, const Type& type1,
                           const std::string& exp2, const Type& type2)
  {
    if (!(type1.compatible_with(type2)))
      type_mismatch(ast, exp1, type1, exp2, type2);
  }


  void
  TypeChecker::check_types(const ast::Ast& ast,
                           const std::string& exp1, ast::Typable& type1,
                           const std::string& exp2, ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    if (!(type1.type_get()->compatible_with(*type2.type_get())))
      type_mismatch(ast, exp1, *type1.type_get(), exp2, *type2.type_get());
  }


  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void
  TypeChecker::operator()(ast::SimpleVar& e)
  {
    type_default(e, type(*e.def_get()));
  }

  void
  TypeChecker::operator()(ast::SubscriptVar& e)
  {
    type_default(e, type(e.var_get()));
  }

  void
  TypeChecker::operator()(ast::FieldVar& e)
  {
    type_default(e, type(e.var_get()));
  }

  void
  TypeChecker::operator()(ast::CastVar& e)
  {
    type_default(e, type(e.ty_get()));
  }



  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void
  TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void
  TypeChecker::operator()(ast::IntExp& e)
  {
    type_default(e, &Int::instance());
  }

  void
  TypeChecker::operator()(ast::StringExp& e)
  {
    type_default(e, &String::instance());
  }


  // Complex values.

  void
  TypeChecker::operator()(ast::RecordExp& e)
  {
    // If no error occured, check for nil types in the record initialization.
    // If any error occured, there's no need to set any nil types.
    // If there are any record initializations, set the `record_type_`
    // of the `Nil` to the expected type.
    const Record* record;
    if (!(record = dynamic_cast<const Record*>(type(e.name_ty_get()))))
      error_and_recover(e, "not a record", *record);
    if (record->fields_get().size() != e.fieldinits_get().size())
      error_and_recover(e, "size not equal", *record);
    for (int i = 0; i < e.fieldinits_get().size(); i++)
    {
      if (e.fieldinits_get()[i]->name_get() != record->fields_get()[i].name_get())
        error_and_recover(e, "names not equal", *record);
      const Type* t = type(e.fieldinits_get()[i]->init_get());
      if (!(t->compatible_with(record->fields_get()[i].type_get())))
        error_and_recover(e, "incompatible types", *record);
    }
    type_default(e, record);

  }

  void
  TypeChecker::operator()(ast::OpExp& e)
  {
    e.left_get().accept(*this);
    e.right_get().accept(*this);
    // If any of the operands are of type Nil, set the `record_type_` to the
    // type of the opposite operand.
    if (!error_)
    {
      if (auto nil_right = to_nil(*e.right_get().type_get()))
      {
        const Nil* nil = to_nil(*e.right_get().type_get());
        nil->record_type_set(*e.left_get().type_get());
        e.right_get().type_set(nil);
      }
    }
    type_default(e, e.left_get().type_get());
  }

  void
  TypeChecker::operator()(ast::SeqExp& e)
  {
    for (auto exp : e.exps_get())
      type(*exp);
    if (e.exps_get().size() != 0)
      type_default(e, e.exps_get().back()->type_get());
  }

  void
  TypeChecker::operator()(ast::WhileExp& e)
  {
    type(e.test_get());
    type(e.body_get());
    type_default(e, &Void::instance());
  }

  void
  TypeChecker::operator()(ast::LetExp& e)
  {
    for (auto decs : e.decs_get().decs_get())
    {
      if (auto functiondecs = dynamic_cast<ast::FunctionDecs*>(decs))
        functiondecs->accept(*this);
      else if (auto typedecs = dynamic_cast<ast::TypeDecs*>(decs))
        typedecs->accept(*this);
      else if (auto vardecs = dynamic_cast<ast::VarDecs*>(decs))
        type(*vardecs->decs_get().front());
    }
    type_default(e, type(e.exp_get()));
  }

  void
  TypeChecker::operator()(ast::IfExp& e)
  {
    type(e.test_get());
    type(e.body_get());
    if (e.body_2_get())
      type_default(e, type(*e.body_2_get()));
    else
      type_default(e, &Void::instance());
  }

  void
  TypeChecker::operator()(ast::ForExp& e)
  {
    type(e.vardec_get());
    type(e.hi_get());
    type(e.body_get());
    type_default(e, &Void::instance());
  }

  void
  TypeChecker::operator()(ast::CastExp& e)
  {
    type(e.exp_get());
    type_default(e, type(e.ty_get()));
  }

  void
  TypeChecker::operator()(ast::CallExp& e)
  {
    for (auto exp : e.exps_get())
      type(*exp);
    type_default(e, type(*e.def_get()));
  }

  void
  TypeChecker::operator()(ast::BreakExp& e)
  {
    type_default(e, &Void::instance());
  }

  void
  TypeChecker::operator()(ast::AssignExp& e)
  {
    type(e.var_get());
    type(e.exp_get());
    type_default(e, &Void::instance());
  }

  void
  TypeChecker::operator()(ast::ArrayExp& e)
  {
    type(e.name_ty_get());
    type(e.size_get());
    type(e.value_get());
    type_default(e, &Void::instance());
  }

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  TypeChecker::operator()(ast::FunctionDecs& e)
  {
    decs_visit<ast::FunctionDec>(e);
  }


  void
  TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store the type of this function.
  template <>
  void
  TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
  // FIXME: Some code was deleted here.
  }


  // Type check this function's body.
  template <>
  void
  TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      {
        visit_routine_body<Function>(e);

        // Check for Nil types in the function body.
        if (!error_)
          {
  // FIXME: Some code was deleted here.
          }
      }
  }


  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void
  TypeChecker::operator()(ast::VarDec& e)
  {
    if (e.type_name_get())
      type(*e.type_name_get());
    if (e.init_get())
      type(*e.init_get());
    type_default(e, &Void::instance());
  }


  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  TypeChecker::operator()(ast::TypeDecs& e)
  {
    decs_visit<ast::TypeDec>(e);
  }


  void
  TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }


  // Store this type.
  template <>
  void
  TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
  // FIXME: Some code was deleted here.
  }

  // Bind the type body to its name.
  template <>
  void
  TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
  // FIXME: Some code was deleted here.
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  TypeChecker::decs_visit(ast::AnyDecs<D>& e)
  {
  // FIXME: Some code was deleted here.
  }


  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void
  TypeChecker::operator()(ast::NameTy& e)
  {
  // FIXME: Some code was deleted here (Recognize user defined types, and built-in types).
    type_default(e, type(*e.def_get()));
  }

  void
  TypeChecker::operator()(ast::RecordTy& e)
  {
    type_default(e, type(e.fields_get()));
  }

  void
  TypeChecker::operator()(ast::ArrayTy& e)
  {
    type_default(e, type(e.base_type_get()));
  }

} // namespace type
