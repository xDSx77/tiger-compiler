/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{

  inline const NameTy&
  RecordExp::type_get() const
  {
    return *type_;
  }
  inline NameTy&
  RecordExp::type_get()
  {
    return *type_;
  }

  inline const FieldInit&
  RecordExp::field_get() const
  {
    return *field_;
  }
  inline FieldInit&
  RecordExp::field_get()
  {
    return *field_;
  }


} // namespace ast
