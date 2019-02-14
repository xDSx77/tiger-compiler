/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{


  inline const Exp&
  CallExp::body_get() const
  {
    return *body_;
  }
  inline Exp&
  CallExp::body_get()
  {
    return *body_;
  }
  inline void
  CallExp::body_set(Exp* body)
  {
    body_ = body;
  }

  inline const misc::symbol&
  CallExp::name_get() const
  {
    return name_;
  }
  inline misc::symbol&
  CallExp::name_get()
  {
    return name_;
  }
  inline void
  CallExp::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const FunctionDec&
  CallExp::dec_get() const
  {
    return *dec_;
  }
  inline FunctionDec&
  CallExp::dec_get()
  {
    return *dec_;
  }

} // namespace ast

