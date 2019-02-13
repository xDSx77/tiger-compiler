/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{
  inline const Field&
  RecordTy::field_get() const
  {
    return *fld_;
  }
  inline Field&
  RecordTy::field_get()
  {
    return *fld_;
  }
  inline const Ty&
  RecordTy::ty_get() const
  {
    return *ty_;
  }
  inline Ty&
  RecordTy::ty_get()
  {
    return *ty_;
  }
} // namespace ast

