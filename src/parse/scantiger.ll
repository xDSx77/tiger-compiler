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
cast            _cast
decs            _decs
exp             _exp
lvalue          _lvalue
namety          _namety
id              [a-zA-Z][a-zA-Z_0-9]*|_main

%%
%{
  static int comments_ = 0;
  std::string grown_string = "";
  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */

"\""            grown_string.clear(); tp.location_.step(); BEGIN SC_STRING;

<SC_STRING>{ /* Handling of the strings. Initial " is eaten */
  "\""        {
                BEGIN INITIAL;
                return TOKEN_VAL(STRING, grown_string);
              }
  <<EOF>>     {
                tp.error_ << misc::error::error_type::scan << tp.location_
                          << ": Unterminated string" << std::endl;
                yyterminate();
              }
  "\\a"         grown_string.append("\\a");
  "\\b"         grown_string.append("\\b");
  "\\f"         grown_string.append("\\f");
  "\\n"         grown_string.append("\\n");
  "\\r"         grown_string.append("\\r");
  "\\t"         grown_string.append("\\t");
  "\\v"         grown_string.append("\\v");
  \\int       {
                if (strtol(yytext + 2, 0, 10) > 255)
                {
                  tp.error_ << misc::error::error_type::scan << tp.location_
                            <<  ": illegal octal value" << std::endl;
                  yyterminate();
                }
                grown_string.append(yytext + 2);
              }
  \n+           tp.location_.lines(yyleng); tp.location_.step();
  \\x[0-9a-fA-F]{2} grown_string.append(yytext + 2);
  .             grown_string.append(yytext);
}

"/*"            comments_++; tp.location_.step(); BEGIN SC_COMMENT;

<SC_COMMENT>{
  "/*"          comments_++; BEGIN SC_COMMENT;
  <<EOF>>     {
                tp.error_ << misc::error::error_type::scan << tp.location_
                          << ": unexpected end of file in a comment" << std::endl;
                yyterminate();
              }
  \n+           tp.location_.lines(yyleng);
  "*/"        {
                comments_--;
                if (comments_ == 0)
                  BEGIN INITIAL;
              }
  .           ;
}
"*/"          {
                tp.error_ << misc::error::error_type::scan << tp.location_
                          << ": unexpected end of comment" << std::endl;
                yyterminate();
              }
<<EOF>>         yyterminate();
cast            return TOKEN(CAST);
decs            return TOKEN(DECS);
exp             return TOKEN(EXP);
lvalue          return TOKEN(LVALUE);
namety          return TOKEN(NAMETY);
{int}           return TOKEN_VAL(INT, std::stoi(yytext));
"if"            return TOKEN(IF);
"of"            return TOKEN(OF);
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
"new"           return TOKEN(NEW);
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
{id}            return TOKEN_VAL(ID, yytext);
[ \t]+          tp.location_.step();
\n+             tp.location_.lines(yyleng); tp.location_.step();

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
