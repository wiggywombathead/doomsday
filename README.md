# doomsday
Written to emulate stories of John Conway not being able to log in to his computer until he'd computed the day on which a particular date fell.

## Algorithm
Start by indexing the days of the week such that Sunday = 0, Monday = 1, ..., Saturday = 6

### Compute the century's "anchor day"
```
c = floor(year / 100)
a = (5 * (c mod 4) mod 7) + 2
```

For example, for the 21st century we have
```
c = floor(20xx / 100) = 20
a = (5 * (20 mod 4) mod 7) + 2
  = ((5 * 0) mod 7) + 2
  = 2
```

So the anchor day is day 2, Tuesday.

### Compute the year's "doomsday"
Let `T := year - c`, that is, the last two digits of the year\
Now apply the "Odd-plus-11" rule twice

```
T += (T % 2 != 0) ? 11 : ;
T /= 2
T += (T % 2 != 0) ? 11 : ;
T = 7 - (T mod 7)

doomsday = a + T
```

The value of `T` for 2019 would be
```
T := 19 -> 30 -> 15 -> 26 -> 2
```
So the doomsday for 2019 is Tuesday + 2 => Thursday

###
The doomsday describes the day of the week on which an easy-to-remember set of dates all fall. Calculating the day on which an arbitrary day falls is then a case of finding it in relation to one in this set. The set is (at least) as follows:

| Test | Column |
|------|--------|
| Pants| Balls  |

| &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
|----------------------------|:-----:|:-----:|:-----:|:-----:|:-----:|
| Even day-month pairs 		 | 04/04 | 06/06 | 08/08 | 10/10 | 12/12 |
| Working 9-to-5 at the 7-11 | 09/05 | 07/11 | 05/09 | 11/07 | | |
| Memorable dates			 | 14/03 (Pi Day) | 04/07 (Independence Day) | 31/10 (Hallowe'en) | 26/12 (Boxing Day) | &nbsp; | &nbsp; |
| On regular years			 | 03/01 | 14/02 (Valentine's Day) | 28/02 (Last day of February) | &nbsp; | &nbsp; | &nbsp; |
| On leap years				 | 04/01 | 29/02 | &nbsp; | &nbsp; | &nbsp; | &nbsp; |
