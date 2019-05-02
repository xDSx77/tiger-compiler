/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <ostream>
#include <set>

#include <type/named.hh>
#include <type/visitor.hh>

namespace type
{

  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
  {
    type_set(type);
  }

  void Named::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void Named::accept(Visitor& v)
  {
    v(*this);
  }

  bool Named::sound() const
  {
    if (name_ == dynamic_cast<const Named*>(type_)->name_get())
      return false;
    return true;
  }

  bool Named::compatible_with(const Type& other) const
  {
    if (*type_ == other)
      return true;
    return false;
  }

} // namespace type
