#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

struct position
{
  int row, col;
};

void initKeyPos(struct position *keys, char *keypad)
{
  int i, j, c = 0, key;
  int init = 0;

  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
    {
      key = keypad[c] - '0';
      assert(!(init & (1 << key)));
      assert(key >= 1 && key <= 9);
      keys[key].row = i;
      keys[key].col = j;
      init |= (1 << key);
      c++;
    }
}

int cost(struct position from, struct position to)
{
  int row_diff, col_diff;
  if (from.row == to.row && from.col == to.col)
    return 0;

  row_diff = (int) abs(from.row - to.row);
  col_diff = (int) abs(from.col - to.col);
  return (row_diff > 1 || col_diff > 1)? 2: 1;
}

int entryTime(char* s, char* keypad) {
  struct position keys[9], *curr = NULL, *pos = NULL;
  int key, total_cost = 0;

  printf("initKeyPos %d\n", strlen(keypad));
  if (!s || !keypad || strlen(keypad) != 9)
    return 0;
  initKeyPos(keys, keypad);

  while (*s)
  {
    key = *s -  '0';
    assert(key >= 1 && key <= 9);
    keys[key];
    if (!curr)
    {
      curr = &keys[key];
      continue;
    }
    total_cost += cost(*curr, keys[key]);
    s++;
    curr = &keys[key];
  }

  return total_cost;
}



int main()
{
  struct position keys[9];
  char keypad [] = {"639485712"};
  char key[80] = {"91566165"};

  printf("output %d\n", entryTime(key, keypad));
}
