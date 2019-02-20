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
  error(const ast::Ast& loc, const std::string& msg)
  {
  }

  void
  Binder::check_main(const ast::FunctionDec& e)
  {
      e.formals_get();

      e.result_get();
      e.body_get();
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
      super_type::operator()(e);
  }

/*
  void
  Binder::operator()(ast::NilExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::IntExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::StringExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::CallExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::OpExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::RecordExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::SeqExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::AssignExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::IfExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::WhileExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::ForExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::BreakExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::ArrayExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::CastExp& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::FieldInit& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::SimpleVar& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::FieldVar& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::SubscriptVar& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::CastVar& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::Ast& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::DecsList& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::Decs& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::NameTy& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::RecordTy& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::ArrayTy& e)
  {
      super_type::operator()(e);
  }

  void
  Binder::operator()(ast::Field e)
  {
      super_type::operator()(e);
  }
*/

  /*-------------------.
  | Visiting VarDecs.  |
  `-------------------*/

  void
  Binder::operator()(ast::VarDecs& e)
  {
    super_type::operator()(e);
  }

  void
  Binder::operator()(ast::VarDec& e)
  {
    super_type::operator()(e);
  }

  /*------------------------.
  | Visiting FunctionDecs.  |
  `------------------------*/

/*
  void operator()(ast::FunctionDecs& e)
  {
    super_type::operator()(e);
  }

  void operator()(ast::FunctionDec& e)
  {
    super_type::operator()(e);
  }
*/

  /*--------------------.
  | Visiting TypeDecs.  |
  `--------------------*/

/*
 void operator()(ast::TypeDecs& e)
 {
    super_type::operator()(e);
 }

 void operator()(ast::TypeDec& e)
 {
    super_type::operator()(e);
 }
*/

} // namespace bind
