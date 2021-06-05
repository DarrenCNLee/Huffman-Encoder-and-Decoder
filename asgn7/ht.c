// Darren Lee
// CSE13S
// This program implements the hash table ADT.

#include "ht.h"

#include "ll.h"
#include "speck.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// struct definition provided by Professor Long in assignment pdf
struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// contructor function provided by Professor Long in assignment pdf
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < ht_size(*ht); i++) {
            if ((*ht)->lists[i]) { // delete each of the linked lists
                ll_delete(&((*ht)->lists[i]));
            }
        }
        free((*ht)->lists);
        free(*ht); // free the hash table, and the lists
        *ht = NULL; // set the pointer to null
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // use ll_lookup to search for the oldspeak
    return ll_lookup(ht->lists[hash(ht->salt, oldspeak) % ht_size(ht)], oldspeak);
    // returns null if the node is not fount
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // hash the oldspeak to get the index
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    if (!ht->lists[index]) { // if the list at the index is null
        ht->lists[index] = ll_create(ht->mtf); // create the list
    }
    ll_insert(ht->lists[index], oldspeak, newspeak); // insert the old and newspeak into the list
}

uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        if (ht->lists[i]) { // if the list is not null
            count++; // increment count
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        if (ht->lists[i]) { // if the list is not null
            ll_print(ht->lists[i]); // print the list
        }
    }
}
