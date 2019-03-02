/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>

namespace misc
{

  template <typename Key, typename Data>
  scoped_map<Key, Data>::scoped_map()
  {
    scope_begin();
  }

  template <typename Key, typename Data>
  inline void
  scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    scoped_map_.back()->insert(std::pair<Key, Data>(key, value));
  }

  template <typename Key, typename Data>
  inline Data
  scoped_map<Key, Data>::get(const Key& key) const
  {
    auto pair = scoped_map_.back()->find(key);
    return pair->second;
  }

  template <typename Key, typename Data>
  inline int
  scoped_map<Key, Data>::is_inside(const Key& key) const
  {
    auto pair = scoped_map_.back()->find(key);
    if (pair != scoped_map_.back()->end())
      return 1;
    return 0;
  }

  template <typename Key, typename Data>
  inline void
  scoped_map<Key, Data>::scope_begin()
  {
    scoped_map_.push_back(new std::map<Key, Data>());
  }

  template <typename Key, typename Data>
  inline void
  scoped_map<Key, Data>::scope_end()
  {
    delete scoped_map_.back();
  }

  template <typename Key, typename Data>
  inline std::ostream&
  scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    for (auto i = scoped_map_.back().begin(); i != scoped_map_.back().end(); i++)
      ostr << i->first << i->second << '\n';
    return ostr;
  }

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
