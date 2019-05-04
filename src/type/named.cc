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

  void
  Named::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Named::accept(Visitor& v)
  {
    v(*this);
  }

  bool
  Named::sound() const
  {
    std::set<misc::symbol> visited_named;
    visited_named.insert(name_);
    const Named* cur = this;
    while(1)
    {
      auto named = dynamic_cast<const Named*>(cur->type_);
      if (named)
      {
        if (visited_named.find(named->name_get()) != visited_named.end())
          return false;
        visited_named.insert(named->name_get());
        cur = named;
      }
      else
        return true;
    }
  }

  bool
  Named::compatible_with(const Type& other) const
  {
    return *type_ == other;
  }

} // namespace type
