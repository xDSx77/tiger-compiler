/**
 ** \file ast/typable.hxx
 ** \brief Inline methods of ast::Typable.
 */

#pragma once

#include <ast/typable.hh>

namespace ast
{

  inline const type::Type*
  Typable::type_get() const
  {
    return type_;
  }

  inline void
  Typable::type_set(const type::Type* type)
  {
    type_ = type;
  }

} // namespace ast

