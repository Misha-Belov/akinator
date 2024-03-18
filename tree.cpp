#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    node * no;
    node * yes;
};

void node_insert(node * root, int insert_key);
void print_tree(node * root);
node * search_node(node * root, int key);
void delete_node(node * root, int key);
void tree_destr(node * root);

int main()
{
    node * root = (node *) calloc(1, sizeof(node));
    root->key = 50;
    node_insert(root, 60);
    node_insert(root, 30);
    node_insert(root, 5);
    node_insert(root, 10);
    node_insert(root, 20);
    node_insert(root, 100);
    node_insert(root, 40);
    search_node(root, 5);
    // delete_node(root, 5);
    print_tree(root);
    tree_destr(root);
}

void node_insert(node * root, int insert_key)
{
    node * insert_node = (node *) calloc(1, sizeof(node));
    insert_node->key = insert_key;

    while (1)
    {
        if (insert_node->key < root->key)
        {
            if (root->yes == NULL)
            {
                root->yes = insert_node;
                break;
            }
            else
                root = root->yes;
        }
        else
        {
            if (root->no == NULL)
            {
                root->no = insert_node;
                break;
            }
            else
                root = root->no;
        }
    }
}

void print_tree(node * root)
{
    printf("{%d", root->key);

    if (root->yes != NULL)
        print_tree(root->yes);
    if (root->no != NULL)
        print_tree(root->no);

    printf("}");
}

node * search_node(node * root, int key)
{
    while (1)
    {
        if (root->key == key)
        {
            printf("number exist in tree\n");
            return root;
        }
        if (root->key < key)
        {
            if (root->no == NULL)
            {
                printf("root doesn't exist in tree\n");
                return NULL;
            }
            root = root->no;
        }
        if (root->key > key)
        {
            if (root->yes == NULL)
            {
                printf("root don't exist in tree\n");
                return NULL;
            }
            root = root->yes;
        }
    }
}

void delete_node(node * root, int key)
{
    node * tmp1 = (node *) calloc(1, sizeof(node));
    node * tmp2 = (node *) calloc(1, sizeof(node));
    // node * remove = (node *) calloc(1, sizeof(node));
    node * remove = search_node(root, key);
    // node * tmp = remove->right;

    memcpy(tmp1, remove->no, sizeof(node));
    // tmp = remove->right;

    printf("%d %d\n", remove->key, tmp1->key);

    // remove = remove->left;

    // memcpy(remove, remove->left, sizeof(node));
    memcpy(tmp2, remove->yes, sizeof(node));
    memcpy(remove, tmp2, sizeof(node));

    printf("%d %d\n", remove->key, tmp1->key);

//     if(tmp != NULL)
//     {
//         while(remove->right != NULL)
//         {
//             remove = remove->right;
//         }
//
//         // memcpy(remove->right, tmp1, sizeof(node));
//         remove->right = tmp1;
//     }
}

void tree_destr(node * root)
{
    if (root->yes != NULL)
        tree_destr(root->yes);
    if (root->no != NULL)
        tree_destr(root->no);

    free(root);
}
