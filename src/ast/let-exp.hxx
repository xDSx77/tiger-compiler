/**
 ** \file ast/let-exp.hxx
 ** \brief Inline methods of ast::LetExp.
 */

#pragma once

#include <ast/let-exp.hh>

namespace ast
{

  inline const DecsList&
  LetExp::decs_get() const
  {
    return *decs_;
  }
  inline DecsList&
  LetExp::decs_get()
  {
    return *decs_;
  }

  inline const Exp&
  LetExp::body_get() const
  {
    return *body_;
  }
  inline Exp&
  LetExp::body_get()
  {
    return *body_;
  }

} // namespace ast

