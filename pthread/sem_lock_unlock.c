#include <errno.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_error(char *msg)
{
  printf("%s Error %s\n", msg, strerror(errno));
  exit(-1);
}

int main()
{
  sem_t sem;

  // Create unnamed semaphore which is not shared across processes
  // with count 1.
  if (sem_init(&sem, 0/* Not shared across processes. */, 1 /* Count */))
  {
    print_error("sem_init() failed.");
  }
  printf("Unlocking already unlocked semaphore.\n");
  // sem_post does not throw any error in this case.
  if (sem_post(&sem))
  {
    print_error("sem_post() failed.");
  }
  // Becasue of above sem_post() both next two calls to sem_wait()
  // shall be succeeded.
  printf("(1'st) Lock unlocked semaphore.\n");
  if (sem_wait(&sem))
  {
    print_error("sem_wait() failed.");
  }
  printf("(2'nd) Lock unlocked semaphore.\n");
  if (sem_wait(&sem))
  {
    print_error("sem_wait() failed.");
  }
  printf("Both sem_wait() calls succeeded.\n");
  if (sem_destroy(&sem))
  {
    print_error("sem_destroy() failed.");
  }
}
