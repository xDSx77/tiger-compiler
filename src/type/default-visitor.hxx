/**
 ** \file type/default-visitor.hxx
 ** \brief Implementation for type/default-visitor.hh.
 */

#pragma once

#include <misc/algorithm.hh>
#include <type/class.hh>
#include <type/default-visitor.hh>
#include <type/types.hh>

namespace type
{

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::GenDefaultVisitor() :
    GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenDefaultVisitor<Const>::~GenDefaultVisitor() = default;

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Nil>&)
  {}

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Void>&)
  {}

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Int>&)
  {}

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<String>&)
  {}

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Named>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Array>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Record>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Class>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Function>& e)
  {
    super_type::operator()(e);
  }

  template <template <typename> class Const>
  void
  GenDefaultVisitor<Const>::operator()(const_t<Method>& e)
  {
    e.Function::accept(*this);
  }

} // namespace type
