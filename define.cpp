#include "akinator.h"


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
    node * tmp_root = root;
    bool is_found = 0;
    char * answer = (char *) calloc(100, sizeof(char));

    stack def_stack;
    stack_construct(&def_stack, 10);

    printf("input your character:\n");
    scanf("%s", answer);

    person_search(root, answer, &def_stack, &is_found);
    printf("%s is ", answer);
    print_definition(root, &def_stack);
    printf(".\n");

    stack_destruct(&def_stack);
    free(answer);

    root = tmp_root;
}

void print_definition(node * root, stack * def_stack)
{
    int direction = 0;
    bool is_first = 1;


    while (def_stack->size != 0)
    {
        direction = queue_pop(def_stack);
        
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
                    printf("%s", root->content);
                }
                else
                {
                    printf("and %s", root->content);
                }
            }
            else
            {
                if(is_first == 1)
                {
                    printf("not %s", root->content);
                }
                else
                {
                    printf("and not %s", root->content);
                }
            }
        }
    }
}

void person_search(node * root, char * person_name, stack * def_stack, bool * is_found)
{    
    if (!strcmp(root->content, person_name))
    {
        *is_found = 1;
        printf("charachter found\n");
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
}
