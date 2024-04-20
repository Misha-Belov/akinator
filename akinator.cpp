#include "akinator.h"

int main()
{
    node * root = (node *) calloc(1, sizeof(node));
    
    import_tree(root);

    game(root);

    FILE* tree_draw = fopen("tree_draw.dot", "wb");
    draw_tree(root, tree_draw);
    fclose(tree_draw);

    FILE* tree_save = fopen("tree_save2.txt", "wb");
    save_tree(root, tree_save);
    fclose(tree_save);

    tree_destr(root);
}

void import_tree(node * root)
{
    char * answer = (char *) calloc(100, sizeof(char));

    // printf("do you want to import tree?\n");
    // scanf("%s", answer);

    // if (!strcmp(answer, "yes"))
    // {
    //     FILE* tree_scan = fopen("tree_save.txt", "rb");
    //     scan_tree(root, tree_scan);
    //     fclose(tree_scan);
    // }
    // else
    // {
    //     char first[100] = "unknown";
    //     strcpy(root->content, first);
    // }

    FILE* tree_scan = fopen("tree_save.txt", "rb");
    scan_tree(root, tree_scan);
    fclose(tree_scan);

    free(answer);
}

void game(node * root)
{
    node * start = (node *) calloc(1, sizeof(node));

    start = root;

    char * ans = (char *) calloc(100, sizeof(char));
    char * que = (char *) calloc(100, sizeof(char));
    char * answer = (char *) calloc(100, sizeof(char));

    // char answer[100];
    // char ans[100];
    // char que[100];

    while (true)
    {
        printf("is your character %s?\n", root->content);
        scanf("%s", answer);

        if (!strcmp(answer, "D"))
        {
            definition(root);
        }

        if (!strcmp(answer, "C"))
        {
            comparison(root);
        }

        if (root->yes == NULL && root->no == NULL)
        {
            if (!strcmp(answer, "yes"))
            {
                printf("\n\n!!!YOU GOT ZEM RIGHT!!!\n\n");
                root = start;
            }
            else if (!strcmp(answer,"no"))
            {
                person_insert(root, ans, que);

                root = start;
            }
            else
                break;
        }
        else
        {
            if (!strcmp(answer,"yes"))
            {
                root = root->yes;
            }
            else if (!strcmp(answer,"no"))
            {
                root = root->no;
            }
            else
                break;
        }
    }

    free(answer);
    free(ans);
    free(que);
}

void person_insert(node * root, char * ans, char * que)
{
    node * new_false = (node *) calloc(1, sizeof(node));
    node * new_true = (node *) calloc(1, sizeof(node));
    char tmp[100];

    printf("who was your character?\n");
    scanf("%s", ans);
    printf("how is your character diifferent from %s?\n", root->content);
    scanf("%s", que);

    root->no = new_false;
    root->yes = new_true;
    strcpy(tmp, root->content);
    strcpy(root->content, que);
    strcpy(new_false->content, tmp);
    strcpy(new_true->content, ans);
}

void definition(node * root)
{
    bool is_found = 0;
    char * answer = (char *) calloc(100, sizeof(char));
    stack def_stack;
    stack_construct(&def_stack, 10);

    printf("input your character:\n");
    scanf("%s", answer);

    person_search(root, answer, &def_stack, &is_found);
    print_stack(&def_stack);
    printf("%s is ", answer);
    print_definition(root, &def_stack);

    stack_destruct(&def_stack);
    free(answer);
}

void comparison(node * root)
{
    bool is_found = 0;

    char * answer_1 = (char *) calloc(100, sizeof(char));
    char * answer_2 = (char *) calloc(100, sizeof(char));

    stack def_stack_1;
    stack def_stack_2;
    stack comp_stack;

    stack_construct(&def_stack_1, 10);
    stack_construct(&def_stack_2, 10);
    stack_construct(&comp_stack, 10);

    printf("input first character:\n");
    scanf("%s", answer_1);
    person_search(root, answer_1, &def_stack_1, &is_found);
    print_stack(&def_stack_1);

    is_found = 0;
    
    printf("input second character:\n");
    scanf("%s", answer_2);
    person_search(root, answer_2, &def_stack_2, &is_found);
    print_stack(&def_stack_2);

    stack_compare(&def_stack_1, &def_stack_2, &comp_stack);
    print_stack(&comp_stack);
    print_compare(&comp_stack, &def_stack_1, &def_stack_2, answer_1, answer_2, root);


    stack_destruct(&def_stack_1);
    stack_destruct(&def_stack_2);
    stack_destruct(&comp_stack);

    free(answer_1);
    free(answer_2);
}

void stack_compare(stack * def_stack_1, stack * def_stack_2, stack * comp_stack)
{
    int i = 0;
    while (def_stack_1->data[i] == def_stack_2->data[i])
    {
        if (def_stack_1->data[i] == 1)
        {
            push(comp_stack, 1);
        }
        else
        {
            push(comp_stack, 0);
        }
        // printf("direct - %d", def_stack_1->data[i]);
        i++;
    }
}


void print_definition(node * root, stack * def_stack)
{
    int direction = 0;
    bool is_first = 1;
    // bool is_prelast = 0; 


    while (def_stack->size != 0)
    {
        direction = queue_pop(def_stack);
        // printf("direct: %d\n", direction);
        
        if (def_stack->size != 0)
        {
            is_first = 0;

            if (direction == 1)
            {
                if (def_stack->size == 1)
                {
                    printf("%s ", root->content);
                }
                else
                {
                    printf("%s, ", root->content);
                }
                root = root->yes;
            }
            else
            {
                if (def_stack->size == 1)
                {
                    printf("not %s ", root->content);
                }
                else
                {
                    printf("not %s, ", root->content);
                }
                root = root->no;
            }
        }
        else
        {
            if (direction == 1)
            {
                if(is_first == 1)
                {
                    printf("%s.\n", root->content);
                }
                else
                {
                    printf("and %s.\n", root->content);
                }
            }
            else
            {
                if(is_first == 1)
                {
                    printf("not %s.\n", root->content);
                }
                else
                {
                    printf("and not %s.\n", root->content);
                }
            }
        }
    }
}

void print_compare(stack * comp_ctack, stack * def_stack_1, stack * def_stack_2, char * name_1, char * name_2, node * root)
{
    int direction_1 = 0;
    int direction_2 = 0;
    bool is_first = 1;
    // bool is_prelast = 0; 

    if(!strcmp(name_1, name_2))
    {
        printf("it is one person");
        return;
    }

    while (def_stack_1->size != 0 && def_stack_2->size != 0)
    {
        direction_1 = queue_pop(def_stack_1);
        direction_2 = queue_pop(def_stack_2);

        if (direction_1 == direction_2 && is_first == 1)
        {
            if(direction_1 == 1)
            {
                printf("%s is like %s in that they're both %s", name_1, name_2, root->content);
                root = root->yes;
            }
            if(direction_1 == 0)
            {
                printf("%s is like %s in that they're both not %s", name_1, name_2, root->content);
                root = root->no;
            }

            direction_1 = queue_pop(def_stack_1);
            direction_2 = queue_pop(def_stack_2);

            while (direction_1 == direction_2 && def_stack_1->size != 0 && def_stack_2->size != 0)
            {
                if(direction_1 == 1)
                {
                    printf(", %s", root->content);
                    root = root->yes;
                }
                if(direction_1 == 0)
                {
                    printf(", not %s", root->content);
                    root = root->no;
                }

                direction_1 = queue_pop(def_stack_1);
                direction_2 = queue_pop(def_stack_2);
            }
        }
    }
}

void person_search(node * root, char * person_name, stack * def_stack, bool * is_found)
{
    // print_stack(def_stack);
    // printf("%s\n", root->content);
    
    if (!strcmp(root->content, person_name))
    {
        *is_found = 1;
        printf("charachter found\n");
        // print_stack(def_stack);
        return;
    }
    if (root->yes != NULL && *is_found == 0)
    {
        push(def_stack, 1);
        person_search(root->yes, person_name, def_stack, is_found);
        if (*is_found == 1) return;
        pop(def_stack);
    }
    if (root->no != NULL && *is_found == 0)
    {
        push(def_stack, 0);
        person_search(root->no, person_name, def_stack, is_found);
        if (*is_found == 1) return;
        pop(def_stack);
    }
    // return;
    // print_queue(def_stack);
}

void save_tree(node * root, FILE * file)
{
    fprintf(file, "{%s", root->content);

    if (root->yes != NULL)
        save_tree(root->yes, file);
    if (root->no != NULL)
        save_tree(root->no, file);

    
    fprintf(file, "}");
}

void scan_tree(node * root, FILE* file)
{
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    // printf("string size: %d\n", size);

    char* string = (char*) calloc((size + 1), sizeof(char));

    fread(string, sizeof(char), size, file);

    size_t pos = 0;

    fill_tree(root, string, &pos);
}

void fill_tree(node * root, char * string, size_t * pos)
{
    node * insert_node_yes = (node *) calloc(1, sizeof(node));
    node * insert_node_no = (node *) calloc(1, sizeof(node));

    size_t cnt = 1;

    while (string[*pos] != '{' && string[*pos] != '\0')
    {
        (*pos)++;
    }
    
    if (string[*pos] == '{')
    {
        while (string[*pos + cnt] != '}' && string[*pos + cnt] != '{')
        {
            cnt++;
        }

        strncpy(root->content, string + *pos + 1, cnt - 1);    
        // printf("%s(%d); ", root->content, string[*pos + cnt]);

        *pos += cnt;

        if (string[*pos] == '{')
        {
            if (string[*pos + 1] == '}')
            {
                *pos += 3;
            }
            else 
            {
                root->no = insert_node_no;
                root->yes = insert_node_yes;

                fill_tree(root->yes, string, pos);
                fill_tree(root->no, string, pos);
            }
        }
    }
}

void draw_tree(node * root, FILE* file)
{
    fprintf(file, "digraph {\n");
    draw_node(root, file);
    fprintf(file, "}\n");
}

void draw_node(node * root, FILE* file)
{
    fprintf(file, "\t\"%p\" ", root);

    fprintf(file, "[label = \"%s\", color = \"blue\"]\n", root->content);

    if (root->no != NULL)
    {
        fprintf(file, "\t\"%p\" -> \"%p\"\n", root, root->no);
        draw_node(root->no, file);
    }
    if (root->yes != NULL)
    {
        fprintf(file, "\t\"%p\" -> \"%p\"\n", root, root->yes);
        draw_node(root->yes, file);
    }
}


void tree_destr(node * root)
{
    if (root->yes != NULL)
        tree_destr(root->yes);
    if (root->no != NULL)
        tree_destr(root->no);


    free(root);
}

int queue_pop(struct stack* pstk)
{
    if (pstk->size == 0)
    {
        printf("queue is empty\n");
        return -374560234;
    }

    pstk->data++;
    pstk->size--;
    return *(pstk->data - 1);
}