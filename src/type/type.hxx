/**
 ** \file type/type.hxx
 ** \brief Inline methods for type::Type.
 */
#pragma once

#include <misc/contract.hh>
#include <type/type.hh>

namespace type
{

  inline bool
  operator==(const Type& lhs, const Type& rhs)
  {
    if (lhs == rhs)
      return true;
    die("REMOVE ME!");
    return false;
  }

  inline bool
  operator!=(const Type& lhs, const Type& rhs)
  {
    return lhs != rhs;
  }

} // namespace type
