/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{

  inline symbol&
  symbol::operator=(const symbol& rhs)
  {
    return *this->symbol(rhs.obj_);
  }

  inline bool
  symbol::operator==(const symbol& rhs) const
  {
    return (this->obj_ == rhs.obj_);
  }

  inline bool
  symbol::operator!=(const symbol& rhs) const
  {
    return !(this->obj_ == rhs.obj_);
  }

  inline std::ostream&
  operator<<(std::ostream& ostr, const symbol& the)
  {
    return ostr << the.obj_;
  }

}
