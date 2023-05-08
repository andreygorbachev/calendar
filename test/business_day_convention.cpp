#include <business_day_convention.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std::chrono;


namespace
{

	TEST(business_day_convention, following)
	{
		const auto c = test_rule_england();

		EXPECT_EQ(2023y / January / 1d, Following.adjust(2023y / January / 1d, c));
	}

}
