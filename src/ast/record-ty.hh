/**
 ** \file ast/record-ty.hh
 ** \brief Declaration of ast::RecordTy.
 */

#pragma once

#include <ast/field.hh>
#include <ast/ty.hh>

namespace ast
{

  /// RecordTy.
  class RecordTy : public Ty
  {
      /** \class ast::CastExp
   ** \brief Cast the type of an expression to a given type.
   **
   ** This node is only used in the bounds checking transformation
   ** (see desugar::bounds_checks_add).  You don't need to worry
   ** about it (nor about the `cast' keyword) if you don't implement
   ** this option.
   */
    RecordTy(const Location& location, Field* fld, Ty* ty);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;
    /// Destroy a CastExp node.
    virtual ~RecordTy();
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
    /// Return field.
    const Field& field_get() const;
    /// Return field.
    Field& field_get();
    /** \} */
    /// Return the target type.
    const Ty& ty_get() const;
    /// Return the target type.
    Ty& ty_get();
    /** \} */

  protected:
    /// Field.
    Field* fld_;
    /// The target type.
    Ty* ty_;
  };

} // namespace ast

#include <ast/record-ty.hxx>

