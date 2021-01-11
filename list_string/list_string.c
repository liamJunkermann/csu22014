//   list_string.c
//   David Gregg
//   January 2021

#include "list_string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string *new_list_string(char *text) {
    struct list_string *result = malloc(sizeof(struct list_string)); // Setup Liststring
    struct ls_node *prev_node = malloc(sizeof(struct ls_node));      // Setup current_node

    char current_char = text[0];

    for (int i = 0; current_char != '\0'; i++) {                       // Loops through text until null char
        current_char = text[i];                                        // Get current char
        if (current_char != 0) {                                       // Ignoring weird edge case
            struct ls_node *new_node = malloc(sizeof(struct ls_node)); // Creating temp node (made sense to create new node here as opposed to reuse one from outside because new memory needs to be allocated)
            new_node->c = current_char;
            new_node->next = NULL;
            if (i == 0)
                result->head = new_node;
            else
                prev_node->next = new_node;
            prev_node = new_node;
        }
    }

    return result;
}

// find the length of the list string
int list_string_length(struct list_string *this) {
    struct ls_node *selected_node = this->head;             // Creating new pointer starting at head
    int count;                                              // Instantiate count
    for (count = 1; selected_node->next != NULL; count++) { // Counting from 1 because people count from 1 not 0, repeating till next elem is null
        selected_node = selected_node->next;
    }
    return count;
}

int get_lex_sum(struct ls_node *head_node) {   // Private function to get lexicographical sum of string
    int sum = (int)head_node->c;               // instantiate with head char val
    struct ls_node *selected_node = head_node; // pointer to selected node

    while (selected_node->next != NULL) {    // repeat till end of string
        selected_node = selected_node->next; // iterate string
        sum += (int)selected_node->c;        // add to sum
    }
    return sum;
}

// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd".
int list_string_compare(struct list_string *s1, struct list_string *s2) {
    int s1_sum = get_lex_sum(s1->head); // use above function to get sum
    int s2_sum = get_lex_sum(s2->head);

    // Straightforward comparisons below.
    if (s1_sum < s2_sum)
        return -1;
    else if (s1_sum > s2_sum)
        return 1;
    else
        return 0;
}

// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string *text, struct list_string *str) {
    int str_length = list_string_length(str);  // Get length of search string
    if (str_length > list_string_length(text)) // Ensure search string is not longer than text string
        return 0;

    struct ls_node *selected_node = text->head; // Temp pointer to iterate through text
    struct ls_node *test_text = text->head;     // temp pointers to compare char values inside second for loop
    struct ls_node *test_str = str->head;

    while (selected_node->next != NULL) {
        int count = 0;                         // Arbitrary count to 0, if this remains 0 after inner for loop, str is substring of text
        test_text = selected_node;             // Set test_text to start at selected node
        test_str = str->head;                  // reset test_str
        for (int i = 0; i < str_length; i++) { // iterate through string length
            if (test_str->c != test_text->c)   // Add to count if there is a non-matching character
                count++;
            test_text = test_text->next;
            test_str = test_str->next;
        }
        selected_node = selected_node->next;    // iterate to next node of text
        if (count == 0)
            return 1;                           // return 1 if substring
    }
    return 0;                                   // If you've reached this point, theres no substring
}
