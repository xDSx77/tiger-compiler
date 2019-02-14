/**
 ** \file ast/break-exp.hxx
 ** \brief Inline methods of ast::BreakExp.
 */

#pragma once

#include <ast/break-exp.hh>

// Hint: this needs to be done at TC-3.


namespace ast
{
  inline const Exp&
  BreakExp::exp_get() const
  {
    return *exp_;
  }
  inline Exp&
  BreakExp::exp_get()
  {
    return *exp_;
  }
} // namespace ast

