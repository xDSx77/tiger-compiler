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
  void
  scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    scoped_map_.back()->insert_or_assign(key, value);
  }

  template <typename Key, typename Data>
  Data
  scoped_map<Key, Data>::get(const Key& key) const
  {
    auto pair = *(scoped_map_.back()->find(key));
    return pair.second;
  }

  template <typename Key, typename Data>
  void
  scoped_map<Key, Data>::scope_begin()
  {
    scoped_map_.push_back(new std::map<Key, Data>());
  }

  template <typename Key, typename Data>
  void
  scoped_map<Key, Data>::scope_end()
  {
    delete scoped_map_.back();
  }

  template <typename Key, typename Data>
  std::ostream&
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
