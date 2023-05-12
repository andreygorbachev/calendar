#include <holiday_schedule.h>
#include <ics_parser.h>
#include <holiday.h>

#include <fstream>
#include <unordered_set>


namespace calendar
{

	inline auto parse_ics_england() -> const holiday_schedule&
	{
		// from https://www.gov.uk/bank-holidays
		static auto calendar = parse_ics("../../test/data/england-and-wales.ics");

		return calendar;
	}

	inline auto parse_ics_united_states() -> const holiday_schedule&
	{
		// from https://www.newyorkfed.org/aboutthefed/holiday_schedule
		static auto calendar = parse_ics("../../test/data/united-states.ics");

		return calendar;
	}


	inline auto make_holiday_schedule_england() -> holiday_schedule
	{
		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto SummerBankHoliday = weekday_last_holiday{ std::chrono::August / std::chrono::Monday[std::chrono::last] };

		auto rules1 = std::unordered_set<const annual_holiday*>{};
		rules1.insert(&NewYearsDay);
		rules1.insert(&GoodFriday);
		rules1.insert(&EasterMonday);
		rules1.insert(&EarlyMayBankHoliday);
		rules1.insert(&SpringBankHoliday);
		rules1.insert(&SummerBankHoliday);
		rules1.insert(&ChristmasDay);
		rules1.insert(&BoxingDay);

		const auto hs2018 = make_holiday_schedule(
			std::chrono::year{ 2018 },
			std::chrono::year{ 2018 },
			rules1
		);

		const auto hs2019 = make_holiday_schedule(
			std::chrono::year{ 2019 },
			std::chrono::year{ 2019 },
			rules1
		);

		const auto VictoryInEuropeDay = named_holiday{ std::chrono::May / std::chrono::day{ 8u } };

		auto rules2 = std::unordered_set<const annual_holiday*>{};
		rules2.insert(&NewYearsDay);
		rules2.insert(&GoodFriday);
		rules2.insert(&EasterMonday);
		rules2.insert(&VictoryInEuropeDay);
		rules2.insert(&SpringBankHoliday);
		rules2.insert(&SummerBankHoliday);
		rules2.insert(&ChristmasDay);
		rules2.insert(&BoxingDay);

		const auto hs2020 = make_holiday_schedule(
			std::chrono::year{ 2020 },
			std::chrono::year{ 2020 },
			rules2
		);

		const auto hs2021 = make_holiday_schedule(
			std::chrono::year{ 2021 },
			std::chrono::year{ 2021 },
			rules1
		);

		const auto SpringBankHoliday2 = named_holiday{ std::chrono::June / std::chrono::day{ 2u } };
		const auto PlatinumJubileeHoliday = named_holiday{ std::chrono::June / std::chrono::day{ 3u } };
		const auto StateFuneral = named_holiday{ std::chrono::September / std::chrono::day{ 19u } }; // Bank Holiday for the State Funeral of Queen Elizabeth II

		auto rules3 = std::unordered_set<const annual_holiday*>{};
		rules3.insert(&NewYearsDay);
		rules3.insert(&GoodFriday);
		rules3.insert(&EasterMonday);
		rules3.insert(&EarlyMayBankHoliday);
		rules3.insert(&SpringBankHoliday2);
		rules3.insert(&PlatinumJubileeHoliday);
		rules3.insert(&SummerBankHoliday);
		rules3.insert(&StateFuneral);
		rules3.insert(&ChristmasDay);
		rules3.insert(&BoxingDay);

		const auto hs2022 = make_holiday_schedule(
			std::chrono::year{ 2022 },
			std::chrono::year{ 2022 },
			rules3
		);

		const auto Coronation = named_holiday{ std::chrono::May / std::chrono::day{ 8u } }; // Bank holiday for the coronation of King Charles III

		auto rules4 = std::unordered_set<const annual_holiday*>{};
		rules4.insert(&NewYearsDay);
		rules4.insert(&GoodFriday);
		rules4.insert(&EasterMonday);
		rules4.insert(&EarlyMayBankHoliday);
		rules4.insert(&Coronation);
		rules4.insert(&SpringBankHoliday);
		rules4.insert(&SummerBankHoliday);
		rules4.insert(&ChristmasDay);
		rules4.insert(&BoxingDay);

		const auto hs2023 = make_holiday_schedule(
			std::chrono::year{ 2023 },
			std::chrono::year{ 2023 },
			rules4
		);

		const auto hs2024 = make_holiday_schedule(
			std::chrono::year{ 2024 },
			std::chrono::year{ 2024 },
			rules1
		);

		const auto hs2025 = make_holiday_schedule(
			std::chrono::year{ 2025 },
			std::chrono::year{ 2025 },
			rules1
		);

		return hs2018 + hs2019 + hs2020 + hs2021 + hs2022 + hs2023 + hs2024 + hs2025;
	}

}
