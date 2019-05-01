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
    for (auto dec : e.decs_get())
      visit_dec_header(*dec);
    for (auto dec : e.decs_get())
      if (dec != nullptr)
        visit_dec_body(*dec);
  }

  template <>
  inline
  void
  Binder::visit_dec_header(ast::FunctionDec& e)
  {
    auto& cur_map = scope_map_func_.map_get().back();
    auto pair = cur_map.find(e.name_get());
    if (e.name_get() == misc::symbol("_main"))
      check_main(e);
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
    std::vector<ast::Exp*> copy_loops = loops_;
    loops_ = *(new std::vector<ast::Exp*>());
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
    loops_ = copy_loops;
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
