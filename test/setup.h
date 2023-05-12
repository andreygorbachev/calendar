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

		auto rules = std::unordered_set<const annual_holiday*>{};
		rules.insert(&NewYearsDay);
		rules.insert(&GoodFriday);
		rules.insert(&EasterMonday);
		rules.insert(&EarlyMayBankHoliday);
		rules.insert(&SpringBankHoliday);
		rules.insert(&SummerBankHoliday);
		rules.insert(&ChristmasDay);
		rules.insert(&BoxingDay);

		const auto hs2018_2019 = make_holiday_schedule(
			std::chrono::year{ 2018 },
			std::chrono::year{ 2019 },
			rules
		);

		const auto VictoryInEuropeDay = named_holiday{ std::chrono::May / std::chrono::day{ 8u } };

		auto rules2020 = std::unordered_set<const annual_holiday*>{};
		rules2020.insert(&NewYearsDay);
		rules2020.insert(&GoodFriday);
		rules2020.insert(&EasterMonday);
		rules2020.insert(&VictoryInEuropeDay);
		rules2020.insert(&SpringBankHoliday);
		rules2020.insert(&SummerBankHoliday);
		rules2020.insert(&ChristmasDay);
		rules2020.insert(&BoxingDay);

		const auto hs2020 = make_holiday_schedule(
			std::chrono::year{ 2020 },
			std::chrono::year{ 2020 },
			rules2020
		);

		const auto hs2021 = make_holiday_schedule(
			std::chrono::year{ 2021 },
			std::chrono::year{ 2021 },
			rules
		);

		const auto SpringBankHoliday2 = named_holiday{ std::chrono::June / std::chrono::day{ 2u } };
		const auto PlatinumJubileeHoliday = named_holiday{ std::chrono::June / std::chrono::day{ 3u } };
		const auto StateFuneral = named_holiday{ std::chrono::September / std::chrono::day{ 19u } }; // Bank Holiday for the State Funeral of Queen Elizabeth II

		auto rules2022 = std::unordered_set<const annual_holiday*>{};
		rules2022.insert(&NewYearsDay);
		rules2022.insert(&GoodFriday);
		rules2022.insert(&EasterMonday);
		rules2022.insert(&EarlyMayBankHoliday);
		rules2022.insert(&SpringBankHoliday2);
		rules2022.insert(&PlatinumJubileeHoliday);
		rules2022.insert(&SummerBankHoliday);
		rules2022.insert(&StateFuneral);
		rules2022.insert(&ChristmasDay);
		rules2022.insert(&BoxingDay);

		const auto hs2022 = make_holiday_schedule(
			std::chrono::year{ 2022 },
			std::chrono::year{ 2022 },
			rules2022
		);

		const auto Coronation = named_holiday{ std::chrono::May / std::chrono::day{ 8u } }; // Bank holiday for the coronation of King Charles III

		auto rules2023 = std::unordered_set<const annual_holiday*>{};
		rules2023.insert(&NewYearsDay);
		rules2023.insert(&GoodFriday);
		rules2023.insert(&EasterMonday);
		rules2023.insert(&EarlyMayBankHoliday);
		rules2023.insert(&Coronation);
		rules2023.insert(&SpringBankHoliday);
		rules2023.insert(&SummerBankHoliday);
		rules2023.insert(&ChristmasDay);
		rules2023.insert(&BoxingDay);

		const auto hs2023 = make_holiday_schedule(
			std::chrono::year{ 2023 },
			std::chrono::year{ 2023 },
			rules2023
		);

		const auto hs2024_2025 = make_holiday_schedule(
			std::chrono::year{ 2024 },
			std::chrono::year{ 2025 },
			rules
		);

		return hs2018_2019 + hs2020 + hs2021 + hs2022 + hs2023 + hs2024_2025;
	}

	inline auto make_holiday_schedule_united_states() -> holiday_schedule
	{
		const auto MartinLutherKing = weekday_indexed_holiday{ std::chrono::January / std::chrono::Monday[3] }; // Birthday Of Martin Luther King, Jr.
		const auto Washington = weekday_indexed_holiday{ std::chrono::February / std::chrono::Monday[3] }; // Washington's Birthday
		const auto MemorialDay = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto Juneteenth = named_holiday{ std::chrono::June / std::chrono::day{ 19u } }; // Juneteenth National Independence Day
		const auto IndependenceDay = named_holiday{ std::chrono::July / std::chrono::day{ 4u } };
		const auto LaborDay = weekday_indexed_holiday{ std::chrono::September / std::chrono::Monday[1] };
		const auto ColumbusDay = weekday_indexed_holiday{ std::chrono::October / std::chrono::Monday[2] };
		const auto VeteransDay = named_holiday{ std::chrono::November / std::chrono::day{ 11u } };
		const auto ThanksgivingDay = weekday_indexed_holiday{ std::chrono::November / std::chrono::Thursday[4] };

		auto rules = std::unordered_set<const annual_holiday*>{};
		rules.insert(&NewYearsDay);
		rules.insert(&MartinLutherKing);
		rules.insert(&Washington);
		rules.insert(&MemorialDay);
		rules.insert(&Juneteenth);
		rules.insert(&IndependenceDay);
		rules.insert(&LaborDay);
		rules.insert(&ColumbusDay);
		rules.insert(&VeteransDay);
		rules.insert(&ThanksgivingDay);
		rules.insert(&ChristmasDay);

		const auto hs2023_2026 = make_holiday_schedule(
			std::chrono::year{ 2023 },
			std::chrono::year{ 2026 },
			rules
		);

		return hs2023_2026;
	}

}
