#include <stdio.h>
#include "danish_number.h"

int main()
{
    char buffer[1024];
    NumberFormat format;

    printf("Demonstration af dansketal-funktionen:\n\n");

    long long numbers[] = {0, 325, -997, 4395, 5589, 1100000, 999999999, 2000400060, -145602000};
    int num_tests = sizeof(numbers) / sizeof(numbers[0]);

    set_default_format(&format);
    printf("Standard format:\n");
    for (int i = 0; i < num_tests; i++) {
        dansketal(numbers[i], buffer, format);
        printf("%lld -> %s\n", numbers[i], buffer);
    }

    printf("\nFormel stil med stort begyndelsesbogstav:\n");
    format.style = FORMAL;
    format.capitalize_first = 1;
    dansketal(325, buffer, format);
    printf("325 -> %s\n", buffer);

    printf("\nUformel stil med 'og' overalt:\n");
    format.style = CASUAL;
    format.og = EVERY;
    format.capitalize_first = 0;
    dansketal(325, buffer, format);
    printf("325 -> %s\n", buffer);

    printf("\nBrug numerisk for store tal:\n");
    set_default_format(&format);
    format.use_numeric_for_large = 1;
    format.numeric_threshold = 1000000; 
    dansketal(2000400000, buffer, format);
    printf("2000400000 -> %s\n", buffer);

    return 0;
}