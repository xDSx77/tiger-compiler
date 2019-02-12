/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{

  inline Exp&
  SeqExp::exp_get() const
  {
    return *exp_;
  }

} // namespace ast

