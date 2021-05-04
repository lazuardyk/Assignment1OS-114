# Code Modification

Kode-kode yang diubah di dalam XV6:
## - Makefile  

Line 3:
```c
CS333_PROJECT ?= 1
```
Line 4 (Jika ingin memunculkan syscall name):
```c
PRINT_SYSCALLS ?= 1
```
Line 16:
```c
CS333_UPROGS += _date
```

## - syscall.c

Line 109 - 111:
```c
#ifdef CS333_P1
extern int sys_date(void);
#endif
```
Line 138 - 140:
```c
#ifdef CS333_P1
[SYS_date]    sys_date,
#endif
```
Line 169 - 171:
```c
#ifdef CS333_P1
  [SYS_date]    "date",
#endif
```
Line 184 - 186:
```c
    #if defined CS333_PROJECT && defined PRINT_SYSCALLS
    cprintf("%s -> %d\n", syscallnames[num], curproc->tf->eax);
    #endif
```

## - user.h

Line 28 - 30:
```c
#ifdef CS333_P1
int date(struct rtcdate*);
#endif
```

## - usys.S

Line 33:
```c
SYSCALL(date)
```

## - syscall.h

Line 25:
```c
#define SYS_date    SYS_halt+1
```

## - sysproc.c

Line 101 - 112:
```c
#ifdef CS333_P1
int
sys_date(void)
{
  struct rtcdate *d;

  if(argptr(0, (void*)&d, sizeof(struct rtcdate)) < 0)
    return -1;
  cmostime(d);
  return 0;
}
#endif
```

## - proc.h

Line 52:
```c
#ifdef CS333_P1
  uint start_ticks;
#endif
```

## - proc.c

Line 151 - 153:
```c
#ifdef CS333_P1
  p->start_ticks = ticks;
#endif
```

Line 568 - 569:
```c
  uint elapsed_ms = ticks - p->start_ticks;
  cprintf("%d\t%s\t\t%d.%d\t%s\t%d\t", p->pid, p->name, elapsed_ms/1000, elapsed_ms%1000, state_string, p->sz);
```
