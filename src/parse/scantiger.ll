                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>

#define YY_USER_ACTION tp.location_.columns(yyleng);

  // FIXME: Some code was deleted here.

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+
id              [a-zA-Z][a-zA-Z_0-9]*
string          "\""([^\\]|\\.)*"\""

%%
%{
  // FIXME: Some code was deleted here (Local variables).

  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */

<<EOF>>         yyterminate();
{int}         {
                int val = 0;
                if (std::stoi(yytext))
                    val = std::stoi(std::string(yytext));
  // FIXME: Some code was deleted here (Decode, and check the value).
                return TOKEN_VAL(INT, val);
              }
{id}            return TOKEN(ID);
{string}        return TOKEN(STRING);
"if"            return TOKEN(IF);
"nil"           return TOKEN(NIL);
"then"          return TOKEN(THEN);
"else"          return TOKEN(ELSE);
"while"         return TOKEN(WHILE);
"do"            return TOKEN(DO);
"for"           return TOKEN(FOR);
"to"            return TOKEN(TO);
"break"         return TOKEN(BREAK);
"let"           return TOKEN(LET);
"in"            return TOKEN(IN);
"end"           return TOKEN(END);
":="            return TOKEN(ASSIGN);
"type"          return TOKEN(TYPE);
"class"         return TOKEN(CLASS);
"extends"       return TOKEN(EXTENDS);
"function"      return TOKEN(FUNCTION);
"import"        return TOKEN(IMPORT);
"primitive"     return TOKEN(PRIMITIVE);
"var"           return TOKEN(VAR);
"method"        return TOKEN(METHOD);
"array"         return TOKEN(ARRAY);
"."             return TOKEN(DOT);
","             return TOKEN(COMMA);
":"             return TOKEN(COLON);
";"             return TOKEN(SEMI);
"*"             return TOKEN(TIMES);
"/"             return TOKEN(DIVIDE);
"+"             return TOKEN(PLUS);
"-"             return TOKEN(MINUS);
"("             return TOKEN(LPAREN);
")"             return TOKEN(RPAREN);
"["             return TOKEN(LBRACK);
"]"             return TOKEN(RBRACK);
"{"             return TOKEN(LBRACE);
"}"             return TOKEN(RBRACE);
">="            return TOKEN(GE);
"<="            return TOKEN(LE);
"="             return TOKEN(EQ);
"<>"            return TOKEN(NE);
"<"             return TOKEN(LT);
">"             return TOKEN(GT);
"&"             return TOKEN(AND);
"|"             return TOKEN(OR);
\n+             tp.location_.line(yyleng); tp.location_.step();

%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
