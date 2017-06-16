#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define N 255

void getString(char* string){
    fgets(string, N, stdin); //Использована fgets(), т.к gets() устарела
    for (int i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]); //Преобразование всех символов к нижнему регистру
    }
}
void printString(int result){
    printf("Количество слов, начинающихся и заканчивающихся на одну и ту же букву:\n%d", result);
}

int main() {
    char string[N];
    int word_start = 0;
    int word_end = 0;
    int result_count = 0;
    setlocale(__LC_ALL, "russian"); //Поддержка кириллицы

    getString(string); //Получаем строку

    word_end = (int)strlen(string)-2; //Страховка, если строка из 1 слова

    //Выполненение действий
    for (int i = 0; i < strlen(string); i++) {
        char curr_char = string[i];
        if((curr_char == ' ') | (curr_char == '\n')){
            word_end = i-1;
            if(string[word_end] == string[word_start]){
                result_count++;
            }
            word_start = i+1;
        }

    }

    printString(result_count); //Выводим количество слов
}
