#include "akinator.h"


int main()
{
    node * root = (node *) calloc(1, sizeof(node));
    
    import_tree(root);
    game(root);
    export_tree(root);

    FILE* tree_draw = fopen("tree_draw.dot", "wb");
    draw_tree(root, tree_draw);
    fclose(tree_draw);

    tree_destr(root);
}

void import_tree(node * root)
{
    char * answer = (char *) calloc(100, sizeof(char));

    printf("do you want to import tree?\n");
    scanf("%s", answer);

    if (!strcmp(answer, "yes"))
    {
        FILE* tree_scan = fopen("tree_save.txt", "rb");
        scan_tree(root, tree_scan);
        fclose(tree_scan);
    }
    else
    {
        char first[100] = "unknown";
        strcpy(root->content, first);
    }

    free(answer);
}

void export_tree(node * root)
{
    char * answer = (char *) calloc(100, sizeof(char));

    printf("do you want to save tree?\n");
    scanf("%s", answer);

    if (!strcmp(answer, "yes"))
    {
        FILE* tree_save = fopen("tree_save2.txt", "wb");
        save_tree(root, tree_save);
        fclose(tree_save);
    }

    free(answer);
}

void game(node * root)
{
    node * start = (node *) calloc(1, sizeof(node));

    start = root;

    char * ans = (char *) calloc(100, sizeof(char));
    char * que = (char *) calloc(100, sizeof(char));
    char * answer = (char *) calloc(100, sizeof(char));

    while (true)
    {
        printf("is your character %s?\n", root->content);
        scanf("%s", answer);

        if (!strcmp(answer, "D") || !strcmp(answer, "d"))
        {
            definition(root);
        }

        if (!strcmp(answer, "C") || !strcmp(answer, "c"))
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