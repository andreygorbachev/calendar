# calendar

What we want to achieve is to calculate a number of business days between 2 days.

For this we need a notion of "weekend" and a notion of "holidays schedule".

Following std::chrono we assume the Gregorian calendar.

It is expected that calendars do not change frequently (so the underlying data is quite static), but are used a lot.
