/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{

  /// IfExp.
  class IfExp : public Exp
  {
      public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct an IfExp node.
    IfExp(const Location& location, Exp* if);
    IfExp(const IfExp&) = delete;
    IfExp& operator=(const IfExp&) = delete;
    /// Destroy an IfExp node.
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return stored integer value.
    int if_get() const;
    /** \} */

  protected:
    /// Stored if.
    int if_;
  };

} // namespace ast

#include <ast/if-exp.hxx>

