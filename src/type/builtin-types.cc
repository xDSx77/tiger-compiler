/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>

namespace type
{

  void Int::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void Int::accept(Visitor& v)
  {
    v(*this);
  }

  void String::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void String::accept(Visitor& v)
  {
    v(*this);
  }

  void Void::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void Void::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace type
