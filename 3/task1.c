#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
#define M 3
#define FULLPATH "/home/vitaliy/Dropbox/studing/prog/C/3/1/"

void readFile(char (*result)[M]){
    FILE * f;
    char line[M];
    int string_counter = 0;
    char input_file[255];
    strcpy(input_file,FULLPATH);
    strcat(input_file,(char*)"input.txt");
    f = fopen(input_file, "r");
    while ((fscanf(f, "%s", line))!=EOF){
        for (int i = 0; i < M; i++) {
            result[string_counter][i] = line[i];
        }
        string_counter++;
    }
}

int compare(const void* a, const void* b)
{
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );

    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}

void sortArray(char (*array)[M]){
    int temp_counter = 0;
    int temp_array[N*M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char val = array[i][j];
            temp_array[temp_counter] = atoi(&val);
            temp_counter++;
        }
    }
    temp_counter = 0;
    qsort(temp_array,N*M, sizeof(int), compare);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char val[1];
            sprintf(val, "%d", temp_array[temp_counter]);
            array[i][j] = val[0];
            temp_counter++;
        }
    }
}

void writeFile(char (*array)[M]){
    FILE * f;
    char output_file[255];
    strcpy(output_file,FULLPATH);
    strcat(output_file,(char*)"output.txt");
    f = fopen(output_file, "w+");
    for (int i = 0; i < N; i++) {
        if(((i+1)%2)){
            for (int j = 0; j < M; j++) {
                fprintf(f, "%c", array[i][j]);
            }
        }else{
            for (int j = M-1; j >= 0; j--) {
                fprintf(f, "%c", array[i][j]);
            }
        }
        fprintf(f, "\n");
    }
}

int main() {
    char file[N][M];
    readFile(file);
    sortArray(file);
    writeFile(file);
    return 0;
}