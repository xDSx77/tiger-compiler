/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <iostream>
#include <ostream>

#include <misc/indent.hh>
#include <type/class.hh>
#include <type/visitor.hh>

namespace type
{

  Class::Class(const Class* super)
    : Type()
    , id_(fresh_id())
    , super_(super)
    , subclasses_()
  {}

  void
  Class::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  Class::accept(Visitor& v)
  {
    v(*this);
  }

  const Type*
  Class::attr_type(const misc::symbol& key) const
  {
    for (const Class* cur = this; cur; cur = cur->super_get())
      for (const Attribute& attr : cur->attrs_get())
        if (attr.name_get() == key)
          return &attr.type_get();
    return nullptr;
  }

  const Type*
  Class::meth_type(const misc::symbol& key) const
  {
    for (const Class* cur = this; cur; cur = cur->super_get())
      for (const Method* meth : cur->meths_get())
        if (meth->name_get() == key)
          return &meth->type_get();
    return nullptr;
  }

  const Class*
  Class::common_root(const Class& other) const
  {
    for (const Class* cur = this; cur; cur = cur->super_get())
      for (const Class* cur2 = &other; cur2; cur2 = cur2->super_get())
        if (cur->id_get() == cur2->id_get())
          return cur;
    return nullptr;
  }

  bool
  Class::sound() const
  {
  }

  bool
  Class::compatible_with(const Type& other) const
  {
    for (const Class* sub : subclasses_)
      if (*sub == dynamic_cast<const Class&>(other))
        return true;
    return false;
  }

  const Class&
  Class::object_instance()
  {
    Class* object = new Class(nullptr);
    return *object;
  }

  unsigned Class::fresh_id()
  {
    static unsigned counter_ = 0;
    return counter_++;
  }

} // namespace type
