
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<fcntl.h>
void visitdir(DIR *,char *);
int main(int argc, char *argv[])
{
        int fp ;
        struct stat status1 ;
        unsigned long ftype ;
        DIR *dp;
        dp = opendir(argv[1]);
        printf("%s",argv[1]);
        if( dp != NULL)
        {
        	   	stat(argv[1], &status1);
                ftype = (status1.st_mode) & (0xF000);
                printf("\n ftype = 0x%x \n",ftype);

                if (ftype == 0x4000 )
                        visitdir(dp,argv[1]);
        }


        return 0;
}

void visitdir(DIR *dptr,char a[])
{

	struct dirent *dp;
        struct stat dtl;
        char *msg,*b,*c,*curfp,*backup,*temp;

        printf("In Visit Dir");
        printf("%s",a);
        printf("%d",strlen(a));
        strcat(a,"/");
        temp = malloc(strlen(a) + strlen("/") );
                while((dp = readdir(dptr)) != NULL)
                {


                					strcpy(temp, a);
                  	        		//strcat(temp,"/");
                					strcat(temp,dp->d_name);
               	                	printf("current entry=%s\n",dp->d_name);
               	                	printf("Path=%s\n",temp);
              	                       if (stat(temp, &dtl) != -1)
               	                        {
               	                        	printf("Entry name: %s\tLast modified on %ld\n",dp->d_name,&dtl.st_mtime);
              	                                //c=NULL;
               	                                //continue;
               	                        }                        else
               	                        {
               	                        	printf("%s\n",strerror(errno));

                	                        	//c=NULL;
                	                        	continue;
               	                        }


                }
                free(temp);
        }


