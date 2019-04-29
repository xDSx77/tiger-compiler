/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{

    EscapesVisitor::EscapesVisitor()
      : scope_depth(0)
    {}

    void
    EscapesVisitor::operator()(ast::SimpleVar& e)
    {
    }
    void
    EscapesVisitor::operator()(ast::FieldVar& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::SubscriptVar& e)
    {
        super_type::operator()(e);
    }

    void
    EscapesVisitor::operator()(ast::FunctionDecs& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::VarDec& e)
    {
      if (map_var_.at(e.name_get()) == scope_depth)
        return;
      map_var_.insert(std::pair<misc::symbol, int>(e.name_get(), scope_depth));
    }

} // namespace escapes
