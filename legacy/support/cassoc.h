#include <CSupport.h>
#include <CAssert.h>

#ifndef _CAssoc_h
#define _CAssoc_h

template <class Xc, class Yc, class AssocItem>
class CSExport Assoc
{
private:

  enum Constants
  {
    BucketSize = 1024
  };

  class ChainElement
  {
  public:
    void          SetNext(ChainElement* _next)  { next = _next;  }
    ChainElement* QueryNext(void)               { return next;   }
    void          SetItem(AssocItem* _item)     { item = *_item; }
    AssocItem*    QueryItem(void)               { return &item;  }
    void          SetRow(Xc _row)               { row = _row;    }
    Xc            QueryRow(void)                { return row;    }
    void          SetCol(Yc _col)               { col = _col;    }
    Yc            QueryCol(void)                { return col;    }

  private:
    Xc                 row;
    Yc                 col;
    ChainElement*      next;
    AssocItem          item;
  };

  typedef CDList<ChainElement*> ElementStack;
  typedef CDListIterator<ChainElement*> ElementStackIter;

public:
  Assoc(void);
  ~Assoc();
  void Destroy(void);
  void InsertCell(Xc _row, Yc _col, AssocItem& _info);
  AssocItem* QueryCell(Xc _row, Yc _col);
  ChainElement* GetElement(void)
    {
      if (!stackIter)
        {
          ChainElement* newElement = new ChainElement;
          stack.addTail(newElement);
          stackIter.fastforward();
        }
      return stackIter++;
    }

private:

    // This is the one to tweak.

    unsigned int
    HashItems(Xc _row, Yc _col)
    {
      unsigned int a = (unsigned int)_row;
      unsigned int b = (unsigned int)_col;
      unsigned int c = (unsigned int)_rotl((unsigned short)a,
					   (int)(b & 0xf) + 1);
      unsigned int d = a + b;
      unsigned int e = c ^ d;
      return e % BucketSize;
    }

  ChainElement**    bucket;
  ElementStack      stack;
  ElementStackIter  stackIter;
};

#ifndef _CSET2
#include <CAssoc.c>
#endif

#endif

