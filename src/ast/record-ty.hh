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
    public:
    /** \name Ctor & dtor
     ** \{ */
    RecordTy(const Location& location, fields_type& fields);
    RecordTy(const RecordTy&) = delete;
    RecordTy& operator=(const RecordTy&) = delete;
    /// Destroy a RecordTy node.
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
    /// Return fields.
    const fields_type& fields_get() const;
    /// Return field.
    fields_type& fields_get();
    /** \} */

  protected:
    /// The field of the record.
    fields_type fields_;
  };

} // namespace ast

#include <ast/record-ty.hxx>

