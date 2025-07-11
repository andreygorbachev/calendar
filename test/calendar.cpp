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

#include <period.h>
#include <time_series.h>

#include <weekend.h>
#include <schedule.h>
#include <calendar.h>
#include <business_day_adjusters.h>

#include <gtest/gtest.h>

#include <cstddef>
#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;
using namespace gregorian::util;


namespace gregorian
{

	TEST(calendar, constructor1)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{}
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
			schedule::dates{
				2023y / January / 1d,
			}
		};

		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
				schedule::dates{
					2023y / January / 2d,
				}
			}
		};

		auto c = calendar{
			SaturdaySundayWeekend,
			schedule{
				period{ 2023y / January / 1d, 2023y / January / 31d },
				schedule::dates{
					2023y / January / 1d,
				}
			}
		};
		c.substitute(Following);

		EXPECT_EQ(expected, c);
	}

	TEST(calendar, get_weekend)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{
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
		const auto& c = make_calendar_england();

		EXPECT_TRUE(c.is_non_business_day(2023y / May / 1d));
		EXPECT_FALSE(c.is_non_business_day(2023y / May / 2d));
		EXPECT_THROW(c.is_non_business_day(1y / May / 1d), out_of_range);
		EXPECT_THROW(c.is_non_business_day(9999y / May / 1d), out_of_range);
		EXPECT_FALSE(c.is_non_business_day(2023y / February / 30d)); // not .ok()
	}

	TEST(calendar, is_non_business_day2)
	{
		const auto& c = make_calendar_england();

		EXPECT_TRUE(c.is_non_business_day(sys_days{ 2023y / May / 1d }));
		EXPECT_FALSE(c.is_non_business_day(sys_days{ 2023y / May / 2d }));
		EXPECT_THROW(c.is_non_business_day(sys_days{ 1y / May / 1d }), out_of_range);
		EXPECT_THROW(c.is_non_business_day(sys_days{ 9999y / May / 1d }), out_of_range);
		EXPECT_FALSE(c.is_non_business_day(sys_days{ 2023y / February / 30d })); // not .ok()
	}

	TEST(calendar, is_business_day1)
	{
		const auto& c = make_calendar_england();

		EXPECT_FALSE(c.is_business_day(2023y / May / 1d));
		EXPECT_TRUE(c.is_business_day(2023y / May / 2d));
		EXPECT_THROW(c.is_business_day(1y / May / 1d), out_of_range);
		EXPECT_THROW(c.is_business_day(9999y / May / 1d), out_of_range);
		EXPECT_TRUE(c.is_business_day(2023y / February / 30d)); // not .ok()
	}

	TEST(calendar, is_business_day2)
	{
		const auto& c = make_calendar_england();

		EXPECT_FALSE(c.is_business_day(sys_days{ 2023y / May / 1d }));
		EXPECT_TRUE(c.is_business_day(sys_days{ 2023y / May / 2d }));
		EXPECT_THROW(c.is_business_day(sys_days{ 1y / May / 1d }), out_of_range);
		EXPECT_THROW(c.is_business_day(sys_days{ 9999y / May / 1d }), out_of_range);
		EXPECT_TRUE(c.is_business_day(sys_days{ 2023y / February / 30d })); // not .ok()
	}

	TEST(calendar, count_business_days1)
	{
		const auto& c = make_calendar_england();

		const auto bd1 =
			c.count_business_days(days_period{ 2023y / May / 1d, 2023y / May / 1d });
		const auto bd2 =
			c.count_business_days(days_period{ 2023y / May / 31d, 2023y / May / 31d });
		const auto bd3 =
			c.count_business_days(days_period{ 2023y / April / 28d, 2023y / May / 31d });

		EXPECT_EQ(0uz, bd1);
		EXPECT_EQ(1uz, bd2);
		EXPECT_EQ(21uz, bd3);

		const auto bd4 =
			c.count_business_days(days_period{ 2023y / May / 1d, 2023y / May / 31d }); // from a non-business day
		const auto bd5 =
			c.count_business_days(days_period{ 2023y / April / 28d, 2023y / May / 29d }); // until a non-business day
		const auto bd6 =
			c.count_business_days(days_period{ 2023y / May / 1d, 2023y / May / 29d }); // from a non-business day, until a non-business day

		EXPECT_EQ(20uz, bd4);
		EXPECT_EQ(19uz, bd5);
		EXPECT_EQ(18uz, bd6);
	}

	TEST(calendar, count_business_days2)
	{
		const auto& c = make_calendar_england();

		const auto bd1 =
			c.count_business_days(period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 1d } });
		const auto bd2 =
			c.count_business_days(period{ sys_days{ 2023y / May / 31d }, sys_days{ 2023y / May / 31d } });
		const auto bd3 =
			c.count_business_days(period{ sys_days{ 2023y / April / 28d }, sys_days{ 2023y / May / 31d } });

		EXPECT_EQ(0uz, bd1);
		EXPECT_EQ(1uz, bd2);
		EXPECT_EQ(21uz, bd3);

		const auto bd4 =
			c.count_business_days(period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 31d } }); // from a non-business day
		const auto bd5 =
			c.count_business_days(period{ sys_days{ 2023y / April / 28d }, sys_days{ 2023y / May / 29d } }); // until a non-business day
		const auto bd6 =
			c.count_business_days(period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 29d } }); // from a non-business day, until a non-business day

		EXPECT_EQ(20uz, bd4);
		EXPECT_EQ(19uz, bd5);
		EXPECT_EQ(18uz, bd6);
	}

	// should this be a _time_series_bool test?
	TEST(calendar, count_business_days3)
	{
		const auto cs = time_series<bool>::get_chunk_size();

		const auto& c = make_calendar_england();
		const auto& cp = c.get_schedule().get_period();

		// both from and until are on the boundary of the same chunk
		const auto bd1 =
			c.count_business_days(days_period{
				cp.get_from(),
				sys_days{ cp.get_from() } + days{ cs } - days{ 1 }
			});
		// both from and until are inside of the same chunk
		const auto bd2 =
			c.count_business_days(days_period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } - days{ 1 } - days{ 1 }
			});
		// from is inside the chunk and until is on the boundary of a different chunk
		const auto bd3 =
			c.count_business_days(days_period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 }
			});
		// from is on the boundary of a chunk and until is inside the different chunk
		const auto bd4 =
			c.count_business_days(days_period{
				cp.get_from(),
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 } - days{ 1 }
			});
		// from is on the boundary of a chunk and until is on the boundary of a different chunk
		const auto bd5 =
			c.count_business_days(days_period{
				cp.get_from(),
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 }
			});
		// at least 3 chunks involved
		const auto bd6 =
			c.count_business_days(days_period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } + days{ cs } - days{ 1 } - days{ 1 }
			});

		EXPECT_EQ(45uz, bd1);
		EXPECT_EQ(44uz, bd2);
		EXPECT_EQ(88uz, bd3);
		EXPECT_EQ(87uz, bd4);
		EXPECT_EQ(88uz, bd5);
		EXPECT_EQ(132uz, bd6);
		// we assume 64 days in a chunk
	}

	// should this be a _time_series_bool test?
	TEST(calendar, count_business_days4)
	{
		const auto cs = time_series<bool>::get_chunk_size();

		const auto& c = make_calendar_england();
		const auto& cp = c.get_schedule().get_period();

		// both from and until are on the boundary of the same chunk
		const auto bd1 =
			c.count_business_days(period{
				sys_days{ cp.get_from() },
				sys_days{ cp.get_from() } + days{ cs } - days{ 1 }
			});
		// both from and until are inside of the same chunk
		const auto bd2 =
			c.count_business_days(period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } - days{ 1 } - days{ 1 }
				});
		// from is inside the chunk and until is on the boundary of a different chunk
		const auto bd3 =
			c.count_business_days(period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 }
			});
		// from is on the boundary of a chunk and until is inside the different chunk
		const auto bd4 =
			c.count_business_days(period{
				sys_days{ cp.get_from() },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 } - days{ 1 }
			});
		// from is on the boundary of a chunk and until is on the boundary of a different chunk
		const auto bd5 =
			c.count_business_days(period{
				sys_days{ cp.get_from() },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } - days{ 1 }
			});
		// at least 3 chunks involved
		const auto bd6 =
			c.count_business_days(days_period{
				sys_days{ cp.get_from() } + days{ 1 },
				sys_days{ cp.get_from() } + days{ cs } + days{ cs } + days{ cs } - days{ 1 } - days{ 1 }
			});

		EXPECT_EQ(45uz, bd1);
		EXPECT_EQ(44uz, bd2);
		EXPECT_EQ(88uz, bd3);
		EXPECT_EQ(87uz, bd4);
		EXPECT_EQ(88uz, bd5);
		EXPECT_EQ(132uz, bd6);
		// we assume 64 days in a chunk
	}

	TEST(calendar, make_business_days_schedule1)
	{
		const auto& c = make_calendar_england();

		const auto s1 =
			c.make_business_days_schedule(days_period{ 2023y / May / 1d, 2023y / May / 1d });
		const auto expected_s1 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 1d },
			{
			}
		};
		const auto s2 =
			c.make_business_days_schedule(days_period{ 2023y / May / 31d, 2023y / May / 31d });
		const auto expected_s2 = schedule{
			days_period{ 2023y / May / 31d, 2023y / May / 31d },
			{
				2023y / May / 31d
			}
		};
		const auto s3 =
			c.make_business_days_schedule(days_period{ 2023y / April / 28d, 2023y / May / 31d });
		const auto expected_s3 = schedule{
			days_period{ 2023y / April / 28d, 2023y / May / 31d },
			{
				2023y / April / 28d,
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
				2023y / May / 30d,
				2023y / May / 31d,
			}
		};

		EXPECT_EQ(expected_s1, s1);
		EXPECT_EQ(expected_s2, s2);
		EXPECT_EQ(expected_s3, s3);

		const auto s4 =
			c.make_business_days_schedule(days_period{ 2023y / May / 1d, 2023y / May / 31d }); // from a non-business day
		const auto expected_s4 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 31d },
			{
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
				2023y / May / 30d,
				2023y / May / 31d,
			}
		};
		const auto s5 =
			c.make_business_days_schedule(days_period{ 2023y / April / 28d, 2023y / May / 29d }); // until a non-business day
		const auto expected_s5 = schedule{
			days_period{ 2023y / April / 28d, 2023y / May / 29d },
			{
				2023y / April / 28d,
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
			}
		};
		const auto s6 =
			c.make_business_days_schedule(days_period{ 2023y / May / 1d, 2023y / May / 29d }); // from a non-business day, until a non-business day
		const auto expected_s6 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 29d },
			{
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
			}
		};

		EXPECT_EQ(expected_s4, s4);
		EXPECT_EQ(expected_s5, s5);
		EXPECT_EQ(expected_s6, s6);
	}

	TEST(calendar, make_business_days_schedule2)
	{
		const auto& c = make_calendar_england();

		const auto s1 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 1d } });
		const auto expected_s1 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 1d },
			{
			}
		};
		const auto s2 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / May / 31d }, sys_days{ 2023y / May / 31d } });
		const auto expected_s2 = schedule{
			days_period{ 2023y / May / 31d, 2023y / May / 31d },
			{
				2023y / May / 31d
			}
		};
		const auto s3 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / April / 28d }, sys_days{ 2023y / May / 31d } });
		const auto expected_s3 = schedule{
			days_period{ 2023y / April / 28d, 2023y / May / 31d },
			{
				2023y / April / 28d,
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
				2023y / May / 30d,
				2023y / May / 31d,
			}
		};

		EXPECT_EQ(expected_s1, s1);
		EXPECT_EQ(expected_s2, s2);
		EXPECT_EQ(expected_s3, s3);

		const auto s4 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 31d } }); // from a non-business day
		const auto expected_s4 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 31d },
			{
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
				2023y / May / 30d,
				2023y / May / 31d,
			}
		};
		const auto s5 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / April / 28d }, sys_days{ 2023y / May / 29d } }); // until a non-business day
		const auto expected_s5 = schedule{
			days_period{ 2023y / April / 28d, 2023y / May / 29d },
			{
				2023y / April / 28d,
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
			}
		};
		const auto s6 =
			c.make_business_days_schedule(days_period{ sys_days{ 2023y / May / 1d }, sys_days{ 2023y / May / 29d } }); // from a non-business day, until a non-business day
		const auto expected_s6 = schedule{
			days_period{ 2023y / May / 1d, 2023y / May / 29d },
			{
				2023y / May / 2d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / May / 9d,
				2023y / May / 10d,
				2023y / May / 11d,
				2023y / May / 12d,
				2023y / May / 15d,
				2023y / May / 16d,
				2023y / May / 17d,
				2023y / May / 18d,
				2023y / May / 19d,
				2023y / May / 22d,
				2023y / May / 23d,
				2023y / May / 24d,
				2023y / May / 25d,
				2023y / May / 26d,
			}
		};

		EXPECT_EQ(expected_s4, s4);
		EXPECT_EQ(expected_s5, s5);
		EXPECT_EQ(expected_s6, s6);
	}


	TEST(calendar, operator_equal_to)
	{
		const auto s = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{
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
			schedule::dates{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{
				2023y / January / 1d,
			}
		};

		const auto expected = calendar{
			SaturdaySundayWeekend,
			s_expected
		};

		const auto s1 = schedule{
			period{ 2022y / December / 1d, 2023y / January / 31d },
			schedule::dates{
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
			schedule::dates{
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
			schedule::dates{
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
			schedule::dates{
				2023y / January / 1d,
			}
		};

		const auto c1 = calendar{
			SaturdaySundayWeekend,
			s1
		};

		const auto s2 = schedule{
			period{ 2023y / January / 1d, 2023y / February / 28d },
			schedule::dates{
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
