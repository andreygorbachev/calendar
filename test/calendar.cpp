#include <calendar.h>

using namespace std;
using namespace std::chrono;


constexpr auto make_May_calendar() -> calendar
{
	auto hols = calendar::holiday_storage{
		2023y/May/1d,
		2023y/May/8d,
		2023y/May/29d,
	};

	return calendar{ move(hols) };
}

constexpr auto make_empty_calendar() -> calendar
{
	auto hols = calendar::holiday_storage{
	};

	return calendar{ move(hols) };
}


constexpr auto calendar_tests() -> bool
{
	const auto c1 = make_May_calendar();
	const auto c2 = make_empty_calendar();

	return c1 != c2;
}


int main()
{
	static_assert(calendar_tests());
}
