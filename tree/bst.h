#ifndef __BST_H__

typedef struct node
{
    int data;
    struct node *parent;
    struct node *left_child;
    struct node *right_child;
} node_t;

node_t *bst_create(unsigned int n);
node_t *bst_find_node(node_t *cur_root, int data);
void bst_destroy(node_t **root);
int bst_add_node(node_t **cur_root, node_t *new_node);
int bst_cal_height(node_t *cur_root);
void bst_print_level_spiral(node_t *cur_root, int level, int alternate);
void bst_print_spiral(node_t *cur_root);
void bst_print_inorder(node_t *cur_root);
void bst_print_inorder_nonrecur(node_t *cur_root);
void bst_print_inorder_nonrecur_1stack(node_t *cur_root);
void bst_print_preorder(node_t *cur_root);
void bst_print_preorder_nonrecur(node_t *cur_root);
void bst_print_postorder(node_t *cur_root);
void bst_print_postorder_nonrecur(node_t *cur_root);
void bst_print_levelwise(node_t *cur_root);
int bst_is_cousin(node_t *cur_root, node_t *a, node_t *b);

#endif //__BST_H__
