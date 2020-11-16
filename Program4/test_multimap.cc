#include <gtest/gtest.h>
#include <vector>

#include "multimap.h"

// Test one key
TEST(Multimap, OneKey) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2};

  for (auto i : keys) {
    multimap.Insert(i, i);
  }

  EXPECT_EQ(multimap.Contains(2), true);
  EXPECT_EQ(multimap.Get(2), keys[0]);
}

// Test multiple keys
TEST(Multimap, MultipleKeys) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 18, 42, 43};

  // Insert a bunch of keys
  for (auto i : keys) {
    multimap.Insert(i, i);
  }

  // Check that every key is contained
  std::random_shuffle(keys.begin(), keys.end());
  for (auto i : keys) {
    EXPECT_EQ(multimap.Contains(i), true);
    EXPECT_EQ(multimap.Get(i), i);
  }
}

// Test multiple values assigned to one key
TEST(Multimap, MultipleKeysAndValues) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 18, 42, 43};
  std::vector<int> values{2, 18, 42, 43};

  // Insert a buch of keys and values
  for (auto i : keys) {
    for (auto j : values) {
      multimap.Insert(i,j);
    }
  }
  
  // Test removing some values
  multimap.Remove(2);
  multimap.Remove(2);
  multimap.Remove(2);
  
  // Should still have 2
  EXPECT_EQ(multimap.Contains(2), true);
  EXPECT_EQ(multimap.Get(2), values[3]);
}

TEST(Multimap, Min) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 4, 1, 19};

  // Insert keys
  for (auto i : keys) {
    multimap.Insert(i, i);
  }

  // Check that min is 1
  EXPECT_EQ(multimap.Min(), 1);

  multimap.Remove(1);
  
  // Check that min is now 2
  EXPECT_EQ(multimap.Min(), 2);
}

TEST(Multimap, Max) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 4, 1, 19};

  // Insert keys
  for (auto i : keys) {
    multimap.Insert(i, i);
  }

  // Check that max is 19
  EXPECT_EQ(multimap.Max(), 19);

  multimap.Remove(1);

  // Check that max is still 19
  EXPECT_EQ(multimap.Max(), 19);
}

TEST(Multimap, Size) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 18, 42, 43};

  // Insert a bunch of keys and values
  for (auto i : keys) {
    multimap.Insert(i, i);
  }

  // Ensure size is 4
  EXPECT_EQ(multimap.Size(), 4);

  for (auto i : keys) {
    multimap.Insert(5, i);
  }
  
  // Ensure size is 8
  EXPECT_EQ(multimap.Size(), 8);
}

TEST(Multimap, Get) {
  Multimap<int, int> multimap;
  std::vector<int> keys{2, 18, 42, 43};

  // Insert a bunch of keys and values
  for (auto i : keys) {
    for (auto j : keys) {
      multimap.Insert(i, j);
    }
  }
  // Ensure 2 is the value for every key
  for (auto i : keys) {
    EXPECT_EQ(multimap.Get(i), 2);
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
