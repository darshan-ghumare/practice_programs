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
 * Print Binary Search Tree in inorder fashion without using recursion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_inorder_nonrecur(node_t *cur_root)
{
    /* Stack of nodes that we have visited but yet to process their left sub-tree. */
    Stack_t nodes_stack;
    /* Stack of childrens of nodes in the above stack which are yet to be visited. */
    Stack_t childs_stack;

    stack_init(&nodes_stack);
    stack_init(&childs_stack);

    if (!cur_root)
    {
        //NO-OP.
        return;
    }

    /* we have just visited root's parent :). */
    stack_push(&childs_stack, cur_root);

    while (!stack_empty(&childs_stack) || !stack_empty(&nodes_stack))
    {
        if (!stack_empty(&childs_stack))
        {
            node_t *child = (node_t *) stack_pop(&childs_stack);
            assert(child);

            if (child->left_child)
            {
                /* As this is inorder we need to process left sub-tree first. */
                stack_push(&childs_stack, child->left_child);
                /* Once left sub-tree is prcessed we can process its parent then. */
                stack_push(&nodes_stack, child);
            }
            else
            {
                //Done with left sub-tree.
                printf("%d ", child->data);

                if (child->right_child)
                {
                    stack_push(&childs_stack, child->right_child);
                }
            }
        }
        else
        {
            assert(!stack_empty(&nodes_stack));
            node_t *node = (node_t *) stack_pop(&nodes_stack);
            assert(node);

            //Done with left sub-tree.
            printf("%d ", node->data);

            if (node->right_child)
            {
                stack_push(&childs_stack, node->right_child);
            }
        }
    }

    assert(stack_empty(&nodes_stack) && stack_empty(&childs_stack));
}

/*
 * Print Binary Search Tree in in-order fashion without using recursion using single stack.
 *
 * @cur_root : Pointer to the root of the binary search tree.
 */
void bst_print_inorder_nonrecur_1stack(node_t *cur_root)
{
    /* Stack of nodes of which we have processed left sub-tree. */
    Stack_t nodes_stack;
    node_t *node = cur_root;

    stack_init(&nodes_stack);

    while (node || !stack_empty(&nodes_stack))
    {
        if (node)
        {
            //First process left sub-tree.
            while (node->left_child)
            {
                //Push current node on stack for processing of right sub-tree later.
                stack_push(&nodes_stack, node);
                node = node->left_child;
            }

            printf("%d ", node->data);
            node = node->right_child;
        }
        else
        {
            assert(!stack_empty(&nodes_stack));
            node = (node_t *) stack_pop(&nodes_stack);
            assert(node);

            printf("%d ", node->data);
            node = node->right_child;
        }
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
 * Printf Binary Search tree in preorder fashion without recursion.
 *
 * @cur_root : Root of the Biinary Search Tree.
 */
void bst_print_preorder_nonrecur(node_t *cur_root)
{
    /* Stack of nodes of which we have processed left sub-tree. */
    Stack_t nodes_stack;
    node_t *node = cur_root;

    stack_init(&nodes_stack);

    while (node || !stack_empty(&nodes_stack))
    {
        if (node)
        {
            printf("%d ", node->data);

            //Process left sub-tree.
            while (node->left_child)
            {
                //Push current node on stack for processing of right sub-tree later.
                stack_push(&nodes_stack, node);
                node = node->left_child;
                printf("%d ", node->data);
            }

            node = node->right_child;
        }
        else
        {
            assert(!stack_empty(&nodes_stack));
            node = (node_t *) stack_pop(&nodes_stack);
            assert(node);

            node = node->right_child;
        }
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

/*
 * Print Binary Search Tree in preorder fashion without recursion.
 *
 * @cur_root : Root of the Binary Search Tree.
 */
void bst_print_postorder_nonrecur(node_t *cur_root)
{
    /* Stack of nodes of which we have processed left sub-tree. Once right sub-tree is processed pop it. */
    Stack_t nodes_stack;
    node_t *node = cur_root;

    stack_init(&nodes_stack);

    while (node || !stack_empty(&nodes_stack))
    {
        if (node)
        {
            //Process left sub-tree.
            while (node->left_child)
            {
                //Push current node on stack for processing of right sub-tree later.
                stack_push(&nodes_stack, node);
                node = node->left_child;
            }

            /*
             * We have processed left sub-tree of the current node.
             * Add a marker before processing right sub-tree.
             * This will helps us to know that we have processed both left and right sub-tree.
             */
            stack_push(&nodes_stack, node);
            stack_push(&nodes_stack, NULL);
            node = node->right_child;
        }
        else
        {
            assert(!stack_empty(&nodes_stack));
            node = (node_t *) stack_top(&nodes_stack);

            while (!node && !stack_empty(&nodes_stack))
            {
                //Done with both left and right sub-tree.
                node = (node_t *) stack_pop(&nodes_stack);
                assert(!node);
                node = (node_t *) stack_pop(&nodes_stack);
                assert(node);
                printf("%d ", node->data);

                node = (node_t *) stack_top(&nodes_stack);
            }

            if (!stack_empty(&nodes_stack))
            {
                /*
                 * We have processed left sub-tree of the current node (at top-of-stack).
                 * Add a marker before processing right sub-tree.
                 * This will helps us to know that we have processed both left and right sub-tree.
                 */
                stack_push(&nodes_stack, NULL);
                node = node->right_child;
            }
        }
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

int main()
{
    unsigned int n;
    node_t *root = NULL;
    queue_t *q = NULL;
    Stack_t *stack = NULL;

    printf("Please enter number nodes : ");
    scanf("%u", &n);
    printf("Please enter their data : ");
    root = bst_create(n);

    printf("\nPre-Order:\n");
    bst_print_preorder(root);
    printf("\nPre-Order-ono-resursive:\n");
    bst_print_preorder_nonrecur(root);
    printf("\nIn-Order:\n");
    bst_print_inorder(root);
    printf("\nIn-Order-Nonrecursive:\n");
    bst_print_inorder_nonrecur(root);
    printf("\nIn-Order-Nonrecursive-one-stack:\n");
    bst_print_inorder_nonrecur_1stack(root);
    printf("\nPost-Order:\n");
    bst_print_postorder(root);
    printf("\nPost-Order-ono-resursive:\n");
    bst_print_postorder_nonrecur(root);
    printf("\nLevel-wise:\n");
    bst_print_levelwise(root);
    printf("\n=======================\n");
    bst_destroy(&root);
    assert(!root);

    return 0;
}

void test_stack_queue()
{
    unsigned int n;
    queue_t *q = NULL;
    Stack_t *stack = NULL;

    printf("Please enter number nodes : ");
    scanf("%u", &n);
    printf("\nPlease enter queue data : ");
    q = queue_create(n);
    printf("\nQueue entries:\n");
    queue_print(q);
    printf("\n=======================\n");
    //queue destroy
    while (!queue_empty(q))
    {
        free(queue_remove(q));
    }
    free(q);

    printf("\nPlease enter stack data : ");
    stack = stack_create(n);
    printf("\nStack entries:\n");
    stack_print(stack);
    printf("\n=======================\n");
    //Stack destroy
    while (!stack_empty(stack))
    {
        free(stack_pop(stack));
    }
    free(stack);
}

