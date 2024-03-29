/**
 ** \file ast/field-var.hh
 ** \brief Declaration of ast::FieldVar.
 */

#pragma once

#include <ast/var.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// FieldVar.
  class FieldVar : public Var
  {
  public:
    FieldVar(const Location& location, const misc::symbol& name, Var* var);
    FieldVar(const FieldVar&) = delete;
    FieldVar& operator=(const FieldVar&) = delete;
    virtual ~FieldVar();

    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const misc::symbol& name_get() const;
    misc::symbol& name_get();

    void name_set(const misc::symbol&);

    const Var& var_get() const;
    Var& var_get();

  protected:
    misc::symbol name_;
    Var* var_;
  };

} // namespace ast

#include <ast/field-var.hxx>

