#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>
#include<pwd.h>
char *seltable[3]={"-name","-mtime","-user"};
char *sel = NULL,*arg = NULL;
int caseval;
int procarg(char *,char *,char *);
void visitdir(char *);
int main(int argc, char *argv[])
{
	 struct stat status1 ;
		        unsigned long ftype ;
		DIR *dp;
		 dp = opendir(argv[1]);
		 sel = malloc(strlen(argv[1]) + strlen("/") + 30 );
		 	arg = malloc(strlen(argv[1]) + strlen("/") + 30 );
      if( dp != NULL)
     	        {
    	          procarg(argv[1],argv[2],argv[3]);
     	        	   	stat(argv[1], &status1);
     	                ftype = (status1.st_mode) & (0xF000);
     	                if (ftype == 0x4000 )
     	               visitdir(argv[1]);
     	              else
     	                printf("directory doesnot exist\n ");
     	        }
      free(sel);
      free(arg);
        return 0;
}
void visitdir(char a[])
{
	struct dirent *dp;
	struct passwd *t;
	       DIR *dptr;
	       int fd;
	 long giventime,systime,b,c,presenttime;
        struct stat dtl;
        char *temp=NULL,*d;
        unsigned long ftype;
        if((dptr = opendir(a))!=NULL)
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
        		  ftype=(dtl.st_mode) & 0xF000;
                     switch(caseval)
                     {
                         case 0:
        	              	                    	  if(ftype==0x4000)
        	              	                    	  {
        	              	                    		if((strcasecmp(dp->d_name,arg)) == 0)
        	              	                    		{
        	              	                    		  printf("DIR\t%s\n",dp->d_name);
        	              	                    		printf(" the path is %s\n",temp);
        	              	                    		}
        	              	                    	  visitdir(temp);
        	              	                    	free(temp);
        	              	                    	  }
        	              	                    	  else if(ftype==0x8000)
        	              	                    	  {
        	               	                    		  if((strcasecmp(dp->d_name,arg)) == 0)
        	              	                    	  {
        	              	                    			printf("REG\t%s\n",dp->d_name);
        	              	                    			 printf(" the path is %s\n",temp);
        	              	                    			 continue;
        	              	                    	  }
        	              	                    	  }
        	              	                    	  else
        	              	                    	  {
        	              	                    		if((strcasecmp(dp->d_name,arg)) == 0)
        	              	                    		{
        	              	                    		printf("OTHER\t%s\n",dp->d_name);
        	              	                    		 printf(" the path is %s\n",temp);
        	              	                    		 continue;
        	              	                    	  }
        	              	                    	  }
        	              	                     /*  else
        	               	                        {
        	              	                    	   printf("fstat failed\n");
        	              	                    	  d=(char *)strerror(errno);
        	              	                    	   perror(d);
        	                	                        	continue;
        	               	                        }*/
        	              	                       break;
        case 1:
        	giventime=((*arg)*86400);
        	        time(&systime);
        	        b=systime % 86400;
        	        c=(systime-giventime)-b;

        	              	                    	  if(ftype==0x4000)
        	              	                    	  {
        	              	                    		  visitdir(temp);
        	              	                    		  free(temp);
        	              	                    	 }
        	              	                    	  else if(ftype==0x8000)
        	              	                    	  {
        	              	                    		  time(&presenttime);
        	              	                    		  if(dtl.st_mtime>c && presenttime)
        	              	                    		  {
        	              	                    			  printf("%s %s\n",dp->d_name,ctime(&dtl.st_mtime));
        	              	                    			  continue;
        	              	                    		  }
        	              	                    		  else
        	              	                    			  printf("no file modified\n");
        	              	                    	  }
        	              	                    	  else
        	              	                    	  {

        	              	                    		  printf("");
        	              	                    	  }

        	              	                       /*else
        	               	                        {
        	              	                    	   printf("fstat failed\n");
        	              	                    	  d=(char *)strerror(errno);
        	              	                    	   perror(d);
        	                	                        	continue;
        	               	                        }*/

        	 break;
        case 2:
       	                                t=getpwnam(arg);
                     	                    	  if(ftype==0x4000)
                     	                    	  {
                     	                    		  if(t->pw_uid==dtl.st_uid)
                     	                    		  {
                     	                    			  printf("%s\t %s\t\n",t->pw_name,dp->d_name);
                     	                    		  }
                     	                    		  visitdir(temp);
                     	                    		  free(temp);
                     	                    	 }
                     	                    	  else if(ftype==0x8000)
                     	                    	  {
                     	                    		if(t->pw_uid==dtl.st_uid)
                     	                    		{
                     	                    	 printf("%s\t %s\t\n",t->pw_name,dp->d_name);
                     	                    	 continue;
                     	                    		}
                     	                    	  }
                     	                    	  else
                     	                    	  {
                     	                    		if(t->pw_uid==dtl.st_uid)
                     	                    		{
                     	                    		printf("%s\t %s\t\n",t->pw_name,dp->d_name);
                     	                    		continue;
                     	                    	  }
                     	                    	  }
 /*                    	                       else
                      	                        {
                     	                    	   printf("fstat failed");
                     	                    	  d=(char *)strerror(errno);
                     	                    	   perror(d);
                       	                        	continue;
                      	                        }*/

        break;
        default:

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

        	              	           /*            else
        	               	                        {
        	              	                    	  d=(char *)strerror(errno);
        	              	                    	   perror(d);
        	                	                        	continue;
        	               	                        }*/
        	   break;
        }
}
                     else
                             	               	                        {
                             	              	                    	   printf("fstat failed\n");
                             	              	                    	  d=(char *)strerror(errno);
                             	              	                    	   perror(d);
                             	                	                        	continue;
                             	               	                        }
        	                }
        }
                closedir(dptr);
                free(temp);
        }

int procarg(char a[],char b[],char c[])
{
	int i,j;
	for(i=0;i<3;i++)
	{
	if(strcasecmp(b,seltable[i])==0)
	{
		printf("source=%s selection=%s arg=%s\n",a,b,c);
		strcpy(sel,b);
		strcpy(arg,c);
		caseval=i;
		return 0;
	}
	}
	printf("%s",c);
	return 0;
}
