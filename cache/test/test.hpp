#ifndef TEST_HPP
#define TEST_HPP

#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <type_traits>

#include "lrucache.hpp"

/* --------------- Test Setup --------------- */
/* Type struct encapsulation */
template <typename Key, typename Val>
struct TypeDefinitions {
    typedef Key key;
    typedef Val val;
};

/* Defining types to test */
using testing::Types;
using String = std::string;

template <typename T>
using Vector = std::vector<T>;

/* Class fixture test for typed test with default constructor */
template <typename types>
class LRUCacheTest : public ::testing::Test {
protected:
    LRUCacheTest()
        : _cache(cache::LRUCache<typename types::key, typename types::val>()) {}

    void SetUp(std::uint64_t len) {
        _cache = cache::LRUCache<typename types::key, typename types::val>(len);
    }

    cache::LRUCache<typename types::key, typename types::val> _cache;
};

/* Class fixture test for functioanl tests */
class LRUCacheFunctionTest : public ::testing::Test {
protected:
    void SetUp() override {}

    cache::LRUCache<int, int> int_cache;
    cache::LRUCache<float, double> float_cache;
    cache::LRUCache<String, char> string_cache;
    cache::LRUCache<int, Vector<String>> container_cache;
};

/* Inherited classes for different test suites */
template <typename types>
class LRUEmplaceTestInt : public LRUCacheTest<types> {};

template <typename types>
class LRUEmplaceTestChar : public LRUCacheTest<types> {};

template <typename types>
class LRUEmplaceTestIntChar : public LRUCacheTest<types> {};

template <typename types>
class LRUEmplaceTestCharInt : public LRUCacheTest<types> {};

template <typename types>
class LRUEmplaceTestContainer : public LRUCacheTest<types> {};

/* Creating type traits for special types */
template <typename T>
struct is_string_type : std::false_type {};

template <typename T>
    requires std::same_as<T, char>
struct is_string_type<T> : std::true_type {};

template <typename T>
T construct(char arg) {
    if constexpr (is_string_type<T>::value) {
        return T(1, arg);
    }

    return arg;
}

/* typedefs for TYPED_TEST */
typedef Types<TypeDefinitions<int, String>, TypeDefinitions<String, String>,
              TypeDefinitions<char, char>, TypeDefinitions<float, double>,
              TypeDefinitions<double, Vector<int>>>
    HashTypes;

typedef Types<TypeDefinitions<int, int>, TypeDefinitions<float, double>>
    IntTypes;

typedef Types<TypeDefinitions<String, String>, TypeDefinitions<char, char>>
    CharTypes;

typedef Types<TypeDefinitions<int, String>, TypeDefinitions<float, char>>
    IntCharTypes;

typedef Types<TypeDefinitions<String, int>, TypeDefinitions<char, double>>
    CharIntTypes;

typedef Types<TypeDefinitions<int, Vector<int>>,
              TypeDefinitions<int, Vector<String>>>
    ContainerTypes;
/* --------------- Test Setup Ends Here --------------- */

#endif // !TEST_HPP
