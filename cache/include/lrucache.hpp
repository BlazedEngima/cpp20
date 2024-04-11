#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <list>
#include <unordered_map>

namespace cache {

static constexpr std::size_t default_size = 5000;

template <typename Key>
concept Hashable = requires(Key key) {
    { std::hash<Key> {}(key) } -> std::convertible_to<std::size_t>;
};

template <typename Key, typename Val>
    requires Hashable<Key>
using Dict = std::unordered_map<Key, Val>;

template <typename T>
using List = std::list<T>;

template <typename Key, typename Val>
    requires Hashable<Key>
using Pair = std::pair<Key, Val>;

template <typename Key, typename Val>
class LRUCache {
public:
    LRUCache();
    LRUCache(std::size_t);
    LRUCache(const LRUCache &);
    LRUCache(LRUCache &&) noexcept;

    auto operator=(const LRUCache &) -> LRUCache &;
    auto operator=(LRUCache &&) noexcept -> LRUCache &;

    template <typename... Args>
    auto emplace(Args &&...) -> void;
    auto insert(const Pair<Key, Val> &) -> void;

    auto size() noexcept -> std::size_t;
    auto ssize() noexcept -> std::ptrdiff_t;

private:
    std::size_t max_size;
    Dict<Key, Val> map;
    List<decltype(map.begin())> order;

    auto keep_coherent() -> void;
};

/* Constructor */
template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache() : max_size(default_size) {}

template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(std::size_t len) : max_size(len) {}

/* Copy Constructor */
template <typename Key, typename Val>
LRUCache<Key, Val>::LRUCache(const LRUCache<Key, Val> &cache) {
    this->size_ = cache.size_;
    this->map = cache.map;
    for (const auto &it : cache.order) {
        Key key = it->first;
        this->order.push_front(this->map.find(key));
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
        Key key = it->first;
        this->order.push_front(this->map.find(key));
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

/* Emplace new element */
template <typename Key, typename Val>
template <typename... Args>
auto LRUCache<Key, Val>::emplace(Args &&...args) -> void {
    auto [it, success] = this->map.emplace(std::forward<Args>(args)...);
    if (!success) {
        return;
    }

    this->keep_coherent();
    this->order.push_front(it);
}

/* Getters for size */
template <typename Key, typename Val>
auto LRUCache<Key, Val>::size() noexcept -> std::size_t {
    return this->map.size();
}

template <typename Key, typename Val>
auto LRUCache<Key, Val>::ssize() noexcept -> std::ptrdiff_t {
    return std::ssize(this->map);
}

/* Bounds checking on LRUCache */
template <typename Key, typename Val>
auto LRUCache<Key, Val>::keep_coherent() -> void {
    if (this->map.size() <= this->size_ || this->map.empty()) {
        return;
    }

    auto last = this->order.back();
    this->map.erase(last);
    this->order.pop_back();
}

} // namespace cache

#endif // LRU_CACHE_H
