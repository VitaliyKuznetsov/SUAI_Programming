#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_MONTHS 60

typedef struct
{
    char name[30];
    int salary[MAX_MONTHS];
    int sumSalary;
    int averageSalary;
} TPerson;

void sort(TPerson *persons,int personCount)
{ int i=0,j=0,tmp=0;
    for (i = 0; i < personCount; i++)
        for (j = i + 1; j < personCount; j++)
        {
            if (persons[i].sumSalary < persons[j].sumSalary)
            {
                tmp = persons[i].sumSalary;
                persons[i].sumSalary = persons[j].sumSalary;
                persons[j].sumSalary = tmp;
            }
        }
}

void median(TPerson *persons,int personCount)
{   int sr,imedian;
    sr=(personCount/2);
    imedian=persons[sr].sumSalary;
    printf("\nMedian is: %d\n\n",imedian);
}

void decil(TPerson *persons,int personCount)
{   int i,tenPercent,topTen,topDecil=0,lowDecil=0,decilCoef;
    tenPercent=(personCount*0.1);
    topTen=(personCount-tenPercent);
    for (i=0;i<tenPercent;i++)
    {
        topDecil+=persons[i].sumSalary;
    }
    for (i=topTen;i<personCount;i++)
    {
        lowDecil+=persons[i].sumSalary;
    }
    decilCoef=topDecil/lowDecil;
    printf("Decil coefficient is: %d\n\n",decilCoef);
}

void giniCoef(TPerson *persons,int personCount,int commonSalary) {
    int i,topTen,halfcommonSalary,l=0,k=0,j=0;
    int high,mid,low;
    int gini1,gini2,gini3,KJ;
    int L,J,K;
    for (i = 0; i < personCount; i++)
    {

        topTen=(persons[0].sumSalary)*0.1; /// общий доход
        halfcommonSalary = commonSalary/2; /// сумма пополам


        for (i = 0; i < personCount; i++)
        {
            if (persons[i].sumSalary < topTen) {
                j++;
            }
            if (persons[i].sumSalary > topTen && persons[i].sumSalary < halfcommonSalary)
            {
                k++;
            }
            if (persons[i].sumSalary > halfcommonSalary) {
                l++;
            }

        }
    }
    printf("Max = %d\n",l);
    printf("Medium = %d\n", k);
    printf("Min = %d\n", j);
    L=0,K=0,J=0;
    for (i = 0; i < j; i++) {
        L += persons[i].sumSalary;
    }
    for (i = 0; i < k; i++) {
        K += persons[i+j].sumSalary;
    }
    for (i = 0; i < l; i++) {
        J += persons[i+k+j].sumSalary;
    }

    gini1 = L;
    gini2 = K;
    gini3 = J;
    gini1 =gini1 / commonSalary;
    gini2 = gini2 / commonSalary;
    gini3 =gini3 / commonSalary;
    high =j /personCount;
    mid = k /personCount;
    low = l / personCount;
    KJ = 1-2 * (gini1*high + (gini1+gini2)*mid + low) + (gini1*high + gini2*mid + gini3*low);

    printf("Koefficient Jini = %f\n\n", KJ);

}

void histogram(TPerson *persons,int personCount)
{
    int i,k,n;
    for (i = 0; i<personCount; i++)
    {   printf("%s ", persons[i].name);
        printf("\t\t%d ",persons[i].averageSalary);
        k=persons[i].averageSalary/100;
        printf("\t");
        for (n = 0; n < k; n++)
        {
            printf("$");
        }
        printf("\n");
    }
}

//returns month count from Jan 1980

int get_month(char *date)
{
    char *month, *year;
    int iMonth,iYear;

    month=strchr(date, '.');
    sscanf(month+1,"%d", &iMonth);

    year=strchr(month+1, '.');
    sscanf(year+1, "%d", &iYear);
    return (iYear-1980)*12+iMonth;
}

void main (void)
{
    FILE *F;
    TPerson *persons = NULL;
    char s[200];
    char name[30], date[20];
    int salary;
    int tmp;
    int sr;
    int commonSalary=0,halfcommonSalary,gini1,gini2,gini3,L,J,K,high,mid,low,KJ,l=0,k=0,j=0;
    char *semicolon1, *semicolon2;
    int personCount=0;
    int i;
    int max = 0;
    int personFound;
    int maxMonth=0, minMonth=99999;
    int month;


    F=fopen("salary.csv","rt");

    //get range

    while (!feof(F))
    {
        //read string from file
        fgets(s,200,F);


        semicolon1=strchr(s,';');
        semicolon2=strchr(semicolon1+1, ';');
        strncpy(date,semicolon1+1,semicolon2-semicolon1);
        date[semicolon2-semicolon1]=0;

        month = get_month(date);
        if (month>maxMonth)
            maxMonth=month;
        if (month<minMonth)
            minMonth=month;
    }

    fseek(F,0,SEEK_SET);

    //reading names and salaries
    while(!feof(F))
    {
        //read string from file
        fgets(s,200,F);

        semicolon1=strchr(s,';');
        strncpy(name,s,semicolon1-s);
        name[semicolon1-s]=0;

        semicolon2=strchr(semicolon1+1,';');
        strncpy(date,semicolon1+1,semicolon2-semicolon1);
        date[semicolon2-semicolon1]=0;

        sscanf(semicolon2+1,"%d",&salary);

        //search for person in array
        personFound=0;
        for (i=0;i<personCount;i++)
            if (strcmp(name,persons[i].name)==0)
            {
                persons[i].salary[get_month(date)-minMonth] += salary;
                /// sum of salary
                persons[i].sumSalary  += salary;
                personFound=1;
                break;
            }
        //if person not found
        if(!personFound)
        {
            //add person to array
            persons=(TPerson*)realloc(persons,(personCount+1)*sizeof(TPerson));
            memset(persons[personCount].salary,0,sizeof(persons[personCount].salary));
            persons[personCount].sumSalary=0;
            persons[personCount].averageSalary=0;
            persons[personCount].salary[get_month(date)-minMonth]=salary;
            strcpy(persons[personCount].name,name);
            personCount++;
        }
    }

    ///averageSalary + commonSalary
    for (i=0;i<personCount;i++)
    {   persons[i].averageSalary=(persons[i].sumSalary/MAX_MONTHS);
        commonSalary+=persons[i].sumSalary;
    }
    sort(persons,personCount);
    median(persons,personCount);
    decil(persons,personCount);
    giniCoef(persons,personCount,commonSalary);
    histogram(persons,personCount);
    fclose(F);
    getchar();
}