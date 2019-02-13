/**
 ** \file ast/if-exp.hh
 ** \brief Declaration of ast::IfExp.
 */

#pragma once

#include <ast/exp.hh>
#include <ast/seq-exp.hh>

namespace ast
{
    /// WhileExp.
    class IfExp : public Exp
    {
    public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a WhileExp node.
      IfExp(const Location& location, Exp* test, Exp* body, Exp* body_2);
      IfExp(const IfExp&) = delete;
      IfExp& operator=(const IfExp&) = delete;
      /// Destroy a WhileExp node.
      virtual ~IfExp();
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
      /// Return exit condition of the loop.
      const Exp& test_get() const;
      /// Return exit condition of the loop.
      Exp& test_get();
      /// Return instructions executed in the loop.
      const Exp& body_get() const;
      /// Return instructions executed in the loop.
      Exp& body_get();
      /// Return instructions executed in the loop.
      const Exp& body_2_get() const;
      /// Return instructions executed in the loop.
      Exp& body_2_get();

      /** \} */

  protected:
    /// Exit condition of the loop.
    Exp* test_;
    /// Instructions executed in the loop.
    Exp* body_;
    /// Instructions executed in the else.
    Exp* body_2_;
  };
} // namespace ast

#include <ast/if-exp.hxx>

