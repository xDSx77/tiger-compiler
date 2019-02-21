                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.value.type variant
%define api.token.constructor
%expect 2
%skeleton "glr.cc"
%glr-parser
%define parse.error verbose
%defines
%debug
// Prefix all the tokens with TOK_ to avoid colisions.
%define api.token.prefix {TOK_}

/* We use pointers to store the filename in the locations.  This saves
   space (pointers), time (no deep copy), but leaves the problem of
   deallocation.  This would be a perfect job for a misc::symbol
   object (passed by reference), however Bison locations require the
   filename to be passed as a pointer, thus forcing us to handle the
   allocation and deallocation of this object.

   Nevertheless, all is not lost: we can still use a misc::symbol
   object to allocate a flyweight (constant) string in the pool of
   symbols, extract it from the misc::symbol object, and use it to
   initialize the location.  The allocated data will be freed at the
   end of the program (see the documentation of misc::symbol and
   misc::unique).  */
%define filename_type {const std::string}
%locations

// The parsing context.
%param { ::parse::TigerParser& tp }

/*---------------------.
| Support for tokens.  |
`---------------------*/
%code requires
{
#include <string>
#include <misc/algorithm.hh>
#include <misc/separator.hh>
#include <misc/symbol.hh>
#include <parse/fwd.hh>

  // Pre-declare parse::parse to allow a ``reentrant'' parsing within
  // the parser.
  namespace parse
  {
    ast_type parse(Tweast& input);
  }
}

%code provides
{
  // Announce to Flex the prototype we want for lexing (member) function.
  # define YY_DECL_(Prefix)                               \
    ::parse::parser::symbol_type                          \
    (Prefix parselex)(::parse::TigerParser& tp)
  # define YY_DECL YY_DECL_(yyFlexLexer::)
}

%printer { yyo << $$; } <int> <std::string> <misc::symbol>;

%token <std::string>    STRING "string"
%token <misc::symbol>   ID     "identifier"
%token <int>            INT    "integer"

/*--------------------------------.
| Support for the non-terminals.  |
`--------------------------------*/

%code requires
{
# include <ast/fwd.hh>
// Provide the declarations of the following classes for the
// %destructor clauses below to work properly.
# include <ast/exp.hh>
# include <ast/var.hh>
# include <ast/ty.hh>
# include <ast/name-ty.hh>
# include <ast/field.hh>
# include <ast/field-init.hh>
# include <ast/function-dec.hh>
# include <ast/type-dec.hh>
# include <ast/var-dec.hh>
# include <ast/any-decs.hh>
# include <ast/decs-list.hh>
}

%destructor { delete $$; } <ast::Decs*>
                           <ast::DecsList*>
                           <ast::exps_type*>
                           <ast::Exp*>
                           /*<ast::fieldinits_type>*/
                           <ast::FieldVar*>
                           <ast::Ty*>
                           <ast::NameTy*>
                           <ast::RecordTy*>
                           <ast::VarDecs*>
                           <ast::SubscriptVar*>
                           <ast::VarDec*>
                           <ast::Var*>

/*-----------------------------------------.
| Code output in the implementation file.  |
`-----------------------------------------*/

%code
{
# include <parse/tiger-parser.hh>
# include <parse/scantiger.hh>
# include <parse/tweast.hh>
# include <misc/separator.hh>
# include <misc/symbol.hh>
# include <ast/all.hh>
# include <ast/libast.hh>

  namespace
  {

    /// Get the metavar from the specified map.
    template <typename T>
    T*
    metavar(parse::TigerParser& tp, unsigned key)
    {
      parse::Tweast* input = tp.input_;
      return input->template take<T>(key);
    }

  }

  /// Use our local scanner object.
  inline
  ::parse::parser::symbol_type
  parselex(parse::TigerParser& tp)
  {
    return tp.scanner_->parselex(tp);
  }
}

// Definition of the tokens, and their pretty-printing.
%token AND          "&"
       ARRAY        "array"
       ASSIGN       ":="
       BREAK        "break"
       CAST         "_cast"
       CLASS        "class"
       COLON        ":"
       COMMA        ","
       DIVIDE       "/"
       DO           "do"
       DOT          "."
       ELSE         "else"
       END          "end"
       EQ           "="
       EXP          "_exp"
       EXTENDS      "extends"
       FOR          "for"
       FUNCTION     "function"
       GE           ">="
       GT           ">"
       IF           "if"
       IMPORT       "import"
       IN           "in"
       LBRACE       "{"
       LBRACK       "["
       LE           "<="
       LET          "let"
       LPAREN       "("
       LT           "<"
       LVALUE       "_lvalue"
       MINUS        "-"
       METHOD       "method"
       NAMETY       "_namety"
       NE           "<>"
       NEW          "new"
       NIL          "nil"
       OF           "of"
       OR           "|"
       PLUS         "+"
       PRIMITIVE    "primitive"
       RBRACE       "}"
       RBRACK       "]"
       RPAREN       ")"
       SEMI         ";"
       THEN         "then"
       TIMES        "*"
       TO           "to"
       TYPE         "type"
       VAR          "var"
       WHILE        "while"
       EOF 0        "end of file"

%type <ast::Decs*> dec
%type <ast::DecsList*> decs
%type <ast::SeqExp*> exps
%type <ast::Exp*> exp
%type <ast::fieldinits_type> id_exp
%type <ast::exps_type*> exp2
%type <ast::SeqExp*> exp3
%type <ast::Decs*> classfield
%type <ast::DecsList*> classfields
%type <ast::FieldVar*> lvalue_c
%type <ast::Ty*> ty
%type <ast::NameTy*> type-id
%type <ast::RecordTy*> tyfield
%type <ast::RecordTy*> tyfields
%type <ast::VarDecs*> tyfield_decs
%type <ast::VarDecs*> tyfields_decs
%type <ast::SubscriptVar*> lvalue_b
%type <ast::VarDec*> vardec
%type <ast::Var*> lvalue

%left AND
%left OR
%left GE LE EQ GT LT NE
%left PLUS MINUS
%left TIMES DIVIDE
%left ASSIGN
%nonassoc DOT
%nonassoc THEN
%nonassoc ELSE
%nonassoc OF
%nonassoc DO

%start program

%%
program:
  /* Parsing a source program.  */
  exp
    { tp.ast_ = $1; }
| /* Parsing an imported file.  */
  decs
    { tp.ast_ = $1; }

id_exp:
  %empty
    {
      ast::fieldinits_type empty;
      $$ = empty;
    }
| ID EQ exp
    {
      ast::fieldinits_type fields;
      ast::FieldInit* field = new ast::FieldInit(@1, $1, $3);
      fields.emplace_back(field);
      $$ = fields;
    }
| ID EQ exp COMMA id_exp
    {
      ast::FieldInit* field = new ast::FieldInit(@1, $1, $3);
      $5.insert($5.begin(), field);
      $$ = $5;
    }

exp2:
  %empty
    {
      ast::exps_type* empty = new ast::exps_type();
      $$ = empty;
    }
| exp
    {
      ast::exps_type* exps = new ast::exps_type();
      exps->emplace_back($1);
      $$ = exps;
    }
| exp COMMA exp2
    {
      $3->insert($3->begin(), $1);
      $$ = $3;
    }

exp:
  INT
    { $$ = new ast::IntExp(@$, $1); }
| NIL
    { $$ = new ast::NilExp(@$); }
| STRING
    { $$ = new ast::StringExp(@$, $1); }
| type-id LBRACK exp RBRACK OF exp
    { $$ = new ast::ArrayExp(@$, $1, $3, $6); }
| type-id LBRACE id_exp RBRACE
    { $$ = new ast::RecordExp(@$, $1, $3); }
| NEW type-id
    { $$ = new ast::ObjectExp(@$, $2); }
| lvalue
    { $$ = $1; }
| ID LPAREN exp2 RPAREN
    { $$ = new ast::CallExp(@$, $1, $3); }
| lvalue_c LPAREN exp2 RPAREN
    { $$ = new ast::MethodCallExp(@$, $1->name_get(), $3, $1); }
| MINUS exp
    { $$ = new ast::OpExp(@$, nullptr, ast::OpExp::Oper::sub, $2); }
| exp MINUS exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
| exp PLUS exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
| exp AND exp
    {
      $$ = new ast::IfExp(@$, $1, new ast::IfExp(@3, $3,
      new ast::StringExp(@3, "true"), nullptr), new ast::StringExp(@3, "false"));
    }
| exp LE exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::le, $3); }
| exp GE exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ge, $3); }
| exp GT exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::gt, $3); }
| exp LT exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::lt, $3); }
| exp NE exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::ne, $3); }
| exp EQ exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::eq, $3); }
| exp DIVIDE exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::div, $3); }
| exp TIMES exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::mul, $3); }
| exp OR exp
    {
      $$ = new ast::IfExp(@$, $1, new ast::StringExp(@1, "true"),
        new ast::IfExp(@3, $3, new ast::StringExp(@3, "true"),
          new ast::StringExp(@3, "false")));
    }
| LPAREN exps RPAREN
    { $$ = $2; }
| LPAREN error RPAREN
    { $$ = nullptr; }
| lvalue ASSIGN exp
    { $$ = new ast::AssignExp(@$, $1, $3); }
| IF exp THEN exp
    { $$ = new ast::IfExp(@$, $2, $4, nullptr);  }
| IF exp THEN exp ELSE exp
    { $$ = new ast::IfExp(@$, $2 ,$4, $6); }
| WHILE exp DO exp
    { $$ = new ast::WhileExp(@$, $2, $4); }
| FOR ID ASSIGN exp TO exp DO exp
    { $$ = new ast::ForExp(@$, new ast::VarDec(@2, $2, nullptr, $4), $6, $8); }
| BREAK
    { $$ = new ast::BreakExp(@$); }
| LET decs IN exps END
    { $$ = new ast::LetExp(@$, $2, $4); }
| CAST LPAREN exp COMMA ty RPAREN
    { $$ = new ast::CastExp(@$, $3, $5); }
| EXP LPAREN INT RPAREN
    { $$ = metavar<ast::Exp>(tp, $3); }

lvalue:
  ID
    { $$ = new ast::SimpleVar(@$, $1); }
| lvalue_b
    { $$ = $1; }
| lvalue_c
    { $$ = $1; }
| CAST LPAREN lvalue COMMA ty RPAREN
    { $$ = new ast::CastVar(@$, $3, $5); }
| LVALUE LPAREN INT RPAREN
    { $$ = metavar<ast::Var>(tp, $3); }

lvalue_b:
  ID LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, new ast::SimpleVar(@1, $1), $3); }
| lvalue_b LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, $1, $3); }
| lvalue_c LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, $1, $3); }
| lvalue_b LBRACK error RBRACK
    {$$ = new ast::SubscriptVar(@$, $1, nullptr);}
| lvalue_c LBRACK error RBRACK
    {$$ = new ast::SubscriptVar(@$, $1, nullptr);}


lvalue_c:
  ID DOT ID
    { $$ = new ast::FieldVar(@$, $3, new ast::SimpleVar(@1, $1)); }
| lvalue_c DOT ID
    { $$ = new ast::FieldVar(@$, $3, $1); }
| lvalue_b DOT ID
    { $$ = new ast::FieldVar(@$, $3, $1); }
| error DOT ID
    {$$ = new ast::FieldVar(@$, $3, nullptr); }

exp3:
  exp
    {
      ast::exps_type* exps = new ast::exps_type();
      exps->emplace_back($1);
      ast::SeqExp* exp = new ast::SeqExp(@$, exps);
      $$ = exp;
    }
| exp SEMI exp3
    {
      $3->exps_get().insert($3->exps_get().begin(), $1);
      $$ = $3;
    }

exps:
  %empty
    {
      ast::SeqExp* empty = new ast::SeqExp(@$, new ast::exps_type());
      $$ = empty;
    }
| exp3
    { $$ = $1; }

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";

decs:
  %empty
    { $$ = new ast::DecsList(@$); }
| DECS LPAREN INT RPAREN decs
    {
      $5->splice_front(*(metavar<ast::DecsList>(tp, $3)));
      $$ = $5;
    }
| dec decs
    {
      $2->push_front($1);
      $$ = $2;
    }

dec:
  TYPE ID EQ ty
    {
      ast::TypeDecs* typedecs = new ast::TypeDecs(@$);
      ast::TypeDec* typedec = new ast::TypeDec(@$, $ID, $4);
      typedecs->push_front(*typedec);
      $$ = typedecs;
    }
| CLASS ID LBRACE classfields RBRACE
    {
      ast::TypeDecs* typedecs = new ast::TypeDecs(@$);
      ast::TypeDec* typedec = new ast::TypeDec(@$, $2, new ast::ClassTy(@$, nullptr, $4));
      typedecs->push_front(*typedec);
      $$ = typedecs;
    }
| CLASS ID EXTENDS type-id LBRACE classfields RBRACE
    {
      ast::TypeDecs* typedecs = new ast::TypeDecs(@$);
      ast::TypeDec* typedec = new ast::TypeDec(@$, $2, new ast::ClassTy(@$, $4, $6));
      typedecs->push_front(*typedec);
      $$ = typedecs;
    }
| vardec
    {
      ast::VarDecs* vardecs = new ast::VarDecs(@$);
      vardecs->push_front(*$1);
      $$ = vardecs;
    }
| FUNCTION ID LPAREN tyfield_decs RPAREN EQ exp
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2, $4, nullptr, $7);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| FUNCTION ID LPAREN tyfield_decs RPAREN COLON type-id EQ exp
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2, $4, $7, $9);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| FUNCTION ID LPAREN error RPAREN COLON type-id EQ exp
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2,
      nullptr, $7, $9);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| PRIMITIVE ID LPAREN tyfield_decs RPAREN
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2, $4, nullptr, nullptr);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| PRIMITIVE ID LPAREN tyfield_decs RPAREN COLON type-id
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2, $4, $7, nullptr);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| PRIMITIVE ID LPAREN error RPAREN
    {
      ast::FunctionDecs* functiondecs = new ast::FunctionDecs(@$);
      ast::FunctionDec* functiondec = new ast::FunctionDec(@$, $2, nullptr, nullptr, nullptr);
      functiondecs->push_front(*functiondec);
      $$ = functiondecs;
    }
| IMPORT STRING
    {
      ast::DecsList* decs = tp.parse_import($2, @$);
      $$ = decs->decs_get().front();
      if (!$$)
      {
        decs = new ast::DecsList(@$);
        $$ = decs->decs_get().front();
      }
    }

tyfields_decs:
  %empty
    {
      ast::VarDecs* empty = new ast::VarDecs(@$);
      $$ = empty;
    }
| COMMA ID COLON type-id tyfields_decs
    {
      ast::VarDec* vardec = new ast::VarDec(@$, $2, $4, nullptr);
      $5->push_front(*vardec);
      $$ = $5;
    }

tyfield_decs:
  %empty
    {
      ast::VarDecs* empty = new ast::VarDecs(@$);
      $$ = empty;
    }
| ID COLON type-id tyfields_decs
    {
      ast::VarDec* vardec = new ast::VarDec(@$, $1, $3, nullptr);
      $4->push_front(*vardec);
      $$ = $4;
    }

vardec:
  VAR ID ASSIGN exp
    { $$ = new ast::VarDec(@$, $ID, nullptr, $4); }
| VAR ID COLON type-id ASSIGN exp
    { $$ = new ast::VarDec(@$, $2, $4, $6); }

classfields:
  %empty
    { $$ = new ast::DecsList(@$); }
| classfield classfields
    {
      $2->push_front($1);
      $$ = $2;
    }

classfield:
  vardec
    {
      ast::VarDecs* vardecs = new ast::VarDecs(@$);
      vardecs->push_front(*$1);
      $$ = vardecs;
    }
| METHOD ID LPAREN tyfield_decs RPAREN EQ exp
    {
      ast::MethodDecs* methoddecs = new ast::MethodDecs(@$);
      ast::MethodDec* methoddec = new ast::MethodDec(@$, $2, $4, nullptr, $7);
      methoddecs->push_front(*methoddec);
      $$ = methoddecs;
    }
| METHOD ID LPAREN tyfield_decs RPAREN COLON type-id EQ exp
    {
      ast::MethodDecs* methoddecs = new ast::MethodDecs(@$);
      ast::MethodDec* methoddec = new ast::MethodDec(@$, $2, $4, $7, $9);
      methoddecs->push_front(*methoddec);
      $$ = methoddecs;
    }
| METHOD ID LPAREN error RPAREN EQ exp
    {
      ast::MethodDecs* methoddecs = new ast::MethodDecs(@$);
      ast::MethodDec* methoddec = new ast::MethodDec(@$, $2,nullptr ,
      nullptr, $7);
      methoddecs->push_front(*methoddec);
      $$ = methoddecs;
    }

ty:
  type-id
    { $$ = $1; }
| LBRACE tyfield RBRACE
    { $$ = $2; }
| ARRAY OF type-id
    { $$ = new ast::ArrayTy(@$, $3); }
| CLASS LBRACE classfields RBRACE
    { $$ = new ast::ClassTy(@$, nullptr, $3); }
| CLASS EXTENDS type-id LBRACE classfields RBRACE
    { $$ = new ast::ClassTy(@$, $3, $5); }

tyfields:
  %empty
    {
      ast::fields_type fields;
      ast::RecordTy* empty = new ast::RecordTy(@$, fields);
      $$ = empty;
    }
| COMMA ID COLON type-id tyfields
    {
      ast::fields_type fields;
      ast::Field* field =  new ast::Field(@1, $2, $4);
      fields.insert(fields.begin(), field);
      ast::RecordTy* record = new ast::RecordTy(@$, fields);
      $5->fields_get().insert($5->fields_get().end(), record->fields_get().begin(),
          record->fields_get().end());
      $$ = $5;
    }

tyfield:
  %empty
    {
      ast::fields_type fields;
      ast::RecordTy* empty = new ast::RecordTy(@$, fields);
      $$ = empty;
    }
| ID COLON type-id tyfields
    {
      ast::fields_type fields;
      ast::Field* field = new ast::Field(@1, $1, $3);
      fields.insert(fields.begin(), field);
      ast::RecordTy* record = new ast::RecordTy(@$, fields);
      $4->fields_get().insert($4->fields_get().end(), record->fields_get().begin(),
          record->fields_get().end());
      $$ = $4;
    }

type-id:
  ID
    { $$ = new ast::NameTy(@$, $ID); }
| NAMETY LPAREN INT RPAREN
    { $$ = metavar<ast::NameTy>(tp, $3); }

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  tp.error_ << misc::error::error_type::parse
            << l << ": " << m << std::endl;
}
