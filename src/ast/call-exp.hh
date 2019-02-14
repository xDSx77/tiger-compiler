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
    CallExp(const Location& location, Exp* body, FunctionDec* dec,
        const misc::symbol& name);
    CallExp(const CallExp&) = delete;
    CallExp& operator=(const CallExp&) = delete;

    virtual ~CallExp();
    void accept(ConstVisitor& v) const override;
    void accept(Visitor& v) override;

    const FunctionDec& dec_get() const;
    FunctionDec& dec_get();

    const Exp& body_get() const;
    Exp& body_get();
    void body_set(Exp* body);

    const misc::symbol& name_get() const;
    misc::symbol& name_get();
    void name_set(const misc::symbol& name);

  protected:
    Exp* body_;
    FunctionDec* dec_;
    misc::symbol name_;
  };
} // namespace ast

#include <ast/call-exp.hxx>

