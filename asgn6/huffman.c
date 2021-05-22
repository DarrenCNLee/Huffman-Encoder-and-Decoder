// Darren Lee
// CSE13S
// This program implments the Huffman coding module interface.

#include "huffman.h"

#include "code.h"
#include "defines.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// This function creates the codes for each symbol and stores the in the code table.
void postorder(Node *n, Code table[static ALPHABET], Code c) {
    uint8_t bit; // bit for popping
    if (n) { // if node is not null
        if (!n->left && !n->right) {
            table[n->symbol] = c; // if the node is a leaf, store the code for the node's symbol
        }
        code_push_bit(&c, 0); // push a 0
        postorder(n->left, table, c); // go to the left child
        code_pop_bit(&c, &bit); // pop the 0
        code_push_bit(&c, 1); // push a 1
        postorder(n->right, table, c); // go the right child
        code_pop_bit(&c, &bit); // pop the 1
    }
}

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *q = pq_create(ALPHABET); // create a priority queue
    Node *left, *right, *root; // nodes for left, right, and root
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            // if the histogram has a non-zero frequency for the symbol, enqueue a node with that symbol and that symbol's frequency
            enqueue(q, node_create(i, hist[i]));
        }
    }
    while (pq_size(q) > 1) { // while there is more than one node in the priority queue
        dequeue(q, &left); // dequeue and store the node in the left child
        dequeue(q, &right); // dequeue and store the node in the right child
        enqueue(q, node_join(left, right)); // enqueue the parent of the left and right children
    }
    dequeue(q, &root); // dequeue the last node and store in the root
    pq_delete(&q); // delete the priority queue
    return root; // return the root
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init(); // create a code c
    postorder(root, table, c); // create the codes using a postorder traversal
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *s = stack_create(ALPHABET); // create a stack
    Node *left, *right, *root; // create left, right, and root nodes
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') { // if the symbol is an 'L'
            // create a node with the symbol of the next symbol and push it on the stack
            stack_push(s, node_create(tree_dump[i + 1], 0));
            i++; // increment the index
        } else if (tree_dump[i] == 'I') { // if the symbol is an 'I'
            stack_pop(s, &right); // pop and store in the right node
            stack_pop(s, &left); // pop and store in the left node
            // push the parent node of the left and right children
            stack_push(s, node_join(left, right));
        }
    }
    stack_pop(s, &root); // pop the last node and store in the  root
    stack_delete(&s); // delete the stack
    return root; // return the root
}

// uses a postorder traversal to delete each node in the tree when given the root
void delete_tree(Node **root) {
    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
