#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#define N 5
#define M 5
void displayArray(char (*array)[M]){
    printf("\n\n    ");
    for (int i = 0; i < M; i++) {
        printf("%d", i+1);
        if(i != M-1){
            printf(" ");
        }
    }
    printf("\n");
    printf("    ");
    for(int i = 0; i < ((M*2)-1); i++){
        printf("-");
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("%d | ", i+1);
        for (int j = 0; j < M; j++) {
            printf("%c", array[i][j]);
            if(j != M-1){
                printf(" ");
            }
        }
        printf("\n");
    }
}
void fillArray(char (*array)[M]){
    printf("Введите значения для матрицы.\nБудут считаны только первые %d символов:\n", N*M);
    char maxsize[255];
    fgets(array,N*M+1, stdin);
    while ((getchar()) != '\n');
}
void take_coord(int type, int* value){
    if(type){
        printf("\tКоордината Y должна принадлежать отрезку [1,%d], введите новую координату: ", N);
    }else{
        printf("\tКоордината X должна принадлежать отрезку [1,%d], введите новую координату: ", M);
    }
    scanf("%d", value);
    while ((getchar()) != '\n');
}
int main() {
	setlocale(__LC_ALL, "russian");
    int coord_x = 0;
    int coord_y = 0;
    char array[N][M] = {0};
    fillArray(array);
    displayArray(array);
    printf("\nВведите координаты клетки, по которой нужно вычислить расстояния:\n");
    while((coord_x <= 0) || (coord_x > M)){
        take_coord(0,&coord_x);
    }
    while((coord_y <= 0) || (coord_y > N)){
        take_coord(1,&coord_y);
    }
    coord_x = coord_x-1;
    coord_y = coord_y-1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int check_x = abs(coord_x-j);
            int check_y = abs(coord_y-i);
            if(check_x > check_y){
                sprintf(&array[i][j], "%d", check_x);
            }else{
                sprintf(&array[i][j], "%d", check_y);
            }
        }
    }
    displayArray(array);
    return 0;
}