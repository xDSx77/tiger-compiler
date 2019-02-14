/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{

  inline const misc::symbol&
  FieldVar::name_get() const
  {
    return name_;
  }
  inline misc::symbol&
  FieldVar::name_get()
  {
    return name_;
  }

  inline void
  FieldVar::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const Var&
  FieldVar::var_get() const
  {
    return *var_;
  }
  inline Var&
  FieldVar::var_get()
  {
    return *var_;
  }
} // namespace ast

