#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char content[100];
    node * no;
    node * yes;
};

// size_t pos;

// void node_insert(node * root, int insert_key);
// void print_tree(node * root);
// node * search_node(node * root, int key);
void save_tree(node * root, FILE* file);
void tree_destr(node * root);
void scan_tree(node * root, FILE* file);
void fill_tree(node * root, char * string, size_t * pos);

int main()
{
    node * root = (node *) calloc(1, sizeof(node));
    // node * start = (node *) calloc(1, sizeof(node));

    // start = root;

    // // char * ans = (char *) calloc(100, sizeof(char));
    // // char * que = (char *) calloc(100, sizeof(char));
    // // char * answer = (char *) calloc(100, sizeof(char));

    // char answer[100];
    // char ans[100];
    // char que[100];

    // char first[100] = "unknown";
    // strcpy(root->content, first);

    // while (true)
    // {
    //     if (root->yes == NULL && root->no == NULL)
    //     {
    //         printf("is your character %s?\n", root->content);
    //         scanf("%s", answer);

    //         if (!strcmp(answer,"yes"))
    //         {
    //             printf("\n\n!!!YOU GOT ZEM RIGHT!!!\n\n");
    //             root = start;
    //         }
    //         else if (!strcmp(answer,"no"))
    //         {
    //             node * new_false = (node *) calloc(1, sizeof(node));
    //             node * new_true = (node *) calloc(1, sizeof(node));
    //             char tmp[100];

    //             printf("who was your character?\n");
    //             scanf("%s", ans);
    //             printf("how is your character diifferent from %s?\n", root->content);
    //             scanf("%s", que);

    //             root->no = new_false;
    //             root->yes = new_true;
    //             strcpy(tmp, root->content);
    //             strcpy(root->content, que);
    //             strcpy(new_false->content, tmp);
    //             strcpy(new_true->content, ans);

    //             root = start;
    //         }
    //         else
    //             break;
    //     }
    //     else
    //     {
    //         printf("is your character %s?\n", root->content);
    //         scanf("%s", answer);

    //         if (!strcmp(answer,"yes"))
    //         {
    //             root = root->yes;
    //         }
    //         else if (!strcmp(answer,"no"))
    //         {
    //             root = root->no;
    //         }
    //         else
    //             break;
    //     }
    // }

    // FILE* tree_save = fopen("tree_save.txt", "wb");
    // save_tree(root, tree_save);
    // fclose(tree_save);

    FILE* tree_scan = fopen("tree_save.txt", "rb");
    scan_tree(root, tree_scan);
    fclose(tree_scan);

    FILE* tree_save = fopen("tree_save2.txt", "wb");
    save_tree(root, tree_save);
    fclose(tree_save);

    tree_destr(root);
}

void save_tree(node * root, FILE* file)
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
    printf("string size: %d\n", size);

    // size_t str_num = 1;

    char* string = (char*) calloc((size + 1), sizeof(char));

    fread(string, sizeof(char), size, file);

    // for (size_t i = 0; i < size; i++)
    // {
    //     if (string[i] == '{' || string[i] == '}')
    //     {
    //         str_num++;
    //     }
    // }
    // str_num = str_num / 2;

    // char * arr_pointer[] = (char**) calloc(str_num, 100);

    // printf("%s", string);

    // size_t pos = 1;
    // node * insert_node_yes = (node *) calloc(1, sizeof(node));
    // node * insert_node_no = (node *) calloc(1, sizeof(node));

    // while (string[pos] != '}' && string[pos] != '{')
    // {
    //     pos++;
    // }

    // // strncpy(root->content, string + 1, pos - 1);    
    // // printf("%s(%d); ", root->content, string[pos]);

    // if (string[pos] == '{')
    // {
    //     root->no = insert_node_no;
    //     root->yes = insert_node_yes;
    // }
    // else if (string[pos] == '}')
    // {
    //     return;        
    // }

    size_t pos = 0;

    fill_tree(root, string, &pos);
}

void fill_tree(node * root, char * string, size_t * pos)
{
    node * insert_node_yes = (node *) calloc(1, sizeof(node));
    node * insert_node_no = (node *) calloc(1, sizeof(node));

    // char buf[100] = {};
    size_t cnt = 1;

    // printf("pos: %d  ", pos);

    // for (; string[pos] != '\0'; pos++)
    // {
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
        printf("%s(%d); ", root->content, string[*pos + cnt]);

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
                
                // if (string[pos - cnt - 1] != '}' || (pos - cnt) == 0)
                // {
                //     fill_tree(root->yes, string, size);
                // }
                // if (string[pos - cnt - 1] == '}')
                // {
                //     fill_tree(root->no, string, size);
                // }

                fill_tree(root->yes, string, pos);
                fill_tree(root->no, string, pos);
            }
        }
        // else if (string[pos + cnt] == '}')
        // {
        //     if (string[pos - 1] != '}' || pos == 0)
        //     {
        //         fill_tree(root->yes, string, size, pos + cnt);
        //     }
        //     else if (string[pos - 1] == '}')
        //     {
        //         fill_tree(root->no, string, size, pos + cnt);
        //     }
        // }
        

        // if (string[pos + cnt] == '{' && string[pos - 2] != '}')
        // {
        //     fill_tree(root->yes, string, size, pos + 1);
        // }
        // else if (string[pos + cnt] == '{' && string[pos - 2] == '}')
        // {
        //     fill_tree(root->no, string, size, pos + 1);
        // }

        // else if (string[pos + cnt] == '}')
        // {
            
        // }
    }
    // }
}

void tree_destr(node * root)
{
    if (root->yes != NULL)
        tree_destr(root->yes);
    if (root->no != NULL)
        tree_destr(root->no);


    free(root);
}
