/**
 ** \file escapes/escapes-visitor.hh
 ** \brief Compute the escapes.
 **
 ** Variables and formals of a function may escape, i.e., be accessed
 ** by an inner function.
 **
 ** When the semantic analysis finds a declaration of variable or
 ** formal FOO, it needs to know whether it escapes or not.  This
 ** requires an additional pass, before the semantic analysis, just to
 ** spot the potential escapes of FOO.
 **
 ** In order to pass the result to the semantic analysis which walks
 ** across the ast, the most natural and easy solution consists in
 ** tagging the various VarDec and Field.
 **
 ** Now, how shall we compute the escapes?
 ** The answer is obvious: we need to walk the ast, searching for variables
 ** declared then accessed by an inner function.
 */

#pragma once

#include <map>

#include <ast/default-visitor.hh>
#include <ast/non-object-visitor.hh>

namespace escapes
{

  /** \brief Compute the escapes.
   **
   ** The EscapeVisitor is extremely similar to type::TypeChecker:
   ** in its course of operation it must relate uses to
   ** definitions.  Therefore it will be run after the bind::Binder.
   ** It also needs auxiliary information about the definitions (their
   ** depth): a simple map suffices, since scoping issues were handled
   ** by the bind::Binder.
   **
   ** Note that this EscapesVisitor is mainly doing nothing: it is just
   ** interested in declaration and uses of variables/formals (and, of
   ** course, function declaration...).  It would be somewhat stupid to
   ** write all the methods that `do nothing but walk'.  This is why we
   ** will inherit from the non const ast::DefaultVisitor.
   **/
  class EscapesVisitor
    : public ast::DefaultVisitor
    , public ast::NonObjectVisitor
  {
  public:
    /// Super class type.
    using super_type = ast::DefaultVisitor;
    /// Import all the overloaded visit methods.
    using super_type::operator();

    void operator()(ast::SimpleVar& e) override;
    void operator()(ast::FieldVar& e) override;
    void operator()(ast::SubscriptVar& e) override;
    void operator()(ast::CastVar& e) override;

    void operator()(ast::NilExp&) override;
    void operator()(ast::IntExp&) override;
    void operator()(ast::StringExp&) override;

    void operator()(ast::CallExp& e) override;
    void operator()(ast::OpExp& e) override;
    void operator()(ast::RecordExp& e) override;
    void operator()(ast::SeqExp& e) override;
    void operator()(ast::AssignExp& e) override;
    void operator()(ast::IfExp& e) override;
    void operator()(ast::WhileExp& e) override;
    void operator()(ast::ForExp& e) override;
    void operator()(ast::LetExp& e) override;
    void operator()(ast::ArrayExp& e) override;
    void operator()(ast::CastExp& e) override;
    void operator()(ast::BreakExp&) override;

    void operator()(ast::FunctionDecs& e) override;
    void operator()(ast::FunctionDec&) override;
    void operator()(ast::TypeDecs& e) override;
    void operator()(ast::TypeDec&) override;
    void operator()(ast::VarDec& e) override; 

    void operator()(ast::NameTy& e) override;
    void operator()(ast::RecordTy& e) override;
    void operator()(ast::ArrayTy& e) override;

  protected:

    std::map<misc::symbol, ast::TypeDec*> map_type_;
    std::map<misc::symbol, ast::FunctionDec*> map_func_;
    std::map<misc::symbol, ast::VarDec*> map_var_;

  };

} // namespace escapes
