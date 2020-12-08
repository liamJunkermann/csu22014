// code for a huffman coder

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

void huffcoder_tree2table_rec(struct huffcoder *this, struct huffchar *node, int *path, int depth) {
    if (node->is_compound) {
        // Handle if it is a compound
        int *temp = malloc(sizeof(int) * depth + 1);
        for (int i = 0; i < depth; i++) {
            temp[i] = path[i];
        }
        temp[depth] = 0;
        if (node->u.compound.left != NULL) {
            huffcoder_tree2table_rec(this, node->u.compound.left, temp, depth + 1);
        }
        if (node->u.compound.right != NULL) {
            huffcoder_tree2table_rec(this, node->u.compound.right, temp, depth + 1);
        }
    } else {
        // Is a char node
        unsigned long long code = 0;
        for (int i = 0; i < depth; i++) {
            code = (code << 1) | path[i];
        }
        this->codes[node->u.c] = code;
        this->code_lengths[node->u.c] = depth;
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
        ;
    }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = openFile(input_filename, "r");
    FILE *out_file = openFile(output_filename, "a");
    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
        fprintf(out_file, "%s", this->codes[c]);
    }
}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder *this, char *input_filename,
                      char *output_filename) {
    FILE *in_file = openFile(input_filename, "r");
    FILE *out_file = openFile(output_filename, "a");

    unsigned char c;
    while (!feof(in_file)) {
        c = fgetc(in_file);
    }
}

FILE *openFile(char *filename, char opentype) {
    FILE *file = fopen(filename, opentype);
    if (file == NULL) {
        printf("Error Opening file %s, quitting\n", filename);
        exit(1);
    }

    return file;
}

char findChar(struct huffcoder *this, char *code) {
}