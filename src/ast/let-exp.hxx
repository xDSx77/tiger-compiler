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

  inline const exps_type&
  LetExp::exps_get() const
  {
    return exps_;
  }
  inline exps_type&
  LetExp::exps_get()
  {
    return exps_;
  }

} // namespace ast

