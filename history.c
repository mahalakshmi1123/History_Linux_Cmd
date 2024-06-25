#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUF_SIZE 1024

void print_usage(char* prg_name)
{
	printf("Usage: %s [-f argument] [-c] [h]\n", prg_name);
	printf("\n./history -f <bash_history file path>" 
			"\nuse echo $HISTFILE to get file path\n");
	printf("\n eg : ./history -f <file_path> -c\n"); 
}

int main(int argc, char **argv)
{
    FILE* fptr;
    char his_buf[MAX_BUF_SIZE];
    char *filename = NULL;
    int c;
    char clear_flag = 0;

    /* parse the option */
    while ((c = getopt (argc, argv, "hf:c")) != -1) {
        switch (c) {
            case 'f':
		filename = optarg;
                break;
            case 'c':
                clear_flag = 1;
                break;
            case 'h':
		print_usage(argv[0]);
		exit(EXIT_SUCCESS);
	    default:
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
        }
    }

    if( filename == NULL )
    {
	    print_usage(argv[0]);
	    exit(EXIT_FAILURE);
    }

    if( clear_flag )
    {
	    fptr = fopen(filename, "w");
    }
    else
    {
	    fptr = fopen(filename, "r");
    }

    if (fptr == NULL) {
        printf("%s file not found\n",filename);
        exit(EXIT_FAILURE);
    }
	
    if( !clear_flag ) /* if clear_flag is not set then read the history */
    {
	    /* read 1kb of data from .bash_history file until EOF */
	    while(!feof(fptr))
	    {
		    fread(his_buf, sizeof(char), MAX_BUF_SIZE,fptr);
		    printf("%s",his_buf);
	    }
    }
    fclose(fptr);

    printf("\n **********************************\n");
    printf(" only %d bytes of history is shown \n",MAX_BUF_SIZE);
    printf("\n **********************************\n");
    return 0;
}
