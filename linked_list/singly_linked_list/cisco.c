
struct node {
  int val;
  struct node* next;
} *head=NULL;

void delete_aLL_nodes_ge_x(struct node *head, int x)
{
  struct node *h = head;

  while(h && h->val >= x)
    h = h->next;
  if (!h)
    return;

  prev = h;
  h = h->next;
  while (h)
  {
    if (h->val >= x)
    {
      prev->next = h->next;
    }
    else
    {
      prev = h;
    }
    h = h->next;
  }
}
