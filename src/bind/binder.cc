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
  Binder::check_main(ast::FunctionDec& e)
  {
    visit_dec_header(e);
    visit_dec_body(e);
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
    scope_begin();
    /*
    for (ast::VarDecs* i = *(e.decs_get().decs_get().begin()); i != *(e.decs_get().decs_get().end()); i++)
      for (unsigned j = 0; j < i->decs_get().size(); j++)
        scope_map_var_.put(i->decs_get()[j]->name_get(), *(i->decs_get()[j]));*/
  }


  void
  Binder::operator()(ast::CallExp& e)
  {
  }

  void
  Binder::operator()(ast::OpExp& e)
  {
  }

  void
  Binder::operator()(ast::RecordExp& e)
  {
  }

  void
  Binder::operator()(ast::SeqExp& e)
  {
  }

  void
  Binder::operator()(ast::AssignExp& e)
  {
  }

  void
  Binder::operator()(ast::IfExp& e)
  {
  }

  void
  Binder::operator()(ast::WhileExp& e)
  {
  }

  void
  Binder::operator()(ast::ForExp& e)
  {
  }

  void
  Binder::operator()(ast::BreakExp& e)
  {
  }

  void
  Binder::operator()(ast::ArrayExp& e)
  {
  }

  void
  Binder::operator()(ast::CastExp& e)
  {
  }

  void
  Binder::operator()(ast::FieldInit& e)
  {
  }

  void
  Binder::operator()(ast::SimpleVar& e)
  {
  }

  void
  Binder::operator()(ast::FieldVar& e)
  {
  }

  void
  Binder::operator()(ast::SubscriptVar& e)
  {
  }

  void
  Binder::operator()(ast::CastVar& e)
  {
  }

  void
  Binder::operator()(ast::Ast& e)
  {
  }

  void
  Binder::operator()(ast::DecsList& e)
  {
  }

  void
  Binder::operator()(ast::Decs& e)
  {
  }

  void
  Binder::operator()(ast::NameTy& e)
  {
  }

  void
  Binder::operator()(ast::RecordTy& e)
  {
  }

  void
  Binder::operator()(ast::ArrayTy& e)
  {
  }

  void
  Binder::operator()(ast::Field& e)
  {
  }


  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/
/*
  void
  Binder::operator()(ast::VarDecs& e)
  {
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
  }
*/
  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

/*
  void operator()(ast::FunctionDecs& e)
  {
  }

  void operator()(ast::FunctionDec& e)
  {
  }
*/

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

/*
 void operator()(ast::TypeDecs& e)
 {
 }

 void operator()(ast::TypeDec& e)
 {
 }
*/

} // namespace bind
