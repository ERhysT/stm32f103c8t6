#include <sys/stat.h>

#include "syscalls.h"
#include "usart.h"

int _write(int fd, char *s, int len) {
  static char t[] = "Oioioi\r\n";

  if (fd == 1)
    usart_write_str(USART2,t,  sizeof t);
      //usart_write_str(USART2, s, len);

  return -1;
}

int _fstat(int fd, struct stat *st) {
  return -1;
}

void *_sbrk(int incr) {
  extern char end asm("end");
  static char *heap_end = NULL;
  char *prev_heap_end;

  if (NULL == heap_end)
    heap_end = &end;

  prev_heap_end = heap_end;
  heap_end +=incr;

  return prev_heap_end;
}

int _close(int fd) {
  return -1;
}

int _isatty(int fd) {
  return 1;
}

int _read(int fd, char *ptr, int len) {
  return -1;
}

int _lseek(int fd, int ptr, int dir) {
  return 0;
}

void _exit(int status) {
  for (;;);
}
