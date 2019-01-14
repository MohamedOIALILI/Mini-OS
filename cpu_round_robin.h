struct process_rr
{
  char name;
  int at_rr,bt_rr,wt_rr,tt_rr,rt_rr;
  int completed;
  float ntt_rr;
}p[10];
int n;
int q[100];
int front=-1,rear=-1;
void enqueue(int i)
{
  if(rear==100)
  {
    printf("overflow");
    return;
  }
  rear++;
  q[rear]=i;
  if(front==-1)
    front=0;
}
int dequeue()
{
  if(front==-1)
  {
    printf("underflow");
    return 0;
}
int temp=q[front];
  if(front==rear)
    front=rear=-1;
  else
    front++;
    return temp;
}
int isInQueue(int i)
{
  int k;
  for(k=front;k<=rear;k++)
  {
    if(q[k]==i)
    return 1;
  }
  return 0; 
}
void sortByArrival()
{
  struct process_rr temp;
  int i,j;
  for(i=0;i<n-1;i++)
  for(j=i+1;j<n;j++)
  {
    if(p[i].at_rr>p[j].at_rr)
    {
      temp=p[i];
      p[i]=p[j];
      p[j]=temp;
    }
  }
}
void ROUND_ROBIN()
{
  int i,j,time=0,sum_bt=0,tq;
  char c;
  float avgwt=0;
  printf("Enter the number of processes: ");
  scanf("%d",&n);
  for(i=0,c='A';i<n;i++,c++)
  {
    p[i].name=c;
    printf("\nEnter the arrival time and burst time of process %c: ",p[i].name);
    scanf("%d%d",&p[i].at_rr,&p[i].bt_rr);
    p[i].rt_rr=p[i].bt_rr;
    p[i].completed=0;
    sum_bt+=p[i].bt_rr;
  }
  printf("\nEnter the time quantum:");
  scanf("%d",&tq);
  sortByArrival();
  enqueue(0);
  printf("Process execution order: ");
  for(time=p[0].at_rr;time<sum_bt;)
  {
    i=dequeue();
    if(p[i].rt_rr<=tq)
    {
      time+=p[i].rt_rr;
      p[i].rt_rr=0;
      p[i].completed=1;         
      printf(" %c ",p[i].name);
      p[i].wt_rr=time-p[i].at_rr-p[i].bt_rr;
      p[i].tt_rr=time-p[i].at_rr;     
      p[i].ntt_rr=((float)p[i].tt_rr/p[i].bt_rr);
      for(j=0;j<n;j++)
      {
	if(p[j].at_rr<=time && p[j].completed!=1&& isInQueue(j)!=1)
	{
	  enqueue(j);
	}
      }
    }
    else
    {
      time+=tq;
      p[i].rt_rr-=tq;
      printf(" %c ",p[i].name);
      for(j=0;j<n;j++)
      {
	if(p[j].at_rr<=time && p[j].completed!=1&&i!=j&& isInQueue(j)!=1)
	{
	  enqueue(j);
	}
      }
      enqueue(i);
    } 
  }
  printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
  for(i=0;i<n;i++)
  {
    avgwt+=p[i].wt_rr;
    printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",p[i].name,p[i].at_rr,p[i].bt_rr,p[i].wt_rr,p[i].tt_rr,p[i].ntt_rr);
  }
  printf("\nAverage waiting time:%f\n",avgwt/n);
}