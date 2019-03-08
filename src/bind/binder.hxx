/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

#pragma once

#include <bind/binder.hh>

namespace bind
{

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  template <typename T>
  void
  Binder::undeclared(const std::string& k, const T& e)
  {
    std::string str = "undeclared ";
    error(e, str.append(k).append(": ").append(e.name_get()));
  }

  template <typename T>
  void
  Binder::redefinition(const T& e1, const T& e2)
  {
    error(e1, "redefinition: ");
    error(e2, "first definition");
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  Binder::decs_visit(ast::AnyDecs<D>& e)
  {
    // Shorthand.
    //using decs_type = ast::AnyDecs<D>;
    for (unsigned i = 0; i < e.decs_get().size(); i++)
      visit_dec_header(*(e.decs_get()[i]));
    for (unsigned i = 0; i < e.decs_get().size(); i++)
      if (e.decs_get()[i] != nullptr)
        visit_dec_body(*(e.decs_get()[i]));
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::TypeDec& e)
  {
    if (scope_map_type_.get(e.name_get()) != nullptr)
      redefinition(*(scope_map_type_.get(e.name_get())), e);
    else
      scope_map_type_.put(e.name_get(), &e);
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    auto& map = scope_map_func_.map_get().back();
    auto pair = map->find(e.name_get());
    if (pair != map->end())
      redefinition(*(scope_map_func_.get(e.name_get())), e);
    else
      scope_map_func_.put(e.name_get(), &e);
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::FunctionDec& e)
  {
    scope_begin();
    for (unsigned i = 0; i < e.formals_get().decs_get().size(); i++)
    {
      if (scope_map_var_.get(e.formals_get().decs_get()[i]->name_get()) != nullptr)
        redefinition(*(scope_map_var_.get(e.formals_get().decs_get()[i]->name_get())), *(e.formals_get().decs_get()[i]));
    }
    if (e.body_get() != nullptr)
      e.body_get()->accept(*this);
    scope_end();
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::TypeDec& e)
  {
    scope_begin();
    e.ty_get().accept(*this);
    scope_end();
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

} // namespace bind
