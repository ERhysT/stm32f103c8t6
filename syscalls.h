#ifndef GAURD_SYSCALLS_H
#define GAURD_SYSCALLS_H

/* Increase the size of the heap by incr bytes */
void *_sbrk(int incr);

/* Write maximum len bytes from buf to file descriptor. Returns
   number of bytes written. */
int _write(int fd, char *buf, int len);

/* get file status */
int _fstat(int file, struct stat *st);

void _exit(int status);

/* Do nothing yet */
int _read (int fd, char *buf, int len);
int _close(int fd);
int _isatty(int fd);
int _lseek(int file, int ptr, int dir);
void _kill(int pid, int sig);
int _getpid(void);

#endif
