#include <CAssoc.h>


template <class Xc, class Yc, class AssocItem>
Assoc<Xc, Yc, AssocItem>::Assoc(void)
: stackIter(stack)
{
  bucket = new ChainElement*[BucketSize];
  CAssert(bucket);

  for (int i = BucketSize; --i >= 0; )
    bucket[i] = 0;
}

template <class Xc, class Yc, class AssocItem>
Assoc<Xc, Yc, AssocItem>::~Assoc(void)
{
  delete [] bucket;

  stackIter.rewind();
  while (stackIter)
    delete stackIter++;
}

template <class Xc, class Yc, class AssocItem>
void
Assoc<Xc, Yc, AssocItem>::Destroy(void)
{
  for (int i = BucketSize; --i >= 0; )
    bucket[i] = 0;
  stackIter.rewind();
}

template <class Xc, class Yc, class AssocItem>
void
Assoc<Xc, Yc, AssocItem>::InsertCell(Xc _row, Yc _col, AssocItem& _info)
{
  // Hash up the _row and _col parameters to get an index into
  // the bucket.

  unsigned int index = HashItems(_row, _col);

  ChainElement* element = bucket[index];
  if (element == 0)
    {
      ChainElement* newElement = GetElement();
      newElement->SetRow(_row);
      newElement->SetCol(_col);
      newElement->SetItem(&_info);
      newElement->SetNext(0);
      bucket[index] = newElement;
    }
  else
    {
      while (element)
        {
          if (element->QueryRow() == _row && element->QueryCol() == _col)
            break;

          ChainElement* next = element->QueryNext();
          if (next == 0)
            {
              ChainElement* newElement = GetElement();
              newElement->SetRow(_row);
              newElement->SetCol(_col);
              newElement->SetItem(&_info);
              newElement->SetNext(0);
              element->SetNext(newElement);
              break;
            }
          else
            element = next;
        }
    }
}

template <class Xc, class Yc, class AssocItem>
AssocItem*
Assoc<Xc, Yc, AssocItem>::QueryCell(Xc _row, Yc _col)
{
  unsigned int index = HashItems(_row, _col);

  ChainElement* element = bucket[index];
  while (element)
    if (element->QueryRow() == _row && element->QueryCol() == _col)
      return element->QueryItem();
    else
      element = element->QueryNext();

  return 0;
}


