                                                                // -*- C++ -*-
%require "3.0"
%language "C++"
// Set the namespace name to `parse', instead of `yy'.
%define api.prefix {parse}
%define api.value.type variant
%define api.token.constructor
%expect 0
%skeleton "lalr1.cc"
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

%type <ast::Exp*> exp
%type <ast::Exp*> exps
%type <ast::DecsList*> decs
%type <ast::Exp*> id_exp
%type <ast::Exp*> exp2
%type <ast::Exp*> exp3
%type <ast::Ty*> ty
%type <ast::Ty::RecordTy*> tyfields
%type <ast::Ty::RecordTy*> id_comma
%type <ast::Dec*> dec
%type <ast::Dec::VarDec*> vardec
%type <ast::FieldInit*> classfields
%type <ast::Field*> classfield
%type <ast::Exp::SeqExp*> lvalue
%type <ast::Exp::SeqExp*> lvalue_b

%left OR
%left AND
%left GE LE EQ GT LT NE
%left PLUS MINUS
%left TIMES DIVIDE
%left LPAREN RPAREN LBRACK RBRACK LBRACE RBRACE
%left ASSIGN
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
;

id_exp:
  %empty
    { $$ = ""; }
| ID EQ exp
    { $$ = $ID "=" $3; }
| ID EQ exp COMMA id_exp
    { $$ = $ID "=" $3 "," $5; }

exp2:
  %empty
    { $$ = ""; }
| exp
    { $$ = $1; }
| exp COMMA exp2
    { $$ = $1 "," $3; }

exp:
  INT
    { $$ = new ast::IntExp(@$, $1); }
| NIL
    { $$ = new ast::NilExp(); }
| STRING
    { $$ = new ast::StringExp(@$, $1); }
| ID LBRACK exp RBRACK OF exp
    { $$ = $ID "[" $3 "]" "of" $6; }
| ID LBRACE id_exp RBRACE
    { $$ = $ID "{" $3 "}"; }
| NEW ID
    { $$ = "new" $2; }
| lvalue
    { $$ = $1; }
| ID LPAREN exp2 RPAREN
    { $$ = $ID "(" $3 ")"; }
| lvalue DOT ID LPAREN exp2 RPAREN
    { $$ = $1 "." $ID "(" $5 ")"; }
| MINUS exp
    { $$ = "-" $2; }
| exp MINUS exp
    { $$ = $1 "-" $3 }
| exp PLUS exp
    { $$ = $1 "+" $3 }
| exp AND exp
    { $$ = $1 "&" $3 }
| exp LE exp
    { $$ = $1 "<=" $3 }
| exp GE exp
    { $$ = $1 ">=" $3 }
| exp GT exp
    { $$ = $1 ">" $3 }
| exp LT exp
    { $$ = $1 "<" $3 }
| exp NE exp
    { $$ = $1 "<>" $3 }
| exp EQ exp
    { $$ = $1 "=" $3 }
| exp DIVIDE exp
    { $$ = $1 "/" $3 }
| exp TIMES exp
    { $$ = $1 "*" $3 }
| exp OR exp
    { $$ = $1 "|" $3 }
| LPAREN exps RPAREN
    { $$ = "(" $2 ")"; }
| lvalue ASSIGN exp
    { $$ = $1 ":=" $3; }
| IF exp THEN exp
    { $$ = "if" $2 "then" $4; }
| IF exp THEN exp ELSE exp
    { $$ = "if" $2 "then" $4 "else" $6; }
| WHILE exp DO exp
    { $$ = "while" $2 "do" $4; }
| FOR ID ASSIGN exp TO exp DO exp
    { $$ = "for" $ID ":=" $4 "to" $6 "do" $8; }
| BREAK
    { $$ = "break"; }
| LET decs IN exps END
    { $$ = "let" $2 "in" $4 "end"; }

lvalue:
  ID
    { $$ = $ID; }
| lvalue_b
    { $$ = $1; }

lvalue_b:
  ID OF LBRACK exp RBRACK
    { $$ = $ID "of" "{" $4 "}"; }
| lvalue_b LBRACK exp RBRACK
    { $$ = $1 "{" $3 "}"; }

exp3:
  exp
    { $$ = $1; }
| exp SEMI exp3
    { $$ = $1 ";" $3; }

exps:
  %empty
    { $$ = new ast::Exp(@$); }
| exp3
    { $$ = new ast::Exp(@$, $1); }

/*---------------.
| Declarations.  |
`---------------*/

%token DECS "_decs";
decs:
  %empty
    { $$ = new ast::DecsList(@$); }
| dec decs
    { $$ = $1 $2; }

dec:
  TYPE ID EQ ty
    { $$ = "type" $ID "=" $4; }
| CLASS ID LBRACE classfields RBRACE
    { $$ = "class" $ID "{" $4 "}"; }
| CLASS ID EXTENDS ID LBRACE classfields RBRACE
    { $$ = "class" $2 "extends" $4 "{" $6 "}"; }
| vardec
    { $$ = $1; }
| FUNCTION ID LPAREN tyfields RPAREN EQ exp
    { $$ = "function" $ID "(" $4 ")" "=" $7; }
| FUNCTION ID LPAREN tyfields RPAREN COLON ID EQ exp
    { $$ = "function" $2 "(" $4 ")" ":" $7 "=" $9; }
| PRIMITIVE ID LPAREN tyfields RPAREN
    { $$ = "primitive" $ID "(" $4 ")"; }
| PRIMITIVE ID LPAREN tyfields RPAREN COLON ID
    { $$ = "primitive" $2 "(" $4 ")" ":" $7; }
| IMPORT STRING
    { $$ = "import" $STRING; }

vardec:
  VAR ID ASSIGN exp
    { $$ = "var" $ID ":=" $4; }
| VAR ID COLON ID ASSIGN exp
    { $$ = "var" $2 ":" $4 ":=" $6; }

classfields:
  %empty
    { $$ = "";}
| classfield classfields
    { $$ = $1 $2; }

classfield:
  vardec
    { $$ = $1; }
| METHOD ID LPAREN tyfields RPAREN EQ exp
    { $$ = "method" $ID "(" $4 ")" "=" $7; }
| METHOD ID LPAREN tyfields RPAREN COLON ID EQ exp
    { $$ = "method" $2 "(" $4 ")" ":" $7 "=" $9; }

ty:
  ID
    { $$ = $ID; }
| LBRACE tyfields RBRACE
    { $$ = "{" $2 "}"; }
| ARRAY OF ID
    { $$ = "array" "of" $ID; }
| CLASS LBRACE classfields RBRACE
    { $$ = "class" "{" $3 "}"; }
| CLASS EXTENDS ID LBRACE classfields RBRACE
    { $$ = "class" "extends" $ID "{" $5 "}"; }

id_comma:
  %empty
    { $$ = ""; }
| COMMA ID COLON ID id_comma
    { $$ = "," $2 ":" $4 $5; }

tyfields:
  %empty
    { $$ = ""; }
| ID COLON ID id_comma
    { $$ = $1 ":" $3 $4; }

%%

void
parse::parser::error(const location_type& l, const std::string& m)
{
  // FIXME: Some code was deleted here.
}
