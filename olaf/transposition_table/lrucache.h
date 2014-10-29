#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <cassert>
#include <mutex>
#include <vector>
#include "olaf/transposition_table/zobristhash.h"

namespace olaf
{

template <typename V>
class LruCache
{
public:
  typedef ZobristHash::hash_t key_t;

  explicit LruCache(long capacity_bytes);

  const V* get(key_t key) const;

  void put(key_t key, const V& value);

  void put(key_t key, V&& value);

  long hits() const { return m_hits; }

  long misses() const { return m_misses; }

private:
  long index(key_t key) const;

  struct Entry {
    inline Entry(const key_t key, const V& value):
      key(key),
      value(value)
    {}

    inline Entry(const key_t key, V&& value):
      key(key),
      value(std::move(value))
    {}

    key_t key;
    V value;
  };

  const long m_capacity;

  std::vector<Entry> m_elements;

  mutable long m_hits = 0;

  mutable long m_misses = 0;
};

template <typename V>
LruCache<V>::LruCache(const long capacity):
  m_capacity(capacity)
{
  assert(capacity > 0);
  m_elements.resize(capacity, Entry(0, V()));
}

template <typename V>
const V* LruCache<V>::get(const key_t key) const
{
  const long i = index(key);
  const Entry& entry = m_elements[i];
  if (entry.key == key) {
    ++m_hits;
    return &(entry.value);
  } else {
    ++m_misses;
    return nullptr;
  }
}

template <typename V>
void LruCache<V>::put(const key_t key, const V& value)
{
  const long i = index(key);
  m_elements[i] = Entry(key, value);
}

template <typename V>
void LruCache<V>::put(const key_t key, V&& value)
{
  const long i = index(key);
  m_elements[i] = Entry(key, std::move(value));
}

template <typename V>
long LruCache<V>::index(const key_t key) const
{
  return key % m_capacity;
}

} // namespace olaf

#endif // LRUCACHE_H
