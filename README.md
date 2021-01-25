# doomsday

Written to emulate stories of John Conway not being able to log in to his
computer until he'd computed the day on which a particular date fell.

## Usage

```
./doomsday
```

This gives you a date and prompts you to enter your guess for the day on which
that date falls.

```
./doomsday DD/MM/YYYY
```

This queries the Doomsday Algorithm to show you the day on which the supplied
date falls.

Usage is displayed with `./doomsday --help`.

## Algorithm

Start by indexing days of the week such that `day[0] = Sunday, day[1] =
Monday`, etc.

First compute the "anchor day":

```
c = floor(year / 100)
anchor = (5 * (c mod 4) mod 7) + 2
```

For example, for the 21st century the anchor day would be index 2, which is
Tuesday:

```
c = floor(20xx / 100) = 20
anchor = (5 * (20 mod 4) mod 7) + 2
       = 2
```

Now we compute the year's "doomsday", which is the day of the year on which a
number of memorable dates fall.  Let `T := year - c` be the last two digits of
the year. Now we apply the "Odd-plus-11" rule twice, find its distance to a
multiple of seven, and add the result to the value of the previously computed
`anchor` to get the doomsday.

```
T += (T % 2 != 0) ? 11 : ;
T /= 2
T += (T % 2 != 0) ? 11 : ;
T = 7 - (T mod 7)

doomsday = anchor + T
```

The value of `T` for 2019 would be `T = 19 -> 30 -> 15 -> 26 -> 2`, so the
Doomsday for 2019 is the century's anchor day, Tuesday, plus 2, giving us
Thursday. The table below shows the dates on which the doomsday falls --
finding the day of the week for a given date is then a case of counting from
the nearest doomsday date.

| Rule | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
|----------------------------|:-----:|:-----:|:-----:|:-----:|:-----:|
| Even day-month pairs 		 | 04/04 | 06/06 | 08/08 | 10/10 | 12/12 |
|"Working 9-to-5 at the 7-11"| 09/05 | 07/11 | 05/09 | 11/07 | | |
| Memorable dates			 | 14/03 (Pi Day) | 04/07 (Independence Day) | 31/10 (Hallowe'en) | 26/12 (Boxing Day) | &nbsp; | &nbsp; |
| On regular years			 | 03/01 | 14/02 (Valentine's Day) | 28/02 (Last day of February) | &nbsp; | &nbsp; | &nbsp; |
| On leap years				 | 04/01 | 29/02 | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
