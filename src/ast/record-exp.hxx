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

