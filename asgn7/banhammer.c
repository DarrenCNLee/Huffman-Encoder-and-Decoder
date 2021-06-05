// Darren Lee
// CSE13S
// This program implements the main function and regex.
// The banhammer progrma reads in a list of badspeak words
// and newspeak word pairs. Then it uses a hash table
// and Bloom filter to detect if stdin contains badspeak words.
// It then prints out the appropriate message depending on the
// severity of the transgressions and words used.

#include "bf.h"
#include "ht.h"
#include "messages.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "ht:f:ms"
#define WORD    "\\w+([-']\\w+)*"

int main(int argc, char **argv) {
    // code for parsing words inspired by assignment pdf
    regex_t re;
    // stats is a flag for printing statistics
    // thoughtcrime is a flag for whether the citizen is guilty of a thoughtcrime
    // counseling is a flag for whether or not the citizen requires counseling
    int opt, stats = 0, thoughtcrime = 0, counseling = 0;
    char old[2048], new[2048]; // create strings for reading oldspeak and newspeak
    bool mtf = false; // mtf flag for move-to-front rule, disabled by default
    uint64_t hash_size = 10000, bloom_size = 1048576; // defaults for hash table size
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { // parse command line options
        switch (opt) {
        case 'h': // help message inspired by resources repository program
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -m           Enable move-to-front rule.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            return 0; // exit program after printing help message
        case 't':
            // specify hash table size
            hash_size = strtoul(optarg, NULL, 10);
            break;
        case 'f':
            // specify bloom filter size
            bloom_size = strtoul(optarg, NULL, 10);
            break;
        case 'm': mtf = true; break; // enable move to front rule
        case 's': stats = 1; break; // enable printing stats
        default: // if an invalid option is entered, print help message and exit program
            printf("SYNOPSIS\n");
            printf("  A word filtering program for the GPRSC.\n");
            printf("  Filters out and reports bad words parsed from stdin.\n");
            printf("\n");
            printf("USAGE\n");
            printf("  ./banhammer [-hsm] [-t size] [-f size]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h           Program usage and help.\n");
            printf("  -s           Print program statistics.\n");
            printf("  -m           Enable move-to-front rule.\n");
            printf("  -t size      Specify hash table size (default: 10000).\n");
            printf("  -f size      Specify Bloom filter size (default: 2^20).\n");
            return 1;
        }
    }
    if (bloom_size == 0) { // if Bloom filter size is 0, print invalid size message and exit
        fprintf(stderr, "Invalid Bloom filter size.\n");
        return 1;
    }
    if (hash_size == 0) { // if hash table size is 0, print invalid size message and exit
        fprintf(stderr, "Invalid hash table size.\n");
        return 1;
    }
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        // print an error message and exit the program if regex fails to compile
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    // create Bloom filter, hash table, linked list for badspeak used, and linked list for oldspeak words with newspeak translations
    BloomFilter *bf = bf_create(bloom_size);
    if (!bf) { // if the Bloom filter is not created
        clear_words();
        regfree(&re);
        bf_delete(&bf);
        fprintf(stderr, "Failed to create Bloom filter.\n");
        return 1; // print error message and exit
    }
    HashTable *ht = ht_create(hash_size, mtf);
    if (!ht) { // if the hash table is not created
        clear_words();
        regfree(&re);
        bf_delete(&bf);
        ht_delete(&ht);
        fprintf(stderr, "Failed to create hash table.\n");
        return 1; // print error message and exit
    }
    LinkedList *bad_list = ll_create(mtf);
    LinkedList *right_list = ll_create(mtf);
    // open badspeak.txt
    FILE *bad_file = fopen("badspeak.txt", "r");
    if (bad_file == NULL) { // if the file fails to open, print error message and exit
        clear_words();
        regfree(&re);
        bf_delete(&bf);
        ht_delete(&ht);
        fprintf(stderr, "Error: Failed to open badspeak.txt.\n");
        return 1;
    }
    while (fscanf(bad_file, "%s\n", old) != EOF) {
        // read from badspeak.txt
        // insert each oldspeak word into the Bloom filter and hash table
        bf_insert(bf, old);
        ht_insert(ht, old, NULL);
    }
    fclose(bad_file);
    // open newspeak.txt
    FILE *new_file = fopen("newspeak.txt", "r");
    if (new_file == NULL) { // if the file fails to open, print error message and exit
        clear_words();
        regfree(&re);
        bf_delete(&bf);
        ht_delete(&ht);
        fprintf(stderr, "Error: Failed to open newspeak.txt.\n");
        return 1;
    }
    // read from newspeak.txt
    while (fscanf(new_file, "%s %s\n", old, new) != EOF) {
        // insert the oldspeak into the Bloom filter
        bf_insert(bf, old);
        //insert the oldspeak and newspeak pairs into the hash table
        ht_insert(ht, old, new);
    }
    fclose(new_file);
    char *word;
    Node *n;
    // parse the words in stdin
    while ((word = (next_word(stdin, &re))) != NULL) {
        for (uint32_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]); // make the words lowercase to compare
        }
        if (bf_probe(bf, word)) { // if probing the Bloom filter for the word returns true
            n = ht_lookup(ht, word); // lookup the word in the hash table
            if (n) { // if the word is in the hash table
                if (n->newspeak) { // if the word has a newspeak translation
                    // insert the word and newspeak translation into the right_list
                    ll_insert(right_list, word, n->newspeak);
                    counseling = 1; // set counseling flag to 1
                } else if (!n->newspeak) { // else if the word does not have a newspeak translation
                    // insert the word into the bad_list
                    ll_insert(bad_list, word, NULL);
                    thoughtcrime = 1; // set the thoughtcrime flag to 1
                }
            }
        }
    }
    if (!stats) { // if we are not printing statistics
        // if the citize is guilty of thoughtcrime and needs counseling
        if (thoughtcrime && counseling) {
            printf("%s", mixspeak_message); // print mixspeak message
            ll_print(bad_list); // print badspeak words used
            ll_print(right_list); // print oldspeak words used with translations
        } else if (thoughtcrime) { // if only guilty of thoughtcrime
            printf("%s", badspeak_message); // print badspeak message
            ll_print(bad_list); // print badspeak words used
        } else if (counseling) { // if the citizen only requires counseling
            printf("%s", goodspeak_message); // print goodspeak message
            ll_print(right_list); // print oldspeak words with their translations
        }
    } else if (stats) { // else if stats is enabled, print stats
        printf("Seeks: %" PRIu64 "\n", seeks);
        printf("Average seek length: %.6lf\n", (double) links / (double) seeks);
        printf("Hash table load: %.6lf%%\n", 100 * (double) ht_count(ht) / (double) ht_size(ht));
        printf("Bloom filter load: %.6lf%%\n", 100 * (double) bf_count(bf) / (double) bf_size(bf));
    }
    ll_delete(&bad_list);
    ll_delete(&right_list);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
