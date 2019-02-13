/**
 ** \file ast/if-exp.hxx
 ** \brief Inline methods of ast::IfExp.
 */

#pragma once

#include <ast/if-exp.hh>

namespace ast
{
  inline const Exp&
  IfExp::if_get() const
  {
    return if_;
  }
} // namespace ast

