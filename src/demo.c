#include <stdio.h>
#include "danish_number.h"

void print_format_results(NumberFormat format, const char* format_name, int* numbers, int num_tests) 
{
    char buffer[255];
    printf("---------------------------\n");
    printf("%s:\n", format_name);
    for (int i = 0; i < num_tests; i++) 
    {
        dansketal(numbers[i], buffer, format);
        printf("%d -> %s\n", numbers[i], buffer);
    }
}

int main()
{
    int numbers_for_demo[] = {0, 1, -1, 21, 100, 101, 789, 1000, 1001, 1100, 45678, 123456, 1000001, 987654321, 2000000001, -1234567891};

    int num_tests = sizeof(numbers_for_demo) / sizeof(numbers_for_demo[0]);
    NumberFormat format;

    printf("Demonstration af dansketal-funktionen:\n\n");

    // Standard format
    set_default_format(&format);
    print_format_results(format, "Standard format", numbers_for_demo, num_tests);

    // Stil variationer
    format.style = CASUAL;
    print_format_results(format, "CASUAL format", numbers_for_demo, num_tests);

    format.style = FORMAL;
    print_format_results(format, "FORMAL format", numbers_for_demo, num_tests);

    // 'og' forekomst variationer
    format.style = NORMAL;
    format.og = NEVER;
    print_format_results(format, "'og' NEVER", numbers_for_demo, num_tests);

    format.og = EVERY;
    print_format_results(format, "'og' EVERY", numbers_for_demo, num_tests);

    // Andre booleanske indstillinger
    set_default_format(&format);
    format.skip_one_thousand = 0;
    print_format_results(format, "Ikke spring 'et' over i 'et tusind'", numbers_for_demo, num_tests);

    format.capitalize_first = 1;
    print_format_results(format, "Stort begyndelsesbogstav", numbers_for_demo, num_tests);

    format.use_numeric_for_large = 1;
    format.numeric_threshold = 1000000;
    print_format_results(format, "Brug numerisk for tal over 1 million", numbers_for_demo, num_tests);

    return 0;
}