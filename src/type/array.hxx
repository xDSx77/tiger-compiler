/**
 ** \file type/array.hxx
 ** \brief Inline methods for type::Array.
 */
#pragma once

#include <misc/contract.hh>
#include <type/array.hh>

namespace type
{

  inline const Type&
  Array::type_get() const
  {
    return type_;
  }

} // namespace type
