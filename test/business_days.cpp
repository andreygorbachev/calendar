#include <calendar.h>
#include <business_days.h>

#include <cstddef>
#include <memory>
#include <chrono>

using namespace std;
using namespace std::chrono;



consteval auto make_May_London_calendar() -> calendar
{
	auto hols = calendar::holidays_storage{
		2023y/May/1d,
		2023y/May/8d,
		2023y/May/29d,
	};

	return calendar{ 2023y/May/1d, 2023y/May/31d, move(hols) };
}



consteval auto business_days_tests() -> bool
{
	const auto c1 = make_May_London_calendar();
	const auto bd1 = business_days{ &c1 };

	const auto test1 =
//		!bd1.is_business_day(2023y/May/1d) &&
//		bd1.is_business_day(2023y/May/2d) &&
		bd1.count(2023y/May/1d, 2023y/May/31d) == 0/*uz*/;

	return
		test1;
}


int main()
{
	static_assert(business_days_tests());
}
