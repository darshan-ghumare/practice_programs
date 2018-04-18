#include <pthread.h> 
#include <stdio.h> 
#include <unistd.h> 
 
pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_function (void* arg) 
{
  while (1)
  {
    pthread_mutex_lock(&cond_mutex);
    fprintf (stderr, "thread(%lu) waiting.\n", *(unsigned long *) arg); 
    pthread_cond_wait(&cond, &cond_mutex);
    pthread_mutex_unlock(&cond_mutex);
    fprintf (stderr, "thread(%lu) woke up.\n", *(unsigned long *) arg); 
  }
  return NULL; 
} 
 
int main () 
{
  pthread_t thread1, thread2, thread3; 
  int ret;
  pthread_create (&thread1, NULL, &thread_function, &thread1); 
  pthread_create (&thread2, NULL, &thread_function, &thread2);
  sleep(2);
  /*
    Thread1 & thread2 woke up *only once* becasue both are waiting for the event
    to occur (enqueued in the wait queue) before that event occurred.
  */
  pthread_mutex_lock(&cond_mutex);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&cond_mutex);
  // Thread3 won't wake up as it start waiting after event occurred. 
  pthread_create (&thread3, NULL, &thread_function, &thread3);
  pthread_join(thread2, (void **) &ret);
  return 0; 
}
