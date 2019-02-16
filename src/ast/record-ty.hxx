/**
 ** \file ast/record-ty.hxx
 ** \brief Inline methods of ast::RecordTy.
 */

#pragma once

#include <ast/record-ty.hh>

namespace ast
{

  inline const fields_type&
  RecordTy::fields_get() const
  {
    return fields_;
  }
  inline fields_type&
  RecordTy::fields_get()
  {
    return fields_;
  }

} // namespace ast

