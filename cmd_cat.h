#define MAX_FILE_NAME_CHARS 255
void CAT(int argc, char *argv[])
{
  FILE *fp;
  char file_name[MAX_FILE_NAME_CHARS], ch;
  int i;
  if(argc<1){
    printf("Usage mycat <filename> \n");
    return;
  }
  for(i=1; i<=argc;i++){
    strncpy(file_name, argv[i], MAX_FILE_NAME_CHARS);
    fp=fopen(file_name, "r");
    if(fp == NULL) {
      printf("%s: No such file or directory\n", file_name);
      return;
    }
    while((ch=fgetc(fp)) != EOF){
    putchar(ch);
  }
  fclose(fp);
  }
}
