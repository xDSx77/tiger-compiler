/**
 ** \file bind/libbind.cc
 ** \brief Define exported bind functions.
 */
#include <fstream>

#include <bind/libbind.hh>
#include <ast/pretty-printer.hh>

namespace bind
{
  // Making the following variables const is more than merely
  // stylistic.  If they were not, Swig will create set/get for them,
  // and there is no set (operator=), since it has a const member.

  /// xalloc slot to enable escapes display in Ast display.
  const misc::xalloc<bool> escapes_display;
  /// xalloc slot to enable bindings display in Ast display.
  const misc::xalloc<bool> bindings_display;

  // Print the TREE on OSTR.
  std::ostream&
  operator<<(std::ostream& ostr, const ast::Dec& e)
  {
      ast::PrettyPrinter print(ostr);
    print(e);
    return ostr;
  }

}
