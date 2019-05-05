// -------------------------------
//  $Source: D:\logical\store\classes/RCS/CQSORT.H,v $
//  $Revision: 1.13 $
//  $Date: 1994/04/26 03:49:17 $
//  $Author: jason $
//  Language:       C++
//  Licence:        Public Domain
//  Purpose:        Sorting templates for arrays and CVectors
// -------------------------------

#ifndef _CQSort_h
#define _CQSort_h

#include <CSupport.h>
#include <stdlib.h>

const long qsQuickSortThresh       = 4;
const long qsQuickSortMedianThresh = 6;

// The following functions sort an array of
// objects.

template <class T>
void qsQuick_Sort(T huge* bot, ULONG nmemb);

template <class T>
void qsInsertion_Sort(T huge* bot, ULONG nmemb);

template <class T>
void
QuickSort(T* bot, ULONG nmemb)
{
  if (nmemb <= 1)
    return;

  if (nmemb >= qsQuickSortThresh)
    qsQuick_Sort((T huge*)bot, nmemb);
  else
    qsInsertion_Sort((T huge*)bot, nmemb);
}

template <class T>
void
qsQuickSwap(T huge* a, T huge* b)
{
  T tmp = *(T*)a;
  *a = *b;
  *b = tmp;
}

template <class T>
void
qsDoSort(T huge*& bot, ULONG n, T huge*& t1)
{
  if (n > 1)
    if (n == 2) 
      {
        t1 = bot + 1;
        if (*(T*)t1 < *(T*)bot)
          qsQuickSwap(t1, bot);
      } 
    else
      qsInsertion_Sort(bot, (ULONG)n);
}

template <class T>
void
qsQuick_Sort(T huge* bot, ULONG nmemb)
{
  T huge* top, huge* mid, huge* t1, huge* t2;
  long n1, n2;
  T huge* bsv;
  
  /* bot and nmemb must already be set. */
 partition:
  
  /* find mid and top elements */
  mid = bot + (nmemb >> 1);
  top = bot + (nmemb - 1);
  
  /*
   * Find the median of the first, last and middle element (see Knuth,
   * Vol. 3, page 123, Eq. 28).  This test order gets the equalities
   * right.
   */
  if (nmemb >= qsQuickSortMedianThresh) 
    {
      n1 = (*(T*)bot < *(T*)mid) ? -1 : (*(T*)bot == *(T*)mid) ? 0 : 1;
      n2 = (*(T*)mid < *(T*)top) ? -1 : (*(T*)mid == *(T*)top) ? 0 : 1;
      if (n1 < 0 && n2 > 0)
        t1 = (*(T*)bot < *(T*)top) ? top : bot;
      else if (n1 > 0 && n2 < 0)
        t1 = (*(T*)bot > *(T*)top) ? top : bot;
      else
        t1 = mid;
      
      /* if mid element not selected, swap selection there */
      if (t1 != mid) 
        {
          qsQuickSwap(t1, mid);
          mid--;
        }
    }
  
  /* Standard quicksort, Knuth, Vol. 3, page 116, Algorithm Q. */
  
  long& didswap = n1;
  T huge*& newbot = t1;
  T huge*& replace = t2;          

  didswap = 0;
  for (bsv = bot;;) 
    {
      for (; bot < mid && (*(T*)bot <= *(T*)mid); bot++);
      while (top > mid)
        {
          if (*(T*)mid <= *(T*)top)
            {
              top--;
              continue;
            }
          newbot = bot + 1;     /* value of bot after swap */
          if (bot == mid)               /* top <-> mid, mid == top */
            replace = mid = top;
          else 
            {                   /* bot <-> top */
              replace = top;
              top--;
            }
          goto swap;
        }
      if (bot == mid)
        break;
      
      /* bot <-> mid, mid == bot */
      replace = mid;
      newbot = mid = bot;               /* value of bot after swap */
      top--;
      
    swap:
      qsQuickSwap(bot, replace);
      bot = newbot;
      didswap = 1;
    }
  
  /*
   * Quicksort behaves badly in the presence of data which is already
   * sorted (see Knuth, Vol. 3, page 119) going from O N lg N to O N^2.
   * To avoid this worst case behavior, if a re-partitioning occurs
   * without swapping any elements, it is not further partitioned and
   * is insert sorted.  This wins big with almost sorted data sets and
   * only loses if the data set is very strangely partitioned.  A fix
   * for those data sets would be to return prematurely if the insertion
   * sort routine is forced to make an excessive number of swaps, and
   * continue the partitioning.
   */
  if (!didswap)
    {
      qsInsertion_Sort(bsv, nmemb);
      return;
    }
  
  /*
   * Re-partition or sort as necessary.  Note that the mid element
   * itself is correctly positioned and can be ignored.
   */
  
  long& nlower = n1;
  long& nupper = n2;          
  
  bot = bsv;
  nlower = (long)(mid - bot);    /* size of lower partition */
  mid++;
  nupper = nmemb - nlower - 1;  /* size of upper partition */
  
  /*
   * If must call recursively, do it on the smaller partition; this
   * bounds the stack to lg N entries.
   */
  if (nlower > nupper) 
    {
      if (nupper >= qsQuickSortThresh)
        qsQuick_Sort(mid, (ULONG)nupper);
      else 
        {
          qsDoSort(mid, (ULONG)nupper, t1);
          if (nlower < qsQuickSortThresh) 
            {
              qsDoSort(bot, (ULONG)nlower, t1);
              return;
            }
        }
      nmemb = nlower;
    } 
  else 
    {
      if (nlower >= qsQuickSortThresh)
        qsQuick_Sort(bot, (ULONG)nlower);
      else 
        {
          qsDoSort(bot, (ULONG)nlower, t1);
          if (nupper < qsQuickSortThresh) 
            {
              qsDoSort(mid, (ULONG)nupper, t1);
              return;
            }
        }
      bot = mid;
      nmemb = nupper;
    }
  goto partition;
  /* NOTREACHED */
}


template <class T>
void
qsInsertion_Sort(T huge* bot, ULONG nmemb)
{
  for (ULONG a = 0; a < nmemb; a++)
    {
      T& aElem = bot[a];
      for (ULONG b = a + 1; b < nmemb; b++)
        {
          T& bElem = bot[b];
          if (bElem < aElem)
            {
              T temp = aElem;
              aElem = bElem;
              bElem = temp;
            }
        }
    }
}






//
//
//
// The following functions sort an array of
// pointers to objects.
//
//
//

template <class T>
void qsQuick_SortP(T huge*huge* bot, ULONG nmemb);

template <class T>
void qsInsertion_SortP(T huge*huge* bot, ULONG nmemb);

template <class T>
void
QuickSortP(T** bot, ULONG nmemb)
{
  if (nmemb <= 1)
    return;

  if (nmemb >= qsQuickSortThresh)
    qsQuick_SortP((T huge*huge*)bot, nmemb);
  else
    qsInsertion_SortP((T huge*huge*)bot, nmemb);
}

template <class T>
void
qsDoSortP(T huge*huge*& bot, ULONG n, T huge*huge*& t1)
{
  if (n > 1)
    if (n == 2)
      {
        t1 = bot + 1;
        if (**t1 < **bot)
          qsQuickSwap(t1, bot);
      }
    else
      qsInsertion_SortP(bot, (ULONG)n);
}

template <class T>
void
qsQuick_SortP(T huge*huge* bot, ULONG nmemb)
{
  T huge*huge*top, huge*huge*mid, huge*huge*t1, huge*huge*t2;
  long n1, n2;
  T huge*huge*bsv;

  /* bot and nmemb must already be set. */
 partition:

  /* find mid and top elements */
  mid = bot + (nmemb >> 1);
  top = bot + (nmemb - 1);

  /*
   * Find the median of the first, last and middle element (see Knuth,
   * Vol. 3, page 123, Eq. 28).  This test order gets the equalities
   * right.
   */
  if (nmemb >= qsQuickSortMedianThresh)
    {
      if (**bot < **mid && **mid > **top)
        t1 = **bot < **top ? top : bot;
      else if (**bot > **mid && **mid < **top)
        t1 = (**bot > **top) ? top : bot;
      else
        t1 = mid;

      /* if mid element not selected, swap selection there */
      if (t1 != mid)
        {
          qsQuickSwap(t1, mid);
          mid--;
        }
    }

  /* Standard quicksort, Knuth, Vol. 3, page 116, Algorithm Q. */

  long& didswap = n1;
  T huge*huge*& newbot = t1;
  T huge*huge*& replace = t2;

  didswap = 0;
  for (bsv = bot;;)
    {
      for (; bot < mid && (**bot <= **mid); bot++);
      while (top > mid)
        {
          if (**mid <= **top)
            {
              top--;
              continue;
            }
          newbot = bot + 1;     /* value of bot after swap */
          if (bot == mid)               /* top <-> mid, mid == top */
            replace = mid = top;
          else
            {                   /* bot <-> top */
              replace = top;
              top--;
            }
          goto swap;
        }
      if (bot == mid)
        break;

      /* bot <-> mid, mid == bot */
      replace = mid;
      newbot = mid = bot;               /* value of bot after swap */
      top--;

    swap:
      qsQuickSwap(bot, replace);
      bot = newbot;
      didswap = 1;
    }

  /*
   * Quicksort behaves badly in the presence of data which is already
   * sorted (see Knuth, Vol. 3, page 119) going from O N lg N to O N^2.
   * To avoid this worst case behavior, if a re-partitioning occurs
   * without swapping any elements, it is not further partitioned and
   * is insert sorted.  This wins big with almost sorted data sets and
   * only loses if the data set is very strangely partitioned.  A fix
   * for those data sets would be to return prematurely if the insertion
   * sort routine is forced to make an excessive number of swaps, and
   * continue the partitioning.
   */

  if (!didswap)
    {
      if (nmemb < 500)
        qsInsertion_SortP(bsv, nmemb);
    }

  /*
   * Re-partition or sort as necessary.  Note that the mid element
   * itself is correctly positioned and can be ignored.
   */

  long& nlower = n1;
  long& nupper = n2;

  bot = bsv;
  nlower = (long)(mid - bot);    /* size of lower partition */
  mid++;
  nupper = nmemb - nlower - 1;  /* size of upper partition */

  /*
   * If must call recursively, do it on the smaller partition; this
   * bounds the stack to lg N entries.
   */
  if (nlower > nupper)
    {
      if (nupper >= qsQuickSortThresh)
        qsQuick_SortP(mid, (ULONG)nupper);
      else
        {
          qsDoSortP(mid, (ULONG)nupper, t1);
          if (nlower < qsQuickSortThresh)
            {
              qsDoSortP(bot, (ULONG)nlower, t1);
              return;
            }
        }
      nmemb = nlower;
    }
  else
    {
      if (nlower >= qsQuickSortThresh)
        qsQuick_SortP(bot, (ULONG)nlower);
      else
        {
          qsDoSortP(bot, (ULONG)nlower, t1);
          if (nupper < qsQuickSortThresh) {
            qsDoSortP(mid, (ULONG)nupper, t1);
            return;
          }
        }
      bot = mid;
      nmemb = nupper;
    }
  goto partition;
  /* NOTREACHED */
}

// This isn't an Insertion sort!
// Now a nice simple, easily debuggable Blubble Sort

template <class T>
void
qsInsertion_SortP(T huge*huge* bot, ULONG nmemb)
{
  ULONG i;
  ULONG j;
  T huge* v;

  for (i=1; i<nmemb; i++)
    {
      v = bot[i];
      j = i;
      while (j && *bot[j-1] > *v)
        {
          bot[j] = bot[j-1];
          j--;
        }
      bot[j] = v;
    }


/*
  for (ULONG a = 0; a < nmemb; a++)
    {
      T huge* aElem = bot[a];
      for (ULONG b = a + 1; b < nmemb; b++)
        {
          T huge* bElem = bot[b];
          if (*bElem < *aElem)
            {
              bot[b] = aElem;
              aElem = bElem;
            }
        }
      bot[a] = aElem;
    }
*/
}





#endif

