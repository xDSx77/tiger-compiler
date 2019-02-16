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

  //Elias moved that way
  void
  PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get() << '(';
    for (size_t i = 0; i < e.exps_get().size(); i++)
    {
        ostr_ << e.exps_get()[i];
    }
    ostr_ << ')';
  }

  //Elias moved that way
  void
  PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << e.left_get() << ' ' << << e.right_get();
  }

  void
  PrettyPrinter::operator()(const RecordExp& e)
  {
    for (unsigned i = 0; i < e.fieldinits_get().size(); i++)
    {
        ostr_ << e.fieldinits_get()[i];
    }
  }

  void
  PrettyPrinter::operator()(const SeqExp& e)
  {
      for (unsigned i = 0; i < e.exps_get().size(); ++i)
      {
        ostr_ << e.exps_get()[i];
      }
  }

  void
  PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << e.exp_get();
  }

  void
  PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << e.test_get() << e.body_get() << e.body_2_get();
  }

  void
  PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << e.test_get() << e.body_get();
  }

  void
  PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << e.vardec_get() << e.hi_get() << e.body_get();
  }

  void
  PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << e.decs_get();
    for (unsigned j = 0; j < e.exps_get().size(); j++)
      ostr_ << e.exps_get()[j];
  }

  void
  PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.type_get();
  }

  void
  PrettyPrinter::operator()(const FieldInit& e)
  {
      ostr_ << e.init_get();
  }

  /*
  void
  PrettyPrinter::operator()(const DecsList& e)
  {
    ostr_ << e.decs_get();
  }

  void
  PrettyPrinter::operator()(const Dec& e)
  {
      ostr_ << e.name_get();
  }
  */

  void
  PrettyPrinter::operator()(const VarDec& e)
  {
      ostr_ << e.type_name_get();
  }

  void
  PrettyPrinter::operator()(const FunctionDec& e)
  {
    ostr_ << e.body_get() << e.formals_get();
  }

  void
  PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << e.ty_get();
  }

  void
  PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get() << e.def_get();
  }

  void
  PrettyPrinter::operator()(const RecordTy& e)
  {
      ostr_ << e.ty_get() << e.field_get();
  }

  void
  PrettyPrinter::operator()(const ArrayTy& e)
  {
      ostr_ << e.base_type_get();
  }

  void
  PrettyPrinter::operator()(const Field& e)
  {
      ostr_ << e.type_name_get();
  }

} // namespace ast
