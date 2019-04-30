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
      : scope_depth_(0)
    {}

    void
    EscapesVisitor::operator()(ast::SimpleVar& e)
    {
      try
      {
        if (scope_depth_ == map_var_.at(e.name_get()))
          e.def_get()->escape_set(false);
      }
      catch (const std::exception& x)
      {
        return;
      }
    }
    void
    EscapesVisitor::operator()(ast::FieldVar& e)
    {
      e.var_get().accept(*this);
    }
    void
    EscapesVisitor::operator()(ast::SubscriptVar& e)
    {
      e.var_get().accept(*this);
    }
    void
    EscapesVisitor::operator()(ast::CastVar& e)
    {
      e.var_get().accept(*this);
    }

    void
    EscapesVisitor::operator()(ast::FunctionDec& e)
    {
      scope_depth_++;
      for (ast::Dec* vardec : e.formals_get().decs_get())
        vardec->accept(*this);
      e.body_get()->accept(*this);
      scope_depth_--;
    }
    void
    EscapesVisitor::operator()(ast::VarDec& e)
    {
      e.escape_set(true);
      try
      {
        if (map_var_.at(e.name_get()) == scope_depth_)
          return;
      }
      catch (const std::exception& x)
      {
        map_var_.insert(std::pair<misc::symbol, int>(e.name_get(), scope_depth_));
      }
    }

} // namespace escapes
