#ifndef __BST_H__

typedef struct node
{
    int data;
    struct node *left_child;
    struct node *right_child;
} node_t;

node_t *bst_create(unsigned int n);
void bst_destroy(node_t **root);
int bst_add_node(node_t **cur_root, node_t *new_node);
void bst_print_inorder(node_t *cur_root);
void bst_print_inorder_nonrecur_1stack(node_t *cur_root);
void bst_print_preorder(node_t *cur_root);
void bst_print_postorder(node_t *cur_root);

#endif //__BST_H__
