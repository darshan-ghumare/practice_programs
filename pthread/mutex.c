#include <stdio.h>
#include <pthread.h>

void *thread1_todo(void *arg)
{
  pthread_mutex_t *lock = (void *) arg;
  printf("releasing lock....(%d)\n", pthread_mutex_unlock(lock));
  sleep(3);
  printf("Aquaring lock....(%d)\n", pthread_mutex_lock(lock));
  printf("releasing lock....(%d)\n", pthread_mutex_unlock(lock));
  pthread_mutex_unlock(lock);

  return NULL;
}

int main()
{
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
  pthread_t th1;
  int ret = 0;

  printf("Mutex lock %d\n", pthread_mutex_lock(&lock));
  /* Next state shall cause a deadlock. */
  //printf("Mutex lock %d\n", pthread_mutex_lock(&lock));

  pthread_create(&th1, NULL, thread1_todo, (void *) &lock);
  sleep(1);
  printf("Mutex lock %d\n", pthread_mutex_lock(&lock));
  sleep(4);
  printf("Mutex unlock....(%d)\n", pthread_mutex_unlock(&lock));
  pthread_mutex_unlock(&lock);
  pthread_join(th1, (void *) &ret);

  return 0;
}
