#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#include "cpu_round_robin.h"
#include "cpu_priority.h"
#include "cpu_fcfs.h"
#include "cpu_hrrn.h"
#include "cpu_sjf.h"
#include "mmu.h"
#include "hd.h"
#include "cmd_ls.h"
#include "cmd_grep.h"
#include "cmd_rm.h"
#include "cmd_cp.h"
#include "cmd_cat.h"

int main(int argc, char* argv[])
{
  unsigned short choose,type_sch,type_cmd;
  printf("\t##################################################\n");
  printf("\t##################################################\n");
  printf("\t####################          ####################\n");
  printf("\t####################   Menu   ####################\n");
  printf("\t####################          ####################\n");
  printf("\t##################################################\n");
  printf("\t##################################################\n");
  printf("\n\n");
  printf("   1) Simulate CPU Sheduling\n");
  printf("   2) Simulate Memory\n");
  printf("   3) Simulate Hard Drive\n");
  printf("   4) Simulate Commands\n");
  printf("   5) Quite\n");
  printf("\nEnter your choose: ");
  scanf("%d",&choose);
  if(choose == 1)
  {
    printf("  1) Round Robin Scheduling\n");
    printf("  2) Priority Based Scheduling\n");
    printf("  3) FCFS Scheduling\n");
    printf("  4) Highest Response Ratio Next Scheduling\n");
    printf("  5) Shortest Job First Scheduling\n");
    printf("\nEnter the type of Scheduling: ");
    scanf("%d",&type_sch);
    if(type_sch == 1) { ROUND_ROBIN(); }
    if(type_sch == 2) { PRIORITY(); }
    if(type_sch == 3) { FCFS(); }
    if(type_sch == 4) { HRRN(); }
    if(type_sch == 5) { SJF(); }
  }
  if(choose == 2) { MMU(argc,argv); }
  if(choose == 3) { HD(argc,argv); }
  if(choose == 4)
  {
    printf("  1) LS Command\n");
    printf("  2) GREP Command\n");
    printf("  3) RM Command\n");
    printf("  4) CP Command\n");
    printf("  5) CAT Command\n");
    printf("\nEnter the type of Command: ");
    scanf("%d",&type_cmd);
    if(type_cmd == 1) { LS(); }
    if(type_cmd == 2) { GREP(); }
    if(type_cmd == 3) { RM(); }
    if(type_cmd == 4) { CP(argc,argv); }
    if(type_cmd == 5) { CAT(argc,argv); }
  }
  return 0;
}