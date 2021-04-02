#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define PHILOS 14

// Returns  the  position  of the  player  to the  left.
// pos:     The  position  of the  current  player.
// players: The  number  of  players  in the  game.
static inline uint8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

//  Returns  the  position  of the  player  to the  right.
//  pos:     The  position  of the  current  player.
//  players: The  number  of  players  in the  game.
static inline uint8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

// Returns a random number from 0 to n
static inline uint32_t roll(uint32_t n) {
    return random() % n;
}

int main(void) {
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
    uint32_t dollars[] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };    // array for the dollars of each player
    uint32_t seed, philos, roll_state;
    uint32_t pot = 0;
    printf("Random seed: ");
    if (scanf("%u", &seed) < 1 || seed < 1) {
        printf("Pseudorandom seed must be non-negative (%u).\n", seed);
        return 1;
    }
    srandom(seed);                                                        
    printf("How many players? ");
    if ((scanf("%u", &philos) < 1) || philos < 1 || philos > PHILOS) {    // exit main function if the number of players
        printf("Number of players must be from 1 to 14.\n");              // is not from 1 to 14
        return 1;
    }
    uint32_t alive = philos;
    while (alive > 1) {
        for (uint32_t i = 0; i < philos; i++) {
            roll_state = 0;
            alive = 0;
            for (uint32_t k = 0; k < philos; k++) {
                if (dollars[k] > 0) {
                    alive++;
                }
            }
            if (alive == 1) {
                break;
            }
            if (dollars[i] > 0) {                                         // check how much money the player has
                printf("%s rolls... ", philosophers[i]);
                roll_state = 1;
            }
            uint32_t current_dollars = dollars[i], min, space_count;
            if (3 < current_dollars) {
                min = 3;
            } else {
                min = current_dollars;
            }
            space_count = 0;
            for (uint32_t j = 0; j < min; j++) {
                uint32_t roll_num = roll(6);
                if (die[roll_num] == LEFT) {
                    dollars[i]--;
                    dollars[left(i, philos)]++;
                    printf("gives $1 to %s", philosophers[left(i, philos)]);
                }
                if (die[roll_num] == RIGHT) {
                    dollars[i]--;
                    dollars[right(i, philos)]++;
                    printf("gives $1 to %s", philosophers[right(i, philos)]);
                }
                if (die[roll_num] == CENTER) {
                    dollars[i]--;
                    pot++;
                    printf("puts $1 in the pot");
                }
                if (die[roll_num] == PASS) {
                    printf("gets a pass");
                }
                if (space_count < min - 1) {
                    printf(" ");
                }
                space_count++;
            }
            if (roll_state) {
                printf("\n");
            }
        }
    }
    for (uint32_t i = 0; i < philos; i++) {
        if (dollars[i] > 0) {
            printf("%s wins the $%u pot with $%u left in the bank!\n", philosophers[i], pot,
                dollars[i]);
        }
    }
    return 0;
}
