#include "lrucache.hpp"
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

/* Class fixture test */
template <typename types>
class LRUCacheTest : public ::testing::Test {
protected:
    LRUCacheTest()
        : _cache(cache::LRUCache<typename types::key, typename types::val>()) {}

    cache::LRUCache<typename types::key, typename types::val> _cache;
};

/* Defining types to test */
using testing::Types;
using String = std::string;
typedef Types<TypeDefinitions<int, String>, TypeDefinitions<String, String>,
              TypeDefinitions<char, char>>
    HashTypes;
/* --------------- Test Setup Ends Here --------------- */

/* Tests start here */
TYPED_TEST_SUITE(LRUCacheTest, HashTypes);

TYPED_TEST(LRUCacheTest, BasicConstructor) {
    ASSERT_NO_THROW({ this->_cache.size() == 5000; });
}
