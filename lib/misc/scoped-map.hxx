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
    scoped_map_.insert_or_assign(key, value);
  }
/*
  template <typename Key, typename Data>
  Data
  scoped_map<Key, Data>::get(const Key& key) const
  {
  }
*/
  template <typename Key, typename Data>
  void
  scoped_map<Key, Data>::scope_begin()
  {
    scoped_map();
  }

  template <typename Key, typename Data>
  void
  scoped_map<Key, Data>::scope_end()
  {
  }

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }
/*
  template <typename Key, typename Data>
  inline std::ostream&
  dump(std::ostream& ostr) const
  {
  }
*/
} // namespace misc
