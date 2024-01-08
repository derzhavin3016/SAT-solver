import sat;

#include <gtest/gtest.h>

TEST(example, test)
{
  constexpr int first = 30;
  constexpr int sec = 12;

  ASSERT_EQ(first + sec, 42);
}

TEST(naive, simple)
{
  sat::CNF cnf{{1, -1, 2}};

  auto sol = cnf.solve();

  ASSERT_TRUE(sol.has_value());
  EXPECT_TRUE(cnf.eval(*sol));
}

TEST(naive, fromExample)
{
  sat::CNF cnf{{1, 2, -3}, {2, 3, -1}};

  auto sol = cnf.solve();

  ASSERT_TRUE(sol.has_value());
  EXPECT_TRUE(cnf.eval(*sol));
}

TEST(naive, bad)
{
  sat::CNF cnf{{1, 1, 1}, {-1, -1, -1}};

  auto sol = cnf.solve();

  EXPECT_FALSE(sol.has_value());
}
