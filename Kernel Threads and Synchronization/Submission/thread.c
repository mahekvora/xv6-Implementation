#include "types.h"
#include "stat.h"
#include "user.h"

#include "x86.h"

struct balance 
{
 char name[32];
 int amount;
};

struct spinlock {
  uint locked;       // Is the lock held?
  char *name;        // Name of lock.
};

void
thread_spin_init(struct spinlock *lk, char *name)
{
  lk->name = name;
  lk->locked = 0;
}

// Check whether this cpu is holding the lock.
int
holding(struct spinlock *lock)
{
  int r;
  r = lock->locked;
  return r;
}

// Acquire the lock.
// Loops (spins) until the lock is acquired.
// Holding a lock for a long time may cause
// other CPUs to waste time spinning to acquire it.
void
thread_spin_lock(struct spinlock *lk)
{

  // The xchg is atomic.
  // Until lock is free, aka its value is 0, the while loop runs
  // which means processor is stuck here until context switch happens and frees
  // the lock at some point and comes back to this thread.
  while(xchg(&lk->locked, 1) != 0)
    ;

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen after the lock is acquired.
  __sync_synchronize();

}

// Release the lock.
void
thread_spin_unlock(struct spinlock *lk)
{
  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that all the stores in the critical
  // section are visible to other cores before the lock is released.
  // Both the C compiler and the hardware may re-order loads and
  // stores; __sync_synchronize() tells them both not to.
  __sync_synchronize();

  // Release the lock, equivalent to lk->locked = 0.
  // This code can't use a C assignment, since it might
  // not be atomic. A real OS would use C atomics here.
  asm volatile("movl $0, %0" : "+m" (lk->locked) : );

}

/// why pushcli and popcli are not required?? ans?

struct thread_mutex {
  uint locked;       // Is the lock held?
};

void thread_mutex_init(struct thread_mutex *m){
    m->locked = 0;
}
void thread_mutex_lock(struct thread_mutex *m)
{
  while(xchg(&m->locked, 1) != 0)
    sleep(1);
  __sync_synchronize();
}
void thread_mutex_unlock(struct thread_mutex *m)
{
//   unlock(m);
  __sync_synchronize();
  asm volatile("movl $0, %0" : "+m" (m->locked) : );
}

volatile int total_balance = 0;

volatile unsigned int delay (unsigned int d) 
{
 unsigned int i; 
 for (i = 0; i < d; i++) 
 {
 __asm volatile( "nop" ::: );
 }
 return i; 
}

struct spinlock lock;
char* name = "testlock";

struct thread_mutex mutexlock;

void do_work(void *arg)
{
 
 printf(1,"Entering process .... ?");
 int i; 
 int old;
 struct balance *b = (struct balance*) arg; 
 printf(1, "Starting do_work: s:%s\n", b->name);
 for (i = 0; i < b->amount; i++) 
 { 

    thread_spin_lock(&lock);
    // thread_mutex_lock(&mutexlock);

    old = total_balance;
    delay(100000);
    total_balance = old + 1;

    thread_spin_unlock(&lock);
    // thread_mutex_unlock(&mutexlock);
 }
 printf(1, "Done s:%x %s\n", b->name, b->name);
 thread_exit();
 return;
}

int main(int argc, char *argv[]) {
 struct balance b1 = {"b1", 3200};
 struct balance b2 = {"b2", 2800};
 void *s1, *s2;
 int t1, t2, r1, r2;
 s1 = malloc(4096);
 s2 = malloc(4096);

 thread_spin_init(&lock, name);
 thread_mutex_init(&mutexlock);

 t1 = thread_create(do_work, (void*)&b1, s1);
 t2 = thread_create(do_work, (void*)&b2, s2); 
 r1 = thread_join();
 r2 = thread_join();
 printf(1, "Threads finished: (%d):%d, (%d):%d, shared balance:%d\n", 
 t1, r1, t2, r2, total_balance);
 exit();
}