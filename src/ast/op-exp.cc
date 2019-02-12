/**
 ** \file ast/op-exp.cc
 ** \brief Implementation of ast::OpExp.
 */

#include <ast/visitor.hh>
#include <ast/op-exp.hh>

namespace ast
{

  OpExp::OpExp(const Location& location, Exp* left, OpExp::Oper oper,
               Exp* right)
    : Exp(location)
    , left_(left)
    , oper_(oper)
    , right_(right)
  {}

  OpExp::~OpExp()
  {
    delete left_;
    delete right_;
  }

  void
  OpExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  OpExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast

std::string
str(ast::OpExp::Oper oper);
{
  switch (oper)
  {
    case add:
      return "+";
    case sub:
      return "-";
    case mul:
      return "*";
    case div:
      return "/";
    case eq:
      return "=";
    case ne:
      return "<>";
    case lt:
      return "<";
    case le:
      return "<=";
    case gt:
      return ">";
    case ge:
      return ">=";
  }
}
