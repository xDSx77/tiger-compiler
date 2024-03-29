/**
 ** \file ast/call-exp.hh
 ** \brief Declaration of ast::CallExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/function-dec.hh>
#include <misc/symbol.hh>

namespace ast
{

  /// CallExp.
  class CallExp : public Exp
  {
  public:
    CallExp(const Location& location, const misc::symbol& name, exps_type* exps);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;

    virtual ~CallExp();
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const misc::symbol& name_get() const;
    misc::symbol& name_get();
    void name_set(const misc::symbol& name);

    const exps_type& exps_get() const;
    exps_type& exps_get();

    /// Return definition site.
    const FunctionDec* def_get() const;
    /// Return definition site.
    FunctionDec* def_get();
    /// Set definition site.
    void def_set(FunctionDec*);
    /** \} */

  protected:
    misc::symbol name_;
    exps_type* exps_;
    FunctionDec* def_ = nullptr;
  };
} // namespace ast

#include <ast/call-exp.hxx>

