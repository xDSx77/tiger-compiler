/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>
#include <exception>
#include <misc/contract.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error&
  Binder::error_get() const
  {
    return error_;
  }

  void
  Binder::error(const ast::Ast& loc, const std::string& msg)
  {
    error_ << misc::error::error_type::bind << loc.location_get()  << ' ' << msg
           << std::endl;
  }

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
    if (e.formals_get().decs_get().size() != 0)
      error(e, "wrong number of arguments in _main function");
    if (e.result_get() != nullptr)
      error(e, "_main function must not have a return type");
    if (scope_map_func_.get(e.name_get()) != nullptr)
      redefinition(*(scope_map_func_.get(e.name_get())), e);
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/


  void
  Binder::scope_begin()
  {
    scope_map_type_.scope_begin();
    scope_map_func_.scope_begin();
    scope_map_var_.scope_begin();
  }

  void
  Binder::scope_end()
  {
    scope_map_type_.scope_end();
    scope_map_func_.scope_end();
    scope_map_var_.scope_end();
  }

  /*---------.
  | Visits.  |
  `---------*/

  void
  Binder::operator()(ast::LetExp& e)
  {
    for (auto decs : e.decs_get().decs_get())
    {
      decs->accept(*this);
    }
    e.exp_get().accept(*this);
  }


  void
  Binder::operator()(ast::CallExp& e)
  {
    auto functiondec = scope_map_func_.get(e.name_get());
    if (functiondec != nullptr)
      e.def_set(functiondec);
    else
      undeclared("function", e);
  }

  void
  Binder::operator()(ast::SimpleVar& e)
  {
    auto vardec = scope_map_var_.get(e.name_get());
    if (vardec != nullptr)
      e.def_set(vardec);
    else
      undeclared("variable", e);
  }

  void
  Binder::operator()(ast::NameTy& e)
  {
    auto typedec = scope_map_type_.get(e.name_get());
    if (typedec != nullptr || e.name_get() == misc::symbol("int")
        || e.name_get() == misc::symbol("string"))
      e.def_set(typedec);
    else
      undeclared("type", e);
  }

  void
  Binder::operator()(ast::IfExp& e)
  {
    e.test_get().accept(*this);
    scope_begin();
    e.body_get().accept(*this);
    if (e.body_2_get())
      e.body_2_get()->accept(*this);
    scope_end();
  }

  void
  Binder::operator()(ast::ForExp& e)
  {
    scope_begin();
    loops_.push_back(&e);
    e.vardec_get().accept(*this);
    e.hi_get().accept(*this);
    e.body_get().accept(*this);
    loops_.pop_back();
    scope_end();
  }

  void
  Binder::operator()(ast::WhileExp& e)
  {
    scope_begin();
    loops_.push_back(&e);
    e.test_get().accept(*this);
    e.body_get().accept(*this);
    loops_.pop_back();
    scope_end();
  }

  void
  Binder::operator()(ast::BreakExp& e)
  {
    if (loops_.size() == 0)
      error(e, "'break' outside any loop");
  }

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    for (auto vardec : e.decs_get())
      vardec->accept(*this);
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    if (scope_map_var_.get(e.name_get()) != nullptr)
      redefinition(*(scope_map_var_.get(e.name_get())), e);
    else
      scope_map_var_.put(e.name_get(), &e);
    if (e.type_name_get() != nullptr)
      e.type_name_get()->accept(*this);
    if (e.init_get() != nullptr)
      e.init_get()->accept(*this);
  }

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

  void
  Binder::operator()(ast::FunctionDecs& e)
  {
    decs_visit(e);
  }

  void
  Binder::operator()(ast::FunctionDec& e)
  {
    if (e.name_get() == misc::symbol("_main"))
      check_main(e);
  }

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

  void
  Binder::operator()(ast::TypeDecs& e)
  {
    decs_visit(e);
  }

  void
  Binder::operator()(ast::TypeDec& e)
  {
  }

} // namespace bind
