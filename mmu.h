typedef struct {
  int Valid;
  int Frame;
  int Dirty;
  int Requested;
}page_table_entry;
typedef page_table_entry* page_table_pointer;
void ContinueHandler(int Signal) {
//----Nothing to do there
}
void PrintPageTable(page_table_entry PageTable[],int NumberOfPages)
{
  int Index;
  for (Index=0;Index<NumberOfPages;Index++)
  {
    printf("%2d: Valid=%1d Frame=%2d Dirty=%1d Requested=%1d\n",Index,
    PageTable[Index].Valid,PageTable[Index].Frame,PageTable[Index].Dirty,
    PageTable[Index].Requested);
  }
}
void MMU(int argc,char *argv[])
{
  int SharedMemoryKey;
  int NumberOfPages;
  int OSPID;
  int SegmentID;
  page_table_pointer PageTable;
  int RSIndex;
  int Mode;
  int Page;
  if (argc < 2 ||
  (OSPID = SharedMemoryKey = atoi(argv[argc-1])) == 0  ||
  (NumberOfPages = atoi(argv[1])) == 0)
  {
    printf("Usage:");
    exit(EXIT_FAILURE);
  }
  if ((SegmentID = shmget(SharedMemoryKey,
  NumberOfPages*sizeof(page_table_entry),0)) == -1 ||
  (PageTable = (page_table_pointer)shmat(SegmentID,NULL,0)) == NULL)
  {
    perror("ERROR: Could not get page table");
    exit(EXIT_FAILURE);
  }
  if(signal(SIGCONT,ContinueHandler) == SIG_ERR)
  {
    printf("ERROR: Could not initialize continue handler\n");
    exit(EXIT_FAILURE);
  }
  printf("Initialized page table:\n");
  PrintPageTable(PageTable,NumberOfPages);
  printf("\n");
  for(RSIndex=2;RSIndex<argc-1;RSIndex++)
  {
    Mode = argv[RSIndex][0];
    Page = atoi(&argv[RSIndex][1]);
    if(Page >= NumberOfPages)
    {
      printf("ERROR: That page number in %c%d is outside the process\n",Mode,Page);
    }
    else
    {
    printf("Request for page %d in %c mode\n",Page,Mode);
    if(!PageTable[Page].Valid)
    {
      printf("It's not in RAM - page fault\n");
      PageTable[Page].Requested = getpid();
      sleep(1);
      if(kill(OSPID,SIGUSR1) == -1)
      {
	perror("Kill to OS");
	exit(EXIT_FAILURE);
      }
      pause();
      if(!PageTable[Page].Valid)
      {
	printf("Bugger, something wrong\n");
      }
    }
    else
    {
      printf("It's in RAM\n");
    }
    if (Mode == 'W') {
      printf("Set the dirty bit for page %d\n",Page);
      PageTable[Page].Dirty = 1;
    }
    PrintPageTable(PageTable,NumberOfPages);
    printf("\n");
  }
 }
  if(shmdt(PageTable) == -1)
  {
    perror("ERROR: Error detaching segment");
    exit(EXIT_FAILURE);
  }
  printf("Tell OS that I'm finished\n");
  sleep(1);
  if(kill(OSPID,SIGUSR1) == -1)
  {
    perror("Kill to OS");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
