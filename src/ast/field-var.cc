/**
 ** \file ast/field-var.cc
 ** \brief Implementation of ast::FieldVar.
 */

#include <ast/visitor.hh>
#include <ast/field-var.hh>

namespace ast
{
    FieldVar::FieldVar(const Location& location, Var* var, const misc::symbol& name)
    : Var(location)
    , var_(var)
    , name_(name)
  {}

  FieldVar::~CastVar()
  {
    delete var_;
  }

  void
  FieldVar::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  FieldVar::accept(Visitor& v)
  {
    v(*this);
  }
  // FIXME: Some code was deleted here.
} // namespace ast

