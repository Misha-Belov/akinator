#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../stand_funcs/stack.h"

struct node
{
    char content[100];
    node * no;
    node * yes;
};

void game(node * root);
void import_tree (node * root);
void person_insert(node * root, char * ans, char * que);
void definition(node * root);
void person_search(node * root, char * person_name, stack * def_stack);
void save_tree(node * root, FILE* file);
void tree_destr(node * root);
void scan_tree(node * root, FILE* file);
void fill_tree(node * root, char * string, size_t * pos);
void draw_tree(node * root, FILE* file);
void draw_node(node * root, FILE* file);


//  dot -Tsvg tree_draw.dot -o tree_draw.svg

