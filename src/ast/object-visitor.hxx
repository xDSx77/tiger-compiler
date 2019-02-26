/**
 ** \file ast/object-visitor.hxx
 ** \brief Implementation for ast/object-visitor.hh.
 */

#pragma once

#include <misc/contract.hh>
#include <ast/all.hh>
#include <ast/object-visitor.hh>

namespace ast
{

  template <template <typename> class Const>
  GenObjectVisitor<Const>::GenObjectVisitor()
    : GenVisitor<Const>()
  {}

  template <template <typename> class Const>
  GenObjectVisitor<Const>::~GenObjectVisitor()
  {}


  /*-------------------------------.
  | Object-related visit methods.  |
  `-------------------------------*/

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<ClassTy>& e)
  {
      e.super_get().accept(*this);
      for (auto i = *(e.decs_get().decs_get().begin()); i != *(e.decs_get().decs_get().end()); i++)
        i->accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDecs>& e)
  {
    for (unsigned i = 0; i < e.decs_get().size(); i++)
      e.decs_get()[i]->accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodDec>& e)
  {
    e.accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<MethodCallExp>& e)
  {
    e.var_get().accept(*this);
  }

  template <template <typename> class Const>
  void
  GenObjectVisitor<Const>::operator()(const_t<ObjectExp>& e)
  {
    e.type_get().accept(*this);
  }


} // namespace ast
