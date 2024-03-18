#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char content[100];
    node * no;
    node * yes;
};

// void node_insert(node * root, int insert_key);
// void print_tree(node * root);
// node * search_node(node * root, int key);
void print_tree(node * root, FILE* file);
void tree_destr(node * root);

int main()
{
    node * root = (node *) calloc(1, sizeof(node));
    node * start = (node *) calloc(1, sizeof(node));

    start = root;

    // char * ans = (char *) calloc(100, sizeof(char));
    // char * que = (char *) calloc(100, sizeof(char));
    // char * answer = (char *) calloc(100, sizeof(char));

    char answer[100];
    char ans[100];
    char que[100];

    char first[100] = "unknown";
    strcpy(root->content, first);

    while (true)
    {
        if (root->yes == NULL && root->no == NULL)
        {
            printf("is your character %s?\n", root->content);
            scanf("%s", answer);

            if (!strcmp(answer,"yes"))
            {
                printf("\n\n!!!YOU GOT ZEM RIGHT!!!\n\n");
                root = start;
            }
            else if (!strcmp(answer,"no"))
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

                root = start;
            }
            else
                break;
        }
        else
        {
            printf("is your character %s?\n", root->content);
            scanf("%s", answer);

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

    FILE* tree_save = fopen("tree_save.txt", "wb");
    print_tree(root, tree_save);

    tree_destr(root);
}

void print_tree(node * root, FILE* file)
{
    fprintf(file, "{%s", root->content);

    if (root->yes != NULL)
        print_tree(root->yes, file);
    if (root->no != NULL)
        print_tree(root->no, file);

    fprintf(file, "}");
}

void tree_destr(node * root)
{
    if (root->yes != NULL)
        tree_destr(root->yes);
    if (root->no != NULL)
        tree_destr(root->no);

    free(root);
}
