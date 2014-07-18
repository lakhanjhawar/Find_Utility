#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<fcntl.h>
void visitdir(char *);
int main(int argc, char *argv[])
{
	 struct stat status1 ;
	        unsigned long ftype ;
	DIR *dp;
	 dp = opendir(argv[1]);
	        if( dp != NULL)
	        {
	        	   	stat(argv[1], &status1);
	                ftype = (status1.st_mode) & (0xF000);
	                if (ftype == 0x4000 )
	               visitdir(argv[1]);
	              else
	                printf("directory doesnot exist\n ");
	        }
        return 0;
}
void visitdir(char a[])
{
	struct dirent *dp;
	       DIR *dptr;
	       int fd;
        struct stat dtl;
        char *msg,*b,*c,*temp=NULL;
        unsigned long ftype;
        if((dptr = opendir(a))!=NULL);
        {
                while((dp = readdir(dptr)) != NULL)
                {
                	 temp = malloc(strlen(a) + strlen(dp->d_name) + 2 );
                	                					strcpy(temp, a);
                	                					  strcat(temp,"/");
                	                					strcat(temp,dp->d_name);
if((strcmp(dp->d_name,".")==0) || (strcmp(dp->d_name,"..")==0))
{
	continue;
}
              	                       if (lstat(temp, &dtl) != -1)
               	                        {
              	                    	  ftype=(dtl.st_mode) & (0xF000);
              	                    	  if(ftype==0x4000)
              	                    	  {
              	                    		  printf("DIR\t%s\n",dp->d_name);
              	                    	  visitdir(temp);
              	                    	  free(temp);
              	                    	  }
              	                    	  else if(ftype==0x8000)
              	                    		  printf("REG\t%s\n",dp->d_name);
              	                    	  else
              	                    		  printf("OTHER\t%s\n",dp->d_name);
               	                        }
              	                       else
               	                        {
              	                    	  c=(char *)strerror(errno);
              	                    	   perror(c);
                	                        	continue;
               	                        }


                }
        }
                closedir(dptr);
        }


