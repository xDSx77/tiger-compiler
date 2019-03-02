/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <map>
#include <vector>

namespace misc
{

  template <typename Key, typename Data>
  class scoped_map
  {
  protected:
    using scoped_map_t = std::vector<std::map<Key, Data>*>;

  public:
    scoped_map();
    void put(const Key& key, const Data& value);
    Data get(const Key& key) const;
    int is_inside(const Key& key) const;
    std::ostream& dump(std::ostream& ostr) const;
    void scope_begin();
    void scope_end();

  protected:
    scoped_map_t scoped_map_;
  };

  template <typename Key, typename Data>
  std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl);

} // namespace misc

#include <misc/scoped-map.hxx>
