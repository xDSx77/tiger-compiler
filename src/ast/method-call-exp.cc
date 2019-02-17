/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{

  MethodCallExp::MethodCallExp(const Location& location,
                              const misc::symbol& name, exps_type* exps, Var* var)
    : CallExp(location, name, exps)
    , var_(var)
  {}

  MethodCallExp::~MethodCallExp()
  {
    delete var_;
  }

  void
  MethodCallExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  MethodCallExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

