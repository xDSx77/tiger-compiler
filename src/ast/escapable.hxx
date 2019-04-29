/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{

  inline const bool&
  Escapable::escape_get() const
  {
    return escaped_;
  }

  inline void
  Escapable::escape_set(const bool& escaped)
  {
    escaped_ = escaped;
  }

} // namespace ast

