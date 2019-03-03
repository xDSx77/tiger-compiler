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
    error_ << misc::error::error_type::bind << e.location_get() << k << std::endl;
  }

  template <typename T>
  void
  Binder::redefinition(const T& e1, const T& e2)
  {
    error_ << misc::error::error_type::bind /*<< e2.location_get()*/
      << "undeclared variable: " << e2.name_get() << std::endl;
    error_ << misc::error::error_type::bind /*<< e1.location_get()*/
      << "first definition of " << e1.name_get() << std::endl;
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

  template <>
  inline
  void
  Binder::visit_dec_header(ast::TypeDec& e)
  {
    if (scope_map_type_.is_inside(e.name_get()) >= 0)
      redefinition(e, scope_map_type_.get(e.name_get()));
    scope_map_type_.put(e.name_get(), e);
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    if (scope_map_func_.is_inside(e.name_get()) >= 0)
        redefinition(e, scope_map_func_.get(e.name_get()));
    for (unsigned i = 0; i < e.formals_get().decs_get().size(); i++)
    {
      if (scope_map_var_.is_inside(e.formals_get().decs_get()[i]->name_get()) >= 0)
        redefinition(*(e.formals_get().decs_get()[i]),
          scope_map_var_.get(e.formals_get().decs_get()[i]->name_get()));
    }
    scope_map_func_.put(e.name_get(), e);
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::FunctionDec& e)
  {
    scope_begin();
    e.formals_get();
    /*for (unsigned i = 0; i < e.formals_get().decs_get().size(); i++)
      scope_map_var_.put(e.formals_get().decs_get()[i]->name_get(),
          *(e.formals_get().decs_get()[i]));*/
  }

  template <>
  inline
  void
  Binder::visit_dec_body(ast::TypeDec& e)
  {
    scope_begin();
  }

  /* These specializations are in bind/binder.hxx, so that derived
     visitors can use them (otherwise, they wouldn't see them).  */

  // FIXME: Some code was deleted here.

} // namespace bind
