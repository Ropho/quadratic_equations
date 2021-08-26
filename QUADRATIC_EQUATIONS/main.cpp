#include "stdio.h"
#include "string.h"
#include "assert.h"
#include "malloc.h"

const int column = 100;

typedef struct JOJO {
    int len_str;
    char str[column];
}JOJO;


enum ERRORS {

ERROR_FILE_INCORRECT       = 1,
ALLOCATION_MEMORY_ERROR    = 2,
ERROR_IN_READING_FROM_FILE = 3
};

int FILESIZE_FUNC_VLOB (FILE *in) {

    assert (in != NULL);

	int file_size = 0;
	fseek (in, 0, SEEK_SET);


    while (getc(in) != EOF)
        file_size++;

	return file_size;
}

/*
int FILESIZE_FUNC (FILE *fp) {
    assert (fp != NULL);
    int save_pos = 0, size_of_file = 0;
    save_pos = ftell (fp);
    fseek (fp, 0L, SEEK_END);
    size_of_file = ftell (fp);
    fseek (fp, save_pos, SEEK_SET);
    return (size_of_file);
}
*/

int number_lines_in_array (char* str, int filesize) {

    assert (str != NULL);

    int num_of_lines = 0, i = 0;

    while (i < filesize) {

        if (*(str + i) == '\n')
            num_of_lines++;

        ++i;
    }

    num_of_lines++;

    return num_of_lines;
}


void copy_arrays (char source[][column], char destination[][column] , int lines) {

     assert (source != NULL);
     assert (destination != NULL);

     for (int i = 0; i < lines; ++i)
        strcpy (destination[i], source[i]);

     return;
}


void JOJO_FILLIN (char* str, JOJO* array_sort, int number_lines) {

    assert (str != NULL);
    assert (array_sort != NULL);

        char *starto = str;
        char *endo = NULL;

    for (int i = 0; i < number_lines; ++i) {

        if (i == number_lines - 1) {

        strcpy (array_sort[i].str, starto);
        array_sort[i].len_str = strlen (array_sort[i].str);
        //printf ("%s %d\n", array_sort[i].str, array_sort[i].len_str);
        return;

        }

        char *endo = strchr (starto, '\n');
        *endo = '\0';

        strcpy (array_sort[i].str, starto);
        array_sort[i].len_str = endo - starto;

        //printf ("%s %d\n", array_sort[i].str, array_sort[i].len_str);

        starto = endo + 1;
    }
}


void sort_array_BUBBLE (JOJO *str, int lines) {

    assert (str != NULL);

     for (int i = 1; i < lines; ++i) {                 //BUBBLE SORT
            JOJO s = {};

        for (int j = 0; j < lines - i; ++j) {

            if (strcmp(str[j].str, str[j+1].str) > 0){

                    strcpy(s.str, str[j].str);
                    s.len_str = str[j].len_str;

                    strcpy(str[j].str, str[j+1].str);
                    str[j].len_str = str[j+1].len_str;

                    strcpy(str[j+1].str, s.str);
                    str[j+1].len_str = s.len_str;

            }
        }
    }

}


void output_sorted (JOJO *str, int num_lines, FILE *out) {

    assert (str != NULL);
    assert (out != NULL);

    for (int i = 0; i < num_lines; ++i) {

        fputs (str[i].str, out);
        fputs ("\n", out);
    }
    return;

}


void output_ne_sorted (char* str, int num_lines, FILE *out) {

    assert (str != NULL);
    assert (out != NULL);

    char *starto = str;

    for (int i = 0; i < num_lines; ++i) {

        fputs (starto, out);
        fputs ("\n", out);
        starto = strchr (starto, '\0');
        ++starto;
    }
    return;
}


int main (void) {

    FILE *in = fopen ("HAMLET.txt", "r");
    FILE *out = fopen ("HAMLET_SORTED.txt", "w");
    if (in == NULL) {
        puts ("FILE_NOT_FOUND");

        return ERROR_FILE_INCORRECT;
    }


    int filesize = FILESIZE_FUNC_VLOB (in);

    char *array_strings = (char*)malloc(filesize * sizeof(char) + 1);
    if (array_strings == NULL) {
      puts ("ERROR IN MEMORY ALLOCATION");

      return ALLOCATION_MEMORY_ERROR;
    }

    fseek (in, 0, SEEK_SET);

    if (fread (array_strings, 1, filesize, in) != filesize) {
      puts ("ERROR IN READIN FROM FILE");

      return ERROR_IN_READING_FROM_FILE;
    }

    array_strings[filesize] = '\0';


    fclose (in);

    int number_lines = number_lines_in_array (array_strings,filesize);


    JOJO array_sort[number_lines] = {};

    JOJO_FILLIN (array_strings, array_sort, number_lines);

    sort_array_BUBBLE (array_sort, number_lines);

    output_sorted (array_sort, number_lines, out);

    output_ne_sorted (array_strings, number_lines, out);

    fclose (out);
/*
    copy_arrays (array_nesort, array_sort, lines);
    bubble_sort (array_sort, lines);
    FILE *out = fopen ("HAMLET_SORTED.txt", "w");
        if (out == NULL)
            return ERROR_FILE_INCORRECT;
    output_in_file (out, array_sort,   lines);
    output_in_file (out, array_nesort, lines);
    fclose (out);
*/
return 0;
}
