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
    printf(1, "Error: Invalid Maximum/Null Uproc\n");
  else {
    printf(1, "PID\tName\tUID\tGID\tPPID\tElapsed\tCPU\tState\tSize");
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