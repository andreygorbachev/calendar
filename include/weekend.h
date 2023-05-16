#pragma once

#include <chrono>
#include <bitset>
#include <memory>


namespace calendar
{

	constexpr auto week_length = std::size_t{ std::chrono::Sunday.iso_encoding() };


	class weekend
	{

	public:

		using storage = std::bitset<week_length>;

	public:

		constexpr explicit weekend(storage we) noexcept;

	public:

		constexpr auto is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	public:

		constexpr auto get_weekend() const noexcept -> const storage&;

	private:

		storage _we;

	};


	const auto SaturdaySundayWeekend = weekend{ weekend::storage{ "1000001" } };
	const auto FridaySaturdayWeekend = weekend{ weekend::storage{ "1100000" } };
	const auto SundayWeekend = weekend{ weekend::storage{ "0000001" } };



	constexpr auto operator|(const weekend& we1, const weekend& we2) -> weekend
	{
		auto we = we1.get_weekend() | we2.get_weekend();

		return weekend{ std::move(we) };
	}

	constexpr auto operator&(const weekend& we1, const weekend& we2) -> weekend
	{
		auto we = we1.get_weekend() & we2.get_weekend();

		return weekend{ std::move(we) };
	}



	constexpr weekend::weekend(storage we) noexcept : _we{ std::move(we) }
	{
	}


	constexpr auto weekend::is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		const auto wd = std::chrono::weekday{ ymd };

		return _we[wd.c_encoding()];
	}

	constexpr auto weekend::get_weekend() const noexcept -> const storage&
	{
		return _we;
	}

}
