#include "lrucache.hpp"
#include <gtest/gtest.h>
#include <string>

/* Default constructor */
TEST(Constructor, default_constructor) {
    cache::LRUCache<int, std::string> lru;

    EXPECT_EQ(lru.size(), 5000) << "Not initialized to the right size";
}
