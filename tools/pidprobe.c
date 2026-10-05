#define INCL_DOSPROCESS
#define INCL_DOSMISC
#define INCL_DOSPROFILE
#include <os2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void usage(void)
{
  printf("usage: pidprobe PID [q|k]   (q=query alive, k=kill [default q])\n");
}

int main(int argc, char* argv[])
{
  int mode = 0; /* q */
  if (argc < 2) { usage(); return 1; }
  if (argc >= 3 && (strcmp(argv[2], "k") == 0 || strcmp(argv[2], "K") == 0))
    mode = 1;
  if (argc >= 3 && (strcmp(argv[2], "a") == 0 || strcmp(argv[2], "A") == 0))
    mode = 2;
  if (argc >= 3 && (strcmp(argv[2], "h") == 0 || strcmp(argv[2], "H") == 0))
    mode = 3;
  if (argc >= 3 && (strcmp(argv[2], "s") == 0 || strcmp(argv[2], "S") == 0))
    mode = 4;
  if (argc >= 3 && (strcmp(argv[2], "n") == 0 || strcmp(argv[2], "N") == 0))
    mode = 5;

  unsigned long pid = (unsigned long)atoi(argv[1]);
  setvbuf(stdout, NULL, _IONBF, 0);

  if (mode == 1)
    {
      unsigned long rc = DosKillProcess(DKP_PROCESS, pid);
      if (rc == 0)
        printf("PROBE-ALIVE pid=%lu killed\n", pid);
      else
        printf("PROBE-DEAD rc=%lu\n", rc);
      return 0;
    }

  /* mode q: walk QS_PROCESS list, look for pid */
  ULONG bufsize = 64 * 1024;
  PBYTE buf = (PBYTE)malloc(bufsize);
  if (!buf) { printf("OUT-OF-MEM\n"); return 1; }

  for (;;)
    {
      ULONG el = QS_PROCESS;
      if (mode == 5) el |= QS_MTE;
      APIRET rc = DosQuerySysState(el, 1, 0, 0, buf, bufsize);
      if (rc == 0) break;
      if (rc == 2) { bufsize *= 2; PBYTE nb = (PBYTE)realloc(buf, bufsize); if (!nb) { free(buf); printf("OUT-OF-MEM\n"); return 1; } buf = nb; continue; }
      printf("QSYSSTATE-ERR rc=%lu\n", rc);
      free(buf);
      return 1;
    }

  if (mode == 3)
    {
      ULONG i, n = 256;
      for (i = 0; i < n; i += 4)
        {
          ULONG v = 0;
          unsigned k;
          for (k = 0; k < 4; k++) v |= ((ULONG)buf[i + k]) << (8 * k);
          printf("%04lx  %08lx\n", i, v);
        }
      free(buf);
      return 0;
    }

  if (mode == 4)
    {
      ULONG i;
      for (i = 0; i < bufsize - 60; i += 4)
        {
          ULONG v = *(ULONG*)(buf + i);
          if (v == QS_PROCESS)
            {
              USHORT pid = *(USHORT*)(buf + i + 8);
              USHORT ppid = *(USHORT*)(buf + i + 10);
              ULONG nx = (ULONG)(*(void**) (buf + i + 4)) & 0xFFFF;
              printf("off=%04lx pid=%u ppid=%u next=%04lx\n", i, pid, ppid, nx);
            }
        }
      free(buf);
      return 0;
    }

  if (mode == 5)
    {
      ULONG i;
      USHORT wanted_h = 0xFFFF;
      for (i = 0; i < bufsize - 64; i += 4)
        {
          ULONG v = *(ULONG*)(buf + i);
          if (v != QS_PROCESS) continue;
          USHORT spid = *(USHORT*)(buf + i + 8);
          if (spid == pid)
            {
              wanted_h = *(USHORT*)(buf + i + 24);
              printf("PID=%u hMte=0x%04x\n", spid, wanted_h);
            }
        }
      if (wanted_h == 0xFFFF) { printf("DEAD pid=%lu\n", pid); free(buf); return 0; }
      for (i = 0; i < bufsize - 32; i += 4)
        {
          USHORT hm = *(USHORT*)(buf + i + 4);
          if (hm == wanted_h)
            {
              USHORT fflat = *(USHORT*)(buf + i + 6);
              ULONG noff = (ULONG)(*(void**)(buf + i + 20)) & 0xFFFF;
              if ((fflat == 0 || fflat == 1) && noff > 0 && noff < bufsize)
                {
                  printf("NAME=%s\n", buf + noff);
                }
            }
        }
      free(buf);
      return 0;
    }

  {
    ULONG i;
    int found = 0;
    for (i = 0; i < bufsize - 64; i += 4)
      {
        ULONG v = *(ULONG*)(buf + i);
        if (v != QS_PROCESS) continue;
        USHORT spid = *(USHORT*)(buf + i + 8);
        USHORT sppid = *(USHORT*)(buf + i + 10);
        ULONG nx = (ULONG)(*(void**)(buf + i + 4)) & 0xFFFF;
        if (spid == 0) continue;
        if (mode == 2)
          {
            if (spid > 10)
              printf("%-6u  %-6u  type=0x%08lx stat=0x%08lx next=%04lx\n",
                     spid, sppid, *(ULONG*)(buf + i + 12),
                     *(ULONG*)(buf + i + 16), nx);
          }
        if (spid == pid)
          {
            printf("ALIVE pid=%u ppid=%u type=0x%08lx stat=0x%08lx\n",
                   spid, sppid, *(ULONG*)(buf + i + 12),
                   *(ULONG*)(buf + i + 16));
            found = 1;
          }
      }
    if (!found && mode == 0)
      printf("DEAD pid=%lu\n", pid);
  }
  free(buf);
  return 0;
}