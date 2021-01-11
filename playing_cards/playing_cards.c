//   playing_cards.c
//   David Gregg
//   December 2020

#include "playing_cards.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// pack the playing card structures into bytes of memory
unsigned char *pack_playing_cards(struct playing_card *cards,
                                  int number_of_cards) {
    unsigned char packed_cards[] = malloc(sizeof(uint8_t) * (number_of_cards * 6)); // Create packed cards set

    int cardidx = 0; // init card idx to add to packed cards arr
    for (int i = 0; i < number_of_cards; i++) {
        packed_cards[cardidx] = (unsigned char)cards[i].suit; // add suit
        cardidx += 2;
        packed_cards[cardidx] = (unsigned char)cards[i].value; // add value
        cardidx += 4;
    }

    return packed_cards[0];
}

// unpack bytes of memory containing card data into playing card structures
struct playing_card *unpack_playing_cards(unsigned char *packed_cards,
                                          int number_of_cards) {
    struct playing_card *result = malloc(sizeof(struct playing_card) * number_of_cards);
}
