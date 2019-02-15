/**
 ** \file ast/array-exp.hxx
 ** \brief Inline methods of ast::ArrayExp.
 */

#pragma once

#include <ast/array-exp.hh>

namespace ast
{


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

