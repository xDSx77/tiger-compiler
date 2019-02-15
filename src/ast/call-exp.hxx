/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>

namespace ast
{


  inline const misc::symbol&
  CallExp::name_get() const
  {
    return name_;
  }
  inline misc::symbol&
  CallExp::name_get()
  {
    return name_;
  }
  inline void
  CallExp::name_set(const misc::symbol& name)
  {
    name_ = name;
  }

  inline const exps_type&
  CallExp::exps_get() const
  {
    return exps_;
  }
  inline exps_type&
  CallExp::exps_get()
  {
    return exps_;
  }

} // namespace ast

