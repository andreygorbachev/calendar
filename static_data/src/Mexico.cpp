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
#include "cyclical_holiday.h"

#include <period.h>
#include <schedule.h>
#include <weekend.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <calendar.h>

#include <chrono>
#include <utility>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// there was also some changes announced in 2005 about shifting holidays to make long weekends - we are not yet handling the histical calendars
		const auto _ConstitutionDay = weekday_indexed_holiday{ February / Monday[1] }; // Observance
		const auto _BenitoJuarezsBirthday = weekday_indexed_holiday{ March / Monday[3] }; // Observance
		const auto _HolyThursday = offset_holiday{ &_Easter, std::chrono::days{ -3 } }; // should it be in the main library?
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _IndependenceDay = named_holiday{ September / 16d };
		const auto _AllSoulsDay = named_holiday{ November / 2d }; // should it be in the main library?
		const auto _RevolutionDay = weekday_indexed_holiday{ November / Monday[3] }; // Observance
		const auto _FeastOfOurLadyOfGuadalupe = named_holiday{ December / 12d };

		const auto _InaugurationDay = _cyclical_holiday{
			named_holiday{ October / 1d },
			2024y, // before that it was December 1st, but moved to October 1st in 2024 - we are not yet handling the histical calendars
			years{ 6 }
		};



		static auto _make_CNBV_known_schedule_part0() -> schedule // is it a correct name? (CNBV?)
		{
			auto holidays = schedule::dates{

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2006, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2006y / January / 1d, // I. 1 de enero.
				2006y / February / 6d, // II. 5 de febrero.
				2006y / March / 21d, // III. 21 de marzo.
				2006y / April / 13d, // IV. 13 y 14 de abril.
				2006y / April / 14d,
				2006y / May / 1d, // V. 1 de mayo.
				2006y / September / 16d, // VI. 16 de septiembre.
				2006y / November / 2d, // VII. 2 y 20 de noviembre.
				2006y / November / 20d,
				2006y / December / 1d, // VIII. 1, 12 y 25 de diciembre.
				2006y / December / 12d,
				2006y / December / 25d,

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2007, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2007y / January / 1d, // I. El 1 de enero.
				2007y / February / 5d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2007y / March / 19d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2007y / April / 5d, // IV. El 5 y 6 de abril.
				2007y / April / 6d,
				2007y / May / 1d, // V. El 1 de mayo.
				2007y / September / 16d, // VI. El 16 de septiembre.
				2007y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre.
				2007y / November / 19d,
				2007y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2007y / December / 25d,

				// from 

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2009, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2009y / January / 1d, // I. El 1 de enero.
				2009y / February / 2d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 2 de febrero.
				2009y / March / 16d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 16 de marzo.
				2009y / April / 9d, // IV. El 9 y 10 de abril.
				2009y / April / 10d,
				2009y / May / 1d, // V. El 1 de mayo.
				2009y / September / 16d, // VI. El 16 de septiembre.
				2009y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 denoviembre, es decir, el 16 de noviembre.
				2009y / November / 16d,
				2009y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2009y / December / 25d,

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2010, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2010y / January / 1d, //I. El 1 de enero.
				2010y / February / 1d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 1 de febrero.
				2010y / March / 15d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 15 de marzo.
				2010y / April / 1d, // IV. El 1 y 2 de abril.
				2010y / April / 2d,
				2010y / May / 1d, // V. El 1 de mayo.
				2010y / September / 16d, // VI. El 16 de septiembre.
				2010y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 15 de noviembre.
				2010y / November / 15d,
				2010y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2010y / December / 25d,

				// from 

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2012, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2012y / January / 1d, // I. El 1 de enero.
				2012y / February / 6d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 6 de febrero.
				2012y / March / 19d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 19 de marzo.
				2012y / April / 5d, // IV. El 5 y 6 de abril.
				2012y / April / 6d,
				2012y / May / 1d, // V. El 1 de mayo.
				2012y / July / 1d, // VI. El 1 de julio, con motivo de las elecciones federales.
				2012y / September / 16d, // VII. El 16 de septiembre.
				2012y / November / 2d, // VIII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 19 de noviembre.
				2012y / November / 19d,
				2012y / December / 1d, // IX. El 1, 12 y 25 de diciembre.
				2012y / December / 12d,
				2012y / December / 25d,

				// from "DISPOSICIONES DE CARACTER GENERAL QUE SEÑALAN LOS DIAS DEL AÑO 2013, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISION DE LA COMISION NACIONAL BANCARIA Y
				// DE VALORES, DEBERAN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2013y / January / 1d, // I. El 1 de enero.
				2013y / February / 4d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 4 de febrero.
				2013y / March / 18d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 18 de marzo.
				2013y / March / 28d, // IV. El 28 y 29 de marzo.
				2013y / March / 29d,
				2013y / May / 1d, // V. El 1 de mayo.
				2013y / September / 16d, // VI. El 16 de septiembre.
				2013y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 18 de noviembre.
				2013y / November / 18d,
				2013y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2013y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2014, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2014y / January / 1d, // I. El 1 de enero.
				2014y / February / 3d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 3 de febrero.
				2014y / March / 17d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 17 de marzo.
				2014y / April / 17d, // IV. El 17 y 18 de abril.
				2014y / April / 18d,
				2014y / May / 1d, // V. El 1 de mayo.
				2014y / September / 16d, // VI. El 16 de septiembre.
				2014y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 17 de noviembre.
				2014y / November / 17d,
				2014y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2014y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2015, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2015y / January / 1d, // I. El 1 de enero.
				2015y / February / 2d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 2 de febrero.
				2015y / March / 16d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 16 de marzo.
				2015y / April / 2d, // IV. El 2 y 3 de abril.
				2015y / April / 3d,
				2015y / May / 1d, // V. El 1 de mayo.
				2015y / September / 16d, // VI. El 16 de septiembre.
				2015y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 16 de noviembre.
				2015y / November / 16d,
				2015y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2015y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2016, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2016y / January / 1d, // I. El 1 de enero.
				2016y / February / 1d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 1 de febrero.
				2016y / March / 21d, // III. El 21 de marzo.
				2016y / March / 24d, // IV. El 24 y 25 de marzo.
				2016y / March / 25d,
				2016y / May / 1d, // V. El 1 de mayo.
				2016y / September / 16d, // VI. El 16 de septiembre.
				2016y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 21 de noviembre.
				2016y / November / 21d,
				2016y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2016y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2017, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2017y / January / 1d, // I. El 1 de enero.
				2017y / February / 6d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 6 de febrero.
				2017y / March / 20d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 20 de marzo.
				2017y / April / 13d, // IV. El 13 y 14 de abril.
				2017y / April / 14d,
				2017y / May / 1d, // V. El 1 de mayo.
				2017y / September / 16d, // VI. El 16 de septiembre.
				2017y / November / 2d, // VII. El 2 y 20 de noviembre.
				2017y / November / 20d,
				2017y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2017y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2018, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2018y / January / 1d, // I. El 1 de enero.
				2018y / February / 5d, // II. El 5 de febrero.
				2018y / March / 19d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 19 de marzo.
				2018y / March / 29d, // IV. El 29 y 30 de marzo.
				2018y / March / 30d,
				2018y / May / 1d, // V. El 1 de mayo.
				2018y / July / 1d, // VI. El 1 de julio, con motivo de las elecciones federales.
				2018y / September / 16d, // VII. El 16 de septiembre.
				2018y / November / 2d, // VIII. El 2 de noviembre. Adicionalmente, el tercer lunes de dicho mes en conmemoración del 20 de noviembre, es decir, el 19 de noviembre.
				2019y / November / 19d,
				2018y / December / 1d, // IX. El 1, 12 y 25 de diciembre.
				2018y / December / 12d,
				2018y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2019, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2019y / January / 1d, // I. El 1 de enero.
				2019y / February / 4d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 4 de febrero.
				2019y / March / 18d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 18 de marzo.
				2019y / April / 18d, // IV. El 18 y 19 de abril.
				2019y / April / 19d,
				2019y / May / 1d, // V. El 1 de mayo.
				2019y / September / 16d, // VI. El 16 de septiembre.
				2019y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de noviembre en conmemoración del 20 de noviembre, es decir, el 18 de noviembre.
				2019y / November / 18d,
				2019y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2019y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2020, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2020y / January/ 1d, // I. El 1 de enero.
				2020y / February / 3d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 3 de febrero.
				2020y / March / 16d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 16 de marzo.
				2020y / April / 9d, // IV. El 9 y 10 de abril.
				2020y / April / 10d,
				2020y / May / 1d, // V. El 1 de mayo.
				2020y / September / 16d, // VI. El 16 de septiembre.
				2020y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de noviembre en conmemoración del 20 de noviembre, es decir, el 16 de noviembre.
				2020y / November / 16d,
				2020y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2020y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2021, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2021y / January / 1d, // I. El 1 de enero.
				2021y / February / 1d, // II. El primer lunes de febrero en conmemoración del 5 de febrero, es decir, el 1 de febrero.
				2021y / March / 15d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo, es decir, el 15 de marzo.
				2021y / April / 1d, // IV. El 1 y 2 de abril.
				2021y / April / 2d,
				2021y / May / 1d, // V. El 1 de mayo.
				2021y / September / 16d, // VI. El 16 de septiembre.
				2021y / November / 2d, // VII. El 2 de noviembre. Adicionalmente, el tercer lunes de noviembre en conmemoración del 20 de noviembre, es decir, el 15 de noviembre.
				2021y / November / 15d,
				2021y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2021y / December / 25d,


				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2022, EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES, DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2022y / January / 1d, // I. El 1 de enero.
				2022y / February / 7d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2022y / March / 21d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2022y / April / 14d, // IV. El 14 y 15 de abril.
				2022y / April / 15d,
				2022y / May / 1d, // V. El 1 de mayo.
				2022y / September / 16d, // VI. El 16 de septiembre.
				2022y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de noviembre en conmemoración del 20 de noviembre.
				2022y / November / 21d,
				2022y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2022y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2023 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2023y / January / 1d, // I. El 1 de enero.
				2023y / February / 6d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2023y / March / 20d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2023y / April / 6d, // IV. El 6 y 7 de abril.
				2023y / April / 7d,
				2023y / May / 1d, // V. El 1 de mayo.
				2023y / September / 16d, // VI. El 16 de septiembre.
				2023y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de noviembre en conmemoración del 20 de noviembre.
				2023y / November / 20d,
				2023y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2023y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2024 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2024y / January / 1d, // I. El 1o. de enero.
				2024y / February / 5d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2024y / March / 18d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2024y / March / 28d, // IV. El 28 y 29 de marzo.
				2024y / March / 29d,
				2024y / May / 1d, // V. El 1o. de mayo.
				2024y / September / 16d, // VI. El 16 de septiembre.
				2024y / October / 1d, // VII. El 1o. de octubre.
				2024y / November / 2d, // VIII. El 2 de noviembre y el tercer lunes de dicho mes en conmemoración del 20 de noviembre.
				2024y / November / 18d,
				2024y / December / 12d, // IX. El 12 y 25 de diciembre.
				2024y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2025 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y
				// DE VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2025y / January / 1d, // I. El 1o. de enero.
				2025y / February / 3d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2025y / March / 17d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2025y / April / 17d, // IV. El 17 y 18 de abril.
				2025y / April / 18d,
				2025y / May / 1d, // V. El 1o. de mayo.
				2025y / September / 16d, // VI. El 16 de septiembre.
				2025y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de dicho mes en conmemoración del 20 de noviembre.
				2025y / November / 17d,
				2025y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2025y / December / 25d,

				// from "DISPOSICIONES DE CARÁCTER GENERAL QUE SEÑALAN LOS DÍAS DEL AÑO 2026 EN QUE LAS
				// ENTIDADES FINANCIERAS SUJETAS A LA SUPERVISIÓN DE LA COMISIÓN NACIONAL BANCARIA Y DE
				// VALORES DEBERÁN CERRAR SUS PUERTAS Y SUSPENDER OPERACIONES"

				2026y / January / 1d, // I. El 1o. de enero.
				2026y / February / 2d, // II. El primer lunes de febrero en conmemoración del 5 de febrero.
				2026y / March / 16d, // III. El tercer lunes de marzo en conmemoración del 21 de marzo.
				2026y / April / 2d, // IV. El 2 y 3 de abril.
				2026y / April / 3d,
				2026y / May / 1d, // V. El 1o. de mayo.
				2026y / September / 16d, // VI. El 16 de septiembre.
				2026y / November / 2d, // VII. El 2 de noviembre y el tercer lunes de dicho mes, este último en conmemoración del 20 de noviembre.
				2026y / November / 16d,
				2026y / December / 12d, // VIII. El 12 y 25 de diciembre.
				2026y / December / 25d,
			};

			return schedule{
				days_period{ 2006y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}



		static auto _make_CNBV_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_ConstitutionDay,
				&_BenitoJuarezsBirthday,
				&_HolyThursday,
				&GoodFriday,
				&_LabourDay,
				&_IndependenceDay,
				&_InaugurationDay,
				&_AllSoulsDay,
				&_RevolutionDay,
				&_FeastOfOurLadyOfGuadalupe,
				&ChristmasDay
			};

			return make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);
		}

		auto make_CNBV_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_CNBV_known_schedule_part0() +
				_make_CNBV_generated_schedule_part0()
			};

			return {
//				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
				{ 2026y / FirstDayOfJanuary, std::move(cal0) },
			};
		}

	}

}
