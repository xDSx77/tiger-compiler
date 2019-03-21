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
    std::string str = "redefinition: ";
    error(e2, str.append(e2.name_get()));
    error(e1, "first definition");
  }

  /*------------------.
  | Visiting /Decs/.  |
  `------------------*/

  template <class D>
  void
  Binder::decs_visit(ast::AnyDecs<D>& e)
  {
    for (unsigned i = 0; i < e.decs_get().size(); i++)
      visit_dec_header(*(e.decs_get()[i]));
    for (unsigned i = 0; i < e.decs_get().size(); i++)
      if (e.decs_get()[i] != nullptr)
        visit_dec_body(*(e.decs_get()[i]));
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    auto& cur_map = scope_map_func_.map_get().back();
    auto pair = cur_map.find(e.name_get());
    if (pair != cur_map.end())
      redefinition(*(scope_map_func_.get(e.name_get())), e);
    else
      scope_map_func_.put(e.name_get(), &e);
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
  Binder::visit_dec_body(ast::FunctionDec& e)
  {
    scope_begin();
    for (auto dec : e.formals_get().decs_get())
    {
      if (scope_map_var_.get(dec->name_get()) != nullptr)
        redefinition(*(scope_map_var_.get(dec->name_get())), *dec);
      scope_map_var_.put(dec->name_get(), dec);
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

} // namespace bind
