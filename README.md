# calendar

What we want to achieve is to calculate a number of business days between 2 days.

For this we need a notion of "weekend" and a notion of "holidays schedule".

Following std::chrono we assume the Gregorian calendar.

It is expected that calendars do not change frequently (so the underlying data is quite static), but are used a lot.

We do not capture the history of new holidays been announced.

We can think about holiday schedule as just a set of dates, or as a set of rules: to me the historical holidays are always better as a set of dates and future holidays are better as a set of rules. Also the holidays for the current year at least (and maybe for the next year or two) are better as a set of dates (like you would see on your wall calendar).

We assume that for the rule based holidays the rules are unique (as in 01-January has only one rule like NewYear). We do not check for compliance, but multiple rules for the same day might produce unexpected results during calculation of substitution days.

When we have "front" and "back" of some range of dates we do expect that "front" itself is included in the range and "back" itself is included in the range. If "back" < "front" we throw an exception.

When we combine calendars we expect them to have the same front/back.

When we concatenate the calendars we expect not to have a gap between them.

Front/back of holiday_schedule tells us what range the holiday_schedule actually covers as the first holiday in the schedule is not the same as front (and the same for the last holiday is not the same as back).
