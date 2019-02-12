/**
 ** \file ast/string-exp.cc
 ** \brief Implementation of ast::StringExp.
 */

#include <ast/visitor.hh>
#include <ast/string-exp.hh>

namespace ast
{

  StringExp::StringExp(const Location& location, std::string s)
    : Exp(location)
    , s_(s)
  {}

  StringExp::~StringExp()
  {}

  void
  StringExp::accept(ConstVisitor& v) const
  {
    v(*this);
  }

  void
  StringExp::accept(Visitor& v)
  {
    v(*this);
  }

} // namespace ast
