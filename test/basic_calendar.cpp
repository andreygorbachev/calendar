#include "..\include\calendar.h"

using namespace std::chrono;


int main()
{
	constexpr auto c1 = basic_calendar{}; // Saturday/Sunday
	constexpr auto c2 = basic_calendar{ basic_calendar::weekend_storage{} }; // no weekend

	static_assert(c1 != c2);

	// Friday
	static_assert(c1.is_business_day({ 2023y/March/24 }));
	static_assert(c2.is_business_day({ 2023y/March/24 }));

	// Saturday
	static_assert(!c1.is_business_day({ 2023y/March/25 }));
	static_assert(c2.is_business_day({ 2023y/March/25 }));

	// Sunday
	static_assert(!c1.is_business_day({ 2023y/March/26 }));
	static_assert(c2.is_business_day({ 2023y/March/26 }));

	// Monday
	static_assert(c1.is_business_day({ 2023y/March/27 }));
	static_assert(c2.is_business_day({ 2023y/March/27 }));
}
