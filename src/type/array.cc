/**
 ** \file type/array.cc
 ** \brief Implementation for type/array.hh.
 */

#include <ostream>

#include <type/array.hh>
#include <type/visitor.hh>

namespace type
{

  Array::Array(const Type& type)
    : type_(type)
  {}

  void
  Array::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Array::accept(Visitor& v)
  {
    v(*this);
  }

  bool
  Array::compatible_with(const Type& other) const
  {
    return *this == other;
  }

} // namespace type
