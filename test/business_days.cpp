#include <business_days.h>

using namespace std::chrono;


constexpr auto make_May_London_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y / May / 1d,
		2023y / May / 8d,
		2023y / May / 29d,
	};

	return calendar{ 2023y / May / 1d, 2023y / May / 31d, move(hols) };
}


constexpr auto business_days_calendar_tests() -> bool
{
	const auto c1 = make_May_London_calendar();

	const auto test1 =
		!c1.is_business_day(2023y/May/1d) &&
		c1.is_business_day(2023y/May/2d);

	return
		test1;
}


int main()
{
	static_assert(business_days_calendar_tests());
}
