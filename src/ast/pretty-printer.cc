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

#include <type/class.hh>

namespace ast
{

  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline
    std::ostream&
    operator<<(std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr) && e.escape_get())
        ostr << "/* escaping */ ";
      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline
    std::ostream&
    operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
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
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void
  PrettyPrinter::operator()(const FieldVar& e)
  {
    ostr_ << e.var_get() << '.' << e.name_get();
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

  void
  PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
    ostr_ << "(" << misc::separate(e.exps_get(), ',') << ')';
  }

  void
  PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << '(' << e.left_get() << ' ';
    if (e.oper_get() == ast::OpExp::Oper::add)
        ostr_ << '+';
    else if (e.oper_get() == ast::OpExp::Oper::sub)
        ostr_ << '-';
    else if (e.oper_get() == ast::OpExp::Oper::mul)
        ostr_ << '*';
    else if (e.oper_get() == ast::OpExp::Oper::div)
        ostr_ << '/';
    else if (e.oper_get() == ast::OpExp::Oper::eq)
        ostr_ << '=';
    else if (e.oper_get() == ast::OpExp::Oper::ne)
        ostr_ << "<>";
    else if (e.oper_get() == ast::OpExp::Oper::lt)
        ostr_ << '<';
    else if (e.oper_get() == ast::OpExp::Oper::le)
        ostr_ << "<=";
    else if (e.oper_get() == ast::OpExp::Oper::gt)
        ostr_ << '>';
    else if (e.oper_get() == ast::OpExp::Oper::ge)
        ostr_ << ">=";
    ostr_ << ' ' << e.right_get() << ')';
  }

  void
  PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.name_ty_get() << " { " << misc::separate(e.fieldinits_get(), ", ") << " }";
  }

  void
  PrettyPrinter::operator()(const SeqExp& e)
  {
    ostr_ << '(' << misc::separate(e.exps_get(), "; ") << ')';
  }

  void
  PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get();
  }

  void
  PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "if " << e.test_get() << misc::incendl
          << "then " << e.body_get();
    if (e.body_2_get())
    {
      const ast::Exp* exp2 = e.body_2_get();
      ostr_ << misc::decendl << "else " << *exp2;
    }
    else
      ostr_ << misc::decendl << "else " << "()";
  }

  void
  PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while " << e.test_get() << " do" << misc::incendl << e.body_get()
          << misc::decendl;
  }

  void
  PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for " << e.vardec_get().name_get() << " := " << *(e.vardec_get().init_get())
      << " to " << e.hi_get() << " do" << misc::incendl << e.body_get() << misc::decendl;
  }

  void
  PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incendl << e.decs_get() << misc::decendl << "in"
          << misc::incendl << e.exp_get() << misc::decendl << "end";
  }

  void
  PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.name_ty_get() << " [" << e.size_get() << "] of " << e.value_get();
  }

  void
  PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }


  void
  PrettyPrinter::operator()(const DecsList& e)
  {
    ostr_ << misc::separate(e.decs_get(), misc::iendl);
  }

  void
  PrettyPrinter::operator()(const VarDecs& e)
  {
    ostr_ << misc::separate(e.decs_get(), misc::iendl);
  }

  void
  PrettyPrinter::operator()(const FunctionDecs& e)
  {
    ostr_ << misc::separate(e.decs_get(), misc::iendl);
  }

  void
  PrettyPrinter::operator()(const TypeDecs& e)
  {
    ostr_ << misc::separate(e.decs_get(), misc::iendl);
  }

  void
  PrettyPrinter::operator()(const MethodDecs& e)
  {
    ostr_ << misc::separate(e.decs_get(), misc::iendl);
  }

  void
  PrettyPrinter::operator()(const VarDec& e)
  {
    ostr_ << "var " << static_cast<const ast::Escapable&>(e) << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";
    if (e.type_name_get())
      ostr_ << " : " << *(e.type_name_get());
    if (e.init_get())
      ostr_ << " := " << *(e.init_get());
  }

  void
  PrettyPrinter::operator()(const FunctionDec& e)
  {
    unsigned size = e.formals_get().decs_get().size();
    if (e.body_get())
    {
      ostr_ << "function ";
      ostr_ << static_cast<const ast::Dec&>(e);
      ostr_ << '(';
      if (size > 0)
      {
        for (unsigned i = 0; i < size-1; i++)
        {
          ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[i]));
          ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[i]));
          ostr_ << " : " << *(e.formals_get().decs_get()[i]->type_name_get()) << ", ";
        }
        ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[size-1]));
        ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[size-1]));
        ostr_ << " : " << *(e.formals_get().decs_get()[size-1]->type_name_get());
      }
      ostr_ << ')';
    }
    else
    {
      ostr_ << "primitive ";
      ostr_ << static_cast<const ast::Dec&>(e);
      ostr_ << '(';
      if (size >0)
      {
        for (unsigned i = 0; i < size-1; i++)
        {
          ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[i]));
          ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[i]));
          ostr_ << " : " << *(e.formals_get().decs_get()[i]->type_name_get()) << ", ";
        }
        ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[size-1]));
        ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[size-1]));
        ostr_ << " : " << *(e.formals_get().decs_get()[size-1]->type_name_get());
      }
      ostr_ << ')';
    }
    if (e.result_get())
      ostr_ << " : " << *(e.result_get());
    if (e.body_get())
    {
      ostr_ << " =" << misc::incendl << '(' << misc::incendl << *(e.body_get())
            << misc::decendl << ')' << misc::decindent;
    }
    else
      ostr_ << misc::iendl;
  }

  void
  PrettyPrinter::operator()(const MethodDec& e)
  {
    unsigned size = e.formals_get().decs_get().size();
    ostr_ << "method ";
    ostr_ << static_cast<const ast::Dec&>(e);
    ostr_ << '(';
    if (size > 0)
    {
      for (unsigned i = 0; i < size-1; i++)
      {
        ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[i]));
        ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[i]));
        ostr_ << " : " << *(e.formals_get().decs_get()[i]->type_name_get()) << ", ";
      }
      ostr_ << static_cast<const ast::Escapable&>(*(e.formals_get().decs_get()[size-1]));
      ostr_ << static_cast<const ast::Dec&>(*(e.formals_get().decs_get()[size-1]));
      ostr_ << " : " << *(e.formals_get().decs_get()[size-1]->type_name_get());
    }
    ostr_ << ')';
    if (e.result_get())
      ostr_ << " : " << *(e.result_get());
    ostr_ << " =" << misc::incendl << '(' << misc::incendl << *(e.body_get())
          << misc::decendl << ')' << misc::decindent;
  }

  void
  PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";
    ostr_ << " = " << e.ty_get();
  }

  void
  PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void
  PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << '{' << misc::separate(e.fields_get(), ", ") << '}';
  }

  void
  PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get();
  }

  void
  PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << "class extends " << e.super_get() << misc::iendl
          << '{' << misc::incendl << e.decs_get() << misc::decendl << '}';
  }

  void
  PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void
  PrettyPrinter::operator()(const BreakExp&)
  {
    ostr_ << "break";
  }

  void
  PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.var_get() << '.' << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";
    ostr_ << " (" << misc::separate(e.exps_get(), ", ") << ')' << std::endl;
  }

  void
  PrettyPrinter::operator()(const IntExp& e)
  {
    ostr_ << e.value_get();
  }

  void
  PrettyPrinter::operator()(const NilExp&)
  {
    ostr_ << "nil";
  }

  void
  PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << e.type_get().name_get();
  }

  void
  PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << "\"" << e.value_get() << "\"";
  }

} // namespace ast
