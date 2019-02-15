/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>
#include <misc/pair.hh>
#include <ast/all.hh>
#include <ast/pretty-printer.hh>
#include <ast/libast.hh>


namespace ast
{

  // Anonymous namespace: these functions are private to this file.
  namespace
  {

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline
    std::ostream&
    operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      return ostr;
    }
  }



  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}


  void
  PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
  }

  void
  PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.var_get() << e.name_get();
  }

  /* Foo[10]. */
  void
  PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << misc::incindent << e.index_get()
          << misc::decindent << ']';
  }

  void
  PrettyPrinter::operator()(const CastVar& e)
  {
    ostr_ << "_cast(" << e.var_get() << ", " << e.ty_get() << ')';
  }

  void
  PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // faire ca pour toute les fonctions
  void
  PrettyPrinter::operator()(const CallExp e)
  {
      ostr_ << e.body_get() << e.dec_get();
  }

  void
  PrettyPrinter::operator()(const 0pExp e)
  {
      ostr_ << e.left_get() << e.right_get();
  }


  void
  PrettyPrinter::operator()(const RecordExp e)
  {
      ostr_ << e.field_get() << e.right_get();
  }

  void
  PrettyPrinter::operator()(const SeqExp e)
  {
      ostr_ << e.exp_get();
  }

  void
  PrettyPrinter::operator()(const IfExp e)
  {
      ostr_ << e.test_get() << e.body_get() << e.body_2_get();
  }

  void
  PrettyPrinter::operator()(const WhileExp e)
  {
    ostr_ << e.test_get() << e.body_get();
  }

  void
  PrettyPrinter::operator()(const ForExp e)
  {
      ostr_ << e.vardec_get() << e.hi_get() << e.body_get();
  }

  void
  PrettyPrinter::operator()(const LetExp e)
  {
      ostr_ << e.decs_get() << e.body_get();
  }

  void
  PrettyPrinter::operator()(const ArrayExp e)
  {
    ostr_ << e.exp_get() << e.type_get();
  }

  void
  PrettyPrinter::operator()(const CastExp e)
  {
    ostr_ <<  e.exp_get() << e.ty_get();
  }

  void
  PrettyPrinter::operator()(const FieldInit e)
  {
      ostr_ << e.init_get();
  }

  void
  PrettyPrinter::operator()(const DecsList e)
  {
  }

  void
  PrettyPrinter::operator()(const Decs e)
  {
  }

  void
  PrettyPrinter::operator()(const VarDecs e)
  {
  }

  void
  PrettyPrinter::operator()(const FunctionDecs e)
  {
  }

  void
  PrettyPrinter::operator()(const TypeDec e)

  void
  PrettyPrinter::operator()(const TypeDecs e)

  void
  PrettyPrinter::operator()(const NameTy e)
  {
  }

  void
  PrettyPrinter::operator()(const RecordTy e)
  {
  }

  void
  PrettyPrinter::operator()(const ArrayTy e)
  {
      ostr_ << e.base_type_get();
  }
  void
  PrettyPrinter::operator()(const Field e)
  {
      ostr_ << e.type_name_get();
  }

} // namespace ast
