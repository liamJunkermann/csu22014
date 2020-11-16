#include "bitset.h"

// create a new, empty bit vector set with a universe of 'size' items
struct bitset *bitset_new(int size) {
    struct bitset *result = malloc(sizeof(struct bitset));
    int word_size = ((size - 1) / 64) + 1;
    uint64_t *bits = malloc(sizeof(uint64_t *) * word_size);
    for (int i = 0; i < word_size; i++) {
        bits[i] = 0;
    }
    result->bits = bits;
    result->size_in_words = word_size;
    result->universe_size = word_size * 64;
    return result;
}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset *this) {
    int size = this->universe_size;
    return size;
}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset *this) {
    int count = 0;
    for (int i = 0; i < this->size_in_words; i++) {
        uint64_t word = this->bits[i];
        while (word != 0) {
            if (word % 2 == 1) {
                count++;
            }
            word = word / 2;
        }
    }
    return count;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset *this, int item) {
    int block = item / 64;
    int index = item % 64;
    uint64_t word = this->bits[block];
    uint64_t lookupMask = 1UL << 63;
    uint64_t output = word << index;
    if (output & lookupMask) {
        return 1;
    } else {
        return 0;
    }
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset *this, int item) {
    int block = item / 64;
    int index = item % 64;
    uint64_t word = this->bits[block];
    uint64_t mask = 1UL << (63 - index);
    uint64_t output = word | mask;
    this->bits[block] = output;
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset *this, int item) {
    int block = item / 64;
    int index = item % 64;
    uint64_t word = this->bits[block];
    uint64_t mask = (~0UL) ^ (1UL << (63 - index));
    this->bits[block] = word & mask;
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset *dest, struct bitset *src1,
                  struct bitset *src2) {
    int setSize = bitset_size(dest);
    for (int i = 0; i < setSize; i++) {
        if (bitset_lookup(src1, i) == 1 || bitset_lookup(src2, i) == 1) {
            bitset_add(dest, i);
        } else {
            bitset_remove(dest, i);
        }
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset *dest, struct bitset *src1,
                      struct bitset *src2) {
    int setSize = bitset_size(dest);
    for (int i = 0; i < setSize; i++) {
        if (bitset_lookup(src1, i) == 1 && bitset_lookup(src2, i) == 1) {
            bitset_add(dest, i);
        } else
            bitset_remove(dest, i);
    }
}
