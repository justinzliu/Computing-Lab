#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
   int* data;
   unsigned int len;
} intarr_t;

typedef enum {
  INTARR_OK,
  INTARR_BADARRAY,
  INTARR_BADINDEX,
  INTARR_BADALLOC,
  INTARR_NOTFOUND
} intarr_result_t;

int insertion_sort(int arr[], int len) {
   int tempvar;
   for ( int i=1; i <= len-1; i++ ) {
      int x = arr[i];
      int j = i;
      while ( j > 0 && x < arr[j-1] ) { 
         tempvar = arr[j];
         arr[j] = arr[j-1];
         arr[j-1] = tempvar;
         j--;
      }
   }
   return 0;
}

int insertion_sort(int arr[], int len);

/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len ) 
{
   intarr_t* ptr = malloc(sizeof(intarr_t));
   if (ptr != 0) {
      ptr->len = len;
      ptr->data = malloc(len*sizeof(int));
      if (ptr->data != 0) {
         return ptr;
      }
   }
   return NULL;
}

// frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia ) 
{
   if ( ia != 0 && ia->data != 0 ) {
      free(ia);
   }
   return;
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
			    unsigned int index, 
			    int val ) 
{
   if (ia == 0) {
      return INTARR_BADARRAY;
   }
   else if (index < ia->len) {
      ia->data[index] = val;
      return INTARR_OK;
   }
   return INTARR_BADINDEX;
}

// If index is valid and i is non-null, set *i to ia->data[index] and return
// INTARR_OK. Otherwise no not modify *i and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
			    unsigned int index, 
			    int* i ) 
{
   if (ia == 0) {
      return INTARR_BADARRAY;
   }
   if (index < ia->len && i != 0) {
      *i = ia->data[index];
      return INTARR_OK;
   }
   return INTARR_BADINDEX;
}

/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia ) {
   intarr_t* COPYia = malloc(sizeof(intarr_t));
   unsigned int numbytes = (ia->len)*sizeof(int);
   COPYia->data = malloc(numbytes);
   COPYia->len = ia->len;
   if (COPYia->data != 0 && ia != 0) {
      memcpy(COPYia->data,ia->data,numbytes);
      return COPYia;
   }
   return NULL;
}

/* LAB 5 TASK 4 */

// sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia ) {
   if (ia != 0 && ia->data != 0) {
      insertion_sort(ia->data,ia->len);
      return INTARR_OK;
   }
   return INTARR_BADARRAY;
}

/* LAB 5 TASK 5 */

// Find the first occurance of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ) {
   if (ia != 0 && ia->data != 0) {
      for (int j=0; j<(ia->len); j++) {
         if (ia->data[j] == target) {
            if (i != NULL) {
               *i = j;
               return INTARR_OK;
            }
         }
      }
      return INTARR_NOTFOUND;
   }
   return INTARR_BADARRAY;
}

/* LAB 5 TASK 6 */

// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val ) {
   if (ia != 0 && ia->data != 0) {
      ia->data = realloc(ia->data,((ia->len)+1)*sizeof(int));
      if (ia->data != 0) {
         ia->data[ia->len] = val;
         ia->len = (ia->len)+1;
         return INTARR_OK;
      }
      else {
         return INTARR_BADALLOC;
      }
   }
   return INTARR_BADARRAY;
}

// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i ) {
   if (ia != 0) {
      if (ia->data != 0 && i != 0) {
         *i = ia->data[ia->len-1];
         ia->data = realloc(ia->data,((ia->len)-1)*sizeof(int));
         ia->len = ia->len-1;
         return INTARR_OK;

      }
      else {
         return INTARR_BADINDEX;
      }
   }
   return INTARR_BADARRAY;
}

/* LAB 5 TASK 7 */

// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ) {
   if (ia != 0 && ia->data != 0) {
      if (newlen < ia->len) {
         ia->data = realloc(ia->data,((ia->len)-1)*sizeof(int));
         ia->len = newlen;
      }
      else if (newlen > ia->len) {
         ia->data = realloc(ia->data,newlen*sizeof(int));
         ia->len = newlen;
         for (int i=ia->len; i<newlen; i++) {
            ia->data[i] = 0;
         }
      }
      if (ia->data != 0) {
         return INTARR_OK;
      }
      return INTARR_BADALLOC;
   }
   return INTARR_BADARRAY;
}

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
				unsigned int first, 
				unsigned int last ) {
   if (ia != 0 && ia->data != 0) {
      if (last >= first) {
         unsigned int newlen = last-first+1;
         intarr_t* newia = intarr_create(newlen); 
         if (newia->data != 0) {
            newia->len = newlen;
            int j = 0;
            for (int i=first; i<=last; i++) {
               newia->data[j] = ia->data[i];
               j++;
            }
            return newia;
         }
      } 
   return NULL;
   }
}
