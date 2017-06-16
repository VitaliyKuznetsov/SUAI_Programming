#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 255

void getString(char* string){
    fgets(string, N, stdin);
}
void printString(char* print){
    fputs(print, stdout);
}
int main() {
    char string[N]; //Следовало бы использовать тип _Bool, однако для работы с fgets удобнее использовать char
    char *newstring = (char*)malloc(sizeof(string));
    char result_array[N*2+1];
    int result_array_counter = 0;
    char curr_symbol_count[3];
    int curr_symbol_reps = 1;
    getString(string);
    strcpy(newstring, string);
    int real_len = (int)strlen(newstring)-1;
    for(int i = 0; i < real_len; i++){
        while ((newstring[i] == newstring[i+1]) && (i+1 < real_len)){
            curr_symbol_reps++;
            i++;
        }

        sprintf(curr_symbol_count, "%d", curr_symbol_reps);
        for (int j = 0; j < strlen(curr_symbol_count); j++) {
            result_array[result_array_counter] = curr_symbol_count[j];
            result_array_counter++;
        }
        result_array[result_array_counter] = newstring[i];
        result_array_counter++;
        curr_symbol_reps = 1;
    }

    printString(result_array);
    return 0;
}