// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <weekend.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_conventions.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	TEST(calendar, constructor1)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c = calendar{
			SaturdaySundayWeekend,
			s
		};

		EXPECT_EQ(SaturdaySundayWeekend, c.get_weekend());
		EXPECT_EQ(s, c.get_schedule());
	}

	TEST(calendar, constructor2)
	{
		// all good business days

		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{}
		};

		const auto c = calendar{
			NoWeekend,
			s
		};

		EXPECT_EQ(NoWeekend, c.get_weekend());
		EXPECT_EQ(s, c.get_schedule());
	}

	TEST(calendar, constructor3)
	{
		// duplicate holidays are ok

		const auto s_expected = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
				2023y / January / 1d,
			}
		};

		const auto c_expected = calendar{
			SaturdaySundayWeekend,
			s_expected
		};

		const auto c = calendar{
			SaturdaySundayWeekend,
			s
		};

		EXPECT_EQ(c_expected, c);
	}

	TEST(calendar, substitute)
	{
		const auto expected = calendar{
			SaturdaySundayWeekend,
			schedule{
				period{ 2023y / January / 1d, 2023y / January / 31d },
				schedule::storage{
					2023y / January / 2d,
				}
			}
		};

		auto c = calendar{
			SaturdaySundayWeekend,
			schedule{
				period{ 2023y / January / 1d, 2023y / January / 31d },
				schedule::storage{
					2023y / January / 1d,
				}
			}
		};
		c.substitute(&Following);

		EXPECT_EQ(expected, c);
	}

	TEST(calendar, get_weekend)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c = calendar{
			SaturdaySundayWeekend,
			s
		};

		EXPECT_EQ(SaturdaySundayWeekend, c.get_weekend());
	}

	TEST(calendar, get_schedule)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c = calendar{
			SaturdaySundayWeekend,
			s
		};

		EXPECT_EQ(s, c.get_schedule());
	}

	TEST(calendar, is_non_business_day1)
	{
		const auto c = make_calendar_england();

		EXPECT_TRUE(c.is_non_business_day(2023y / May / 1d));
		EXPECT_FALSE(c.is_non_business_day(2023y / May / 2d));
		EXPECT_THROW(c.is_non_business_day(1y / May / 1d), out_of_range);
		EXPECT_THROW(c.is_non_business_day(9999y / May / 1d), out_of_range);
	}

	TEST(calendar, is_non_business_day2)
	{
		const auto c = make_calendar_england();

		EXPECT_TRUE(c.is_non_business_day(sys_days{ 2023y / May / 1d }));
		EXPECT_FALSE(c.is_non_business_day(sys_days{ 2023y / May / 2d }));
		EXPECT_THROW(c.is_non_business_day(sys_days{ 1y / May / 1d }), out_of_range);
		EXPECT_THROW(c.is_non_business_day(sys_days{ 9999y / May / 1d }), out_of_range);
	}

	TEST(calendar, is_business_day1)
	{
		const auto c = make_calendar_england();

		EXPECT_FALSE(c.is_business_day(2023y / May / 1d));
		EXPECT_TRUE(c.is_business_day(2023y / May / 2d));
		EXPECT_THROW(c.is_business_day(1y / May / 1d), out_of_range);
		EXPECT_THROW(c.is_business_day(9999y / May / 1d), out_of_range);
	}

	TEST(calendar, is_business_day2)
	{
		const auto c = make_calendar_england();

		EXPECT_FALSE(c.is_business_day(sys_days{ 2023y / May / 1d }));
		EXPECT_TRUE(c.is_business_day(sys_days{ 2023y / May / 2d }));
		EXPECT_THROW(c.is_business_day(sys_days{ 1y / May / 1d }), out_of_range);
		EXPECT_THROW(c.is_business_day(sys_days{ 9999y / May / 1d }), out_of_range);
	}

	TEST(calendar, count_business_days1)
	{
		const auto c = make_calendar_england();

		const auto bd1 = c.count_business_days(days_period{ 2023y / May / 1d, 2023y / May / 1d });
		const auto bd2 = c.count_business_days(days_period{ 2023y / May / 31d, 2023y / May / 31d });
		const auto bd3 = c.count_business_days(days_period{ 2023y / May / 1d, 2023y / May / 31d });

		EXPECT_EQ(0/*uz*/, bd1);
		EXPECT_EQ(1/*uz*/, bd2);
		EXPECT_EQ(20/*uz*/, bd3);
	}

//	TEST(calendar, count_business_days2)
//	{
//		const auto c = make_calendar_england();
//
//		const auto bd1 = c.count_business_days({ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 1d } });
//		const auto bd2 = c.count_business_days({ sys_days{ 2023y / May / 31d }, sys_days{ 2023y / May / 31d } });
//		const auto bd3 = c.count_business_days({ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 31d } });
//
//		EXPECT_EQ(0/*uz*/, bd1);
//		EXPECT_EQ(1/*uz*/, bd2);
//		EXPECT_EQ(20/*uz*/, bd3);
//	}


	TEST(calendar, operator_equal_to)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s
		};

		const auto c2 = calendar{
			SaturdaySundayWeekend,
			s
		};

		EXPECT_TRUE(c1 == c2);
	}

	TEST(calendar, operator_not_equal_to_1)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s
		};

		const auto c2 = calendar{
			SundayWeekend,
			s
		};

		EXPECT_TRUE(c1 != c2);
	}

	TEST(calendar, operator_not_equal_to_2)
	{
		const auto s1 = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 31d,
			}
		};

		const auto c2 = calendar{
			SaturdaySundayWeekend,
			s2
		};

		EXPECT_TRUE(c1 != c2);
	}

	TEST(calendar, operator_not_equal_to_3)
	{
		const auto s1 = schedule{
			period{ 2022y / December / 1d, 2023y / February / 28d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 31d,
			}
		};

		const auto c2 = calendar{
			SaturdaySundayWeekend,
			s2
		};

		EXPECT_TRUE(c1 != c2);
	}

	TEST(calendar, operator_bitwise_and)
	{
		const auto s_expected = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto expected = calendar{
			SaturdaySundayWeekend,
			s_expected
		};

		const auto s1 = schedule{
			period{ 2022y / December / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
				2023y / January / 31d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / February / 28d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c2 = calendar{
			SaturdaySundayWeekend,
			s2
		};

		EXPECT_EQ(expected, c1 & c2);
	}

	TEST(calendar, operator_bitwise_or)
	{
		const auto s_expected = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
				2023y / January / 31d,
			}
		};

		const auto expected = calendar{
			SaturdaySundayWeekend,
			s_expected
		};

		const auto s1 = schedule{
			period{ 2022y / December / 1d, 2023y / January / 31d },
			schedule::storage{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / February / 28d },
			schedule::storage{
				2023y / January / 31d,
			}
		};

		const auto c2 = calendar{
			SaturdaySundayWeekend,
			s2
		};

		EXPECT_EQ(expected, c1 | c2);
	}

}
