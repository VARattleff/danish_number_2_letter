#include <stdio.h>
#include "danish_number.h" 

int main() 
{
    char buffer[256];  

    NumberFormat format_standard = {LAST, 1};  

    printf("Demonstration af dansketal-funktionen:\n\n");

    int num1 = 125;
    dansketal(num1, buffer, format_standard);
    printf("%d -> %s\n", num1, buffer);

    int num2 = -999;
    dansketal(num2, buffer, format_standard);
    printf("%d -> %s\n", num2, buffer);

    int num3 = 4395;
    dansketal(num3, buffer, format_standard);
    printf("%d -> %s\n", num3, buffer);

    int num4 = 1001;
    dansketal(num4, buffer, format_standard);
    printf("%d -> %s\n", num4, buffer);

    return 0;
}