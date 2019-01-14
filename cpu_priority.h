struct process_p
{
  char name;
  int at_p,bt_p,ct_p,wt_p,tt_p,priority;
  int processed;
  float ntt_p;
}p_p[10];
int n;
void sortByArrival_p()
{
  struct process_p temp;
  int i,j;
  for(i=0;i<n-1;i++)
  {
     for(j=i+1;j<n;j++)
    {
      if(p_p[i].at_p>p_p[j].at_p)
      {
	temp=p_p[i];
	p_p[i]=p_p[j];
	p_p[j]=temp;
      }
    }
  }
}
void PRIORITY()
{
  int i,j,time=0,sum_bt=0,lgst;
  char c;
  float avgwt=0;
  printf("Enter no of processes:");
  scanf("%d",&n);
  for(i=0,c='A';i<n;i++,c++)
  {
    p_p[i].name=c;
    printf("\nEnter the arrival time , burst time, priority of process%c: ",p_p[i].name);
    scanf("%d%d%d",&p_p[i].at_p,&p_p[i].bt_p,&p_p[i].priority);
    p_p[i].processed=0;
    sum_bt+=p_p[i].bt_p;
  }
  sortByArrival_p();
  p_p[9].priority=-9999;
  printf("\nName\tArrival Time\tBurst Time\tPriority\t WT \t TT \t NTT");
  for(time=p_p[0].at_p;time<sum_bt;)
  {
    lgst=9;
    for(i=0;i<n;i++)
    {
      if(p_p[i].at_p<=time && p_p[i].processed!=1 && p_p[i].priority>p_p[lgst].priority)
        lgst=i;
    }
    time+=p_p[lgst].bt_p;
    p_p[lgst].ct_p=time;
    p_p[lgst].wt_p=p_p[lgst].ct_p-p_p[lgst].at_p-p_p[lgst].bt_p;
    p_p[lgst].tt_p=p_p[lgst].ct_p-p_p[lgst].at_p;
    p_p[lgst].ntt_p=((float)p_p[lgst].tt_p/p_p[lgst].bt_p);
    p_p[lgst].processed=1;
    avgwt+=p_p[lgst].wt_p;
    printf("\n%c\t\t%d\t\t%d\t\t%d\t%d\t%d\t%f",p_p[lgst].name,p_p[lgst].at_p,p_p[lgst].bt_p,p_p[lgst].priority,p_p[lgst].wt_p,p_p[lgst].tt_p,p_p[lgst].ntt_p);
  }
  printf("\nAverage waiting time:%f\n",avgwt/n);
}