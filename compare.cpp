#include "akinator.h"


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

    is_found = 0;
    
    printf("input second character:\n");
    scanf("%s", answer_2);
    person_search(root, answer_2, &def_stack_2, &is_found);

    stack_compare(&def_stack_1, &def_stack_2, &comp_stack);
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
        i++;
    }
}

void print_compare(stack * comp_ctack, stack * def_stack_1, stack * def_stack_2, char * name_1, char * name_2, node * root)
{
    bool is_first = 1;
    bool is_common = 0;

    if(!strcmp(name_1, name_2))
    {
        printf("it is one person");
        return;
    }
    
    if (comp_ctack->size != 0)
    {
        is_common = 1;
        printf("%s is like %s in that they're both ", name_1, name_2);
    }

    while (comp_ctack->size != 0)
    {
        if (is_first == 1)
        {
            printf("%s", root->content);
            is_first = 0;
        }
        else if(comp_ctack->size == 1)
        {
            printf(" and %s", root->content);
        }
        else
        {
            printf(", %s", root->content);
        }

        if (queue_pop(comp_ctack) == 1)
        {
            root = root->yes;
        }
        else
        {
            root = root->no;
        }
        
        queue_pop(def_stack_1);
        queue_pop(def_stack_2);
    }

    if(is_common == 1)
    {
        printf(". ");
        printf("But %s is ", name_1);
    }
    else
    {
        printf("%s is ", name_1);
    }
    print_definition(root, def_stack_1);
    printf(", and %s is ", name_2);
    print_definition(root, def_stack_2);
    printf(".\n");
}
