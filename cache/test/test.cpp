#include "test.hpp"

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
