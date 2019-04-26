/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{

    void
    EscapesVisitor::operator()(ast::SimpleVar& e)
    {
        super_type::operator()(e);
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
    EscapesVisitor::operator()(ast::CastVar& e)
    {
        super_type::operator()(e);
    }

    void
    EscapesVisitor::operator()(ast::NilExp&)
    {
    }
    void
    EscapesVisitor::operator()(ast::IntExp&)
    {
    }
    void
    EscapesVisitor::operator()(ast::StringExp&)
    {
    }

    void
    EscapesVisitor::operator()(ast::CallExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::OpExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::RecordExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::SeqExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::AssignExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::IfExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::WhileExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::ForExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::LetExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::ArrayExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::CastExp& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::BreakExp&)
    {
    }

    void
    EscapesVisitor::operator()(ast::FunctionDecs& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::FunctionDec&)
    {
    }
    void
    EscapesVisitor::operator()(ast::TypeDecs& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::TypeDec&)
    {
    }
    void
    EscapesVisitor::operator()(ast::VarDec& e)
    {
        super_type::operator()(e);
    }


    void
    EscapesVisitor::operator()(ast::NameTy& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::RecordTy& e)
    {
        super_type::operator()(e);
    }
    void
    EscapesVisitor::operator()(ast::ArrayTy& e)
    {
        super_type::operator()(e);
    }

} // namespace escapes
