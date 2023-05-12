# calendar

What we want to achieve is to calculate a number of business days between 2 days.

For this we need a notion of "weekend" and a notion of "holidays schedule".

Following std::chrono we assume the Gregorian calendar.

It is expected that calendars do not change frequently (so the underlying data is quite static), but are used a lot.

We do not capture the history of new holidays been announced.

We can think about holiday schedule as just a set of dates, or as a set of rules: to me the historical holidays are always better as a set of dates and future holidays are better as a set of rules. Also the holidays for the current year at least (and maybe for the next year or two) are better as a set of dates (like you would see on your wall calendar).

We assume that for the rule based holidays the rules are unique (as in 01-January has only one rule like NewYear). We do not check for compliance.
