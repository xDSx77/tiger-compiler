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

  // FIXME: Some code was deleted here (Error reporting).

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
  }

  /*----------------.
  | Symbol tables.  |
  `----------------*/


  void
  Binder::scope_begin()
  {
  // FIXME: Some code was deleted here.
  }

  void
  Binder::scope_end()
  {
  // FIXME: Some code was deleted here.
  }

  /*---------.
  | Visits.  |
  `---------*/

  void
  Binder::operator()(ast::LetExp& e)
  {
  // FIXME: Some code was deleted here.
  }

/*
  void
  Binder::operator()(ast::NilExp& e)
  {
  }

  void
  Binder::operator()(ast::IntExp& e)

  void
  Binder::operator()(ast::StringExp& e)

  void
  Binder::operator()(ast::CallExp& e)

  void
  Binder::operator()(ast::OpExp& e)

  void
  Binder::operator()(ast::RecordExp& e)

  void
  Binder::operator()(ast::SeqExp& e)

  void
  Binder::operator()(ast::AssignExp& e)

  void
  Binder::operator()(ast::IfExp& e)

  void
  Binder::operator()(ast::WhileExp& e)

  void
  Binder::operator()(ast::ForExp& e)

  void
  Binder::operator()(ast::BreakExp& e)

  void
  Binder::operator()(ast::ArrayExp& e)

  void
  Binder::operator()(ast::CastExp& e)

  void
  Binder::operator()(ast::FieldInit& e)

  void
  Binder::operator()(ast::SimpleVar& e)

  void
  Binder::operator()(ast::FieldVar& e)

  void
  Binder::operator()(ast::SubscriptVar& e)

  void
  Binder::operator()(ast::CastVar& e)

  void
  Binder::operator()(ast::Ast& e)

  void
  Binder::operator()(ast::DecsList& e)

  void
  Binder::operator()(ast::Decs& e)

  void
  Binder::operator()(ast::NameTy& e)

  void
  Binder::operator()(ast::RecordTy& e)

  void
  Binder::operator()(ast::ArrayTy& e)

  void
  Binder::operator()(ast::Field e)
*/

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
