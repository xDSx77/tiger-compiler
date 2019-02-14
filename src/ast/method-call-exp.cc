/**
 ** \file ast/method-call-exp.cc
 ** \brief Implementation of ast::MethodCallExp.
 */

#include <ast/visitor.hh>
#include <ast/method-call-exp.hh>

namespace ast
{

  MethodCallExp::MethodCallExp(const Location& location, Exp* body,
                              FunctionDec* dec, const misc::symbol& name,
                              Var* var, MethodDec* method)
    : CallExp(location, body, dec, name)
    , var_(var)
    , method_(method)
  {}

  MethodCallExp::~MethodCallExp()
  {
    delete var_;
    delete method_;
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

