#include "gtest/gtest.h"
#include "pow.h"
#include <cmath>

TEST(PowerTest, PositiveIntNos) {
	for (int n = 0; n < 10; n++)
		for (int base = 0; base < 20; ++base)
			EXPECT_DOUBLE_EQ(getPower(n, base), std::pow(n, base));
}

TEST(PowerTest, PositiveFltNos) {
	for (double n = 0; n < 10; n+=0.2)
		for (double base = 0; base < 20; ++base)
			EXPECT_DOUBLE_EQ(getPower(n, base), std::pow(n, base));
}

TEST(PowerTest, NegativeNos) {
	EXPECT_EQ(getPower(1,-1), 0);
	EXPECT_EQ(getPower(1.0,-1.3), 0);
}
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

