# calendar

What we want to achieve is to calculate a number of business days between 2 dates.

For this we need a notion of "weekend" and a notion of "holidays schedule". The library's logic is based around these non-business days (despite the fact that we want to compute the number of business days).

Following std::chrono we assume the Gregorian calendar.

It is expected that calendars do not change frequently (so the underlying data is quite static), but are used a lot. Hence efficient caching is possible.

We do not capture the history of new holidays been announced. Hence it is expected that the calendars are correct as of today (but might not be correct as of a day in the past).

We can think about holiday schedule as just a set of dates, or as a set of rules: to me the historical holidays are always better as a set of dates and future holidays are always better as a set of rules. Also the holidays for the current year at least (and maybe for the next year or two, as long as they are known with a high degree of certainty) are probably better as a set of dates (like you would see on your wall calendar).

We assume that for the rule based holidays the rules are unique (as in 01-January has only one rule like NewYear). We do not check for compliance, but multiple rules for the same day might produce unexpected results during calculation of substitution days.

When we have "from" and "until" of some range of dates we do expect that "from" itself is included in the range and "until" itself is included in the range. If "until" < "from" we throw an exception.

When we combine calendars the result is generated only over the common range of the initial calendars.

When we concatenate the calendars we expect not to have a gap between them.

From/until of holiday schedule tells us what is the actual range of the holiday schedule application as the first holiday in the schedule is not the same as from (and the same for the last holiday is not the same as until). It is expected that the from is not after the first holiday in the schedule and until is not before the last holiday in the schedule. If part of the schedule falls outside the range between the from and until it will be truncated to fit (it is a way to truncate an existing calendar by creating a copy of an existing one with a new from or back or both).

We do not do anything special for std::chrono::year_month_day, which are not "ok".

As we are doing some caching inside calendar we throw an exception if one checks for a business day before from or after until.

# roadmap
1) add handling of serial dates
2) make count_business_days a lot more efficient (either cache business days per month/year or utilise vector<bool> more)
3) maybe do better for rule based calendars (until date does not make sense in this case)
4) consider again how caching should be implemented in a multithread case
