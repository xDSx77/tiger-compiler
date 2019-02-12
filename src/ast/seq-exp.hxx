/**
 ** \file ast/seq-exp.hxx
 ** \brief Inline methods of ast::SeqExp.
 */

#pragma once

#include <ast/seq-exp.hh>

namespace ast
{

  inline const Exp&
  SeqExp::exp_get() const
  {
    return *exp_;
  }

  inline Exp&
  SeqExp::exp_get()
  {
    return *exp_;
  }

} // namespace ast

