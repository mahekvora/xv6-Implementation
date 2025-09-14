#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_thread_create(void){
  int func_add;
  int arg;
  int stack_add;

  if (argint(0, &func_add) < 0)
     return -1;
  if (argint(1, &arg) < 0)
     return -1;
  if (argint(2, &stack_add) < 0)
     return -1;
 
  return thread_create((void *)func_add, (void *)arg, (void *)stack_add);
}

int sys_thread_join(void){
  return thread_join();
}

int sys_thread_exit(void){
  return thread_exit();
}

int sys_draw(void){
  void* buf;
  uint size;
  argptr(0, (void *)&buf, sizeof(buf));
  argptr(1, (void *)&size, sizeof(size));

  char text[] = "                       .,,uod8B8bou,,.\n\
              ..,uod8BBBBBBBBBBBBBBBBRPFT?l!i:.\n\
         ,=m8BBBBBBBBBBBBBBBRPFT?!||||||||||||||\n\
         !...:!TVBBBRPFT||||||||||!!^^\"\"'   ||||\n\
         !.......:!?|||||!!^^\"\"'            ||||\n\
         !.........||||                     ||||\n\
         !.........||||  ##                 ||||\n\
         !.........||||                     ||||\n\
         !.........||||                     ||||\n\
         !.........||||                     ||||\n\
         !.........||||                     ||||\n\
         `.........||||                    ,||||\n\
          .;.......||||               _.-!!|||||\n\
   .,uodWBBBBb.....||||       _.-!!|||||||||!:'\n\
!YBBBBBBBBBBBBBBb..!|||:..-!!|||||||!iof68BBBBBb....\n\
!..YBBBBBBBBBBBBBBb!!||||||||!iof68BBBBBBRPFT?!::   `.\n\
!....YBBBBBBBBBBBBBBbaaitf68BBBBBBRPFT?!:::::::::     `.\n\
!......YBBBBBBBBBBBBBBBBBBBRPFT?!::::::;:!^'`;:::       `.\n\
!........YBBBBBBBBBBRPFT?!::::::::::^''...::::::;         iBBbo.\n\
`..........YBRPFT?!::::::::::::::::::::::::;iof68bo.      WBBBBbo.\n\
  `..........:::::::::::::::::::::::;iof688888888888b.     `YBBBP^'\n\
    `........::::::::::::::::;iof688888888888888888888b.     `\n\
      `......:::::::::;iof688888888888888888888888888888b.\n\
        `....:::;iof688888888888888888888888888888888899fT!\n\
          `..::!8888888888888888888888888888888899fT|!^''\n\
            `' !!988888888888888888888888899fT|!^'''\n\
                `!!8888888888888888899fT|!^\"'\n\
                  `!988888888899fT|!^\"'\n\
                    `!9899fT|!^\"'\n\
                      `!^\"'\n";
  
  // printf(sizeof(text));
  if(sizeof(text) > size) return -1;
  strncpy((char *)buf, text, size);
  return sizeof(text);

}

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}