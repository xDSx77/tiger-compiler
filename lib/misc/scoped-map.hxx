/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <iostream>
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
    scoped_map_.back().insert(std::pair<Key, Data>(key, value));
  }

  template <typename Key, typename Data>
  inline std::vector<std::map<Key, Data>>&
  scoped_map<Key, Data>::map_get()
  {
    return scoped_map_;
  }

  template <typename Key, typename Data>
  Data
  scoped_map<Key, Data>::get(const Key& key) const
  {
    for (auto map = scoped_map_.rbegin(); map != scoped_map_.rend(); map++)
    {
      try
      {
        auto& elem = map->at(key);
        return elem;
      }
      catch(std::exception const& e)
      {
        if (*map != scoped_map_.front())
          continue;
        if constexpr(std::is_pointer_v<Data>)
          return nullptr;
        else
          throw std::range_error("can't find data with that key");
      }
    }
  }

  template <typename Key, typename Data>
  inline void
  scoped_map<Key, Data>::scope_begin()
  {
    scoped_map_.push_back(std::map<Key, Data>());
  }

  template <typename Key, typename Data>
  inline void
  scoped_map<Key, Data>::scope_end()
  {
    scoped_map_.pop_back();
  }

  template <typename Key, typename Data>
  inline std::ostream&
  scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    for (auto i = scoped_map_.back().begin(); i != scoped_map_.back().end(); i++)
      ostr << i.first << i.second << '\n';
    return ostr;
  }

  template <typename Key, typename Data>
  inline std::ostream&
  operator<<(std::ostream& ostr, const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
