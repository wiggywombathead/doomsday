#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 64

char *days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
char *months[] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

int main(void) {

    srand(time(NULL));

    int day, month, year;

    year = 1500 + (rand() % 600);
    month = rand() % 12;
    day = rand();

    bool isleap = (year % 4 == 0) ? true : false;

    switch (month) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            day %= 31;
            break;
        case 3:
        case 5:
        case 8:
        case 10:
            day %= 30;
            break;
        case 1:
            day %= (isleap) ? 29 : 28;
		default:
			exit(EXIT_FAILURE);
    }

    printf("%d %s %d: ", day, months[month], year);

    clock_t start = clock();    /* Start timing */

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

    int doomsday = anchor + T;

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
    char *res = days[index];

    char answer[MAX_STR_LEN];
    if (fgets(answer, MAX_STR_LEN, stdin) != NULL) {
		strtok(answer, "\n");
	} else {
		fputs("Something has gone wrong. Exiting.\n", stderr);
		exit(EXIT_FAILURE);
	}

    clock_t finish = clock();
    double elapsed = (double) (finish - start)/CLOCKS_PER_SEC;
    elapsed *= 1e6;

    if (strcmp(answer, res) == 0) {
        printf("Correct! (%.3lfs)\n", elapsed);
    } else {
        printf("Incorrect. Correct answer was %s (%.3lfs)\n", res, elapsed);
    }

    // TODO: fix timing

    return 0;
}
