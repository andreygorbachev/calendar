#include <calendar.h>

using namespace std;
using namespace std::chrono;


constexpr auto make_April_London_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y/April/7d,
		2023y/April/10d,
	};

	return calendar{ 2023y/April/1d, 2023y/April/30d, move(hols) };
}

constexpr auto make_May_London_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y/May/1d,
		2023y/May/8d,
		2023y/May/29d,
	};

	return calendar{ 2023y/May/1d, 2023y/May/31d, move(hols) };
}

constexpr auto make_May_NewYork_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y/May/29d,
	};

	return calendar{ 2023y/May/1d, 2023y/May/31d, move(hols) };
}

constexpr auto make_empty_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
	};

	return calendar{ 2023y/May/1d, 2023y/May/31d, move(hols) };
}


constexpr auto calendar_tests() -> bool
{
	const auto c1 = make_May_London_calendar();
	const auto c2 = make_empty_calendar();

	const auto test1 =
		c1 != c2 &&
		c1.is_holiday(2023y/May/1d) &&
		!c1.is_weekend(2023y/May/1d) &&
		!c1.is_business_day(2023y/May/1d) &&
		c1.is_business_day(2023y/May/2d);

	const auto c3 = make_May_NewYork_calendar() | c1;
	const auto c4 = make_May_NewYork_calendar() & c1;

	const auto test2 =
		c3 != c1 &&
		c3.is_holiday(2023y/May/1d) &&
		c4 != c1 &&
		c4 != c3 &&
		!c4.is_holiday(2023y/May/1d);
	// add tests for weekend as well

	const auto c5 = make_April_London_calendar() + c1;

	const auto test3 =
		c3.is_holiday(2023y/May/1d);

	return 
		test1 &&
		test2 &&
		test3;
}


int main()
{
	static_assert(calendar_tests());
}
