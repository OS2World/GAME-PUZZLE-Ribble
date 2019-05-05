#include <CSupport.h>
#include <CAssert.h>
#include <CBR.h>

#include <string.h>
#include <stdio.h>
#include <direct.h>
#include <fcntl.h>
#include <io.h>

#if defined(__OS2__) && defined(__IBMC__)
#define open(a,b) _open(a,b)
#define lseek(a,b,c) _lseek(a,b,c)
#endif

CBufferedRead::CBufferedRead(const char* _filename, int _mode)
{
  fd = open(_filename, _mode);
  if (fd != -1)
    {
      fdOpened = 1;
      buffer = new CSHuge char[BufferSize];
      CAssert(buffer);
    }
  else
    {
      fdOpened = 0;
      buffer = 0;
    }
  lineBuffer = 0;
  lineBufferLen = 0;
  bufferSeekPos = 0;
  flush();
}

CBufferedRead::CBufferedRead(int _fd)
{
  fd = _fd;

  if (fd != -1)
    {
      buffer = new CSHuge char[BufferSize];
      CAssert(buffer);
      bufferSeekPos = lseek(_fd, 0, SEEK_CUR);
      flush();
    }
  else
    {
      fdOpened = 0;
      buffer = 0;
      bufferSeekPos = 0;
      bufferSize = 0;
      bufferOff = 0;
    }
  lineBuffer = 0;
  lineBufferLen = 0;
}

CBufferedRead::~CBufferedRead()
{
  if (fdOpened)
    ::close(fd);
  if (buffer)
    delete [] buffer;
}

void
CBufferedRead::close(void)
{
  if (fdOpened)
    ::close(fd);
  fdOpened = 0;
  fd = -1;
}

long
CBufferedRead::opened(void)
{
  return fd != -1;
}

long 
CBufferedRead::rewind(void) 
{ 
  flush();
  return seek(0);
}

long 
CBufferedRead::seek(long _position)
{
  if (fd == -1) return -1;

  long sdiff = _position - bufferSeekPos;

  if (sdiff >= 0 && sdiff < bufferSize)
    {
      bufferOff = sdiff;
      return _position;
    }
  else
    {
      bufferSeekPos = lseek(fd, _position, SEEK_SET);
      flush();
      return bufferSeekPos;
    }
}

void 
CBufferedRead::flush(void)
{
  bufferSize = 0;
  bufferOff = 0;
}

long 
CBufferedRead::read(char* _buffer, unsigned int _length)
{
  if (fd == -1) return -1;

  long bufferLeft = bufferSize - bufferOff;

  if (_length <= bufferLeft)
    {
      memcpy(_buffer, buffer + bufferOff, _length);
      bufferOff += _length;
    }
  else
    {
      if (_length >= BufferSize)
        {
          if (bufferLeft)
            {
              memcpy(_buffer, buffer + bufferOff, (size_t)bufferLeft);
              bufferOff = bufferSize;
            }

          long r = ::read(fd, _buffer + bufferLeft, (size_t)(_length - bufferLeft));
          return r == -1 ? -1 : bufferLeft + r;
        }

      if (bufferLeft)
        {
          memmove(buffer, buffer + bufferOff, (size_t)bufferLeft);
          bufferSize = bufferLeft;
          bufferOff = 0;
        }
      else
        {
          bufferSize = 0;
          bufferOff = 0;
        }

      bufferSeekPos = lseek(fd, 0, SEEK_CUR);
      long r = ::read(fd, buffer + bufferSize, (size_t)(BufferSize - bufferSize));
      if (r == -1)
        return r;

      bufferSize += r;

      bufferLeft = bufferSize - bufferOff;
      if (_length > bufferLeft)
        {
          memcpy(_buffer, buffer + bufferOff, (size_t)bufferLeft);
          bufferOff += bufferLeft;
          return bufferLeft;
        }

      memcpy(_buffer, buffer + bufferOff, _length);
      bufferOff += _length;
    }
  return _length;
}

char*
CBufferedRead::getline(void)
{
  if (lineBufferLen == 0)
    {
      lineBufferLen = 64;
      lineBuffer = new char[lineBufferLen];
      CAssert(lineBuffer);
    }

  *lineBuffer = '\0';

  int eof = 0;

  for (int got = 0; !eof;)
    {
      char ch;
      if (read(&ch, sizeof(ch)) == sizeof(ch))
        {
          if (ch == '\n')
            {
              lineBuffer[got] = '\0';
              break;
            }
          lineBuffer[got++] = ch;
          if (got >= lineBufferLen)
            {
              lineBufferLen <<= 1;
              char* ext = new char[lineBufferLen];
              memcpy(ext, lineBuffer, got);
              delete [] lineBuffer;
              lineBuffer = ext;
            }
        }
      else
        eof = 1;
    }
  return !got && eof ? 0 : lineBuffer;
}



