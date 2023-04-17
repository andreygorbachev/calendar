#include <calendar.h>

using namespace std::chrono;


int main()
{
	constexpr auto c1 = basic_calendar{}; // weekend on Saturday/Sunday
	constexpr auto c2 = basic_calendar{ basic_calendar::weekend_storage{} }; // no weekend

	static_assert(c1 != c2);

	// Friday
	static_assert(c1.is_business_day({ 2023y/March/24d }));
	static_assert(c2.is_business_day({ 2023y/March/24d }));

	// Saturday
	static_assert(!c1.is_business_day({ 2023y/March/25d }));
	static_assert(c2.is_business_day({ 2023y/March/25d }));

	// Sunday
	static_assert(!c1.is_business_day({ 2023y/March/26d }));
	static_assert(c2.is_business_day({ 2023y/March/26d }));

	// Monday
	static_assert(c1.is_business_day({ 2023y/March/27d }));
	static_assert(c2.is_business_day({ 2023y/March/27d }));
}
