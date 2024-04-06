#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <functional>
#include <list>
#include <unordered_map>

namespace cache {

template <typename Key>
concept Hashable = requires(Key key) {
    { std::hash<Key>{}(key) } -> std::convertible_to<std::size_t>;
};

template <typename Key, typename Value>
    requires Hashable<Key>
using Dict = std::unordered_map<Key, Value>;

template <typename T>
using List = std::list<T>;

template <typename Key, typename Val>
class LRUCache {
public:
private:
    Dict<Key, Val> map;
    List<decltype(map.begin())> order;
};

}  // namespace cache

#endif  // LRU_CACHE_H
