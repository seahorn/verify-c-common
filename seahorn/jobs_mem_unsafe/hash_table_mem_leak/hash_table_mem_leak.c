/*
 * 
 */

#include <seahorn/seahorn.h>
#include <stdlib.h>

extern unsigned nd_unsigned(void);

#define SIZE 1000

struct item {
    unsigned key;
    struct item *next;
};

static struct item *buckets[SIZE];

/* Data Layout for buckets
          buckets
     ┌───────────────┐       struct item     struct item
     │               │      ┌──────────┐     ┌──────────┐
  [0]│ struct item * ├─────▶│          │────▶│          │────▶ ...
     ├───────────────┤      └──────────┘     └──────────┘
     │               │      ┌──────────┐
  [1]│ struct item * ├─────▶│          │────▶ ...
     ├───────────────┤      └──────────┘
     │               │
     │      ...      │
     ├───────────────┤      ┌──────────┐
     │               ├─────▶│          │────▶ ...
[max]│ struct item * │      └──────────┘
     └───────────────┘
*/

static void remove(unsigned key) {
    unsigned hash = key % SIZE;
    struct item **pitem = &buckets[hash];
    // #pragma unroll(SIZE)
    while (*pitem) {
        struct item *item = *pitem;
        // sassert(item);
        if (item->key == key) {
            *pitem = item->next; // Memory Leak (previous value of *pitem is unreachable)
            // pitem = &item->next;
            break;
        }

        pitem = &item->next;
    }
}

int main(void) {
    // #pragma unroll(SIZE)
    for (int i = 0; i < SIZE; i++) {
        struct item *item = malloc(sizeof(struct item));
        item->key = nd_unsigned();
        item->next = NULL;
        buckets[i] = item;
    }

    remove(nd_unsigned());
}
