/**
 ** \file ast/field-var.hxx
 ** \brief Inline methods of ast::FieldVar.
 */

#pragma once

#include <ast/field-var.hh>

namespace ast
{

  inline const Var&
  CastVar::var_get() const
  {
    return *var_;
  }
  inline Var&
  CastVar::var_get()
  {
    return *var_;
  }
  // FIXME: Some code was deleted here.
  inline const misc::symbol&
  FieldVar::name_get() const
  {
    return name_;
  }
  inline void
  FieldVar::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const VarDec*
  FieldVar::def_get() const
  {
    return def_;
  }
  inline VarDec*
  FieldVar::def_get()
  {
    return def_;
  }
  inline void
  FieldVar::def_set(VarDec* def)
  {
    def_ = def;
  }
} // namespace ast

