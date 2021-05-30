#include "bf.h"
#include "ht.h"
#include "messages.h"
#include "parser.h"
#include "speck.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "htfms"
#define WORD    "[_a-zA-Z0-9'-]+"

int main(int argc, char **argv) {
    // code inspired by assignment pdf
    regex_t re;
    int opt, c, stats = 0, thoughtcrime = 0, counseling = 0;
    char *old, *new;
    bool mtf = false;
    uint64_t hash_size = 10000, bloom_size = 1 << 20;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
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
            return 0;
        case 't': hash_size = strtoul(optarg, NULL, 10); break;
        case 'f': bloom_size = strtoul(optarg, NULL, 10); break;
        case 'm': mtf = true; break;
        case 's': stats = 1; break;
        default:
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
            return 0;
        }
    }
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    BloomFilter *bf = bf_create(bloom_size);
    HashTable *ht = ht_create(hash_size, mtf);
    LinkedList *bad_list = ll_create(mtf);
    LinkedList *right_list = ll_create(mtf);
    FILE *bad_file = fopen("badspeak.txt", "r");
    while ((c = fscanf(bad_file, "%s\n", old)) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, NULL);
    }
    fclose(bad_file);
    FILE *new_file = fopen("newspeak.txt", "r");
    while ((c = fscanf(new_file, "%s %s\n", old, new)) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    }
    fclose(new_file);
    char *word;
    Node *n;
    while ((word = next_word(stdin, &re)) != NULL) {
        if (bf_probe(bf, word)) {
            n = ht_lookup(ht, word);
            if (n) {
                if (n->newspeak) {
                    ll_insert(right_list, word, n->newspeak);
                    counseling = 1;
                } else {
                    ll_insert(bad_list, word, NULL);
                    thoughtcrime = 1;
                }
            }
        }
    }
    if (!stats) {
        if (thoughtcrime && counseling) {
            printf("%s", mixspeak_message);
            ll_print(bad_list);
            ll_print(right_list);
        } else if (thoughtcrime) {
            printf("%s", badspeak_message);
            ll_print(bad_list);
        } else if (counseling) {
            printf("%s", goodspeak_message);
            ll_print(right_list);
        }
    }
    ll_delete(&bad_list);
    ll_delete(&right_list);
    bf_delete(&bf);
    ht_delete(&ht);
    clear_words();
    regfree(&re);
    return 0;
}
