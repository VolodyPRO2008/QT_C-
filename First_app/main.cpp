#include <stdio.h>  // подключение процедур ввода вывода
#include "Nod.h"
int main()
{
    int a,b;

    puts("Enter two integer value:");
    scanf("%d %d",&a,&b);
    printf("Nod %d и %d = %d.\n",a,b,nod(a,b));
    return 0;
}
