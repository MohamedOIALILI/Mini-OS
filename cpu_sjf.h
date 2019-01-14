struct process_sjf
{
  char name;
  int at_sjf,bt_sjf,ct_sjf,wt_sjf,tt_sjf;
  int processed;
  float ntt_sjf;
}p_sjf[10];
int n;
void sortByArrival_sjf()
{
  struct process_sjf temp;
  int i,j;
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++)
    {
      if(p_sjf[i].at_sjf>p_sjf[j].at_sjf)
      {
	temp=p_sjf[i];
	p_sjf[i]=p_sjf[j];
	p_sjf[j]=temp;
      }
    }
  }
}
void SJF()
{
  int i,j,time,sum_bt=0,smallest;
  char c;
  float avgwt=0;
  printf("Enter no of processes:");
  scanf("%d",&n);
  for(i=0,c='A';i<n;i++,c++)
  {
    p_sjf[i].name=c;
    printf("\nEnter the arrival time of process%c: ",p_sjf[i].name);
    scanf("%d",&p_sjf[i].at_sjf);
    printf("\nEnter the burst time of process%c: ",p_sjf[i].name);
    scanf("%d",&p_sjf[i].bt_sjf);
    p_sjf[i].processed=0;
    sum_bt+=p_sjf[i].bt_sjf;
  }
  sortByArrival_sjf();
  p_sjf[9].bt_sjf=9999;
  printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
  for(time=p_sjf[0].at_sjf;time<sum_bt;)
  {
    smallest=9;
    for(i=0;i<n;i++)
    {
      if(p_sjf[i].at_sjf<=time && p_sjf[i].processed!=1 && p_sjf[i].bt_sjf<p_sjf[smallest].bt_sjf)
	smallest=i;
    }
    time+=p_sjf[smallest].bt_sjf;
    p_sjf[smallest].ct_sjf=time;
    p_sjf[smallest].wt_sjf=time-p_sjf[smallest].at_sjf-p_sjf[smallest].bt_sjf;
    p_sjf[smallest].tt_sjf=p_sjf[smallest].wt_sjf+p_sjf[smallest].bt_sjf;
    p_sjf[smallest].ntt_sjf=((float)p_sjf[smallest].tt_sjf/p_sjf[smallest].bt_sjf);
    p_sjf[smallest].processed=1;
    avgwt+=p_sjf[smallest].wt_sjf;
    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",p_sjf[smallest].name,p_sjf[smallest].at_sjf,p_sjf[smallest].bt_sjf,p_sjf[smallest].wt_sjf,p_sjf[smallest].tt_sjf,p_sjf[smallest].ntt_sjf);
  }
  printf("\nAverage waiting time:%f\n",avgwt/n);
}