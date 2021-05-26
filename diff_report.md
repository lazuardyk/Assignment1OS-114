# Code Modification

Kode-kode yang diubah di dalam XV6 pada Project 2:
## - Makefile  

Line 3:
```c
CS333_PROJECT ?= 2
```

## - syscall.c

Line 112 - 119:
```c
#ifdef CS333_P2
extern int sys_getuid(void);
extern int sys_getgid(void);
extern int sys_getppid(void);
extern int sys_setuid(void);
extern int sys_setgid(void);
extern int sys_getprocs(void);
#endif
```

Line 149 - 156:
```c
#ifdef CS333_P2
[SYS_getuid]  sys_getuid,
[SYS_getgid]  sys_getgid,
[SYS_getppid] sys_getppid,
[SYS_setuid]  sys_setuid,
[SYS_setgid]  sys_setgid,
[SYS_getprocs]  sys_getprocs,
#endif
```

Line 188 - 195:
```c
#ifdef CS333_P2
  [SYS_getuid]  "getuid",
  [SYS_getgid]  "getgid",
  [SYS_getppid] "getppid",
  [SYS_setuid]  "setuid",
  [SYS_setgid]  "setgid",
  [SYS_getprocs]  "getprocs",
#endif
```

## - user.h

Line 31 - 38:
```c
#ifdef CS333_P2
uint getuid(void);
uint getgid(void);
uint getppid(void);
int setuid(uint);
int setgid(uint);
int getprocs(uint max, struct uproc* table);
#endif
```

## - usys.S

Line 34 - 39:
```c
SYSCALL(getuid)
SYSCALL(getgid)
SYSCALL(getppid)
SYSCALL(setuid)
SYSCALL(setgid)
SYSCALL(getprocs)
```

## - syscall.h

Line 26 - 31:
```c
#define SYS_getuid  SYS_date+1
#define SYS_getgid  SYS_getuid+1
#define SYS_getppid SYS_getgid+1
#define SYS_setuid  SYS_getppid+1
#define SYS_setgid  SYS_setuid+1
#define SYS_getprocs  SYS_setgid+1
```

## - sysproc.c

Line 114 - 173:
```c
#ifdef CS333_P2
uint
sys_getuid(void)
{
  return myproc()->uid;
}

uint
sys_getgid(void)
{
  return myproc()->gid;
}

uint
sys_getppid(void)
{
  if(!myproc()->parent){
    return myproc()->pid;
  }
  return myproc()->parent->pid;
}

int
sys_setuid(void)
{
  int uid;

  if(argint(0,&uid) < 0)
    return -1;
  if(uid < 0 || uid > 32767)
    return -1;
  myproc()->uid = uid;
  return 0;
}

int
sys_setgid(void)
{
  int gid;
  
  if(argint(0,&gid) < 0)
    return -1;
  if(gid < 0 || gid > 32767)
    return -1;
  myproc()->gid = gid;
  return 0;
}

int
sys_getprocs(void)
{
  uint max;
  struct uproc* table;
  if(argint(0, (void*)&max) < 0)
    return -1;
  if(argptr(1, (void*)&table, sizeof(&table) * max) < 0)
    return -1;
  return getprocs(max, table);
}
#endif
```

## - proc.h

Line 55 - 61:
```c
#ifdef CS333_P2
  uint uid;
  uint gid;

  uint cpu_ticks_total;
  uint cpu_ticks_in;
#endif
```

## - proc.c

Line 9-11:
```c
#ifdef CS333_P2
#include "uproc.h"
#endif //CS333_P2
```

Line 158-161:
```c
#ifdef CS333_P2
  p->cpu_ticks_total = 0;
  p->cpu_ticks_in = 0;
#endif
```

Line 200-203:
```c
#ifdef CS333_P2
  p->uid = DEFAULT_UID;
  p->gid = DEFAULT_GID;
#endif
```

Line 270 - 273:
```c
#ifdef CS333_P2
  np->uid = curproc->uid;
  np->gid = curproc->gid;
#endif
```

Line 412 - 414:
```c
#ifdef CS333_P2
      p->cpu_ticks_in = ticks;
#endif
```

Line 455 - 457:
```c
#ifdef CS333_P2
  p->cpu_ticks_total += (ticks - p->cpu_ticks_in);
#endif //P2
```

Line 585 - 596:
```c
  int elapsed = ticks - p->start_ticks;
  int total = p->cpu_ticks_total;
  int ppid;
  if(p->parent)
  {
    ppid = p->parent->pid;
  }
  else
  {
    ppid = p->pid;
  }
  cprintf("%d\t%s\t     %d\t\t%d\t%d\t%d.%d\t%d.%d\t%s\t%d\t", p->pid, p->name, p->uid, p->gid, ppid, elapsed/1000, elapsed%1000, total/1000, total%1000, state_string, p->sz);
```

Line 956 - 988:
```c
#ifdef CS333_P2
int
getprocs(uint max, struct uproc* table)
{
  int index = 0;
  struct proc* p;

  acquire(&ptable.lock);
  if(!table || max <= 0){
    release(&ptable.lock);
    return -1;
  }
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(index >= max)
      break;
    if(p->state != EMBRYO && p->state != UNUSED){
      table[index].pid = p->pid;
      table[index].uid = p->uid;
      table[index].gid = p->gid;
      table[index].ppid = (!p->parent) ? p->pid : p->parent->pid;
      table[index].elapsed_ticks = ticks - p->start_ticks;
      table[index].CPU_total_ticks = p->cpu_ticks_total;
      table[index].size = p->sz;
      safestrcpy(table[index].state, states[p->state], sizeof(table[index]).state);
      safestrcpy(table[index].name, p->name, sizeof(table[index]).name);
      index++;
    }
  }
  release(&ptable.lock);

  return index;
}
#endif
```

## - defs.h

Line 12 - 14:
```c
#ifdef CS333_P2
struct uproc;
#endif
```

Line 130 - 132:
```c
#ifdef CS333_P2
int             getprocs(uint max, struct uproc* table);
#endif
```

## - ps.c

Line 1 - 48:
```c
#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

int
main(void)
{
  struct uproc* table;
  int index;
  uint max = 72;
  int procs = 0;
  uint elapsed, decimal, seconds, seconds_decimal;

  table = malloc(sizeof(struct uproc) * max);
  procs = getprocs(max, table);
  
  if(procs == -1)
    printf(1, "\nError: Invalid Maximum/Null Uproc\n");
  else {
    printf(1, "\nPID\tName\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize");
    for(index = 0; index < procs; ++index) {
      decimal = table[index].elapsed_ticks % 1000;
      elapsed = table[index].elapsed_ticks / 1000;
      seconds_decimal = table[index].CPU_total_ticks % 1000;
      seconds = table[index].CPU_total_ticks / 1000;

      printf(1, "\n%d\t%s\t%d\t%d\t%d\t%d.", table[index].pid, table[index].name, table[index].uid, table[index].gid, table[index].ppid, elapsed);
      
      if(decimal < 10)
        printf(1, "00");
      else if(decimal < 100)
        printf(1, "0");
      printf(1, "%d\t%d.", decimal, seconds);
      if(seconds_decimal < 10)
        printf(1, "00");
      else if(seconds_decimal < 100)
        printf(1, "0");

      printf(1, "%d\t%s\t%d", seconds_decimal, table[index].state, table[index].size);
    }
    printf(1, "\n");
  }

  free(table);
  exit();
}
#endif
```

## - testsetuid.c

Line 1 - 11:
```c
#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  printf(1, "***** In %s: my uid is %d\n\n", argv[0], getuid());
  exit();
}
#endif
```

## - time.c

Line 1 - 35:
```c
#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char* argv[])
{
    int time1 = 0, time2 = 0, elapsed = 0, decimal = 0, pid = 0;
    ++argv;
    time1 = uptime();
    pid = fork();

    if(pid < 0) {
        printf(1, "Ran in 0.000 seconds\n");
        exit();
    }
    else if(pid == 0) {
        exec(argv[0], argv);
    }
    else {
        wait();
        time2 = uptime();
        decimal = (time2 - time1) % 1000;
        elapsed = (time2 - time1) / 1000;
        printf(1, "%s ran in %d.", argv[0], elapsed);
        if(decimal < 10)
        printf(1, "00");
        else if(decimal < 100)
        printf(1, "0");
        printf(1, "%d seconds\n", decimal);
    }
    
    exit();
}
#endif
```
