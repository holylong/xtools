#include <stdio.h>
#include <string.h>

#define MAX_LINE 2048

void help(char* argv[])
{
	printf("please input a file as parameter like %s a.txt\n", argv[0]);
}

void display(const char* pwd)
{
        char tstr[MAX_LINE];
	FILE *fp = fopen(pwd, "r");
	if(fp)
	{
		while(!feof(fp))
		{
			fgets(tstr, MAX_LINE, fp);
			printf("%s", tstr);
			memset(tstr, '\0', MAX_LINE);
		}
                fclose(fp);
                fp = NULL;
	}
}

int main(int argc, char* argv[])
{
	if(argc == 1)
	{
		help(argv);
                return -1;
	}

	for(int i = 1; i < argc; i++)
	{
		display(argv[i]);	
	}
	return 0;
}
