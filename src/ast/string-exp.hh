/**
 ** \file ast/string-exp.hh
 ** \brief Declaration of ast::StringExp.
 */

#pragma once

#include <ast/exp.hh>
#include <string>

namespace ast
{

  /// StringExp.
  class StringExp : public Exp
  {

  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a StringExp node.
    StringExp(const Location& location, std::string s);
    StringExp(const StringExp&) = delete;
    StringExp& operator=(const StringExp&) = delete;
    /// Destroy a StringExp node.
    virtual ~StringExp();
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
    /// Return value of the string.
    std::string value_get() const;
    /** \} */

  protected:
    /// Value of the string.
    std::string s_;
  };

} // namespace ast

#include <ast/string-exp.hxx>

