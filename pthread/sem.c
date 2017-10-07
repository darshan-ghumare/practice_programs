#include <fcntl.h>           /* For O_* constants */
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>

/* Semaphore name must start with '/'. */
#define SEM_NAME "/SemOne"

void print_error(char *msg)
{
  perror(msg);
  exit(-1);
}

int main()
{
  sem_t *sem;
  int ret = 0;

  /*
   * It shall create entry under /dev/shm on success.
   *
   * $ ls -la /dev/shm/
   * total 4
   * drwxrwxrwt  3 root    root      80 Sep 25 23:31 .
   * drwxr-xr-x 17 root    root    3300 Jul  6 04:22 ..
   * drwxrwxr-x  2 darshan darshan   40 Jun 27 04:46 config
   * -rw-------  1 darshan darshan   32 Sep 25 23:31 sem.SemOne
   */
  sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0600, 0);
  if (sem == SEM_FAILED)
  {
    print_error("sem_open(): ");
  }

  ret = fork();
  if (ret > 0)
  {
    printf("\nWaiting for child(%d) program to exit.....\n", ret);
    if (sem_wait(sem))
    {
      print_error("sem_wait(): ");
    }
    if(sem_close(sem))
    {
      print_error("process sem_close(): ");
    }
    /* Delete /dev/shm/sem.SemOne created by sem_open(). */
    sem_unlink(SEM_NAME);
  }
  else if (ret == 0)
  {
    printf("child process\n");
    sem = sem_open(SEM_NAME, O_RDWR);
    if (sem == SEM_FAILED)
    {
      print_error("\nchild process sem_open(): ");
    }

    if (sem_post(sem))
    {
      print_error("\nchild process sem_post(): ");
    }
    sleep(2);
    if(sem_close(sem))
    {
      print_error("\nchild process sem_close(): ");
    }
  }
}
