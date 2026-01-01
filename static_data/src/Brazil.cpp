// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "static_data.h"
#include "makers.h"

#include <period.h>
#include <schedule.h>
#include <weekend.h>
#include <annual_holidays.h>
#include <business_day_adjusters.h>

#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// should these be inside make_ANBIMA_calendar_versions?
		const auto _TiradentesDay = named_holiday{ April / 21d };
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _ShroveMonday = offset_holiday{ &_Easter, days{ -47 - 1 } }; // should it be in the main library?
		const auto _ShroveTuesday = offset_holiday{ &_Easter, days{ -46 - 1 } }; // should it be in the main library?
		const auto _CorpusChristi = offset_holiday{ &_Easter, days{ 60 } }; // should it be in the main library?
		const auto _IndependenceDay = named_holiday{ September / 7d };
		const auto _OurLadyOfAparecida = named_holiday{ October / 12d };
		const auto _AllSoulsDay = named_holiday{ November / 2d }; // should it be in the main library?
		const auto _RepublicProclamationDay = named_holiday{ November / 15d };
		const auto _BlackConsciousnessDay = named_holiday{ November / 20d };


		// should it be inside make_ANBIMA_calendar_versions?
		static auto _make_ANBIMA_schedule() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
				2001y / January / 1d, // Confraternização Universal
				2001y / February / 26d, // Carnaval
				2001y / February / 27d, // Carnaval
				2001y / April / 13d, // Paixão de Cristo
				2001y / April / 21d, // Tiradentes
				2001y / May / 1d, // Dia do Trabalho
				2001y / June / 14d, // Corpus Christi
				2001y / September / 7d, // Independência do Brasil
				2001y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2001y / November / 2d, // Finados
				2001y / November / 15d, // Proclamação da República
				2001y / December / 25d, // Natal
				2002y / January / 1d, // Confraternização Universal
				2002y / February / 11d, // Carnaval
				2002y / February / 12d, // Carnaval
				2002y / March / 29d, // Paixão de Cristo
				2002y / April / 21d, // Tiradentes
				2002y / May / 1d, // Dia do Trabalho
				2002y / May / 30d, // Corpus Christi
				2002y / September / 7d, // Independência do Brasil
				2002y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2002y / November / 2d, // Finados
				2002y / November / 15d, // Proclamação da República
				2002y / December / 25d, // Natal
				2003y / January / 1d, // Confraternização Universal
				2003y / March / 3d, // Carnaval
				2003y / March / 4d, // Carnaval
				2003y / April / 18d, // Paixão de Cristo
				2003y / April / 21d, // Tiradentes
				2003y / May / 1d, // Dia do Trabalho
				2003y / June / 19d, // Corpus Christi
				2003y / September / 7d, // Independência do Brasil
				2003y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2003y / November / 2d, // Finados
				2003y / November / 15d, // Proclamação da República
				2003y / December / 25d, // Natal
				2004y / January / 1d, // Confraternização Universal
				2004y / February / 23d, // Carnaval
				2004y / February / 24d, // Carnaval
				2004y / April / 9d, // Paixão de Cristo
				2004y / April / 21d, // Tiradentes
				2004y / May / 1d, // Dia do Trabalho
				2004y / June / 10d, // Corpus Christi
				2004y / September / 7d, // Independência do Brasil
				2004y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2004y / November / 2d, // Finados
				2004y / November / 15d, // Proclamação da República
				2004y / December / 25d, // Natal
				2005y / January / 1d, // Confraternização Universal
				2005y / February / 7d, // Carnaval
				2005y / February / 8d, // Carnaval
				2005y / March / 25d, // Paixão de Cristo
				2005y / April / 21d, // Tiradentes
				2005y / May / 1d, // Dia do Trabalho
				2005y / May / 26d, // Corpus Christi
				2005y / September / 7d, // Independência do Brasil
				2005y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2005y / November / 2d, // Finados
				2005y / November / 15d, // Proclamação da República
				2005y / December / 25d, // Natal
				2006y / January / 1d, // Confraternização Universal
				2006y / February / 27d, // Carnaval
				2006y / February / 28d, // Carnaval
				2006y / April / 14d, // Paixão de Cristo
				2006y / April / 21d, // Tiradentes
				2006y / May / 1d, // Dia do Trabalho
				2006y / June / 15d, // Corpus Christi
				2006y / September / 7d, // Independência do Brasil
				2006y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2006y / November / 2d, // Finados
				2006y / November / 15d, // Proclamação da República
				2006y / December / 25d, // Natal
				2007y / January / 1d, // Confraternização Universal
				2007y / February / 19d, // Carnaval
				2007y / February / 20d, // Carnaval
				2007y / April / 6d, // Paixão de Cristo
				2007y / April / 21d, // Tiradentes
				2007y / May / 1d, // Dia do Trabalho
				2007y / June / 7d, // Corpus Christi
				2007y / September / 7d, // Independência do Brasil
				2007y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2007y / November / 2d, // Finados
				2007y / November / 15d, // Proclamação da República
				2007y / December / 25d, // Natal
				2008y / January / 1d, // Confraternização Universal
				2008y / February / 4d, // Carnaval
				2008y / February / 5d, // Carnaval
				2008y / March / 21d, // Paixão de Cristo
				2008y / April / 21d, // Tiradentes
				2008y / May / 1d, // Dia do Trabalho
				2008y / May / 22d, // Corpus Christi
				2008y / September / 7d, // Independência do Brasil
				2008y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2008y / November / 2d, // Finados
				2008y / November / 15d, // Proclamação da República
				2008y / December / 25d, // Natal
				2009y / January / 1d, // Confraternização Universal
				2009y / February / 23d, // Carnaval
				2009y / February / 24d, // Carnaval
				2009y / April / 10d, // Paixão de Cristo
				2009y / April / 21d, // Tiradentes
				2009y / May / 1d, // Dia do Trabalho
				2009y / June / 11d, // Corpus Christi
				2009y / September / 7d, // Independência do Brasil
				2009y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2009y / November / 2d, // Finados
				2009y / November / 15d, // Proclamação da República
				2009y / December / 25d, // Natal
				2010y / January / 1d, // Confraternização Universal
				2010y / February / 15d, // Carnaval
				2010y / February / 16d, // Carnaval
				2010y / April / 2d, // Paixão de Cristo
				2010y / April / 21d, // Tiradentes
				2010y / May / 1d, // Dia do Trabalho
				2010y / June / 3d, // Corpus Christi
				2010y / September / 7d, // Independência do Brasil
				2010y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2010y / November / 2d, // Finados
				2010y / November / 15d, // Proclamação da República
				2010y / December / 25d, // Natal
				2011y / January / 1d, // Confraternização Universal
				2011y / March / 7d, // Carnaval
				2011y / March / 8d, // Carnaval
				2011y / April / 21d, // Tiradentes
				2011y / April / 22d, // Paixão de Cristo
				2011y / May / 1d, // Dia do Trabalho
				2011y / June / 23d, // Corpus Christi
				2011y / September / 7d, // Independência do Brasil
				2011y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2011y / November / 2d, // Finados
				2011y / November / 15d, // Proclamação da República
				2011y / December / 25d, // Natal
				2012y / January / 1d, // Confraternização Universal
				2012y / February / 20d, // Carnaval
				2012y / February / 21d, // Carnaval
				2012y / April / 6d, // Paixão de Cristo
				2012y / April / 21d, // Tiradentes
				2012y / May / 1d, // Dia do Trabalho
				2012y / June / 7d, // Corpus Christi
				2012y / September / 7d, // Independência do Brasil
				2012y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2012y / November / 2d, // Finados
				2012y / November / 15d, // Proclamação da República
				2012y / December / 25d, // Natal
				2013y / January / 1d, // Confraternização Universal
				2013y / February / 11d, // Carnaval
				2013y / February / 12d, // Carnaval
				2013y / March / 29d, // Paixão de Cristo
				2013y / April / 21d, // Tiradentes
				2013y / May / 1d, // Dia do Trabalho
				2013y / May / 30d, // Corpus Christi
				2013y / September / 7d, // Independência do Brasil
				2013y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2013y / November / 2d, // Finados
				2013y / November / 15d, // Proclamação da República
				2013y / December / 25d, // Natal
				2014y / January / 1d, // Confraternização Universal
				2014y / March / 3d, // Carnaval
				2014y / March / 4d, // Carnaval
				2014y / April / 18d, // Paixão de Cristo
				2014y / April / 21d, // Tiradentes
				2014y / May / 1d, // Dia do Trabalho
				2014y / June / 19d, // Corpus Christi
				2014y / September / 7d, // Independência do Brasil
				2014y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2014y / November / 2d, // Finados
				2014y / November / 15d, // Proclamação da República
				2014y / December / 25d, // Natal
				2015y / January / 1d, // Confraternização Universal
				2015y / February / 16d, // Carnaval
				2015y / February / 17d, // Carnaval
				2015y / April / 3d, // Paixão de Cristo
				2015y / April / 21d, // Tiradentes
				2015y / May / 1d, // Dia do Trabalho
				2015y / June / 4d, // Corpus Christi
				2015y / September / 7d, // Independência do Brasil
				2015y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2015y / November / 2d, // Finados
				2015y / November / 15d, // Proclamação da República
				2015y / December / 25d, // Natal
				2016y / January / 1d, // Confraternização Universal
				2016y / February / 8d, // Carnaval
				2016y / February / 9d, // Carnaval
				2016y / March / 25d, // Paixão de Cristo
				2016y / April / 21d, // Tiradentes
				2016y / May / 1d, // Dia do Trabalho
				2016y / May / 26d, // Corpus Christi
				2016y / September / 7d, // Independência do Brasil
				2016y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2016y / November / 2d, // Finados
				2016y / November / 15d, // Proclamação da República
				2016y / December / 25d, // Natal
				2017y / January / 1d, // Confraternização Universal
				2017y / February / 27d, // Carnaval
				2017y / February / 28d, // Carnaval
				2017y / April / 14d, // Paixão de Cristo
				2017y / April / 21d, // Tiradentes
				2017y / May / 1d, // Dia do Trabalho
				2017y / June / 15d, // Corpus Christi
				2017y / September / 7d, // Independência do Brasil
				2017y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2017y / November / 2d, // Finados
				2017y / November / 15d, // Proclamação da República
				2017y / December / 25d, // Natal
				2018y / January / 1d, // Confraternização Universal
				2018y / February / 12d, // Carnaval
				2018y / February / 13d, // Carnaval
				2018y / March / 30d, // Paixão de Cristo
				2018y / April / 21d, // Tiradentes
				2018y / May / 1d, // Dia do Trabalho
				2018y / May / 31d, // Corpus Christi
				2018y / September / 7d, // Independência do Brasil
				2018y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2018y / November / 2d, // Finados
				2018y / November / 15d, // Proclamação da República
				2018y / December / 25d, // Natal
				2019y / January / 1d, // Confraternização Universal
				2019y / March / 4d, // Carnaval
				2019y / March / 5d, // Carnaval
				2019y / April / 19d, // Paixão de Cristo
				2019y / April / 21d, // Tiradentes
				2019y / May / 1d, // Dia do Trabalho
				2019y / June / 20d, // Corpus Christi
				2019y / September / 7d, // Independência do Brasil
				2019y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2019y / November / 2d, // Finados
				2019y / November / 15d, // Proclamação da República
				2019y / December / 25d, // Natal
				2020y / January / 1d, // Confraternização Universal
				2020y / February / 24d, // Carnaval
				2020y / February / 25d, // Carnaval
				2020y / April / 10d, // Paixão de Cristo
				2020y / April / 21d, // Tiradentes
				2020y / May / 1d, // Dia do Trabalho
				2020y / June / 11d, // Corpus Christi
				2020y / September / 7d, // Independência do Brasil
				2020y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2020y / November / 2d, // Finados
				2020y / November / 15d, // Proclamação da República
				2020y / December / 25d, // Natal
				2021y / January / 1d, // Confraternização Universal
				2021y / February / 15d, // Carnaval
				2021y / February / 16d, // Carnaval
				2021y / April / 2d, // Paixão de Cristo
				2021y / April / 21d, // Tiradentes
				2021y / May / 1d, // Dia do Trabalho
				2021y / June / 3d, // Corpus Christi
				2021y / September / 7d, // Independência do Brasil
				2021y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2021y / November / 2d, // Finados
				2021y / November / 15d, // Proclamação da República
				2021y / December / 25d, // Natal
				2022y / January / 1d, // Confraternização Universal
				2022y / February / 28d, // Carnaval
				2022y / March / 1d, // Carnaval
				2022y / April / 15d, // Paixão de Cristo
				2022y / April / 21d, // Tiradentes
				2022y / May / 1d, // Dia do Trabalho
				2022y / June / 16d, // Corpus Christi
				2022y / September / 7d, // Independência do Brasil
				2022y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2022y / November / 2d, // Finados
				2022y / November / 15d, // Proclamação da República
				2022y / December / 25d, // Natal
				2023y / January / 1d, // Confraternização Universal
				2023y / February / 20d, // Carnaval
				2023y / February / 21d, // Carnaval
				2023y / April / 7d, // Paixão de Cristo
				2023y / April / 21d, // Tiradentes
				2023y / May / 1d, // Dia do Trabalho
				2023y / June / 8d, // Corpus Christi
				2023y / September / 7d, // Independência do Brasil
				2023y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2023y / November / 2d, // Finados
				2023y / November / 15d, // Proclamação da República
				2023y / December / 25d, // Natal
				2024y / January / 1d, // Confraternização Universal
				2024y / February / 12d, // Carnaval
				2024y / February / 13d, // Carnaval
				2024y / March / 29d, // Paixão de Cristo
				2024y / April / 21d, // Tiradentes
				2024y / May / 1d, // Dia do Trabalho
				2024y / May / 30d, // Corpus Christi
				2024y / September / 7d, // Independência do Brasil
				2024y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2024y / November / 2d, // Finados
				2024y / November / 15d, // Proclamação da República
				2024y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2024y / December / 25d, // Natal
				2025y / January / 1d, // Confraternização Universal
				2025y / March / 3d, // Carnaval
				2025y / March / 4d, // Carnaval
				2025y / April / 18d, // Paixão de Cristo
				2025y / April / 21d, // Tiradentes
				2025y / May / 1d, // Dia do Trabalho
				2025y / June / 19d, // Corpus Christi
				2025y / September / 7d, // Independência do Brasil
				2025y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2025y / November / 2d, // Finados
				2025y / November / 15d, // Proclamação da República
				2025y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2025y / December / 25d, // Natal
				2026y / January / 1d, // Confraternização Universal
				2026y / February / 16d, // Carnaval
				2026y / February / 17d, // Carnaval
				2026y / April / 3d, // Paixão de Cristo
				2026y / April / 21d, // Tiradentes
				2026y / May / 1d, // Dia do Trabalho
				2026y / June / 4d, // Corpus Christi
				2026y / September / 7d, // Independência do Brasil
				2026y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2026y / November / 2d, // Finados
				2026y / November / 15d, // Proclamação da República
				2026y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2026y / December / 25d, // Natal
				2027y / January / 1d, // Confraternização Universal
				2027y / February / 8d, // Carnaval
				2027y / February / 9d, // Carnaval
				2027y / March / 26d, // Paixão de Cristo
				2027y / April / 21d, // Tiradentes
				2027y / May / 1d, // Dia do Trabalho
				2027y / May / 27d, // Corpus Christi
				2027y / September / 7d, // Independência do Brasil
				2027y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2027y / November / 2d, // Finados
				2027y / November / 15d, // Proclamação da República
				2027y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2027y / December / 25d, // Natal
				2028y / January / 1d, // Confraternização Universal
				2028y / February / 28d, // Carnaval
				2028y / February / 29d, // Carnaval
				2028y / April / 14d, // Paixão de Cristo
				2028y / April / 21d, // Tiradentes
				2028y / May / 1d, // Dia do Trabalho
				2028y / June / 15d, // Corpus Christi
				2028y / September / 7d, // Independência do Brasil
				2028y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2028y / November / 2d, // Finados
				2028y / November / 15d, // Proclamação da República
				2028y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2028y / December / 25d, // Natal
				2029y / January / 1d, // Confraternização Universal
				2029y / February / 12d, // Carnaval
				2029y / February / 13d, // Carnaval
				2029y / March / 30d, // Paixão de Cristo
				2029y / April / 21d, // Tiradentes
				2029y / May / 1d, // Dia do Trabalho
				2029y / May / 31d, // Corpus Christi
				2029y / September / 7d, // Independência do Brasil
				2029y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2029y / November / 2d, // Finados
				2029y / November / 15d, // Proclamação da República
				2029y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2029y / December / 25d, // Natal
				2030y / January / 1d, // Confraternização Universal
				2030y / March / 4d, // Carnaval
				2030y / March / 5d, // Carnaval
				2030y / April / 19d, // Paixão de Cristo
				2030y / April / 21d, // Tiradentes
				2030y / May / 1d, // Dia do Trabalho
				2030y / June / 20d, // Corpus Christi
				2030y / September / 7d, // Independência do Brasil
				2030y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2030y / November / 2d, // Finados
				2030y / November / 15d, // Proclamação da República
				2030y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2030y / December / 25d, // Natal
				2031y / January / 1d, // Confraternização Universal
				2031y / February / 24d, // Carnaval
				2031y / February / 25d, // Carnaval
				2031y / April / 11d, // Paixão de Cristo
				2031y / April / 21d, // Tiradentes
				2031y / May / 1d, // Dia do Trabalho
				2031y / June / 12d, // Corpus Christi
				2031y / September / 7d, // Independência do Brasil
				2031y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2031y / November / 2d, // Finados
				2031y / November / 15d, // Proclamação da República
				2031y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2031y / December / 25d, // Natal
				2032y / January / 1d, // Confraternização Universal
				2032y / February / 9d, // Carnaval
				2032y / February / 10d, // Carnaval
				2032y / March / 26d, // Paixão de Cristo
				2032y / April / 21d, // Tiradentes
				2032y / May / 1d, // Dia do Trabalho
				2032y / May / 27d, // Corpus Christi
				2032y / September / 7d, // Independência do Brasil
				2032y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2032y / November / 2d, // Finados
				2032y / November / 15d, // Proclamação da República
				2032y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2032y / December / 25d, // Natal
				2033y / January / 1d, // Confraternização Universal
				2033y / February / 28d, // Carnaval
				2033y / March / 1d, // Carnaval
				2033y / April / 15d, // Paixão de Cristo
				2033y / April / 21d, // Tiradentes
				2033y / May / 1d, // Dia do Trabalho
				2033y / June / 16d, // Corpus Christi
				2033y / September / 7d, // Independência do Brasil
				2033y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2033y / November / 2d, // Finados
				2033y / November / 15d, // Proclamação da República
				2033y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2033y / December / 25d, // Natal
				2034y / January / 1d, // Confraternização Universal
				2034y / February / 20d, // Carnaval
				2034y / February / 21d, // Carnaval
				2034y / April / 7d, // Paixão de Cristo
				2034y / April / 21d, // Tiradentes
				2034y / May / 1d, // Dia do Trabalho
				2034y / June / 8d, // Corpus Christi
				2034y / September / 7d, // Independência do Brasil
				2034y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2034y / November / 2d, // Finados
				2034y / November / 15d, // Proclamação da República
				2034y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2034y / December / 25d, // Natal
				2035y / January / 1d, // Confraternização Universal
				2035y / February / 5d, // Carnaval
				2035y / February / 6d, // Carnaval
				2035y / March / 23d, // Paixão de Cristo
				2035y / April / 21d, // Tiradentes
				2035y / May / 1d, // Dia do Trabalho
				2035y / May / 24d, // Corpus Christi
				2035y / September / 7d, // Independência do Brasil
				2035y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2035y / November / 2d, // Finados
				2035y / November / 15d, // Proclamação da República
				2035y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2035y / December / 25d, // Natal
				2036y / January / 1d, // Confraternização Universal
				2036y / February / 25d, // Carnaval
				2036y / February / 26d, // Carnaval
				2036y / April / 11d, // Paixão de Cristo
				2036y / April / 21d, // Tiradentes
				2036y / May / 1d, // Dia do Trabalho
				2036y / June / 12d, // Corpus Christi
				2036y / September / 7d, // Independência do Brasil
				2036y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2036y / November / 2d, // Finados
				2036y / November / 15d, // Proclamação da República
				2036y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2036y / December / 25d, // Natal
				2037y / January / 1d, // Confraternização Universal
				2037y / February / 16d, // Carnaval
				2037y / February / 17d, // Carnaval
				2037y / April / 3d, // Paixão de Cristo
				2037y / April / 21d, // Tiradentes
				2037y / May / 1d, // Dia do Trabalho
				2037y / June / 4d, // Corpus Christi
				2037y / September / 7d, // Independência do Brasil
				2037y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2037y / November / 2d, // Finados
				2037y / November / 15d, // Proclamação da República
				2037y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2037y / December / 25d, // Natal
				2038y / January / 1d, // Confraternização Universal
				2038y / March / 8d, // Carnaval
				2038y / March / 9d, // Carnaval
				2038y / April / 21d, // Tiradentes
				2038y / April / 23d, // Paixão de Cristo
				2038y / May / 1d, // Dia do Trabalho
				2038y / June / 24d, // Corpus Christi
				2038y / September / 7d, // Independência do Brasil
				2038y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2038y / November / 2d, // Finados
				2038y / November / 15d, // Proclamação da República
				2038y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2038y / December / 25d, // Natal
				2039y / January / 1d, // Confraternização Universal
				2039y / February / 21d, // Carnaval
				2039y / February / 22d, // Carnaval
				2039y / April / 8d, // Paixão de Cristo
				2039y / April / 21d, // Tiradentes
				2039y / May / 1d, // Dia do Trabalho
				2039y / June / 9d, // Corpus Christi
				2039y / September / 7d, // Independência do Brasil
				2039y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2039y / November / 2d, // Finados
				2039y / November / 15d, // Proclamação da República
				2039y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2039y / December / 25d, // Natal
				2040y / January / 1d, // Confraternização Universal
				2040y / February / 13d, // Carnaval
				2040y / February / 14d, // Carnaval
				2040y / March / 30d, // Paixão de Cristo
				2040y / April / 21d, // Tiradentes
				2040y / May / 1d, // Dia do Trabalho
				2040y / May / 31d, // Corpus Christi
				2040y / September / 7d, // Independência do Brasil
				2040y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2040y / November / 2d, // Finados
				2040y / November / 15d, // Proclamação da República
				2040y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2040y / December / 25d, // Natal
				2041y / January / 1d, // Confraternização Universal
				2041y / March / 4d, // Carnaval
				2041y / March / 5d, // Carnaval
				2041y / April / 19d, // Paixão de Cristo
				2041y / April / 21d, // Tiradentes
				2041y / May / 1d, // Dia do Trabalho
				2041y / June / 20d, // Corpus Christi
				2041y / September / 7d, // Independência do Brasil
				2041y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2041y / November / 2d, // Finados
				2041y / November / 15d, // Proclamação da República
				2041y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2041y / December / 25d, // Natal
				2042y / January / 1d, // Confraternização Universal
				2042y / February / 17d, // Carnaval
				2042y / February / 18d, // Carnaval
				2042y / April / 4d, // Paixão de Cristo
				2042y / April / 21d, // Tiradentes
				2042y / May / 1d, // Dia do Trabalho
				2042y / June / 5d, // Corpus Christi
				2042y / September / 7d, // Independência do Brasil
				2042y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2042y / November / 2d, // Finados
				2042y / November / 15d, // Proclamação da República
				2042y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2042y / December / 25d, // Natal
				2043y / January / 1d, // Confraternização Universal
				2043y / February / 9d, // Carnaval
				2043y / February / 10d, // Carnaval
				2043y / March / 27d, // Paixão de Cristo
				2043y / April / 21d, // Tiradentes
				2043y / May / 1d, // Dia do Trabalho
				2043y / May / 28d, // Corpus Christi
				2043y / September / 7d, // Independência do Brasil
				2043y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2043y / November / 2d, // Finados
				2043y / November / 15d, // Proclamação da República
				2043y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2043y / December / 25d, // Natal
				2044y / January / 1d, // Confraternização Universal
				2044y / February / 29d, // Carnaval
				2044y / March / 1d, // Carnaval
				2044y / April / 15d, // Paixão de Cristo
				2044y / April / 21d, // Tiradentes
				2044y / May / 1d, // Dia do Trabalho
				2044y / June / 16d, // Corpus Christi
				2044y / September / 7d, // Independência do Brasil
				2044y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2044y / November / 2d, // Finados
				2044y / November / 15d, // Proclamação da República
				2044y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2044y / December / 25d, // Natal
				2045y / January / 1d, // Confraternização Universal
				2045y / February / 20d, // Carnaval
				2045y / February / 21d, // Carnaval
				2045y / April / 7d, // Paixão de Cristo
				2045y / April / 21d, // Tiradentes
				2045y / May / 1d, // Dia do Trabalho
				2045y / June / 8d, // Corpus Christi
				2045y / September / 7d, // Independência do Brasil
				2045y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2045y / November / 2d, // Finados
				2045y / November / 15d, // Proclamação da República
				2045y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2045y / December / 25d, // Natal
				2046y / January / 1d, // Confraternização Universal
				2046y / February / 5d, // Carnaval
				2046y / February / 6d, // Carnaval
				2046y / March / 23d, // Paixão de Cristo
				2046y / April / 21d, // Tiradentes
				2046y / May / 1d, // Dia do Trabalho
				2046y / May / 24d, // Corpus Christi
				2046y / September / 7d, // Independência do Brasil
				2046y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2046y / November / 2d, // Finados
				2046y / November / 15d, // Proclamação da República
				2046y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2046y / December / 25d, // Natal
				2047y / January / 1d, // Confraternização Universal
				2047y / February / 25d, // Carnaval
				2047y / February / 26d, // Carnaval
				2047y / April / 12d, // Paixão de Cristo
				2047y / April / 21d, // Tiradentes
				2047y / May / 1d, // Dia do Trabalho
				2047y / June / 13d, // Corpus Christi
				2047y / September / 7d, // Independência do Brasil
				2047y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2047y / November / 2d, // Finados
				2047y / November / 15d, // Proclamação da República
				2047y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2047y / December / 25d, // Natal
				2048y / January / 1d, // Confraternização Universal
				2048y / February / 17d, // Carnaval
				2048y / February / 18d, // Carnaval
				2048y / April / 3d, // Paixão de Cristo
				2048y / April / 21d, // Tiradentes
				2048y / May / 1d, // Dia do Trabalho
				2048y / June / 4d, // Corpus Christi
				2048y / September / 7d, // Independência do Brasil
				2048y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2048y / November / 2d, // Finados
				2048y / November / 15d, // Proclamação da República
				2048y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2048y / December / 25d, // Natal
				2049y / January / 1d, // Confraternização Universal
				2049y / March / 1d, // Carnaval
				2049y / March / 2d, // Carnaval
				2049y / April / 16d, // Paixão de Cristo
				2049y / April / 21d, // Tiradentes
				2049y / May / 1d, // Dia do Trabalho
				2049y / June / 17d, // Corpus Christi
				2049y / September / 7d, // Independência do Brasil
				2049y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2049y / November / 2d, // Finados
				2049y / November / 15d, // Proclamação da República
				2049y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2049y / December / 25d, // Natal
				2050y / January / 1d, // Confraternização Universal
				2050y / February / 21d, // Carnaval
				2050y / February / 22d, // Carnaval
				2050y / April / 8d, // Paixão de Cristo
				2050y / April / 21d, // Tiradentes
				2050y / May / 1d, // Dia do Trabalho
				2050y / June / 9d, // Corpus Christi
				2050y / September / 7d, // Independência do Brasil
				2050y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2050y / November / 2d, // Finados
				2050y / November / 15d, // Proclamação da República
				2050y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2050y / December / 25d, // Natal
				2051y / January / 1d, // Confraternização Universal
				2051y / February / 13d, // Carnaval
				2051y / February / 14d, // Carnaval
				2051y / March / 31d, // Paixão de Cristo
				2051y / April / 21d, // Tiradentes
				2051y / May / 1d, // Dia do Trabalho
				2051y / June / 1d, // Corpus Christi
				2051y / September / 7d, // Independência do Brasil
				2051y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2051y / November / 2d, // Finados
				2051y / November / 15d, // Proclamação da República
				2051y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2051y / December / 25d, // Natal
				2052y / January / 1d, // Confraternização Universal
				2052y / March / 4d, // Carnaval
				2052y / March / 5d, // Carnaval
				2052y / April / 19d, // Paixão de Cristo
				2052y / April / 21d, // Tiradentes
				2052y / May / 1d, // Dia do Trabalho
				2052y / June / 20d, // Corpus Christi
				2052y / September / 7d, // Independência do Brasil
				2052y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2052y / November / 2d, // Finados
				2052y / November / 15d, // Proclamação da República
				2052y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2052y / December / 25d, // Natal
				2053y / January / 1d, // Confraternização Universal
				2053y / February / 17d, // Carnaval
				2053y / February / 18d, // Carnaval
				2053y / April / 4d, // Paixão de Cristo
				2053y / April / 21d, // Tiradentes
				2053y / May / 1d, // Dia do Trabalho
				2053y / June / 5d, // Corpus Christi
				2053y / September / 7d, // Independência do Brasil
				2053y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2053y / November / 2d, // Finados
				2053y / November / 15d, // Proclamação da República
				2053y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2053y / December / 25d, // Natal
				2054y / January / 1d, // Confraternização Universal
				2054y / February / 9d, // Carnaval
				2054y / February / 10d, // Carnaval
				2054y / March / 27d, // Paixão de Cristo
				2054y / April / 21d, // Tiradentes
				2054y / May / 1d, // Dia do Trabalho
				2054y / May / 28d, // Corpus Christi
				2054y / September / 7d, // Independência do Brasil
				2054y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2054y / November / 2d, // Finados
				2054y / November / 15d, // Proclamação da República
				2054y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2054y / December / 25d, // Natal
				2055y / January / 1d, // Confraternização Universal
				2055y / March / 1d, // Carnaval
				2055y / March / 2d, // Carnaval
				2055y / April / 16d, // Paixão de Cristo
				2055y / April / 21d, // Tiradentes
				2055y / May / 1d, // Dia do Trabalho
				2055y / June / 17d, // Corpus Christi
				2055y / September / 7d, // Independência do Brasil
				2055y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2055y / November / 2d, // Finados
				2055y / November / 15d, // Proclamação da República
				2055y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2055y / December / 25d, // Natal
				2056y / January / 1d, // Confraternização Universal
				2056y / February / 14d, // Carnaval
				2056y / February / 15d, // Carnaval
				2056y / March / 31d, // Paixão de Cristo
				2056y / April / 21d, // Tiradentes
				2056y / May / 1d, // Dia do Trabalho
				2056y / June / 1d, // Corpus Christi
				2056y / September / 7d, // Independência do Brasil
				2056y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2056y / November / 2d, // Finados
				2056y / November / 15d, // Proclamação da República
				2056y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2056y / December / 25d, // Natal
				2057y / January / 1d, // Confraternização Universal
				2057y / March / 5d, // Carnaval
				2057y / March / 6d, // Carnaval
				2057y / April / 20d, // Paixão de Cristo
				2057y / April / 21d, // Tiradentes
				2057y / May / 1d, // Dia do Trabalho
				2057y / June / 21d, // Corpus Christi
				2057y / September / 7d, // Independência do Brasil
				2057y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2057y / November / 2d, // Finados
				2057y / November / 15d, // Proclamação da República
				2057y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2057y / December / 25d, // Natal
				2058y / January / 1d, // Confraternização Universal
				2058y / February / 25d, // Carnaval
				2058y / February / 26d, // Carnaval
				2058y / April / 12d, // Paixão de Cristo
				2058y / April / 21d, // Tiradentes
				2058y / May / 1d, // Dia do Trabalho
				2058y / June / 13d, // Corpus Christi
				2058y / September / 7d, // Independência do Brasil
				2058y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2058y / November / 2d, // Finados
				2058y / November / 15d, // Proclamação da República
				2058y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2058y / December / 25d, // Natal
				2059y / January / 1d, // Confraternização Universal
				2059y / February / 10d, // Carnaval
				2059y / February / 11d, // Carnaval
				2059y / March / 28d, // Paixão de Cristo
				2059y / April / 21d, // Tiradentes
				2059y / May / 1d, // Dia do Trabalho
				2059y / May / 29d, // Corpus Christi
				2059y / September / 7d, // Independência do Brasil
				2059y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2059y / November / 2d, // Finados
				2059y / November / 15d, // Proclamação da República
				2059y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2059y / December / 25d, // Natal
				2060y / January / 1d, // Confraternização Universal
				2060y / March / 1d, // Carnaval
				2060y / March / 2d, // Carnaval
				2060y / April / 16d, // Paixão de Cristo
				2060y / April / 21d, // Tiradentes
				2060y / May / 1d, // Dia do Trabalho
				2060y / June / 17d, // Corpus Christi
				2060y / September / 7d, // Independência do Brasil
				2060y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2060y / November / 2d, // Finados
				2060y / November / 15d, // Proclamação da República
				2060y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2060y / December / 25d, // Natal
				2061y / January / 1d, // Confraternização Universal
				2061y / February / 21d, // Carnaval
				2061y / February / 22d, // Carnaval
				2061y / April / 8d, // Paixão de Cristo
				2061y / April / 21d, // Tiradentes
				2061y / May / 1d, // Dia do Trabalho
				2061y / June / 9d, // Corpus Christi
				2061y / September / 7d, // Independência do Brasil
				2061y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2061y / November / 2d, // Finados
				2061y / November / 15d, // Proclamação da República
				2061y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2061y / December / 25d, // Natal
				2062y / January / 1d, // Confraternização Universal
				2062y / February / 6d, // Carnaval
				2062y / February / 7d, // Carnaval
				2062y / March / 24d, // Paixão de Cristo
				2062y / April / 21d, // Tiradentes
				2062y / May / 1d, // Dia do Trabalho
				2062y / May / 25d, // Corpus Christi
				2062y / September / 7d, // Independência do Brasil
				2062y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2062y / November / 2d, // Finados
				2062y / November / 15d, // Proclamação da República
				2062y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2062y / December / 25d, // Natal
				2063y / January / 1d, // Confraternização Universal
				2063y / February / 26d, // Carnaval
				2063y / February / 27d, // Carnaval
				2063y / April / 13d, // Paixão de Cristo
				2063y / April / 21d, // Tiradentes
				2063y / May / 1d, // Dia do Trabalho
				2063y / June / 14d, // Corpus Christi
				2063y / September / 7d, // Independência do Brasil
				2063y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2063y / November / 2d, // Finados
				2063y / November / 15d, // Proclamação da República
				2063y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2063y / December / 25d, // Natal
				2064y / January / 1d, // Confraternização Universal
				2064y / February / 18d, // Carnaval
				2064y / February / 19d, // Carnaval
				2064y / April / 4d, // Paixão de Cristo
				2064y / April / 21d, // Tiradentes
				2064y / May / 1d, // Dia do Trabalho
				2064y / June / 5d, // Corpus Christi
				2064y / September / 7d, // Independência do Brasil
				2064y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2064y / November / 2d, // Finados
				2064y / November / 15d, // Proclamação da República
				2064y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2064y / December / 25d, // Natal
				2065y / January / 1d, // Confraternização Universal
				2065y / February / 9d, // Carnaval
				2065y / February / 10d, // Carnaval
				2065y / March / 27d, // Paixão de Cristo
				2065y / April / 21d, // Tiradentes
				2065y / May / 1d, // Dia do Trabalho
				2065y / May / 28d, // Corpus Christi
				2065y / September / 7d, // Independência do Brasil
				2065y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2065y / November / 2d, // Finados
				2065y / November / 15d, // Proclamação da República
				2065y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2065y / December / 25d, // Natal
				2066y / January / 1d, // Confraternização Universal
				2066y / February / 22d, // Carnaval
				2066y / February / 23d, // Carnaval
				2066y / April / 9d, // Paixão de Cristo
				2066y / April / 21d, // Tiradentes
				2066y / May / 1d, // Dia do Trabalho
				2066y / June / 10d, // Corpus Christi
				2066y / September / 7d, // Independência do Brasil
				2066y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2066y / November / 2d, // Finados
				2066y / November / 15d, // Proclamação da República
				2066y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2066y / December / 25d, // Natal
				2067y / January / 1d, // Confraternização Universal
				2067y / February / 14d, // Carnaval
				2067y / February / 15d, // Carnaval
				2067y / April / 1d, // Paixão de Cristo
				2067y / April / 21d, // Tiradentes
				2067y / May / 1d, // Dia do Trabalho
				2067y / June / 2d, // Corpus Christi
				2067y / September / 7d, // Independência do Brasil
				2067y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2067y / November / 2d, // Finados
				2067y / November / 15d, // Proclamação da República
				2067y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2067y / December / 25d, // Natal
				2068y / January / 1d, // Confraternização Universal
				2068y / March / 5d, // Carnaval
				2068y / March / 6d, // Carnaval
				2068y / April / 20d, // Paixão de Cristo
				2068y / April / 21d, // Tiradentes
				2068y / May / 1d, // Dia do Trabalho
				2068y / June / 21d, // Corpus Christi
				2068y / September / 7d, // Independência do Brasil
				2068y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2068y / November / 2d, // Finados
				2068y / November / 15d, // Proclamação da República
				2068y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2068y / December / 25d, // Natal
				2069y / January / 1d, // Confraternização Universal
				2069y / February / 25d, // Carnaval
				2069y / February / 26d, // Carnaval
				2069y / April / 12d, // Paixão de Cristo
				2069y / April / 21d, // Tiradentes
				2069y / May / 1d, // Dia do Trabalho
				2069y / June / 13d, // Corpus Christi
				2069y / September / 7d, // Independência do Brasil
				2069y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2069y / November / 2d, // Finados
				2069y / November / 15d, // Proclamação da República
				2069y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2069y / December / 25d, // Natal
				2070y / January / 1d, // Confraternização Universal
				2070y / February / 10d, // Carnaval
				2070y / February / 11d, // Carnaval
				2070y / March / 28d, // Paixão de Cristo
				2070y / April / 21d, // Tiradentes
				2070y / May / 1d, // Dia do Trabalho
				2070y / May / 29d, // Corpus Christi
				2070y / September / 7d, // Independência do Brasil
				2070y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2070y / November / 2d, // Finados
				2070y / November / 15d, // Proclamação da República
				2070y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2070y / December / 25d, // Natal
				2071y / January / 1d, // Confraternização Universal
				2071y / March / 2d, // Carnaval
				2071y / March / 3d, // Carnaval
				2071y / April / 17d, // Paixão de Cristo
				2071y / April / 21d, // Tiradentes
				2071y / May / 1d, // Dia do Trabalho
				2071y / June / 18d, // Corpus Christi
				2071y / September / 7d, // Independência do Brasil
				2071y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2071y / November / 2d, // Finados
				2071y / November / 15d, // Proclamação da República
				2071y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2071y / December / 25d, // Natal
				2072y / January / 1d, // Confraternização Universal
				2072y / February / 22d, // Carnaval
				2072y / February / 23d, // Carnaval
				2072y / April / 8d, // Paixão de Cristo
				2072y / April / 21d, // Tiradentes
				2072y / May / 1d, // Dia do Trabalho
				2072y / June / 9d, // Corpus Christi
				2072y / September / 7d, // Independência do Brasil
				2072y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2072y / November / 2d, // Finados
				2072y / November / 15d, // Proclamação da República
				2072y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2072y / December / 25d, // Natal
				2073y / January / 1d, // Confraternização Universal
				2073y / February / 6d, // Carnaval
				2073y / February / 7d, // Carnaval
				2073y / March / 24d, // Paixão de Cristo
				2073y / April / 21d, // Tiradentes
				2073y / May / 1d, // Dia do Trabalho
				2073y / May / 25d, // Corpus Christi
				2073y / September / 7d, // Independência do Brasil
				2073y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2073y / November / 2d, // Finados
				2073y / November / 15d, // Proclamação da República
				2073y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2073y / December / 25d, // Natal
				2074y / January / 1d, // Confraternização Universal
				2074y / February / 26d, // Carnaval
				2074y / February / 27d, // Carnaval
				2074y / April / 13d, // Paixão de Cristo
				2074y / April / 21d, // Tiradentes
				2074y / May / 1d, // Dia do Trabalho
				2074y / June / 14d, // Corpus Christi
				2074y / September / 7d, // Independência do Brasil
				2074y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2074y / November / 2d, // Finados
				2074y / November / 15d, // Proclamação da República
				2074y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2074y / December / 25d, // Natal
				2075y / January / 1d, // Confraternização Universal
				2075y / February / 18d, // Carnaval
				2075y / February / 19d, // Carnaval
				2075y / April / 5d, // Paixão de Cristo
				2075y / April / 21d, // Tiradentes
				2075y / May / 1d, // Dia do Trabalho
				2075y / June / 6d, // Corpus Christi
				2075y / September / 7d, // Independência do Brasil
				2075y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2075y / November / 2d, // Finados
				2075y / November / 15d, // Proclamação da República
				2075y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2075y / December / 25d, // Natal
				2076y / January / 1d, // Confraternização Universal
				2076y / March / 2d, // Carnaval
				2076y / March / 3d, // Carnaval
				2076y / April / 17d, // Paixão de Cristo
				2076y / April / 21d, // Tiradentes
				2076y / May / 1d, // Dia do Trabalho
				2076y / June / 18d, // Corpus Christi
				2076y / September / 7d, // Independência do Brasil
				2076y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2076y / November / 2d, // Finados
				2076y / November / 15d, // Proclamação da República
				2076y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2076y / December / 25d, // Natal
				2077y / January / 1d, // Confraternização Universal
				2077y / February / 22d, // Carnaval
				2077y / February / 23d, // Carnaval
				2077y / April / 9d, // Paixão de Cristo
				2077y / April / 21d, // Tiradentes
				2077y / May / 1d, // Dia do Trabalho
				2077y / June / 10d, // Corpus Christi
				2077y / September / 7d, // Independência do Brasil
				2077y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2077y / November / 2d, // Finados
				2077y / November / 15d, // Proclamação da República
				2077y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2077y / December / 25d, // Natal
				2078y / January / 1d, // Confraternização Universal
				2078y / February / 14d, // Carnaval
				2078y / February / 15d, // Carnaval
				2078y / April / 1d, // Paixão de Cristo
				2078y / April / 21d, // Tiradentes
				2078y / May / 1d, // Dia do Trabalho
				2078y / June / 2d, // Corpus Christi
				2078y / September / 7d, // Independência do Brasil
				2078y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2078y / November / 2d, // Finados
				2078y / November / 15d, // Proclamação da República
				2078y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2078y / December / 25d, // Natal
				2079y / January / 1d, // Confraternização Universal
				2079y / March / 6d, // Carnaval
				2079y / March / 7d, // Carnaval
				2079y / April / 21d, // Paixão de Cristo
				2079y / April / 21d, // Tiradentes
				2079y / May / 1d, // Dia do Trabalho
				2079y / June / 22d, // Corpus Christi
				2079y / September / 7d, // Independência do Brasil
				2079y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2079y / November / 2d, // Finados
				2079y / November / 15d, // Proclamação da República
				2079y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2079y / December / 25d, // Natal
				2080y / January / 1d, // Confraternização Universal
				2080y / February / 19d, // Carnaval
				2080y / February / 20d, // Carnaval
				2080y / April / 5d, // Paixão de Cristo
				2080y / April / 21d, // Tiradentes
				2080y / May / 1d, // Dia do Trabalho
				2080y / June / 6d, // Corpus Christi
				2080y / September / 7d, // Independência do Brasil
				2080y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2080y / November / 2d, // Finados
				2080y / November / 15d, // Proclamação da República
				2080y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2080y / December / 25d, // Natal
				2081y / January / 1d, // Confraternização Universal
				2081y / February / 10d, // Carnaval
				2081y / February / 11d, // Carnaval
				2081y / March / 28d, // Paixão de Cristo
				2081y / April / 21d, // Tiradentes
				2081y / May / 1d, // Dia do Trabalho
				2081y / May / 29d, // Corpus Christi
				2081y / September / 7d, // Independência do Brasil
				2081y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2081y / November / 2d, // Finados
				2081y / November / 15d, // Proclamação da República
				2081y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2081y / December / 25d, // Natal
				2082y / January / 1d, // Confraternização Universal
				2082y / March / 2d, // Carnaval
				2082y / March / 3d, // Carnaval
				2082y / April / 17d, // Paixão de Cristo
				2082y / April / 21d, // Tiradentes
				2082y / May / 1d, // Dia do Trabalho
				2082y / June / 18d, // Corpus Christi
				2082y / September / 7d, // Independência do Brasil
				2082y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2082y / November / 2d, // Finados
				2082y / November / 15d, // Proclamação da República
				2082y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2082y / December / 25d, // Natal
				2083y / January / 1d, // Confraternização Universal
				2083y / February / 15d, // Carnaval
				2083y / February / 16d, // Carnaval
				2083y / April / 2d, // Paixão de Cristo
				2083y / April / 21d, // Tiradentes
				2083y / May / 1d, // Dia do Trabalho
				2083y / June / 3d, // Corpus Christi
				2083y / September / 7d, // Independência do Brasil
				2083y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2083y / November / 2d, // Finados
				2083y / November / 15d, // Proclamação da República
				2083y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2083y / December / 25d, // Natal
				2084y / January / 1d, // Confraternização Universal
				2084y / February / 7d, // Carnaval
				2084y / February / 8d, // Carnaval
				2084y / March / 24d, // Paixão de Cristo
				2084y / April / 21d, // Tiradentes
				2084y / May / 1d, // Dia do Trabalho
				2084y / May / 25d, // Corpus Christi
				2084y / September / 7d, // Independência do Brasil
				2084y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2084y / November / 2d, // Finados
				2084y / November / 15d, // Proclamação da República
				2084y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2084y / December / 25d, // Natal
				2085y / January / 1d, // Confraternização Universal
				2085y / February / 26d, // Carnaval
				2085y / February / 27d, // Carnaval
				2085y / April / 13d, // Paixão de Cristo
				2085y / April / 21d, // Tiradentes
				2085y / May / 1d, // Dia do Trabalho
				2085y / June / 14d, // Corpus Christi
				2085y / September / 7d, // Independência do Brasil
				2085y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2085y / November / 2d, // Finados
				2085y / November / 15d, // Proclamação da República
				2085y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2085y / December / 25d, // Natal
				2086y / January / 1d, // Confraternização Universal
				2086y / February / 11d, // Carnaval
				2086y / February / 12d, // Carnaval
				2086y / March / 29d, // Paixão de Cristo
				2086y / April / 21d, // Tiradentes
				2086y / May / 1d, // Dia do Trabalho
				2086y / May / 30d, // Corpus Christi
				2086y / September / 7d, // Independência do Brasil
				2086y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2086y / November / 2d, // Finados
				2086y / November / 15d, // Proclamação da República
				2086y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2086y / December / 25d, // Natal
				2087y / January / 1d, // Confraternização Universal
				2087y / March / 3d, // Carnaval
				2087y / March / 4d, // Carnaval
				2087y / April / 18d, // Paixão de Cristo
				2087y / April / 21d, // Tiradentes
				2087y / May / 1d, // Dia do Trabalho
				2087y / June / 19d, // Corpus Christi
				2087y / September / 7d, // Independência do Brasil
				2087y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2087y / November / 2d, // Finados
				2087y / November / 15d, // Proclamação da República
				2087y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2087y / December / 25d, // Natal
				2088y / January / 1d, // Confraternização Universal
				2088y / February / 23d, // Carnaval
				2088y / February / 24d, // Carnaval
				2088y / April / 9d, // Paixão de Cristo
				2088y / April / 21d, // Tiradentes
				2088y / May / 1d, // Dia do Trabalho
				2088y / June / 10d, // Corpus Christi
				2088y / September / 7d, // Independência do Brasil
				2088y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2088y / November / 2d, // Finados
				2088y / November / 15d, // Proclamação da República
				2088y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2088y / December / 25d, // Natal
				2089y / January / 1d, // Confraternização Universal
				2089y / February / 14d, // Carnaval
				2089y / February / 15d, // Carnaval
				2089y / April / 1d, // Paixão de Cristo
				2089y / April / 21d, // Tiradentes
				2089y / May / 1d, // Dia do Trabalho
				2089y / June / 2d, // Corpus Christi
				2089y / September / 7d, // Independência do Brasil
				2089y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2089y / November / 2d, // Finados
				2089y / November / 15d, // Proclamação da República
				2089y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2089y / December / 25d, // Natal
				2090y / January / 1d, // Confraternização Universal
				2090y / February / 27d, // Carnaval
				2090y / February / 28d, // Carnaval
				2090y / April / 14d, // Paixão de Cristo
				2090y / April / 21d, // Tiradentes
				2090y / May / 1d, // Dia do Trabalho
				2090y / June / 15d, // Corpus Christi
				2090y / September / 7d, // Independência do Brasil
				2090y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2090y / November / 2d, // Finados
				2090y / November / 15d, // Proclamação da República
				2090y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2090y / December / 25d, // Natal
				2091y / January / 1d, // Confraternização Universal
				2091y / February / 19d, // Carnaval
				2091y / February / 20d, // Carnaval
				2091y / April / 6d, // Paixão de Cristo
				2091y / April / 21d, // Tiradentes
				2091y / May / 1d, // Dia do Trabalho
				2091y / June / 7d, // Corpus Christi
				2091y / September / 7d, // Independência do Brasil
				2091y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2091y / November / 2d, // Finados
				2091y / November / 15d, // Proclamação da República
				2091y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2091y / December / 25d, // Natal
				2092y / January / 1d, // Confraternização Universal
				2092y / February / 11d, // Carnaval
				2092y / February / 12d, // Carnaval
				2092y / March / 28d, // Paixão de Cristo
				2092y / April / 21d, // Tiradentes
				2092y / May / 1d, // Dia do Trabalho
				2092y / May / 29d, // Corpus Christi
				2092y / September / 7d, // Independência do Brasil
				2092y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2092y / November / 2d, // Finados
				2092y / November / 15d, // Proclamação da República
				2092y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2092y / December / 25d, // Natal
				2093y / January / 1d, // Confraternização Universal
				2093y / February / 23d, // Carnaval
				2093y / February / 24d, // Carnaval
				2093y / April / 10d, // Paixão de Cristo
				2093y / April / 21d, // Tiradentes
				2093y / May / 1d, // Dia do Trabalho
				2093y / June / 11d, // Corpus Christi
				2093y / September / 7d, // Independência do Brasil
				2093y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2093y / November / 2d, // Finados
				2093y / November / 15d, // Proclamação da República
				2093y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2093y / December / 25d, // Natal
				2094y / January / 1d, // Confraternização Universal
				2094y / February / 15d, // Carnaval
				2094y / February / 16d, // Carnaval
				2094y / April / 2d, // Paixão de Cristo
				2094y / April / 21d, // Tiradentes
				2094y / May / 1d, // Dia do Trabalho
				2094y / June / 3d, // Corpus Christi
				2094y / September / 7d, // Independência do Brasil
				2094y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2094y / November / 2d, // Finados
				2094y / November / 15d, // Proclamação da República
				2094y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2094y / December / 25d, // Natal
				2095y / January / 1d, // Confraternização Universal
				2095y / March / 7d, // Carnaval
				2095y / March / 8d, // Carnaval
				2095y / April / 21d, // Tiradentes
				2095y / April / 22d, // Paixão de Cristo
				2095y / May / 1d, // Dia do Trabalho
				2095y / June / 23d, // Corpus Christi
				2095y / September / 7d, // Independência do Brasil
				2095y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2095y / November / 2d, // Finados
				2095y / November / 15d, // Proclamação da República
				2095y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2095y / December / 25d, // Natal
				2096y / January / 1d, // Confraternização Universal
				2096y / February / 27d, // Carnaval
				2096y / February / 28d, // Carnaval
				2096y / April / 13d, // Paixão de Cristo
				2096y / April / 21d, // Tiradentes
				2096y / May / 1d, // Dia do Trabalho
				2096y / June / 14d, // Corpus Christi
				2096y / September / 7d, // Independência do Brasil
				2096y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2096y / November / 2d, // Finados
				2096y / November / 15d, // Proclamação da República
				2096y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2096y / December / 25d, // Natal
				2097y / January / 1d, // Confraternização Universal
				2097y / February / 11d, // Carnaval
				2097y / February / 12d, // Carnaval
				2097y / March / 29d, // Paixão de Cristo
				2097y / April / 21d, // Tiradentes
				2097y / May / 1d, // Dia do Trabalho
				2097y / May / 30d, // Corpus Christi
				2097y / September / 7d, // Independência do Brasil
				2097y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2097y / November / 2d, // Finados
				2097y / November / 15d, // Proclamação da República
				2097y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2097y / December / 25d, // Natal
				2098y / January / 1d, // Confraternização Universal
				2098y / March / 3d, // Carnaval
				2098y / March / 4d, // Carnaval
				2098y / April / 18d, // Paixão de Cristo
				2098y / April / 21d, // Tiradentes
				2098y / May / 1d, // Dia do Trabalho
				2098y / June / 19d, // Corpus Christi
				2098y / September / 7d, // Independência do Brasil
				2098y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2098y / November / 2d, // Finados
				2098y / November / 15d, // Proclamação da República
				2098y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2098y / December / 25d, // Natal
				2099y / January / 1d, // Confraternização Universal 
				2099y / February / 23d, // Carnaval
				2099y / February / 24d, // Carnaval
				2099y / April / 10d, // Paixão de Cristo
				2099y / April / 21d, // Tiradentes
				2099y / May / 1d, // Dia do Trabalho
				2099y / June / 11d, // Corpus Christi
				2099y / September / 7d, // Independência do Brasil
				2099y / October / 12d, // Nossa Sr.a Aparecida - Padroeira do Brasil
				2099y / November / 2d, // Finados
				2099y / November / 15d, // Proclamação da República
				2099y / November / 20d, // Dia Nacional de Zumbi e da Consciência Negra
				2099y / December / 25d, // Natal
			};

			return schedule{ util::days_period{ 2001y / FirstDayOfJanuary, 2099y / LastDayOfDecember }, move(holidays) };
		}
		// notes from the above document:
		// 1) According to Resolution No. 2,516, starting in the year 2000, Holy Thursday was considered a working day.
		// 2) Law No. 9,504/97 established that, in an election year, the first round of elections will be held on the first Sunday of October; and the second round, if any, on the last Sunday of that month.
		// 3) According to Resolution No. 2,596/99, there will be no service to the public on the last business day of the year.
		// 4) This list does not include municipal holidays, elections, and New Year's Day. The criterion adopted was to indicate holidays that do not affect bank reserves.


		auto make_ANBIMA_calendar_versions() -> _calendar_versions
		{
			const auto holidays = _make_ANBIMA_schedule();

			const auto epoch = period{
				holidays.get_period().get_from(), // starts before Epoch
				Epoch.get_until()
			};

			const auto rules = _annual_holiday_period_storage{
				{ &NewYearsDay, epoch, epoch.get_from() },
				{ &_ShroveMonday, epoch, epoch.get_from() },
				{ &_ShroveTuesday, epoch, epoch.get_from() },
				{ &GoodFriday, epoch, epoch.get_from() },
				{ &_TiradentesDay, epoch, epoch.get_from() },
				{ &_LabourDay, epoch, epoch.get_from() },
				{ &_CorpusChristi, epoch, epoch.get_from() },
				{ &_IndependenceDay, epoch, epoch.get_from() },
				{ &_OurLadyOfAparecida, epoch, epoch.get_from() },
				{ &_AllSoulsDay, epoch, epoch.get_from() },
				{ &_RepublicProclamationDay, epoch, epoch.get_from() },
				{
					&_BlackConsciousnessDay,
					period{ 2024y / FirstDayOfJanuary, Epoch.get_until() }, // or should it be the first day it was celebrated? (are we dealing in whole years here?)
					2023y / December / 21d // was enacted as Law No. 14,759 on 21 December 2023
				},
				{ &ChristmasDay, epoch, epoch.get_from() }
			};

			return _make_calendar_versions(
				holidays,
				rules,
				epoch,
				SaturdaySundayWeekend,
				NoAdjustment
			);
		}

	}

}
