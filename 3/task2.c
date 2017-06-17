#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FULLPATH "/home/vitaliy/Dropbox/studing/prog/C/3/2/"
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

int getFilesize(char* filepath){
    FILE * file;
    int filesize = 0;
    char c;
    file = fopen(filepath, "r");
    while ((c = getc(file)) != EOF){
        filesize++;
    }
    fclose(file);
    return filesize;
}
void readFile(char* filepath , int filesize, char* result){
    FILE * file;
    file = fopen(filepath, "r");
    int char_pos = 0;
    fread(result, sizeof(char), filesize, file);
}
int countLines(char* result){
    int count = 1;
    for (int i = 0; i < strlen(result); i++) {
        if(result[i] == '\n'){
            count++;
        }
    }
    return count;
}
int getLineLenght(char *str){
    int linelen = 0;
    char c;
    for (int i = 0; i < strlen(str); i++) {
        if(str[i] == '\n'){
            break;
        }else{
            linelen++;
        }
    }
    return linelen;
}
int compare(const void* a, const void* b)
{
    char a_char = ((char*)a)[0];
    char b_char = ((char*)b)[0];
    int a_val = (a_char - '0');
    int b_val = (b_char - '0');
    if ( a_val == b_val ) return 0;
    else if ( a_val < b_val ) return 1;
    else return -1;
}
int main() {
    char* result = malloc(5);
    int filesize = 0;
    char input_file[1024];
    char output_file[1024];
    strcpy(input_file,FULLPATH);
    strcat(input_file,INPUT_FILE);
    strcpy(output_file,FULLPATH);
    strcat(output_file,OUTPUT_FILE);
    filesize = getFilesize(input_file);
    result = (char *)realloc(result, filesize*sizeof(char));
    readFile(input_file, filesize, result);
    int lines_count = countLines(result);
    int linelen = getLineLenght(result);
    int line_counter = 0;
    int inline_counter = 0;
    char lined_result[lines_count][linelen];
    for (int i = 0; i < strlen(result); i++) {
        if(result[i] != '\n'){
            lined_result[line_counter][inline_counter] = result[i];
            inline_counter++;
        }else{
            inline_counter = 0;
            line_counter++;
        }
    }
    qsort(lined_result,lines_count,sizeof(char)*linelen,compare);

    FILE * file;
    char c;
    file = fopen(output_file, "w+");

    for (int j = 0; j < lines_count; j++) {
        for (int i = 0; i < linelen; i++) {
            fprintf(file, "%c", lined_result[j][i]);
        }
        fprintf(file, "\n");
    }
    return 0;
}