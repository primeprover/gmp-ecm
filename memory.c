/* Memory allocation used during tests.

Copyright 2001, 2002 Free Software Foundation, Inc.

This file was copied from the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */

#ifdef MEMORY_DEBUG

#include <stdio.h>
#include <stdlib.h>  /* for abort */
#include <gmp.h>
#include "ecm.h"

void *__gmp_default_allocate (size_t);
void *__gmp_default_reallocate (void *, size_t, size_t);
void __gmp_default_free (void *, size_t);

/* Each block allocated is a separate malloc, for the benefit of a redzoning
   malloc debugger during development or when bug hunting.

   Sizes passed when reallocating or freeing are checked (the default
   routines don't care about these).

   Memory leaks are checked by requiring that all blocks have been freed
   when tests_memory_end() is called.  Test programs must be sure to have
   "clear"s for all temporary variables used.  */

struct header {
  void           *ptr;
  size_t         size;
  struct header  *next;
};

struct header  *tests_memory_list = NULL;

/* Return a pointer to a pointer to the found block (so it can be updated
   when unlinking). */
static struct header **
tests_memory_find (void *ptr)
{
  struct header  **hp;

  for (hp = &tests_memory_list; *hp != NULL; hp = &((*hp)->next))
    if ((*hp)->ptr == ptr)
      return hp;

  return NULL;
}

#if 0
static int
tests_memory_valid (void *ptr)
{
  return (tests_memory_find (ptr) != NULL);
}
#endif

static void *
tests_allocate (size_t size)
{
  struct header  *h;

  if (size == 0)
    {
      printf ("tests_allocate(): attempt to allocate 0 bytes\n");
      abort ();
    }

  h = (struct header *) __gmp_default_allocate (sizeof (*h));
  h->next = tests_memory_list;
  tests_memory_list = h;

  h->size = size;
  h->ptr = (struct header*) __gmp_default_allocate (size);
  return h->ptr;
}

static void *
tests_reallocate (void *ptr, size_t old_size, size_t new_size)
{
  struct header  **hp, *h;

  if (new_size == 0)
    {
      printf ("tests_reallocate(): attempt to reallocate 0x%lX to 0 bytes\n",
              (unsigned long) ptr);
      abort ();
    }

  hp = tests_memory_find (ptr);
  if (hp == NULL)
    {
      printf ("tests_reallocate(): attempt to reallocate bad pointer 0x%lX\n",
              (unsigned long) ptr);
      abort ();
    }
  h = *hp;

  if (h->size != old_size)
    {
      printf ("tests_reallocate(): bad old size %u, should be %u\n",
              old_size, h->size);
      abort ();
    }

  h->size = new_size;
  h->ptr = (struct header*) __gmp_default_reallocate (ptr, old_size, new_size);
  return h->ptr;
}

static struct header **
tests_free_find (void *ptr)
{
  struct header  **hp = tests_memory_find (ptr);
  if (hp == NULL)
    {
      printf ("tests_free(): attempt to free bad pointer 0x%lX\n",
              (unsigned long) ptr);
      abort ();
    }
  return hp;
}

static void
tests_free_nosize (void *ptr)
{
  struct header  **hp = tests_free_find (ptr);
  struct header  *h = *hp;

  *hp = h->next;  /* unlink */

  __gmp_default_free (ptr, h->size);
  __gmp_default_free (h, sizeof (*h));
}

void
tests_free (void *ptr, size_t size)
{
  struct header  **hp = tests_free_find (ptr);
  struct header  *h = *hp;

  if (h->size != size)
    {
      printf ("tests_free(): bad size %u, should be %u\n", size, h->size);
      abort ();
    }

  tests_free_nosize (ptr);
}

void
tests_memory_start (void)
{
  mp_set_memory_functions (tests_allocate, tests_reallocate, tests_free);
}

void
tests_memory_reset (void)
{
  mp_set_memory_functions (__gmp_default_allocate, __gmp_default_reallocate,
                           __gmp_default_free);
}

void
tests_memory_end (void)
{
  if (tests_memory_list != NULL)
    {
      struct header  *h;
      unsigned  count;

      printf ("tests_memory_end(): not all memory freed\n");

      count = 0;
      for (h = tests_memory_list; h != NULL; h = h->next)
	count++;

      printf ("    %u block(s) remaining\n", count);
      abort ();
    }
}

void
tests_memory_status (void)
{
  unsigned count = 0, size = 0;

  if (tests_memory_list != NULL)
    {
      struct header  *h;

      for (h = tests_memory_list; h != NULL; h = h->next)
        {
          count++;
          size += h->size;
        }

    }

  printf ("    %u blocks remaining, total size %u\n", count, size);
}

#else

/* Stop compiler complaining about empty file */

void memory_dummy (void);

void 
memory_dummy (void)
{
  return;
}

#endif
