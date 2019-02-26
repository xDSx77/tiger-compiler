/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{

  template <typename Def>
  misc::symbol
  new_name_compute(const Def& e)
  {
      return e.Renamer();
  }
  template <typename Def>
  misc::symbol
  new_name(const Def& e)
  {
      return e.Renamer();
  }
  template <class E, class Def>
  void
  visit(E& e, const Def* def)
  {
      def.e;
  }
  template <class E, class Def>
  void
  Renamer::visit(E& e, const Def* def)
  {
      def.e;
  }
  /*void
  Renamer::operator()(ast::NilExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::IntExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::StringExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::CallExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::OpExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::RecordExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::SeqExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::AssignExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::IfExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::WhileExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::ForExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::BreakExp&)
  {}
  void
  Renamer::operator()(ast::LetExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::ArrayExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::CastExp& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::FieldInit& e)
  {
      super_type::operator()(e);
  }*/
  void
  Renamer::operator()(ast::DecsList& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::Decs& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::VarDecs& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::VarDec& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::FunctionDecs& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::FunctionDec& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::TypeDecs& e)
  {
      super_type::operator()(e);
  }
  void
  Renamer::operator()(ast::TypeDec& e)
  {
      super_type::operator()(e);
  }

} // namespace bind
