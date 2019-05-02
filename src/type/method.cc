/**
 ** \file type/method.cc
 ** \brief Implementation for type/method.hh.
 */

#include <iostream>

#include <type/method.hh>
#include <type/visitor.hh>

namespace type
{

  Method::Method(const misc::symbol& name, const Class* owner,
                 const Record* formals, const Type& result,
                 ast::MethodDec* def)
    : Function(formals, result)
    , name_(name)
    , owner_(owner)
    , def_(def)
  {}

  void
  Method::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Method::accept(Visitor& v)
  {
    v(*this);
  }

  bool
  Method::compatible_with(const Type& other) const
  {
    if (*this != other)
      return false;
    const Function& f = dynamic_cast<const Function&>(*this);
    if (!(f.compatible_with(other)))
      return false;
    const Method& m2 = dynamic_cast<const Method&>(other);
    if (owner_ != m2.owner_get())
      return false;
    if (name_ != m2.name_get())
      return false;
    return true;
  }

} // namespace type
