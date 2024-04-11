#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <concepts>
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
    requires Hashable<Key>
using Pair = std::pair<Key, Val>;

template <typename Key, typename Val>
class LRUCache {
public:
    LRUCache();
    LRUCache(std::uint64_t);
    LRUCache(const LRUCache &);
    LRUCache(LRUCache &&) noexcept;

    auto operator=(const LRUCache &) -> LRUCache &;
    auto operator=(LRUCache &&) noexcept -> LRUCache &;

    auto emplace(const Key &, const Val &) -> void;
    auto insert(Pair<Key, Val>) -> void;

    auto size() -> std::uint64_t;
    auto ssize() -> long;

private:
    std::uint64_t size_;
    Dict<Key, Val> map;
    List<decltype(map.begin())> order;

    auto keep_coherent() -> void;
};

/* Constructor */
template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache() : size_(DEFAULT_SIZE) {}

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(std::uint64_t len) : size_(len) {}

/* Copy Constructor */
template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(const LRUCache<Key, Val> &cache) {
    this->size_ = cache.size_;
    this->map = cache.map;
    for (const auto &it : cache.order) {
        [[maybe_unused]] Key key = it->first;
        // this->order.insert(this->map.find(key));
    }
}

/* Move Constructor */
template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(LRUCache<Key, Val> &&cache) noexcept {
    this->size_ = cache.size_;
    this->map = std::move(cache.map);
    this->order = std::move(cache.order);
}

/* Copy Assignment */
template <typename Key, typename Val>
auto LRUCache<Key, Val>::operator=(const LRUCache<Key, Val> &other)
    -> LRUCache<Key, Val> & {
    if (this == &other) {
        return *this;
    }

    this->size_ = other.size_;
    this->map = other.map;
    for (const auto &it : other.order) {
        [[maybe_unused]] Key key = it->first;
        // this->order.insert(this->map.find(key));
    }

    return *this;
}

/* Move assignment */
template <typename Key, typename Val>
auto LRUCache<Key, Val>::operator=(LRUCache<Key, Val> &&other) noexcept
    -> LRUCache<Key, Val> & {
    if (this == &other) {
        return *this;
    }

    this->size_ = other.size_;
    this->map = std::move(other.map);
    this->order = std::move(other.order);

    return *this;
}

template <typename Key, typename Val>
auto LRUCache<Key, Val>::emplace(const Key &key, const Val &val) -> void {
    auto [it, success] = this->map.emplace(key, val);
    if (!success) {
        return;
    }
}

/* Getters for size */
template <typename Key, typename Val>
auto LRUCache<Key, Val>::size() -> std::uint64_t {
    return this->size_;
}

template <typename Key, typename Val>
auto LRUCache<Key, Val>::ssize() -> long {
    return static_cast<long>(this->size_);
}

} // namespace cache

#endif // LRU_CACHE_H
