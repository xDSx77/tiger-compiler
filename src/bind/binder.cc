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
    error_ << misc::error::error_type::bind << loc.location_get() << msg
           << std::endl;
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

  void
  Binder::operator()(ast::LetExp& e)
  {
    /*for (auto i = *(e.decs_get().decs_get().begin());
      i != *(e.decs_get().decs_get().end()); i++)
      decs_visit(*i);*/
  }


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
  Binder::operator()(ast::NameTy& e)
  {
  }

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    for (auto vardec : e.decs_get())
    {
      if (scope_map_var_.is_inside(vardec->name_get()) >= 0)
        redefinition(*(vardec), scope_map_var_.get(vardec->name_get()));

    }
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    scope_map_var_.put(e.name_get(), e);
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
