/**
 ** \file type/array.hh
 ** \brief The class Array.
 */
#pragma once

#include <type/fwd.hh>
#include <type/type.hh>

namespace type
{

  /// Array types.
  class Array : public Type
  {
    /** \name Ctor & dtor.
     ** \{ */
  public:
    /// Construct an Array type.
    Array(const Type& type);
    /** \} */

    /// \name Visitors entry point.
    /** \{ */
    /// Accept a const visitor \a v.
    void accept(ConstVisitor& v) const override;
    /// Accept a non-const visitor \a v.
    void accept(Visitor& v) override;
    /** \} */

    /** \name Accessors.
     ** \{ */
    /// Return the type contained in the Array.
    const Type& type_get() const;
    /** \} */

    bool compatible_with(const Type& other) const override;

  private:
    /// The type contained in the Array.
    const Type& type_;
  };

} // namespace type

#include <type/array.hxx>
