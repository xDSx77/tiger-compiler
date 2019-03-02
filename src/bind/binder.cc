/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

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
    error_ << misc::error::error_type::bind << loc.location_get() << msg << std::endl;
  }

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
    if (e.formals_get().decs_get().size() != 0)
      error(e, "wrong number of arguments in _main function");
    if (e.result_get() != nullptr)
      error(e, "_main function must not have a return type");
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
/*
  void
  Binder::operator()(ast::LetExp& e)
  {
    for (auto i = *(e.decs_get().decs_get().begin());
      i != *(e.decs_get().decs_get().end()); i++)
      decs_visit(*i);
  }
*/

  void
  Binder::operator()(ast::CallExp& e)
  {
    e.def_set(&scope_map_func_.get(e.name_get()));
  }

  void
  Binder::operator()(ast::SimpleVar& e)
  {
    e.def_set(&scope_map_var_.get(e.name_get()));
  }

  void
  Binder::operator()(ast::FieldVar& e)
  {
    e.var_get();
  }

  void
  Binder::operator()(ast::SubscriptVar& e)
  {
    e.var_get();
  }

  void
  Binder::operator()(ast::NameTy& e)
  {
    visit_dec_header(*(e.def_get()));
    visit_dec_body(*(e.def_get()));
  }

  void
  Binder::operator()(ast::RecordTy& e)
  {
    for (unsigned i = 0; i < e.fields_get().size(); i++)
    {
      visit_dec_header(*(e.fields_get()[i]->type_name_get().def_get()));
      visit_dec_body(*(e.fields_get()[i]->type_name_get().def_get()));
    }
  }

  void
  Binder::operator()(ast::ArrayTy& e)
  {
    visit_dec_header(*(e.base_type_get().def_get()));
    visit_dec_body(*(e.base_type_get().def_get()));
  }

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    decs_visit(e);
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    visit_dec_header(e);
    visit_dec_body(e);
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
    visit_dec_header(e);
    visit_dec_body(e);
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
    visit_dec_header(e);
    visit_dec_body(e);
  }

} // namespace bind
