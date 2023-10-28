#include <stdint.h>
#include <stddef.h>
#include <sys/stat.h>

#include "syscalls.h"
#include "usart.h"

/* Initially the heap is set to the end of the bss section. Each
   sequential call to _sbrk increases the size of the heap.*/
void *_sbrk(int incr)
{
  typedef long ldsym;  		/* linker symbol */

  extern ldsym _ebss;
  static uint32_t *brk = NULL;

  if (NULL == brk) 
    brk = (uint32_t *) &_ebss;

  return (void *)(brk + incr);
}

/* Write max len bytes from buffer to file id */
int _write(int fd, char *buf, int len)
{
  int n = 0;

  if (fd == 1) 	   // stdout on USART2
    for (n = 0; n < len && buf[n] != '\0'; ++n)
      usart_write_char(USART2, buf[n]);

  return n;
}

int _read (int fd, char *buf, int len)
{
  return 0;
}

int _close(int fd) {
  return -1;
}

int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd) {
  return 1;
}

int _lseek(int fd, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
  __asm("BKPT #0");
  for (;;) (void) 0;
}

void _kill(int pid, int sig)
{
  return;
}

int _getpid(void) {
  return -1;
}
