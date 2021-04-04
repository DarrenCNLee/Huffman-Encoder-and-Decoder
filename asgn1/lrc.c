// Darren Lee
// CruzID: danalee
// Spring 2021

// This program implements the game Left, Right, and Center.
// The players are 1 to 14 philosophers.
// Each player starts with $3. There are 3 dice with 6 faces each.
// There are 3 pass faces, 1 left face, 1 right face, and 1 center face
// on each die. Player 1 starts and rolls 3 dice if he or she has
// $3 or more. If the player has $2, roll 2 dice. If the player has $1,
// roll 1 die. If the player has no money, he or she passes.
// The player gives $1 to the player on the left if the roll is
// L, gives $1 to the player on the right if the roll is R, puts $1
// in the pot in the center if the roll is C, and ignores a • (pass) roll.
// Then move to the player to the right. Players that lose all their
// money can come back into the game if given money by another player.
// When only one player has money left, that player wins the pot and the
// money they already have.

#include "philos.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define PHILOS 14 // maximum of 14 players

// Returns  the  position  of the  player  to the  left.
// pos:     The  position  of the  current  player.
// players: The  number  of  players  in the  game.
static inline uint8_t left(uint8_t pos, uint8_t players) { // Code from assignment PDF
    return ((pos + players - 1) % players);
}

//  Returns  the  position  of the  player  to the  right.
//  pos:     The  position  of the  current  player.
//  players: The  number  of  players  in the  game.
static inline uint8_t right(uint8_t pos, uint8_t players) { // Code from assignment PDF
    return ((pos + 1) % players);
}

int main(void) {
    typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces; // Code from assignment PDF
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS,
        PASS }; // Code from assignment PDF, array for the faces of each die
    int dollars[]
        = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; // array for the dollars of each player
    int32_t seed;
    int philos,
        roll_state; // philos is the number of players, roll_state is 1 if the player rolls and 0 if the player does not roll
    int pot = 0;

    printf("Random seed: ");
    if ((scanf("%u", &seed) < 1) || seed < 1) { // read a seed
        printf("Pseudorandom seed must be non-negative (%d).\n", seed);
        return 1; // exit main function if number of items succesfully read is < 1 or seed is < 1
    }
    srandom(seed);

    printf("How many players? ");
    if ((scanf("%u", &philos) < 1) || philos < 1 // read number of players
        || philos
               > PHILOS) { // exit main function if number of items successfully read < 1 or the number of players is not from 1 to 14
        printf("Number of players must be from 1 to 14.\n");
        return 1;
    }
    int alive = philos;

    while (alive > 1) { // start game loop

        for (int i = 0; i < philos; i++) { // loop through the players
            roll_state = 0;
            alive = 0;

            for (int j = 0; j < philos;
                 j++) { // loop through players to check how many still have money
                if (dollars[j] > 0) {
                    alive++;
                }
            }
            if (alive == 1) { // exit player loop if there is only one player remaining
                break;
            }
            if (dollars[i] > 0) { // check if the player has money
                printf("%s rolls... ", philosophers[i]);
                roll_state = 1; // player can roll if he or she has money
            }
            int current_dollars = dollars[i], roll_count,
                space_count; // current_dollars is how much money the player has, roll_count is the number of times the player will roll, space_count is how many spaces to print
            if (3
                < current_dollars) { // player can roll 3 times if he or she has more than 3 dollars
                roll_count = 3;
            } else { // otherwise, the number of rolls is equal to the number of dollars the player has
                roll_count = current_dollars;
            }
            space_count = 0;

            for (int k = 0; k < roll_count; k++) { // loop through rolls
                int roll_num = random() % 6; // generate a random roll number
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
                if (space_count
                    < roll_count - 1) { // print a space after each roll message except the last one
                    printf(" ");
                }
                space_count++;
            }
            if (roll_state) { // if roll_state == 1, print a new line
                printf("\n");
            }
        }
    }
    for (int i = 0; i < philos; i++) { // loop through the players
        if (dollars[i] > 0) { // the player with money at the end is the winner
            printf("%s wins the $%u pot with $%u left in the bank!\n", philosophers[i], pot,
                dollars[i]);
        }
    }
    return 0;
}
