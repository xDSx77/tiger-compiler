/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{


  inline const Exp&
  ArrayExp::exp_get() const
  {
    return *exp_;
  }
  inline Exp&
  ArrayExp::exp_get()
  {
    return *exp_;
  }

  inline const NameTy&
  ArrayExp::type_get() const
  {
    return *type_;
  }
  inline NameTy&
  ArrayExp::type_get()
  {
    return *type_;
  }

} // namespace ast

