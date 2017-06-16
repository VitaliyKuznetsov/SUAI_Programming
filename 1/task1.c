#include <stdio.h>
#include <locale.h>
int main(void) {
    setlocale(__LC_ALL, "russian");

    int N, count;
    count = 1;//Т.к число является делителем самого себя

    printf("Введите N\n");
    scanf("%i",&N);


    for (int i = 1; i <= (  N/2)+1; i++) {
        if(!(N%i)){
            count++;
        }
    }
    printf("Количество делителей: %d\n", count);
    return 0;
}