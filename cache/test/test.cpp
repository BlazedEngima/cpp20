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

/* Class fixture test for default constructor */
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

class LRUCacheFunctionTest : public ::testing::Test {
protected:
    void SetUp() override {}

    cache::LRUCache<int, int> int_cache;
    cache::LRUCache<float, double> float_cache;
    cache::LRUCache<String, char> string_cache;
    cache::LRUCache<int, Vector<String>> container_cache;
};

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

/* Creating factory functions */
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

/* Tests start here */
/* Default Constructor Tests */
TYPED_TEST_SUITE(LRUCacheTest, HashTypes);

TYPED_TEST(LRUCacheTest, BasicConstructor) {
    ASSERT_EQ(this->_cache.capacity(), 5000);
    ASSERT_EQ(this->_cache.scapacity(), 5000);
    EXPECT_TRUE(
        (std::is_same_v<decltype(this->_cache.scapacity()), std::ptrdiff_t>));

    this->SetUp(57);
    EXPECT_EQ(this->_cache.capacity(), 57);
}

TYPED_TEST_SUITE(LRUEmplaceTestInt, IntTypes);
TYPED_TEST(LRUEmplaceTestInt, EmplaceIntTest) {
    ASSERT_EQ(this->_cache.capacity(), 5000);

    using KeyType = typename TypeParam::key;
    using ValueType = typename TypeParam::val;

    ASSERT_NO_THROW(this->_cache.emplace(KeyType(42), ValueType(7)));
    EXPECT_EQ(this->_cache.size(), 1);
    ASSERT_NO_THROW(this->_cache.emplace(KeyType(3), ValueType(5)));
    EXPECT_EQ(this->_cache.size(), 2);
    ASSERT_NO_THROW(this->_cache.emplace(KeyType(3), ValueType(12)));
    EXPECT_EQ(this->_cache.size(), 2);

    ASSERT_NO_THROW(this->_cache.emplace(KeyType(40), ValueType(7)));
    ASSERT_NO_THROW(this->_cache.emplace(KeyType(4), ValueType(8)));
    ASSERT_NO_THROW(this->_cache.emplace(KeyType(10), ValueType(10)));
    EXPECT_EQ(this->_cache.size(), 5);
}

TEST(LRUEmplaceTestChar, StringTypes) {
    auto cache = cache::LRUCache<String, char>();

    ASSERT_NO_THROW(cache.emplace("Hello", 'c'));
    EXPECT_EQ(cache.size(), 1);

    ASSERT_NO_THROW(cache.emplace("Hello", 'e'));
    EXPECT_EQ(cache.size(), 1);

    ASSERT_NO_THROW(cache.emplace("Test", 't'));
    EXPECT_EQ(cache.size(), 2);

    ASSERT_NO_THROW(cache.emplace("Hi", 'f'));
    ASSERT_NO_THROW(cache.emplace("Key", 't'));
    ASSERT_NO_THROW(cache.emplace("Test 2", 't'));

    EXPECT_EQ(cache.size(), 5);
}
