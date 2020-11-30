#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include the header files with the declarations of listset
#include "listset.h"

// create a new, empty linked list set
struct listset *listset_new() {
    struct listset *result = malloc(sizeof(struct listset));
    result->head = malloc(sizeof(struct listnode));
    result->head = NULL;
    return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset *this, char *item) {
    for (struct listnode *curr = this->head; curr != NULL; curr = curr->next) {
        if (strcmp(curr->str, item) == 0) {
            return 1;
        }
    }
    return 0;
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set.
// New items that are not already in the set should
// be added to the start of the list
void listset_add(struct listset *this, char *item) {
    if (listset_lookup(this, item) == 0) {
        struct listnode *newNode = malloc(sizeof(struct listnode));
        newNode->str = item;
        newNode->next = this->head;
        this->head = newNode;
    }
}

// remove an item with number 'item' from the set
void listset_remove(struct listset *this, char *item) {
    if (listset_lookup(this, item) == 1) { // if item is in list
        int idx = 0;
        for (struct listnode *selected = this->head; selected != NULL; selected = selected->next) {
            if (idx == 0 && strcmp(selected->str, item) == 0) {
                this->head = selected->next;
            }
            if (selected->next != NULL) {
                if (strcmp(selected->next->str, item) == 0) {
                    selected->next = selected->next->next;
                    return;
                }
            }
            idx++;
        }
    }
}

// place the union of src1 and src2 into dest
void listset_union(struct listset *dest, struct listset *src1,
                   struct listset *src2) {
    for (struct listnode *node = src1->head; node != NULL; node = node->next) {
        listset_add(dest, node->str);
    }
    for (struct listnode *node = src2->head; node != NULL; node = node->next) {
        listset_add(dest, node->str);
    }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset *dest, struct listset *src1,
                       struct listset *src2) {
    for (struct listnode *node = src1->head; node != NULL; node = node->next) {
        if (listset_lookup(src2, node->str) == 1) {
            listset_add(dest, node->str);
        }
    }
}

// return the number of items in the listset
int listset_cardinality(struct listset *this) {
    int count = 0;
    for (struct listnode *node = this->head; node != NULL; node = node->next) {
        count++;
    }
    return count;
}

// print the elements of the list set
void listset_print(struct listset *this) {
    struct listnode *p;

    for (p = this->head; p != NULL; p = p->next) {
        printf("%s, ", p->str);
    }
    printf("\n");
}
