#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <curses.h>
#include <sys/stat.h>

int main(void)
{
	pid_t child;
	DIR *d;
	struct dirent *de;
	int i, c, k;
	char s[256], cmd[256], file[256][1024], dir[256][1024];
	time_t t;
	int num;

	while (1)
	{
		getcwd(s,200);					//	Printing out Current Directory
		printf("\nCurrent Directory: %s\n", s);

                t = time(NULL);                                 //      Printing out the Current Time
                printf("It is now: %s\n", ctime(&t));

		d = opendir(".");
		c = 0;

		printf("Files:\n");

		while ((de = readdir(d)))			//	Printing out Files
		{
                        if (((de -> d_type) & DT_REG))
                        {
                                printf("                %d. %s \n", c, de -> d_name);
				strcpy(file[c], de -> d_name);
				c++;
                        }

		}
		closedir(d);
	

		d = opendir(".");
		c = 0;

		printf("\nDirectories:\n");

		while ((de = readdir(d)))			//	Printing out Directories
		{
                        if ((de -> d_type) & DT_DIR)
                        {
                                printf("                %d. %s \n", c, de -> d_name);
				strcpy(dir[c], de -> d_name);
				c++;
                        }

		}
		closedir(d);

		d = opendir(".");
		c = 0;
		
		printf("\nOperations:\n");
		
		printf("                E  Edit\n");
		printf("                R  Run\n");
		printf("                C  Change Directory\n");
		printf("                M  Make New Subdirectory\n");
		printf("                F  Remove File\n");
		printf("                Q  Quit\n\n");

		printf("----------------------------------------------\n");
		c = getchar();

		strcpy(cmd, "");

		switch (c)
		{
			case 'q' :	exit(0);			// Quit

			case 'e' :	printf("Edit What?: ");		// Edit
					scanf("%d", &num);
					strcpy(s,file[num]);

					strcpy(cmd, "pico ");
					strcat(cmd, s);
					system(cmd);
					break;
			
			case 'r':	printf("Run what?: ");
					scanf("%d", &num);
					strcpy(cmd, "./");
					strcat(cmd, file[num]);
					system(cmd);
					break;

			case 'c':	printf("Change To?: ");
					scanf("%d", &num);
					strcpy(cmd, dir[num]);
					chdir(cmd);
					break;

			case 'f':	printf("Remove what?: ");
					scanf("%d", &num);
					strcpy(cmd, file[num]);
					remove(cmd);
					break;

			case 'm':	printf("Make what?: ");
					scanf("%s", cmd);
					mkdir(cmd, d);
					break;
					
		}
		
	}
}



















