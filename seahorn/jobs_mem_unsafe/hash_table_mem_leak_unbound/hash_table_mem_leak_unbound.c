/*
 * This is an alternative take on the
 * hash_table_mem_leak job that does not
 * model a complete hash table but instead only
 * materializes a bucket of interest.
 */

#include <seahorn/seahorn.h>
#include <stdbool.h>
#include <stdlib.h>

extern unsigned nd_unsigned(void);
extern bool nd_bool(void);

#define SIZE 10000000

struct item {
  unsigned key;
  struct item *next;
};

// For hashtable operations that
// operate on a single bucket we can model the
// hashtable by a 2-element array.
// One entry at the index of interest and
// another entry for other indices.
// The bucket of interest is called MATERIALIZED_IDX
// in this implementation.
static struct item *buckets[2];
static unsigned MATERIALIZED_IDX;

// Initialize hashtable with zero or 1 default element
// that will be returned when Materialized index is not read
static void initBucket(struct item **bucketsarr) {
  MATERIALIZED_IDX = nd_unsigned();
  unsigned any_value = nd_unsigned();

  struct item *item = malloc(sizeof(struct item));
  item->key = any_value;
  item->next = NULL;
  bucketsarr[0] = nd_bool() ? item : NULL;
}

// For Materialized index i,
// Provides array property : Arr' = store(Arr, i, v)
// where Arr'[i] = v and \forall j != i.Arr'[j] = Arr[j]
static void addToBucket(struct item **bucketsarr, int index,
                        struct item *value) {
  sassert(index < SIZE);
  assume(index == MATERIALIZED_IDX);
  bucketsarr[1] = value;
}

// For Materialized Index,
// Provides array property: select(store(arr, MATERIALIZED_IDX, val),
// MATERIALIZED_IDX) == val
static struct item **getFromBucket(struct item **bucketsarr, int index) {
  sassert(index < SIZE);
  return (index == MATERIALIZED_IDX) ? &bucketsarr[1] : &bucketsarr[0];
}

static void remove(unsigned key) {
  unsigned hash = key % SIZE;
  // Replaced array access with getFromBucket wrapper.
  struct item **pitem = getFromBucket(buckets, hash);
  while (*pitem) {
    struct item *item = *pitem;
    // sassert(item);
    if (item->key == key) {
      *pitem =
          item->next; // Memory Leak (previous value of *pitem is unreachable)
      // pitem = &item->next;
      break;
    }
    pitem = &item->next;
  }
}

int main(void) {
  unsigned i = nd_unsigned();
  unsigned value_to_remove = nd_unsigned();
  unsigned any_value = nd_unsigned();

  initBucket(buckets);
  assume(i < SIZE);
  struct item *item = malloc(sizeof(struct item));
  item->key = value_to_remove;
  item->next = NULL;
  // Replace
  // buckets[IDX] = item;
  // access with addToBucket wrapper
  addToBucket(buckets, i, item);
  remove(any_value);
}
