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
  }

  template <typename T>
  void
  Binder::redefinition(const T& e1, const T& e2)
  {
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  Binder::decs_visit(ast::AnyDecs<D>& e)
  {
    // Shorthand.
    using decs_type = ast::AnyDecs<D>;
    for (unsigned i = 0; i < e.decs_get().size(); i++)
    {
      visit_dec_header(*(e.decs_get()[i]));
      visit_dec_body(*(e.decs_get()[i]));
    }
  }

  template <class D>
  void
  Binder::visit_dec_header(D& e)
  {
    if (scope_map_func_.get(e.name_get()))
        redefinition(e.name_get(), e.name_get());
    for (unsigned i = 0; i < e.formals_get().decs_get().size(); i++)
    {
      if (scope_map_var_.get(e.formals_get().decs_get()[i]->name_get()))
        redefinition(e.formals_get().decs_get()[i]->name_get(), e.formals_get().decs_get()[i]->name_get());
    }
    scope_map_func_.put(e.name_get(), e.body_get());
  }

  template <class D>
  void
  Binder::visit_dec_body(D& e)
  {
    scope_begin();
    for (unsigned i = 0; i < e.formals_get().decs_get().size(); i++)
      scope_map_var_.put(e.formals_get().decs_get()[i]->name_get(), e.formals_get().decs_get()[i]->init_get());
  }
  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

} // namespace bind
