// code for a huffman coder

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *huffcoder_new() {
    struct huffcoder *result = malloc(sizeof(struct huffcoder));
    for (int i = 0; i < NUM_CHARS; i++) {
        result->freqs[i] = 0;
        result->code_lengths[i] = 0;
        result->codes[i] = 0;
    }
    result->tree = malloc(sizeof(struct huffchar) * NUM_CHARS);
    result->tree->freq = 1;
    result->tree->is_compound = 0;
    result->tree->seqno = 0;
    result->tree->u.c = '\0';
    result->tree->u.compound.left = (struct huffchar *)malloc(sizeof(struct huffchar));
    result->tree->u.compound.right = (struct huffchar *)malloc(sizeof(struct huffchar));

    return result;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder *this, char *filename) {
    FILE *file = fopen(filename, "r");
    unsigned char c;
    while (!feof(file)) {
        c = fgetc(file);
        this->freqs[(int)c]++;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if (this->freqs[i] == 0)
            this->freqs[i] = 1;
    }
    fclose(file);
}

// finds, removes and returns the least frequent node
struct huffchar *getSmallest(struct huffchar **nodes, int size) {
    int smallest = 0;
    for (int i = 0; i < size; i++) {
        if (nodes[i]->freq < nodes[smallest]->freq) { // if no smaller, lowest index
            smallest = i;
        } else if ((nodes[i]->freq == nodes[smallest]->freq) && (nodes[i]->seqno < nodes[smallest]->seqno)) {
            smallest = i;
        }
    }
    struct huffchar *to_return = nodes[smallest];
    // removes node
    for (int index = smallest; index < size; index++) {
        nodes[index] = nodes[index + 1];
    }
    return to_return;
}

// completes the huffman tree
void finishTree(struct huffchar **nodes, struct huffcoder *this) {
    int space = NUM_CHARS;
    int n = 0;
    while (space > 1) {
        struct huffchar *small1 = getSmallest(nodes, space--);
        struct huffchar *small2 = getSmallest(nodes, space);
        struct huffchar *combined = malloc(sizeof(struct huffchar));
        combined->freq = (small1->freq) + (small2->freq);
        combined->seqno = NUM_CHARS + n++;
        combined->u.compound.left = small1;
        combined->u.compound.right = small2;
        combined->is_compound = 1;
        nodes[space - 1] = combined;
    }
    this->tree = nodes[0];
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder *this) {
    struct huffchar *nodes[NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; i++) {
        nodes[i] = malloc(sizeof(struct huffchar *));
        nodes[i]->freq = this->freqs[i];
        nodes[i]->u.c = i;
        nodes[i]->seqno = i;
        nodes[i]->is_compound = 0;
    }

    finishTree(nodes, this);
}

char *toBinaryString(unsigned long long code, int length) {
    char *buffer = malloc(length + 1);
    int i;
    for (i = 0; i < length; i++) {
        buffer[i] = (char)((code >> i) & 1) + '0';
    }
    buffer[i] = '\0';
    return buffer;
}

void huffcoder_tree2table_rec(struct huffcoder *this, struct huffchar *node, int length, unsigned long long code) {
    if ((node->is_compound) == (int)1) {
        huffcoder_tree2table_rec(this, node->u.compound.left, length + 1, code);
        code = code | ((unsigned long long)1 << (length));
        huffcoder_tree2table_rec(this, node->u.compound.right, length + 1, code);
    } else {
        char *binaryChar = toBinaryString(code, length);
        this->codes[node->u.c] = binaryChar;
        this->code_lengths[node->u.c] = length;
    }
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder *this) {
    huffcoder_tree2table_rec(this, this->tree, 0, 0);
}

// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder *this) {
    for (int i = 0; i < NUM_CHARS; i++) {
        // print the code
        printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);
    }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = fopen(input_filename, "r");
    FILE *out_file = fopen(output_filename, "w");
    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
        fputs(this->codes[c], out_file);
    }
    fputs(this->codes[4], out_file);

    fclose(in_file);
    fclose(out_file);
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = fopen(input_filename, "r");
    FILE *out_file = fopen(output_filename, "w");

    struct huffchar *node = this->tree;
    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
    }

    fclose(in_file);
    fclose(out_file);
}
