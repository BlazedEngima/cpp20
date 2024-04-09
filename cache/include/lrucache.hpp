#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cstdint>
#include <functional>
#include <list>
#include <unordered_map>

#define DEFAULT_SIZE 5000

namespace cache {

template <typename Key>
concept Hashable = requires(Key key) {
    { std::hash<Key> {}(key) } -> std::convertible_to<std::size_t>;
};

template <typename Key, typename Value>
    requires Hashable<Key>
using Dict = std::unordered_map<Key, Value>;

template <typename T>
using List = std::list<T>;

template <typename Key, typename Val>
class LRUCache {
public:
    LRUCache() noexcept;
    LRUCache(std::uint64_t) noexcept;
    LRUCache(const LRUCache &) noexcept;
    LRUCache(LRUCache &&) noexcept;

private:
    std::uint64_t size;
    Dict<Key, Val> map;
    List<decltype(map.begin())> order;
};

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache() noexcept : size(DEFAULT_SIZE) {}

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(std::uint64_t len) noexcept : size(len) {}

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(const LRUCache<Key, Val> &cache) noexcept {
    this->size = cache.size;
    this->map = cache.map;
    this->order = cache.order;
}

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(LRUCache<Key, Val> &&cache) noexcept {
    this->size = cache.size;
    this->map = cache.map;
    this->order = cache.order;
}

} // namespace cache

#endif // LRU_CACHE_H
