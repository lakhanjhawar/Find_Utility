#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<time.h>
#include<pwd.h>
char selTable[4][10] = {"-name","-mtime","-user",NULL};
char sel[10];
char arg[1000];
int calcval = 0;
char **cmd_list;
int glob,N;
FILE *buf;

void ProcArg(int count, char *a[])
{
        int i,j,k;
        printf("Source=%s, Selection=%s,arg=%s\n",a[1],a[2],a[3]);
        for(i = 0 ; i < 4 ; i++)
        {
                if(strcmp(selTable[i],a[2]) == 0)
                {
                        calcval = i;
                        strcpy(sel,a[2]);
                        strcpy(arg,a[3]);

                }
        }

        N = count - 3;
        cmd_list = (char **)malloc(sizeof(char *) * N);
        for (i = 0 ; i < N ; i++)
                cmd_list[i] = (char *)malloc(sizeof(char)*300);
        strcpy(cmd_list[0],a[4]+1);
        i = 1;
        j = 5;
        while (count>j && strncmp(a[j],"-",1) == 0)
        {
        	 strcpy(cmd_list[i],a[j]);
        	                j++;
        	                i++;
        	        }
        	        glob = i;
        	        for (k = i+1 ; j < count ; k++)
        	        {
        	                strcpy(cmd_list[k],a[j]);
        	                j++;
        	        }

        	}

  void visitDir(char dir[1000])
   {
        	        DIR *dptr;
        	        struct dirent *dp;
        	        struct stat dtl;
        	        char *path = NULL;
        	        int ftype ;
        	        int fd,i;
        	        unsigned long int nosecs, tm;
        	        time_t mt;
        	        struct passwd *sf;
        	        if ((dptr = opendir(dir)) != NULL)
        	        {
        	                while((dp = readdir(dptr)) != NULL)
        	                {
        	                        errno = 0;
        	                        path = malloc(strlen(dir)+strlen(dp->d_name)+2);
        	                        path[0] = 0;
        	                        strcpy(path, dir);
        	                        strcat(path, "/");
        	                        strcat(path, dp->d_name);
        	                        if(strcmp(dp->d_name,".")==0 || strcmp(dp->d_name,"..") == 0 )
        	                                                      continue;

        	                       if(lstat(path,&dtl) != -1)
        	                           {
        	                                                      ftype = dtl.st_mode & 0xF000;
        	                                                      switch(calcval)
        	                                                      {
        	                                                      case 0:
        	                                                      if (ftype == S_IFDIR)
        	                                                      {
        	                                                              if(strcasecmp(dp->d_name,arg) == 0)
        	                                                              {
        	                                                              printf("DIR\t%s\n",path);
        	                                                              strcpy(cmd_list[glob],path);
        	                                                              for(i=0 ; i<N ; i++)
        	                                                                      fprintf(buf,"%s ",cmd_list[i]);
        	                                                              fprintf(buf,"\n");
        	                                                              }
        	                                                              visitDir(path);
        	                                                              free(path);
        	                                                      }
        	                                                      else if (ftype == S_IFREG)
        	                                                         {
        	                                                                    if(strcasecmp(dp->d_name,arg) == 0)
        	                                                                      {
        	                                                                      printf("Reg\t%s\n",path);
        	                                                                      strcpy(cmd_list[glob],path);
        	                                                              for(i=0 ; i<N ; i++)
        	                                                                      fprintf(buf,"%s ",cmd_list[i]);
        	                                                              fprintf(buf,"\n");
        	                                                                      continue;

        	                                                                      }
        	                                                              }
        	                                                      else
        	                                                       {
        	                                                      if(strcasecmp(dp->d_name,arg) == 0)
        	                                                      {
        	                                                         printf("Other\t%s\n",path);
        	                                                            strcpy(cmd_list[glob],path);
        	                                                            for(i=0 ; i<N ; i++)
        	                                                          fprintf(buf,"%s ",cmd_list[i]);
        	                                                             fprintf(buf,"\n");
        	                                                                   continue;
        	                                                                               }
        	                                                                              }
        	                                                                      break;

        	                                        case 1:
        	                                           nosecs = atoi(arg);
        	                                          nosecs = nosecs * 86400;
        	                                             time(&mt);
        	                                             tm = mt - dtl.st_mtime;
        	                                              if (ftype == S_IFDIR)
        	                                                {
        	                                                if(tm < nosecs)
        	                                                   {
        	                                                   printf("DIR\t%s\n",path);
        	                                                    strcpy(cmd_list[glob],path);
        	                                                     for(i=0 ; i<N ; i++)
        	                                                     fprintf(buf,"%s ",cmd_list[i]);
        	                                                        fprintf(buf,"\n");
        	                                                            }
        	                                                          visitDir(path);
        	                                                           free(path);
        	                                                              }
        	                                                   else if (ftype == S_IFREG)
        	                                                      {
        	                                                        if(tm < nosecs)
        	                                                         {

        	                                                    printf("Reg\t%s\n",path);
        	                                                     strcpy(cmd_list[glob],path);
        	                                                      for(i=0 ; i<N ; i++)
        	                                                     fprintf(buf,"%s ",cmd_list[i]);
        	                                                     fprintf(buf,"\n");
        	                                                        continue;
        	                                                               }
        	                                                             }
        	                                                      else
        	                                                       {
        	                                                       if(tm < nosecs)
        	                                                        {
        	                                                      printf("Other\t%s\n",path);
        	                                                        strcpy(cmd_list[glob],path);
        	                                                         for(i=0 ; i<N ; i++)
        	                                                         fprintf(buf,"%s ",cmd_list[i]);
        	                                                            fprintf(buf,"\n");
        	                                                               continue;
        	                                                            }
        	                                                              }
        	                                                           break;
        	                                                         case 2:
        	                                                       sf = getpwnam(arg);
        	                                                        if (ftype == S_IFDIR)
        	                                                       {
        	                                                       if(dtl.st_uid == sf->pw_uid)
        	                                                        {

        	                                                        printf("DIR\t%s\n",path);
        	                                                         strcpy(cmd_list[glob],path);
        	                                                           for(i=0 ; i<N ; i++)
        	                                                          fprintf(buf,"%s ",cmd_list[i]);
        	                                                           fprintf(buf,"\n");
        	                                                                 }
        	                                                              visitDir(path);
        	                                                                 free(path);
        	                                                                    }
        	                                                             else if (ftype == S_IFREG)
        	                                                                {
        	                                                             if(dtl.st_uid == sf->pw_uid)
        	                                                                {
        	                                                               printf("Reg\t%s\n",path);
        	                                                               strcpy(cmd_list[glob],path);
        	                                                                for(i=0 ; i<N ; i++)
        	                                                               fprintf(buf,"%s ",cmd_list[i]);
        	                                                                 fprintf(buf,"\n");
        	                                                                       continue;

        	                                                                          }
        	                                                                           }
        	                                                                else
        	                                                                  {
        	                                                                 if(dtl.st_uid == sf->pw_uid)
        	                                                                    {
        	                                                                    printf("Other\t%s\n",path);
        	                                                                  strcpy(cmd_list[glob],path);
        	                                                                   for(i=0 ; i<N ; i++)
        	                                                                   fprintf(buf,"%s ",cmd_list[i]);
        	                                                                    fprintf(buf,"\n");
        	                                                                    continue;
        	                                                                          }
        	                                                                            }
        	                                                                          break;
        	                                                               default:
        	                                                            if (ftype == S_IFDIR)
        	                                                                 {
        	                                                              printf("DIR\t%s\n",dp->d_name);
        	                                                                  visitDir(path);
        	                                                                  free(path);
        	                                                                     }
        	                                                                else if (ftype == S_IFREG)
        	                                                                 {
        	                                                                 printf("Reg\t%s\n",dp->d_name);
        	                                                                  continue;
        	                                                                      }
        	                                                                    else
        	                                                                   {
        	                                                                printf("Other\t%s\n",dp->d_name);
        	                                                                       continue;
        	                                                                    }
        	                                                                 break;
        	                                                               }
        	                           }
        	                                                      else
        	                                                     printf("Stat failed for the file\n");
        	                }
        	                                                                if(dp == NULL)
        	                                                                	printf("");
        	                                                                     else
        	                                                                 free(path);
        	                                                                  closedir(dptr);
        	                                                                       }
        	                                                                 else
        	                                                                 perror(dir);
        	                                                                   }

        	                                  int main(int argc, char *argv[])
        	                                    {
        	                                   struct stat det ;
        	                                  unsigned long ftype ;
        	                                     if (argc < 2)
        	                                      {
        	                                     printf("No arguments found\n");
        	                                       exit(1);
        	                                         }
        	                                  ProcArg(argc,argv);
        	                                     stat(argv[1], &det);
        	                                     printf("%s",argv[1]);
        	                                  ftype = (det.st_mode) & (0xF000);
        	                                      if (ftype == S_IFDIR)
        	                                       {
        	                                    buf = fopen("buf.sh","w+");
        	                                      visitDir(argv[1]);
        	                                       fclose(buf);
        	                                      system("sh -f buf.sh");
        	                                             }
        	                                      else
        	                                printf("not a directory\n");
        	                                                      return 0;
        	                                         }




