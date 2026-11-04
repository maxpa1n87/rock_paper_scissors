#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "rock_paper_scissors_config.h"

#define RPS_MAX_INPUT_STRING 128
#define RPS_MAX_CHOICE_LENGTH 3
#define RPS_MAX_INPUT_CONTINUE 4

typedef enum {
    RPS_ENUM_ROCK,
    RPS_ENUM_PAPER,
    RPS_ENUM_SCISSORS,
    RPS_ENUM_COUNT
} RPS_ENUM_CHOICES;

const char *rps_choices[] = {
    "rock",
    "paper",
    "scissors",
    NULL
};

void rps_init() {
    srand((unsigned int)time(NULL));
}

char *rps_get_string(char *buffer, int length) {
    fgets(buffer, length, stdin);
    fflush(stdin);
    return buffer;
}

int rps_generate_random_number() {
    return rand() % RPS_MAX_CHOICE_LENGTH;
}

void rps_lower_string(char *string) {
    char *p = string;
    while(*p) {
        *p = tolower(*p);
        p++;
    }
}

void rps_trim_string(char *string) {

    while(isspace((int)*string)) {
        string++;
    }

    if(*string) {
        char *p = string;
        while (*p) {
            p++;
        }

        while (isspace((int)*(--p))) {

        }

        p[1] = '\0';        
    }
}

int main(int argc, char **argv) {
    char rps_choice[RPS_MAX_INPUT_STRING + 1];
    char rps_cpu_choice[RPS_MAX_INPUT_STRING + 1];
    char rps_continue[RPS_MAX_INPUT_CONTINUE + 1];
    int x; 
    bool found, player_won, keepgoing;

    rps_init();
    printf("Welcome to rock paper and scissors version %d.%d\n",
        rock_paper_scissors_VERSION_MAJOR,
        rock_paper_scissors_VERSION_MINOR);

    found = false;

    keepgoing = true;

    while(keepgoing) {

        while(!found) {
            printf("Type in rock paper or scissors: ");
            memset(rps_choice, 0, sizeof(rps_choice));
            rps_get_string(rps_choice, sizeof(rps_choice));
            rps_lower_string(rps_choice);
            rps_trim_string(rps_choice);
        
            for(x = 0; x < RPS_ENUM_COUNT; x++) {
                if(stricmp(rps_choice, rps_choices[x]) == 0) {
                    found = true;
                    break;
                }
            }

            if(found) {
                printf("You have chosen %s\n", rps_choice);
                break;
            } else {
                printf("Your choice %s can't be right, try again\n", rps_choice);
                continue;
            }
        }

        strncpy(rps_cpu_choice, rps_choices[rps_generate_random_number()], sizeof(rps_cpu_choice));

        printf("CPU choses %s\n", rps_cpu_choice);

        player_won = false;

        if(stricmp(rps_choice, rps_cpu_choice) == 0) {
            printf("This is a draw\n");
        } else {
            if(stricmp(rps_choice, rps_choices[RPS_ENUM_ROCK]) == 0 &&
            stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_SCISSORS]) == 0) {
                player_won = true;
            } else if(stricmp(rps_choice, rps_choices[RPS_ENUM_SCISSORS]) == 0 &&
                    stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_ROCK]) == 0) {
                player_won = false;
            } else if(stricmp(rps_choice, rps_choices[RPS_ENUM_PAPER]) == 0 &&
                    stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_SCISSORS]) == 0) {
                player_won = false;
            } else if(stricmp(rps_choice, rps_choices[RPS_ENUM_SCISSORS]) == 0 &&
                    stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_PAPER]) == 0) {
                player_won = true;
            } else if(stricmp(rps_choice, rps_choices[RPS_ENUM_ROCK]) == 0 &&
                    stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_PAPER]) == 0) {
                player_won = false;
            } else if(stricmp(rps_choice, rps_choices[RPS_ENUM_PAPER]) == 0 &&
                    stricmp(rps_cpu_choice, rps_choices[RPS_ENUM_ROCK]) == 0) {
                player_won = true;
            }

            if(player_won) {
                printf("Player won this time\n");
            } else {
                printf("CPU won this time\n");
            }
        }

        printf("Want to play again? (yes/no): ");
        memset(rps_continue, 0, sizeof(rps_continue));
        rps_get_string(rps_continue, sizeof(rps_continue));
        rps_lower_string(rps_continue);
        rps_trim_string(rps_continue);

        if(stricmp(rps_continue, "yes") == 0) {
            keepgoing = true;
            found = false;
            continue;
        } else if(stricmp(rps_continue, "no") == 0) {
            keepgoing = false;
            found = true;
            break;
        } else {
            printf("Unknown input stopping program\n");
            keepgoing = false;
            found = true;
            break;
        }
    }

    return EXIT_SUCCESS;
}
