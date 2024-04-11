#include "lrucache.hpp"
#include "gtest/gtest.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <string>

/* --------------- Test Setup --------------- */
/* Type struct encapsulation */
template <typename Key, typename Val>
struct TypeDefinitions {
    typedef Key key;
    typedef Val val;
};

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

/* Defining types to test */
using testing::Types;
using String = std::string;

template <typename T>
using Vector = std::vector<T>;

typedef Types<TypeDefinitions<int, String>, TypeDefinitions<String, String>,
              TypeDefinitions<char, char>, TypeDefinitions<float, double>,
              TypeDefinitions<double, Vector<float>>>
    HashTypes;
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
    ASSERT_EQ(this->_cache.capacity(), 57);
}
