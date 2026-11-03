#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define RPS_MAX_INPUT_STRING 128
#define RPS_MAX_CHOICE_LENGTH 3

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
    srand(time(NULL));
}

const char *rps_get_string(char *buffer) {
    fgets(buffer, RPS_MAX_INPUT_STRING + 1, stdin);
    return buffer;
}

int rps_generate_random_number() {
    return rand() % RPS_MAX_CHOICE_LENGTH + 1;
}

void rps_lower_string(char *string) {
    char *p = string;
    while(*p) {
        *p = tolower(*p);
        p++;
    }
}

void rps_trim_string(char *string) {
    char *p = string;

    while(isspace(*string)) {
        string++;
    }

    while(*p++ = *string++) {}
}

int main(int argc, char **argv) {
    char rps_choice[RPS_MAX_INPUT_STRING + 1];
    char rps_cpu_choice[RPS_MAX_INPUT_STRING + 1];
    int x; 
    bool found, player_won;

    rps_init();
    printf("Welcome to rock paper and scissors");

    found = false;

    while(!found) {
        printf("Type in rock paper or scissors: ");
        rps_get_string(rps_choice);
        rps_lower_string(rps_choice);
        rps_trim_string(rps_choice);
    
        for(x = 0; x < sizeof(rps_choices) / sizeof(rps_choices[0]); x++) {
            if(strncmp(rps_choice, rps_choices[x], RPS_MAX_INPUT_STRING) == 0) {
                found = true;
                break;
            }
        }

        if(found) {
            printf("You have chosen %s\n", rps_choice);
            break;
        } else {
            printf("Your choice %s can't be right, try again\n");
        }
    }

    strncpy(rps_cpu_choice, rps_choices[rps_generate_random_number()], RPS_MAX_INPUT_STRING);

    printf("CPU choses %s\n", rps_cpu_choice);

    player_won = false;

    if(stricmp(rps_choice, rps_cpu_choice) == 0) {
        printf("This is a draw\n");
    } else {
        if(stricmp(rps_choice, rps_choices[RPS_ENUM_ROCK]) == 0 &&
           srticmp(rps_cpu_choice, rps_choices[RPS_ENUM_SCISSORS]) == 0) {
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
        }
    }

    return EXIT_SUCCESS;
}
