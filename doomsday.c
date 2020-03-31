#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 64
#define NUM_DAYS_IN_WEEK 7

char *days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
char *months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

void print_usage() {

	puts("To query a date, input it as a command line argument of the form"
			" day/month/year");

	puts("If no command line arguments are given, then when prompted with a"
			" date, enter the day of the week it falls/fell on.");

	puts("Valid guesses are either the day's index in the week (Sunday = 0,"
			" ..., Saturday = 6), or");

	for (int i = 0; i < NUM_DAYS_IN_WEEK; i++) 
		printf("%s%s",
				i == NUM_DAYS_IN_WEEK - 1 ? "or " : days[i],
				i == NUM_DAYS_IN_WEEK - 1 ? days[i] : ", ");
}

bool is_leap(int year) {
	return (year % 4 == 0);
}

void init_date(int *day, int *month, int *year) {

    srand(time(NULL));

    *year = 1500 + (rand() % 600);
    *month = rand() % 12;
    *day = rand();

    switch (*month) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            *day %= 31;
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            *day %= 30;
            break;
        case 1:
            *day %= (is_leap(*year)) ? 29 : 28;
		default:
			exit(EXIT_FAILURE);
    }

	*day += 1;

}

int compute_doomsday(int year) {

    int c = year / 100;
    int anchor = 2 + (5 * (c % 4) % 7);

    int T = year - 100 * c;

    /* Odd plus 11 */
    if (T % 2 != 0)
        T += 11;

    T /= 2;

    if  (T % 2 != 0)
        T += 11;

    T = 7 - (T % 7);

    return anchor + T;
}

char *compute_day(int day, int month, int year) {

	int doomsday = compute_doomsday(year);

	bool isleap = is_leap(year);

    int target;
    switch (month) {
        case 0:
            if (isleap)
                target = 4;
            else
                target = 3;
            break;
        case 1:
            if (isleap)
                target = 15;
            else
                target = 14;
            break;
        case 2:
            target = 14;
            break;
        case 3:
            target = 4;
            break;
        case 4:
            target = 9;
            break;
        case 5:
            target = 6;
            break;
        case 6:
            target = 11;
            break;
        case 7:
            target = 8;
            break;
        case 8:
            target = 5;
            break;
        case 9:
            target = 10;
            break;
        case 10:
            target = 7;
            break;
        case 11:
            target = 12;
            break;
		default:
			exit(EXIT_FAILURE);
    }

    int diff = (day - target) % 7;
    int index = (doomsday + diff) % 7;

    return days[index];
}

void print_date(int d, int m, int y) {
	printf("%d %s %d", d, months[m], y);
}

int main(int argc, char *argv[]) {

	int day, month, year;

	if (argc > 1) {

		if (strcmp(argv[1], "--help") == 0) {
			print_usage();
		} else { 
			sscanf(argv[1], "%d/%d/%d", &day, &month, &year);
			printf("%s\n", compute_day(day, month-1, year));
		}

		exit(EXIT_SUCCESS);
	}

	init_date(&day, &month, &year);
	print_date(day, month, year);
    printf(": ");

	char *correct_day = compute_day(day, month, year);

    clock_t start = clock();

    char answer[MAX_STR_LEN];
    if (fgets(answer, MAX_STR_LEN, stdin) != NULL) {
		strtok(answer, "\n");
	} else {
		fputs("Something has gone wrong. Exiting.\n", stderr);
		exit(EXIT_FAILURE);
	}

    double elapsed = ((double) (clock() - start)) / (double) CLOCKS_PER_SEC;

    if (strcmp(answer, correct_day) == 0) {
        printf("Correct! (%.6fs)\n", elapsed);
    } else {
        printf("Incorrect. Correct answer was %s (%.6fs)\n", correct_day, elapsed);
    }

    // TODO: fix timing

    return 0;
}
