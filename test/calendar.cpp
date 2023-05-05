#include <calendar.h>

using namespace std;
using namespace std::chrono;


constexpr auto make_May_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y/May/1d,
		2023y/May/8d,
		2023y/May/29d,
	};

	return calendar{ move(hols) };
}

constexpr auto make_empty_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
	};

	return calendar{ move(hols) };
}


constexpr auto calendar_tests() -> bool
{
	const auto c1 = make_May_calendar();
	const auto c2 = make_empty_calendar();

	return
		c1 != c2 &&
		c1.is_holiday(2023y/May/1d) &&
		!c1.is_weekend(2023y/May/1d) &&
		!c1.is_business_day(2023y/May/1d) &&
		c1.is_business_day(2023y/May/2d);
}


int main()
{
	static_assert(calendar_tests());
}
