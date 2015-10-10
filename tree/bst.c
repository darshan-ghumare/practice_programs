#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

/*
 * Previous versions of CPP implemented the comma-deletion extension much more generally. We have restricted it in this release to minimize the differences from C99.
 * To get the same effect with both this and previous versions of GCC, the token preceding the special ‘##’ must be a comma,
 * and there must be white space between that comma and whatever comes immediately before it:
 * #define eprintf(format, args...) fprintf (stderr, format , ##args)
 *
 * Source : https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
 */
#define LOG_ERR(MSG, ...) do { \
        fprintf(stderr, "%s():%d " MSG "\n", __func__, __LINE__ , ##__VA_ARGS__); \
} while (0)


/*
 * Add new node into Binary Search Tree.
 * Returns zero on success and -1 on failure.
 *
 * @data : Data corresponding to the new node.
 * @cur_root : Root of the Binary search tree.
 */
int bst_add_node(node_t **cur_root, node_t *new_node)
{
    int ret = 0;

    assert(cur_root);
    assert(new_node);

    do
    {
        node_t *root = *cur_root;

        // Tree is empty, this is the first node.
        if (!(*cur_root))
        {
            *cur_root = new_node;
            ret = 0;
            break;
        }
        else if (root->data == new_node->data)
        {
            LOG_ERR("%d node already exist.", new_node->data);
            ret = -1;
            break;
        }
        else if (new_node->data < root->data)
        {
            if (root->left_child)
            {
                return bst_add_node(&root->left_child, new_node);
            }
            else
            {
                root->left_child = new_node;
                ret = 0;
                break;
            }
        }
        else
        {
            if (root->right_child)
            {
                return bst_add_node(&root->right_child, new_node);
            }
            else
            {
                root->right_child = new_node;
                ret = 0;
                break;
            }
        }
    } while (0);

    return ret;
}

/*
 * Free the memory allocated for each node in the tree.
 *
 * @cur_root : Double pointer to the root of the Binary Search Tree. Reset it to NULL 
 */
void bst_destroy(node_t **cur_root)
{
    assert(cur_root);

    node_t *root = *cur_root;

    if (root)
    {
        bst_destroy(&root->left_child);
        bst_destroy(&root->right_child);

        free(root);
        *cur_root = NULL;
    }
}

/*
 * Create Binary Search with given number of nodes.
 * Accept data part from stdin for each node.
 * Returns pointer to the root of the newly created tree on success and NULL on error.
 *
 * @n : Number of nodes.
 */
node_t *bst_create(unsigned int n)
{
    node_t *root = NULL;
    unsigned int i = 0;

    for (i = 0; i < n; i++)
    {
        node_t *new_node = (node_t *) malloc(sizeof (node_t));

        if (!new_node)
        {
            LOG_ERR("Failed to allocate memory for new node.\n");
            bst_destroy(&root);
            break;
        }

        scanf("%d", &new_node->data);
        new_node->left_child = new_node->right_child = NULL;

        if (bst_add_node(&root, new_node) != 0)
        {
            LOG_ERR("Failed to add new node %d.\n", new_node->data);
            free(new_node);
            bst_destroy(&root);
            break;
        }
    }

    return root;
}

/*
 * Print Binary search Tree in inorder fashion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_inorder(node_t *cur_root)
{
    if (cur_root)
    {
        bst_print_inorder(cur_root->left_child);
        printf("%d ", cur_root->data);
        bst_print_inorder(cur_root->right_child);
    }
}

/*
 * Print Binary search Tree in preorder fashion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_preorder(node_t *cur_root)
{
    if (cur_root)
    {
        printf("%d ", cur_root->data);
        bst_print_preorder(cur_root->left_child);
        bst_print_preorder(cur_root->right_child);
    }
}

/*
 * Print Binary search Tree in postorder fashion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_postorder(node_t *cur_root)
{
    if (cur_root)
    {
        bst_print_postorder(cur_root->left_child);
        bst_print_postorder(cur_root->right_child);
        printf("%d ", cur_root->data);
    }
}

int main()
{
    unsigned int n;
    node_t *root = NULL;

    printf("Please enter number nodes : ");
    scanf("%u", &n);
    printf("Please enter their data : ");
    root = bst_create(n);

    printf("\nPre-Order:\n");
    bst_print_preorder(root);
    printf("\nIn-Order:\n");
    bst_print_inorder(root);
    printf("\nPost-Order:\n");
    bst_print_postorder(root);
    printf("\n=======================\n");
    bst_destroy(&root);
    assert(!root);

    return 0;
}

