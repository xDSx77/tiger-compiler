/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{


  inline const NameTy&
  ArrayExp::name_ty_get() const
  {
    return *name_ty_;
  }
  inline NameTy&
  ArrayExp::name_ty_get()
  {
    return *name_ty_;
  }

  inline const Exp&
  ArrayExp::size_get() const
  {
    return *size_;
  }
  inline Exp&
  ArrayExp::size_get()
  {
    return *size_;
  }

  inline const Exp&
  ArrayExp::value_get() const
  {
    return *value_;
  }
  inline Exp&
  ArrayExp::value_get()
  {
    return *value_;
  }
} // namespace ast

