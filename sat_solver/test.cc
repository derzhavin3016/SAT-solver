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

TEST(gen, bad)
{
  sat::CNF cnf{
    {2, -3, -4},  {-1, 1, -3}, {-1, -4, 4},  {-1, 3, -1}, {1, 1, -4},
    {-2, -1, -3}, {-3, 4, -3}, {3, 1, 2},    {-4, 1, -2}, {-4, -3, 2},
    {2, 2, 1},    {-2, 4, -2}, {-4, -4, -4}, {2, -4, 4},  {-1, -4, 4},
  };

  auto sol = cnf.solve();

  EXPECT_FALSE(sol.has_value());
}

TEST(gen, good100)
{
  sat::CNF cnf{
    {-17, 20, -11}, {6, 12, 12},    {17, -3, -14},   {-9, -1, 7},
    {3, 11, -8},    {12, 16, 19},   {2, 1, 18},      {-6, 7, 12},
    {-14, 11, 3},   {8, 17, -6},    {-3, 1, 20},     {-9, -4, -18},
    {-7, -18, -6},  {-2, 5, -16},   {9, 13, -10},    {8, -4, 16},
    {-9, 7, -2},    {-11, -4, 20},  {1, 14, 12},     {3, 19, -10},
    {11, 4, 10},    {-9, 17, 13},   {-8, -7, 5},     {-19, 20, -18},
    {-8, 14, -12},  {-12, 10, -4},  {-14, -11, -18}, {9, 19, -10},
    {-19, 10, -16}, {2, -18, -12},  {13, -18, -18},  {10, 6, -13},
    {20, 6, 12},    {-20, 16, 2},   {-14, -8, -7},   {14, -18, -11},
    {10, -10, -11}, {9, 15, -4},    {8, 16, 4},      {-14, 4, -16},
    {-16, 5, -20},  {12, 8, 2},     {-4, 16, -5},    {7, -4, 4},
    {12, -4, 15},   {2, -5, -18},   {-2, 7, -19},    {-17, -11, -1},
    {-13, -2, 15},  {-13, 19, 9},   {6, -6, 2},      {12, -1, 13},
    {-15, 13, -11}, {-14, -17, 19}, {13, -13, 12},   {-15, 20, 2},
    {7, 19, 7},     {9, -16, -15},  {20, 15, -17},   {10, 10, -17},
    {7, 8, 7},      {20, 18, -1},   {9, 6, 18},      {16, 9, 16},
    {-4, -18, -6},  {6, 5, -2},     {16, -2, 19},    {-2, -14, 19},
    {-9, -18, -11}, {-13, 8, 20},   {14, -16, 9},    {-18, 20, 8},
    {-20, -11, -5}, {16, -17, -12}, {19, 20, 20},    {19, -12, 16},
    {18, 14, -12},  {9, -15, 20},   {14, -6, 1},     {17, -5, 11},
    {-3, -16, 20},  {-5, -5, -15},  {-6, -4, 3},     {18, 20, -9},
    {17, 7, 19},    {-3, -8, 16},   {-3, -4, -15},   {1, 6, -4},
    {3, 19, 3},     {2, 3, 4},      {11, 18, 5},     {15, 4, -13},
    {-8, -6, 14},   {15, 7, -5},    {11, -7, -6},    {-16, 3, -13},
    {-10, 12, -19}, {2, -2, 17},    {-14, 16, -9},   {-20, 13, 15},
  };

  const auto sol = cnf.solve();

  ASSERT_TRUE(sol.has_value());
  EXPECT_TRUE(cnf.eval(*sol));
}

TEST(gen, bad300)
{
  sat::CNF cnf{
    {-6, -9, -4},    {20, 9, 19},     {-12, 1, -11},   {-4, 17, -12},
    {-19, -7, 11},   {17, 7, 5},      {2, -14, -14},   {19, -16, -19},
    {-15, 19, -13},  {4, 16, 15},     {-19, 20, 3},    {6, 19, -1},
    {-15, 13, -2},   {-10, 6, 7},     {10, 12, 17},    {15, 16, 11},
    {-15, 16, -8},   {-6, 11, -4},    {-11, 2, -9},    {-10, -10, 20},
    {-13, -18, -16}, {6, -6, -7},     {18, -14, -7},   {12, 18, -2},
    {12, 11, 20},    {16, -1, 12},    {-5, 12, 6},     {-19, -1, 5},
    {-4, 15, 8},     {6, -2, 15},     {-13, 15, 14},   {18, 10, 5},
    {2, -4, -4},     {-17, 1, -15},   {-18, 11, 10},   {6, 11, 18},
    {15, -7, -7},    {8, -5, 1},      {-15, 10, -11},  {9, -2, 20},
    {9, 3, 20},      {18, 8, 11},     {14, 9, 14},     {9, 12, -1},
    {2, -12, -9},    {-5, 4, 11},     {11, -13, -19},  {-6, -12, -14},
    {-17, 14, -5},   {13, -18, 7},    {-15, -7, 17},   {-16, 7, -2},
    {9, 12, -15},    {-12, -2, 1},    {5, -11, -6},    {14, 1, 19},
    {-13, 9, -17},   {14, -19, 15},   {10, 5, 19},     {-5, -6, -11},
    {-11, -11, -19}, {-1, -7, 5},     {18, 11, 7},     {-13, 10, 16},
    {-4, -18, 19},   {3, 1, 10},      {3, 14, -13},    {10, -18, 3},
    {-18, -20, -4},  {-2, 1, -20},    {9, 15, 14},     {-2, 10, 20},
    {19, 17, -3},    {-17, 13, -11},  {-14, 10, 20},   {5, 18, 9},
    {20, -16, -1},   {11, 6, -5},     {18, 20, -2},    {-5, 17, 13},
    {-1, -13, 5},    {19, -8, -5},    {1, 18, 20},     {12, 13, 20},
    {4, 17, 9},      {9, -17, -3},    {-15, -5, -3},   {-14, -9, 19},
    {4, -9, -2},     {-13, 12, 17},   {13, -14, -16},  {-12, 13, 11},
    {3, -1, 11},     {3, -11, 7},     {-7, 18, 10},    {-19, -18, 14},
    {16, 19, 1},     {-8, 16, -13},   {-12, -12, 12},  {18, 13, 2},
    {6, 10, -3},     {-1, 5, 4},      {-9, 17, 8},     {1, -9, -6},
    {-3, 5, -15},    {8, -16, 4},     {-8, 18, -9},    {-20, -6, -4},
    {10, 11, 19},    {-4, 7, 16},     {-7, -1, -9},    {-12, -7, 17},
    {-5, -16, -20},  {-7, -5, -6},    {-17, -16, 19},  {12, -5, 11},
    {-5, 14, -3},    {1, -20, 4},     {-7, 16, -2},    {10, -17, 5},
    {-8, 20, 18},    {18, -18, 11},   {19, -14, -12},  {2, 13, 9},
    {-16, 2, 2},     {9, -7, 1},      {10, -9, 17},    {-18, -9, -9},
    {7, -10, 5},     {9, 18, 7},      {-10, 14, 9},    {-1, -10, 16},
    {8, -1, 20},     {-15, -16, -1},  {20, 20, 7},     {-1, 1, -8},
    {18, -2, -4},    {-17, 15, 6},    {-11, 7, -5},    {19, 6, 8},
    {11, -8, -6},    {17, -12, -1},   {-2, -10, -9},   {16, -6, -14},
    {8, 1, 20},      {16, 7, -4},     {-5, -20, -9},   {-10, -6, -5},
    {9, 1, -5},      {-19, -20, 19},  {-19, 16, -18},  {13, 8, 4},
    {17, 10, -19},   {16, 13, 20},    {-9, 5, -15},    {20, 19, 15},
    {19, 20, -17},   {1, 15, 3},      {-14, 4, -4},    {4, -7, -12},
    {16, -6, 9},     {-14, 16, 3},    {-17, 7, 6},     {17, 15, 3},
    {3, 13, -2},     {-6, 14, 2},     {-1, 3, -13},    {12, -10, 9},
    {-2, -18, 7},    {2, 17, 2},      {-20, 7, 20},    {16, -20, -3},
    {20, 14, -16},   {-4, 2, -10},    {15, 15, 6},     {-2, -17, -1},
    {-15, -18, 7},   {-19, -10, 15},  {6, -5, 9},      {-4, -14, 18},
    {-17, 10, -6},   {20, 4, 19},     {12, -10, 9},    {13, -19, -2},
    {-16, 8, -10},   {-2, 16, -16},   {6, -16, 2},     {8, -20, -18},
    {-11, -1, 14},   {20, -7, 17},    {11, 8, 20},     {-13, -20, 4},
    {-15, 10, -10},  {-20, -20, -12}, {-9, -11, -15},  {-11, -12, 1},
    {12, 4, -18},    {-18, -15, -13}, {1, -20, 9},     {12, -10, 2},
    {-16, 4, 9},     {17, 19, 13},    {17, 17, -12},   {-19, -5, -2},
    {16, -5, -3},    {11, -6, -19},   {-14, 15, -20},  {3, 14, 6},
    {-14, 6, -20},   {1, 17, -16},    {-2, -8, -13},   {2, 5, -12},
    {2, 15, 2},      {7, -15, -7},    {13, -17, -19},  {-6, 20, -19},
    {-3, 9, 1},      {-11, 7, 11},    {16, -4, -17},   {20, 4, 3},
    {15, -20, -14},  {18, -18, -13},  {19, -18, -13},  {14, 15, -11},
    {14, -7, 2},     {-19, 15, 7},    {-18, 11, 16},   {7, -1, -15},
    {8, -11, -14},   {8, -9, -8},     {-13, 11, -20},  {17, 8, -4},
    {-3, 13, 3},     {-14, 11, 17},   {7, -10, -5},    {-8, -18, -16},
    {-19, 12, -3},   {-1, 14, -20},   {-14, -4, 18},   {-7, -3, -3},
    {-10, 16, 1},    {13, 4, 15},     {-17, 2, -11},   {-20, -16, 9},
    {-10, 6, 16},    {-4, -2, -15},   {-3, 18, -13},   {1, 16, -1},
    {1, 1, 15},      {-20, -9, 1},    {-20, -17, -12}, {-20, 6, -7},
    {8, -17, 9},     {-3, 18, 13},    {9, 10, 2},      {16, -2, 15},
    {-17, -16, -20}, {10, -17, 12},   {-10, 14, 1},    {6, 9, -15},
    {15, 6, -13},    {17, -1, -2},    {-13, -9, 12},   {18, -20, -18},
    {20, -19, 6},    {14, 12, 14},    {4, -20, 2},     {-2, -13, -8},
    {4, 16, -1},     {1, 7, 10},      {17, -15, 1},    {-7, 13, 5},
    {5, 12, 14},     {14, 16, -4},    {7, 5, -7},      {3, -14, -4},
    {20, -10, 4},    {-12, 15, -4},   {18, 17, 4},     {-10, -6, -18},
    {-3, -2, 16},    {-11, 17, -14},  {10, -18, 10},   {-13, -13, 3},
    {8, 12, 13},     {-14, -12, -12}, {-2, 3, 6},      {6, 10, 1},
    {6, 14, 13},     {17, -16, -5},   {-7, 5, 20},     {16, -10, -1},
    {1, 1, -9},      {-15, -5, 18},   {-7, 19, -1},    {9, -4, 11},
    {17, -9, 1},     {16, -14, 3},    {-16, 16, 20},   {14, 7, 13},
  };

  auto sol = cnf.solve();

  EXPECT_FALSE(sol.has_value());
}
