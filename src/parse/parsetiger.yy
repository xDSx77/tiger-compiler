                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.value.type variant
%define api.token.constructor
%expect 0
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

%destructor { delete $$; } exp
  // FIXME: Some code was deleted here (Printers and destructors).

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
       MINUS        "-"
       METHOD       "method"
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

%type <ast::Dec*> dec
%type <ast::DecsList*> decs
%type <ast::exps_type> exps
%type <ast::Exp*> exp
%type <ast::fieldinits_type> id_exp
%type <ast::exps_type> exp2
%type <ast::exps_type> exp3
%type <ast::Field*> classfield
%type <ast::FieldInit*> classfields
%type <ast::FieldVar*> lvalue_c
%type <ast::Ty*> ty
%type <ast::RecordTy*> tyfields
%type <ast::RecordTy*> id_comma
%type <ast::SubscriptVar*> lvalue_b
%type <ast::VarDec*> vardec
%type <ast::Var*> lvalue




%left ID
%left OR
%left AND
%left GE LE EQ GT LT NE
%left PLUS MINUS
%left TIMES DIVIDE
%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%left ASSIGN
%left DOT
%right ELSE THEN
%right OF
%right DO

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
      ast::fieldinits_type fields;
      ast::FieldInit* field = new ast::FieldInit(@1, $1, $3);
      fields.emplace_back(field);
      fields.insert(fields.end(), $$.begin(), $$.end());
      $$ = fields;
    }

exp2:
  %empty
    /*{ $$ = ""; }*/
| exp
    /*{ $$ = $1; }*/
| exp COMMA exp2
    /*{ $$ = $1 "," $3; }*/

exp:
  INT
    { $$ = new ast::IntExp(@$, $1); }
| NIL
    { $$ = new ast::NilExp(@$); }
| STRING
    { $$ = new ast::StringExp(@$, $1); }
| ID LBRACK exp RBRACK OF exp
    { $$ = new ast::ArrayExp(@$, new ast::NameTy(@1, $ID), $3, $6); }
| ID LBRACE id_exp RBRACE
    { $$ = new ast::RecordExp(@$, new ast::NameTy(@1, $ID), $3); }
| NEW ID
    /*{ $$ = "new" $2; }*/
| lvalue
    { $$ = $1; }
| ID LPAREN exp2 RPAREN
    /*{ $$ = $ID "(" $3 ")"; }*/
| lvalue_c LPAREN exp2 RPAREN
    /*{ $$ = $1 "." $ID "(" $5 ")"; }*/
| MINUS exp
    /*{ $$ = new ast::OpExp(@$,nullptr, ast::OpExp::Oper::sub, $2); }*/
| exp MINUS exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::sub, $3); }
| exp PLUS exp
    { $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::add, $3); }
| exp AND exp
    /*{ $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::andop, $3); "}*/
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
    /*{ $$ = new ast::OpExp(@$, $1, ast::OpExp::Oper::orop, $3); }*/
| LPAREN exps RPAREN
    /*{ $$ = new ast::SeqExp(@$, $2); }*/
| lvalue ASSIGN exp
    /*{ $$ = new ast::AssignExp(@$,$1 ,$3); }*/
| IF exp THEN exp
    { $$ = new ast::IfExp(@$,$2 ,$4 ,nullptr);  }
| IF exp THEN exp ELSE exp
    /*{ $$ = new ast::IfExp(@$,$2 ,$4 , $6); }*/
| WHILE exp DO exp
    /*{ $$ = new ast::WhileExp(@$,$2,$4); }*/
| FOR ID ASSIGN exp TO exp DO exp
    /*{ $$ = new ast::ForExp(@$,$2,$4);  }*/
| BREAK
    { $$ = new ast::BreakExp(@$); }
| LET decs IN exps END
    /*{ $$ = new ast::LetExp(@$,$2,$4); }*/

lvalue:
  ID
    { $$ = new ast::SimpleVar(@$, $1); }
| lvalue_b
    { $$ = $1; }
| lvalue_c
    { $$ = $1; }


lvalue_b:
  ID LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, new ast::SimpleVar(@1, $1), $3); }
| lvalue_b LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, $1, $3); }
| lvalue_c LBRACK exp RBRACK
    { $$ = new ast::SubscriptVar(@$, $1, $3); }

lvalue_c:
  ID DOT ID
    { $$ = new ast::FieldVar(@$, $1, new ast::SimpleVar(@3, $3)); }
| lvalue_c DOT ID
    { $$ = new ast::FieldVar(@$, $3, $1); }
| lvalue_b DOT ID
    { $$ = new ast::FieldVar(@$, $3, $1); }

exp3:
  exp
    /*{ $$ = $1; }*/
| exp SEMI exp3
    /*{ $$ = $1 ";" $3; }*/

exps:
  %empty
    {
      ast::exps_type empty;
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
| dec decs
    /*{ $$ = $1 $2; }*/

dec:
  TYPE ID EQ ty
    /*{ $$ = "type" $ID "=" $4; }*/
| CLASS ID LBRACE classfields RBRACE
    /*{ $$ = "class" $ID "{" $4 "}"; }*/
| CLASS ID EXTENDS ID LBRACE classfields RBRACE
    /*{ $$ = "class" $2 "extends" $4 "{" $6 "}"; }*/
| vardec
    /*{ $$ = $1; }*/
| FUNCTION ID LPAREN tyfields RPAREN EQ exp
    /*{ $$ = "function" $ID "(" $4 ")" "=" $7; }*/
| FUNCTION ID LPAREN tyfields RPAREN COLON ID EQ exp
    /*{ $$ = "function" $2 "(" $4 ")" ":" $7 "=" $9; }*/
| PRIMITIVE ID LPAREN tyfields RPAREN
    /*{ $$ = "primitive" $ID "(" $4 ")"; }*/
| PRIMITIVE ID LPAREN tyfields RPAREN COLON ID
    /*{ $$ = "primitive" $2 "(" $4 ")" ":" $7; }*/
| IMPORT STRING
    /*{
      $$ = tp.parse_import(take($2), @$);
      if (!$$)
        $$ = new ast::DecsList;
    }*/

vardec:
  VAR ID ASSIGN exp
    /*{ $$ = "var" $ID ":=" $4; }*/
| VAR ID COLON ID ASSIGN exp
    /*{ $$ = "var" $2 ":" $4 ":=" $6; }*/

classfields:
  %empty
    /*{ $$ = "";}*/
| classfield classfields
    /*{ $$ = $1 $2; }*/

classfield:
  vardec
    /*{ $$ = $1; }*/
| METHOD ID LPAREN tyfields RPAREN EQ exp
    /*{ $$ = "method" $ID "(" $4 ")" "=" $7; }*/
| METHOD ID LPAREN tyfields RPAREN COLON ID EQ exp
    /*{ $$ = "method" $2 "(" $4 ")" ":" $7 "=" $9; }*/

ty:
  ID
    /*{ $$ = $ID; }*/
| LBRACE tyfields RBRACE
    /*{ $$ = "{" $2 "}"; }*/
| ARRAY OF ID
    /*{ $$ = "array" "of" $ID; }*/
| CLASS LBRACE classfields RBRACE
    /*{ $$ = "class" "{" $3 "}"; }*/
| CLASS EXTENDS ID LBRACE classfields RBRACE
    /*{ $$ = "class" "extends" $ID "{" $5 "}"; }*/

id_comma:
  %empty
    /*{ $$ = ""; }*/
| COMMA ID COLON ID id_comma
    /*{ $$ = "," $2 ":" $4 $5; }*/

tyfields:
  %empty
    /*{ $$ = ""; }*/
| ID COLON ID id_comma
    /*{ $$ = $1 ":" $3 $4; }*/

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  tp.error_ << misc::error::error_type::parse
            << l << ": " << m << std::endl;
}
