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
 * Find given data in binary search tree.
 * Returns pointer to the node on success and NULL on failure.
 *
 * @cur_root : Root of the binary search tree.
 * @data : Data that needs to be found in the tree.
 */
node_t *bst_find_node(node_t *cur_root, int data)
{
    node_t *node = NULL;

    if (cur_root)
    {
        if (cur_root->data == data)
        {
            return node;
        }

        node = bst_find_node(cur_root->left_child, data);
        if (node)
        {
            return node;
        }

        return bst_find_node(cur_root->right_child, data);
    }
    else
    {
        return NULL;
    }
}

/*
 * Calculate height of a binary search tree, find length of longest path.
 *
 * @cur_root : Root of a binary search tree.
 */
int bst_cal_height(node_t *cur_root)
{
    int left_sub_tree_length = 0, right_sub_tree_length = 0;

    if (!cur_root)
    {
        return 0;
    }

    left_sub_tree_length = bst_cal_height(cur_root->left_child);
    right_sub_tree_length = bst_cal_height(cur_root->right_child);

    return 1 + (left_sub_tree_len > right_sub_tree_length)? left_sub_tree_len: right_sub_tree_length;
}

/*
 * Print nodes from given node in spiral fashion of Binary search tree.
 *
 * @cur_root : Root of a binary search tree.
 * @level : Print nodes from this level.
 * @alternate : if non-zero print in nodes in forward order otherwise reverse order.
 */
void bst_print_level_spiral(node_t *cur_root, int level, int alternate)
{
    if (!cur_root)
    {
        return;
    }
    else if (level == 1)
    {
        printf("%d ", cur_root->data);
    }
    else
    {
        assert(level > 1);
        if (alternate)
        {
            bst_print_level_spiral(cur_root->left_child, level - 1, alternate);
            bst_print_level_spiral(cur_root->right_child, level - 1, alternate);
        }
        else
        {
            bst_print_level_spiral(cur_root->right_child, level - 1, alternate);
            bst_print_level_spiral(cur_root->left_child, level - 1, alternate);
        }
    }
}

/*
 * Print Binary Search Tree in spiral (or zig-zag) fashion.
 * We travel from root to given level before we start printing nodes.
 *
 * @cur_root  Root of binary search tree.
 */
void bst_print_spiral(node_t *cur_root)
{
    int height = bst_cal_height(cur_root);
    int i, alternate = 0;

    for (i = 1; i < height; i++)
    {
        bst_print_level_spiral(cur_root, i, alternate);

        alternate = ~alternate;
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
    node_t *current = cur_root;
    bool done = 0;

    stack_init(&nodes_stack);

    while (!done)
    {
        /* Reach the left most tNode of the current tNode */
        if(current !=  NULL)
        {
            /* place pointer to a tree node on the stack before traversing 
               the node's left subtree */
            stack_push(&nodes_stack, current);                                               
            current = current->left;  
        }

        /* backtrack from the empty subtree and visit the tNode 
           at the top of the stack; however, if the stack is empty,
           you are done */
        else                                                             
        {
            if (!stack_empty(&nodes_stack))
            {
                current = stack_pop(&nodes_stack);
                printf("%d ", current->data);

                /* we have visited the node and its left subtree.
                   Now, it's right subtree's turn */
                current = current->right;
            }
            else
                done = 1; 
        }
    }
}

// BST node which also has pointer to its parent node, root->parent == NULL.
typedef struct Node_t
{
    int data;
    struct Node_t *left_child, *right_child, *parent;
} Node_t;

void bst_print_inorder_nonrecur_nostack(Node_t *root)
{
    Node_t *node = cur_root;

    if (!node)
    {
        //NO-OP.
        return;
    }

    while (1)
    {
        while (node->left_child)
        {
            node = node->left_child;
        }

        printf("%d ", node->data);

        while (1)
        {
            if (node->right_child)
            {
                node = node->right_child;
                break;
            }

            while (node->parent)
            {
                if (node == node->parent->left_child)
                {
                    printf("%d ", node->parent->data);
                    node = node->parent;
                    break;
                }

            }
            else
            {
                break;
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

/*
 * Find A is cousin of B or not.
 * Returns 1 on success and 0 on failure.
 *
 * @cur_root : Root of the Binary search tree.
 * @a : Node A from above tree.
 * @b : Node B from above tree.
 */
int bst_is_cousin(node_t *cur_root, node_t *a, node_t *b)
{
    queue_t q;
    int is_cousin = 0, found_a = 0, found_b = 0;

    if (!cur_root || !a || !b)
    {
        //NO-OP.
        return 0;
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
                is_cousin = 0;
                continue;
            }

            if (found_a || found_b)
            {
                //A & B are not on same level so there are not cousins.
                is_cousin = 0;
                break;
            }

            //All nodes from the next level have already been enqueued, mark end of next level.
            queue_add(&q, NULL);
            continue;
        }

        if ((node->left_child == a && node->right_child == b) ||
            (node->left_child == b && node->right_child == a))
        {
            //They are siblings not cousins.
            is_cousin = 0;
            break;
        }
        else if (!found_a || !found_b)
        {
            if (node->left_child == a || node->right_child == a)
            {
                assert(found_a == 0);
                found_a = 1;
            }
            if (node->left_child == b || node->right_child == b)
            {
                assert(found_b == 0);
                found_b = 1;
            }
        }

        if (found_a && found_b)
        {
            //They are cousins of each other.
            is_cousin = 1;
            break;
        }
        else
        {
            //We haven't found either or both of them, let's check next nodes.
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

    queue_destroy(&q);

    return is_cousin;
}

/*
 * Check given Binary Tree is mirror of itself or not.
 * Returns 1 on success and 0 on failure.
 *
 * @current : Root of the binary search tree.
 */
int bst_check_mirror(node_t *cur_root)
{
/*
Sol 1
// Returns true if trees with roots as root1 and root2 are mirror
bool isMirror(struct Node *root1, struct Node *root2)
{
    // If both trees are emptu, then they are mirror images
    if (root1 == NULL && root2 == NULL)
        return true;
 
    // For two trees to be mirror images, the following three
    // conditions must be true
    // 1 - Their root node's key must be same
    // 2 - left subtree of left tree and right subtree
    //      of right tree have to be mirror images
    // 3 - right subtree of left tree and left subtree
    //      of right tree have to be mirror images
    if (root1 && root2 && root1->key == root2->key)
        return isMirror(root1->left, root2->right) &&
               isMirror(root1->right, root2->left);
 
    // if neither of above conditions is true then root1
    // and root2 are not mirror images
    return false;
}
 
// Returns true if a tree is symmetric i.e. mirror image of itself
bool isSymmetric(struct Node* root)
{
    // Check if tre is mirror of itself
    return isMirror(root, root);
}
*/


    /* Count of nodes which have been visited/processed in the current level. */
    unsigned int visited_node_count = 1;
    /* Total number of nodes in the current level, */
    unsigned int cur_level_total_nodes = 1;
    /* Stack to store visited nodes. */
    Stack_t mirror_nodes;
    queue_t visited_nodes;

    stack_init(&mirror_nodes);
    queue_init(&visited_nodes);

    queue_add(&visited_nodes, cur_root);

    while (!queue_empty(&visited_nodes))
    {
        //We have visited all th nodes in the current level, check for mirror condition.
        if (visited_node_count == cur_level_total_nodes)
        {
            unsigned int i = 0;
            node_t *node = NULL;

            for (i = 0; i < (visited_node_count / 2); i++)
            {
                node = queue_remove(&visited_nodes);
                stack_push(&mirror_nodes, node);
            }

            //Order of nodes in second half has to be exactly opposite of first half.
            while (!stack_empty(&mirror_nodes))
            {
                if (stack_pop(&mirror_nodes) != queue_remove(&visited_nodes))
                {
                    //
                    is_mirror = 0;
                }
            }
        }

    }
}

/*
 * Given a root/sub-tree find smallest element in it.
 * Returns pointer to the smallest element NULL on failure.
 *
 * @node : Root of BST.
 */
Node_t *bst_find_minimum(Node_t *node)
{
    if (!node)
    {
        //NO-OP.
        return NULL;
    }

    while (node->left_child)
    {
        node = node->left_child;
    }

    return node;
}

/*
 * Given a root/sub-tree find largest element in it.
 * Returns pointer to the largest element NULL on failure.
 *
 * @node : Root of BST.
 */
Node_t *bst_find_maximum(Node_t *node)
{
    if (!node)
    {
        //NO-OP.
        return NULL;
    }

    while (node->right_child)
    {
        node = node->right_child;
    }

    return node;
}

/*
 * Given a node from binary search tree find its predecessor i.e.
 * find a node which would appeared just before a (given) node if we travals the tree in in-order fashion.
 * On success returns pointer to the predecessor NULL on failure.
 *
 * @node : BST node.
 */
Node_t *bst_find_predecessor(Node_t *node)
{
    Node_t *ancestor = NULL;

    if (!node)
    {
        //NO-OP.
        return NULL;
    }

    if (node->left_child)
    {
        //By BST property, all elements in the left sub-tree are <= node, so predecessor must be the largest
        //amoung those nodes.
        return bst_find_maximum(node->left_child);
    }

    //If right sub-tree is empty then node predecessor must be one of its lowest ancestor such that given node is in its (ancestor's)
    //right sub-tree, if its in left sub-tree how the ancestor can come before the node otherwise.
    ancestor = node->parent;
    while (ancestor && acestor->left_child == node)
    {
        node = ancestor;
        ancestor = node->parent;
    }

    return ancestor;
}

// This function returns overall maximum path sum in 'res'
// And returns max path sum going through root.
int findMaxUtil(Node* root, int &res)
{
    //Base Case
    if (root == NULL)
        return 0;
 
    // l and r store maximum path sum going through left and
    // right child of root respectively
    int l = findMaxUtil(root->left,res);
    int r = findMaxUtil(root->right,res);
 
    // Max path for parent call of root. This path must
    // include at-most one child of root
    int max_single = max(max(l, r) + root->data, root->data);
 
    // Max Top represents the sum when the Node under
    // consideration is the root of the maxsum path and no
    // ancestors of root are there in max sum path
    int max_top = max(max_single, l + r + root->data);
 
    res = max(res, max_top); // Store the Maximum Result.
 
    return max_single;
}
 
// Returns maximum path sum in tree with given root
//Input: Root of below tree
//       1
//      / \
//     2   3
//Output: 6
//
//See below diagram for another example.
//1+2+3
int findMaxSum(Node *root)
{
    // Initialize result
    int res = INT_MIN;
 
    // Compute and return result
    findMaxUtil(root, res);
    return res;
}

// Utility function to store vertical order in map 'm'
// 'hd' is horigontal distance of current node from root.
// 'hd' is initally passed as 0
void getVerticalOrder(Node* root, int hd, map<int, vector<int>> &m)
{
    // Base case
    if (root == NULL)
        return;
 
    // Store current node in map 'm'
    m[hd].push_back(root->key);
 
    // Store nodes in left subtree
    getVerticalOrder(root->left, hd-1, m);
 
    // Store nodes in right subtree
    getVerticalOrder(root->right, hd+1, m);
}
 
// The main function to print vertical oder of a binary tree
// with given root
//           1
//        /    \
//       2      3
//      / \    / \
//     4   5  6   7
//             \   \
//              8   9 
//               
//              
//The output of print this tree vertically will be:
//4
//2
//1 5 6
//3 8
//7
//9
void printVerticalOrder(Node* root)
{
    // Create a map and store vertical oder in map using
    // function getVerticalOrder()
    map < int,vector<int> > m;
    int hd = 0;
    getVerticalOrder(root, hd,m);
 
    // Traverse the map and print nodes at every horigontal
    // distance (hd)
    map< int,vector<int> > :: iterator it;
    for (it=m.begin(); it!=m.end(); it++)
    {
        for (int i=0; i<it->second.size(); ++i)
            cout << it->second[i] << " ";
        cout << endl;
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

