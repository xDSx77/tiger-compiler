/**
 ** \file ast/record-exp.hxx
 ** \brief Inline methods of ast::RecordExp.
 */

#pragma once

#include <ast/record-exp.hh>

namespace ast
{

  inline const NameTy&
  RecordExp::name_ty_get() const
  {
    return *name_ty_;
  }
  inline NameTy&
  RecordExp::name_ty_get()
  {
    return *name_ty_;
  }

  inline const fieldinits_type&
  RecordExp::fieldinits_get() const
  {
    return fieldinits_;
  }
  inline fieldinits_type&
  RecordExp::fieldinits_get()
  {
    return fieldinits_;
  }


} // namespace ast

