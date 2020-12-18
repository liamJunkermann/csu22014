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
    return result;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder *this, char *filename) {
    unsigned char c;
    FILE *file = fopen(filename, "r");
    assert(file != NULL);
    while (!feof(file)) {
        c = fgetc(file);
        this->freqs[c] += 1;
    }
    for (int i = 0; i < NUM_CHARS; i++) {
        if (this->freqs[i] == 0)
            this->freqs[i] = 1;
    }
    fclose(file);
}

struct huffchar *getLeastFrequent(struct huffchar **nodes, int size) {
    int small = 0;
    for (int i = 0; i < size; i++) {
        if ((nodes[i]->freq < nodes[small]->freq) || ((nodes[i]->freq == nodes[small]->freq) && (nodes[i]->seqno < nodes[small]->seqno))) {
            small = i;
        }
    }

    struct huffchar *returnChar = nodes[small];
    for (int i = small; i < size; i++)
        nodes[i] = nodes[i + 1]; // Removes smallest node
    return returnChar;
}

void fillTree(struct huffchar **nodes, struct huffcoder *this) {
    int space = NUM_CHARS;
    for (int i = 0; space > 1; i++) {
        struct huffchar *s1 = getLeastFrequent(nodes, space--);
        struct huffchar *s2 = getLeastFrequent(nodes, space);
        struct huffchar *combined = malloc(sizeof(struct huffchar));
        combined->freq = (s1->freq) + (s2->freq);
        combined->seqno = NUM_CHARS + i;
        combined->u.compound.left = s1;
        combined->u.compound.right = s2;
        combined->is_compound = 1;
        nodes[space - 1] = combined;
    }
    this->tree = nodes[0];
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder *this) {
    struct huffchar *node[NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; i++) {
        node[i] = malloc(sizeof(struct huffchar *));
        node[i]->freq = this->freqs[i];
        node[i]->u.c = i;
        node[i]->seqno = i;
        node[i]->is_compound = 0;
    }
    fillTree(node, this);
}

void huffcoder_tree2table_rec(struct huffcoder *this, struct huffchar *node, int length, unsigned code) {
    if ((node->is_compound) == (int)1) {
        huffcoder_tree2table_rec(this, node->u.compound.left, length + 1, code);
        code = code | ((unsigned)1 << (length));
        huffcoder_tree2table_rec(this, node->u.compound.right, length + 1, code);
    } else {
        fprintf(stderr, "char: %d, code: %d\n", node->u.c, code);
        this->codes[node->u.c] = (char *)code;
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
        printf("char: %d, freq: %d, code: %c\n", i, this->freqs[i], this->codes[i]);
    }
}

FILE *openFile(char *filename, char *opentype) {
    FILE *file = NULL;
    if (strcmp(opentype, "r")) {
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error Opening file %s, quitting\n", filename);
            exit(1);
        }
    } else if (strcmp(opentype, "a")) {
        file = fopen(filename, "a");
    }

    return file;
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = openFile(input_filename, "r");
    FILE *out_file = openFile(output_filename, "a");
    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
        printf("%s", this->codes[c]);
    }

    fclose(in_file);
    fclose(out_file);
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = openFile((char *)input_filename, "r");
    FILE *out_file = openFile((char *)output_filename, "a");

    struct huffchar *node = this->tree;
    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
    }

    fclose(in_file);
    fclose(out_file);
}
