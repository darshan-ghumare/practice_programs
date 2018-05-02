#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "log.h"
#include "queue.h"
#include "stack.h"


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
                new_node->parent = root;
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
                new_node->parent = root;
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
 * @data : Their data.
 */
node_t *bst_create(unsigned int n, int data[])
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

        new_node->data = data[i];
        new_node->parent = new_node->left_child = new_node->right_child = NULL;

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
        if (cur_root->parent)
          printf("(of %d) ", cur_root->parent->data);
        bst_print_inorder(cur_root->right_child);
    }
}

/*
 * Print Binary Search Tree in level-wise fashion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_levelwise(node_t *cur_root)
{
    queue_t q;

    if (!cur_root)
    {
        //NO-OP.
        return;
    }

    queue_init(&q);

    queue_add(&q, cur_root);
    queue_add(&q, NULL);

    while (!queue_empty(&q))
    {
        node_t *node = (node_t *) queue_remove(&q);

        //End of current level.
        if (!node)
        {
            if (queue_empty(&q))
            {
                //We have processed all the nodes.
                continue;
            }

            //All nodes from the next level have already been enqueued, mark end of next level.
            queue_add(&q, NULL);
            //Print nodes from next level on the next line.
            printf("\n");
            continue;
        }

        printf("%d ", node->data);

        if (node->left_child)
        {
            queue_add(&q, node->left_child);
        }
        if (node->right_child)
        {
            queue_add(&q, node->right_child);
        }
    }
}

void bst_in_order_nonrecursive(node_t *root)
{
  while (root)
  {
    while (root->left_child)
      root = root->left_child;

    printf("%d ", root->data);

    if (root->right_child)
    {
      root = root->right_child;
    }
    else
    {
      while (1)
      {
        while (root->parent && root == root->parent->right_child)
          root = root->parent;
        if (root->parent)
        {
          root = root->parent;
          printf("%d ", root->data);
          if (root->right_child)
          {
            root = root->right_child;
            break;
          }
        }
        else
          return;
      }
    }
  }
}

/*
 * Interval Tree :-
 * INterval tree is BST which help us to serv rnge query.
 * Ex :- Given n appointments, find all conflicting appointments
 * https://www.geeksforgeeks.org/given-n-appointments-find-conflicting-appointments/
 * Each node in Interval tree has three elements :- lo, high amd max. Low and
 * high tells us appointment legnth amd max tell us max(high) of all nodes
 * rooted ar the ginve node.
 $
 */

/*
 * Segment Tree
 * https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
 */

/*
 * Get rank of element in the array.
 * https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
 */


int main()
{
    //unsigned int n = 11;
    unsigned int n = 12;
    //int data[] = {65,50,100,43,60,95,110,47,75,98,45};
    int data[] = {24, 27, 29, 34, 14, 4, 10, 22, 13, 3, 2, 6};
    node_t *root = NULL;
    queue_t *q = NULL;
    Stack_t *stack = NULL;

    root = bst_create(n, data);

    printf("\nIn-Order:\n");
    bst_print_inorder(root);
    printf("\nLevelwise:\n");
    bst_print_levelwise(root);
    printf("\nIn-Order non-recursive:\n");
    bst_in_order_nonrecursive(root);
    printf("\n\n");
    bst_destroy(&root);
    assert(!root);

    return 0;
}
