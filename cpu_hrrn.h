struct process_hrrn
{
  char name;
  int at_hrrn,bt_hrrn,ct_hrrn,wt_hrrn,tt_hrrn;
  int completed;
  float ntt_hrrn;
}p_hrrn[10];
int n;
void sortByArrival_hrrn()
{
  struct process_hrrn temp;
  int i,j;
  for(i=0;i<n-1;i++)
  {
    for(j=i+1;j<n;j++)
    {
      if(p_hrrn[i].at_hrrn>p_hrrn[j].at_hrrn)
      {
	temp=p_hrrn[i];
	p_hrrn[i]=p_hrrn[j];
	p_hrrn[j]=temp;
      }
    }
  }
}
void HRRN()
{
  int i,j,time,sum_bt=0;
  char c;
  float avgwt=0;
  printf("Enter no of processes:");
  scanf("%d",&n);
  for(i=0,c='A';i<n;i++,c++)
  {
    p_hrrn[i].name=c;
    printf("\nEnter the arrival time and burst time of process%c: ",p_hrrn[i].name);
    scanf("%d%d",&p_hrrn[i].at_hrrn,&p_hrrn[i].bt_hrrn);
    p_hrrn[i].completed=0;
    sum_bt+=p_hrrn[i].bt_hrrn;
  }
  sortByArrival_hrrn();
  printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
  for(time=p_hrrn[0].at_hrrn;time<sum_bt;)
  {
  float hrr=-9999;
  int loc;
  for(i=0;i<n;i++)
  {
    if(p_hrrn[i].at_hrrn<=time && p_hrrn[i].completed!=1)
    {
      float temp=(p_hrrn[i].bt_hrrn + (time-p_hrrn[i].at_hrrn))/p_hrrn[i].bt_hrrn;
      if(hrr < temp)
      {
	hrr=temp;
	loc=i;
      }
    }
  }  
  time+=p_hrrn[loc].bt_hrrn; 
  p_hrrn[loc].wt_hrrn=time-p_hrrn[loc].at_hrrn-p_hrrn[loc].bt_hrrn;
  p_hrrn[loc].tt_hrrn=time-p_hrrn[loc].at_hrrn;
  p_hrrn[loc].ntt_hrrn=((float)p_hrrn[loc].tt_hrrn/p_hrrn[loc].bt_hrrn);
  p_hrrn[loc].completed=1;
  avgwt+=p_hrrn[loc].wt_hrrn;
  printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",p_hrrn[loc].name,p_hrrn[loc].at_hrrn,p_hrrn[loc].bt_hrrn,p_hrrn[loc].wt_hrrn,p_hrrn[loc].tt_hrrn,p_hrrn[loc].ntt_hrrn);
  }
  printf("\nAverage waiting time:%f\n",avgwt/n);
}