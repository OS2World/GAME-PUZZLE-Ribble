#include <CSupport.h>
#include <CAssert.h>

#ifndef _CBuffRead_h
#define _CBuffRead_h

class CSExport CBufferedRead
{
public:
  CBufferedRead(const char* _filename, int _mode);
  CBufferedRead(int _fd);
  ~CBufferedRead();

  long opened(void);
  long rewind(void);
  long seek(long _position);
  void close(void);
  void flush(void);
  long read(char* _buffer, unsigned int _length);
  char* getline(void); 

private:
  int         fd;
  int         fdOpened;
  char CSHuge* buffer;
  long        bufferSeekPos;
  long        bufferOff;
  long        bufferSize;
  char*       lineBuffer;
  long        lineBufferLen;

  enum Constants { BufferSize = 32000 };
};


#endif
