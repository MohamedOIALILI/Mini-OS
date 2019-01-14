struct process_fcfs
{
  char name;
  int at_fcfs,bt_fcfs,ct_fcfs,tt_fcfs;
  float ntt_fcfs;
}p_fcfs[10];
int n;
void sortByArrival_fcfs()
{
  struct process_fcfs temp;
  int i,j;
  for(i=0;i<n-1;i++)
  {
    for(j=i+1;j<n;j++)
    {
      if(p_fcfs[i].at_fcfs>p_fcfs[j].at_fcfs)
      {
	temp=p_fcfs[i];
	p_fcfs[i]=p_fcfs[j];
	p_fcfs[j]=temp;
      }
    }
  }
}

void FCFS()
{
  int i,j,time=0;
  char c;
  printf("Enter no of processes:");
  scanf("%d",&n);
  for(i=0,c='A';i<n;i++,c++)
  {
    p_fcfs[i].name=c;
    printf("\nEnter the arrival time of process%d: ",i+1);
    scanf("%d",&p_fcfs[i].at_fcfs);
    printf("\nEnter the burst time of process%d: ",i+1);
    scanf("%d",&p_fcfs[i].bt_fcfs);
  }
  sortByArrival_fcfs();
  printf("\nName\tArrival Time\tBurst Time\tTurnAround Time\t  Normalized TT");
  for(i=0;i<n;i++)
  {
    time+=p_fcfs[i].bt_fcfs;
    p_fcfs[i].ct_fcfs=time;
    p_fcfs[i].tt_fcfs=p_fcfs[i].ct_fcfs-p_fcfs[i].at_fcfs;
    p_fcfs[i].ntt_fcfs=((float)p_fcfs[i].tt_fcfs/p_fcfs[i].bt_fcfs);
    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%f",p_fcfs[i].name,p_fcfs[i].at_fcfs,p_fcfs[i].bt_fcfs,p_fcfs[i].tt_fcfs,p_fcfs[i].ntt_fcfs);
  }
}