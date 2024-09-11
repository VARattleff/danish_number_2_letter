#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "danish_number.h"

void set_default_format(NumberFormat* format)
{
    format->og = LAST;
    format->skip_one_thousand = 1;
    format->style = NORMAL;
    format->capitalize_first = 0;
    format->use_numeric_for_large = 0;
    format->numeric_threshold = 1000000000; 
}

void convert_units_and_teens(int num, char* buffer, Style style) 
{
    const char* ones_and_teens_normal[] = 
    {
        "nul", "en", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni", "ti", "elleve", "tolv", 
        "tretten", "fjorten", "femten", "seksten", 
        "sytten", "atten", "nitten"
    };

    const char* ones_and_teens_formal[] = 
    {
        "nul", "én", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni", "ti", "elleve", "tolv", 
        "tretten", "fjorten", "femten", "seksten", 
        "sytten", "atten", "nitten"
    };
    
    const char* ones_and_teens_casual[] = 
    {
        "nul", "en", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni", "ti", "elle", "tol", 
        "tretten", "fjorten", "femten", "seksten", 
        "sytten", "atten", "nitten"
    };

    const char** ones_and_teens;

    switch(style) 
    {
        case FORMAL: ones_and_teens = ones_and_teens_formal; break;
        case CASUAL: ones_and_teens = ones_and_teens_casual; break;
        default: ones_and_teens = ones_and_teens_normal;
    }

    strcpy(buffer, ones_and_teens[num]);
}

void convert_tens(int num, char* buffer, NumberFormat format) 
{
    const char* ones[] = 
    {
        "nul", "en", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni"
    };
    
    const char* tens[] = 
    {
        "", "", "tyve", "tredive", "fyrre", "halvtreds", 
        "tres", "halvfjerds", "firs", "halvfems"
    };
    
    if (num < 20) 
    {
        convert_units_and_teens(num, buffer, format.style);
    } 
    else 
    {
        int tens_part = num / 10;
        int units_part = num % 10;
        
        if (units_part == 0) 
        {
            strcpy(buffer, tens[tens_part]);
        } 
        else 
        {
            if (format.og == EVERY || (format.og == LAST && tens_part == 2))
            {
                sprintf(buffer, "%sog%s", ones[units_part], tens[tens_part]);
            }
            else
            {
                sprintf(buffer, "%s%s", ones[units_part], tens[tens_part]);
            }
        }
    }
}

void convert_hundreds(int num, char* buffer, NumberFormat format) 
{
    const char* ones[] = 
    {
        "nul", "et", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni"
    }; 
    
    if (num < 100) 
    {
        convert_tens(num, buffer, format);
    } 
    else 
    {
        int hundreds_part = num / 100;
        int remainder = num % 100;
        char temp_buffer[256] = "";  

        if (hundreds_part == 1) 
        {
            strcpy(temp_buffer, "et hundrede");
        } 
        else 
        {
            sprintf(temp_buffer, "%s hundrede", ones[hundreds_part]);
        }
        
        if (remainder == 0) 
        {
            strcpy(buffer, temp_buffer);
        } 
        else 
        {
            if (format.og == EVERY || (format.og == LAST && remainder < 10))
            {
                strcat(temp_buffer, " og ");
            }
            else
            {
                strcat(temp_buffer, " ");
            }
            strcpy(buffer, temp_buffer);
            convert_tens(remainder, buffer + strlen(buffer), format);
        }
    }
}

void convert_thousands(int num, char* buffer, NumberFormat format) 
{
    if (num < 1000) 
    {
        convert_hundreds(num, buffer, format);
        return;
    }

    int thousands_part = num / 1000;
    int remainder = num % 1000;
    char temp_buffer[256] = "";  

    if (thousands_part == 1) 
    {
        strcpy(temp_buffer, format.skip_one_thousand ? "tusind" : "et tusind");
    } 
    else 
    {
        convert_hundreds(thousands_part, temp_buffer, format);
        strcat(temp_buffer, " tusind");
    }
    
    if (remainder == 0) 
    {
        strcpy(buffer, temp_buffer);
    } 
    else 
    {
        strcpy(buffer, temp_buffer); 
        if (remainder < 100 && (format.og == EVERY || format.og == LAST))
        {
            strcat(buffer, " og ");
        }
        else
        {
            strcat(buffer, " ");
        }
        convert_hundreds(remainder, buffer + strlen(buffer), format);
    }
}

void convert_millions(int num, char* buffer, NumberFormat format) 
{
    if (num < 1000000) 
    {
        convert_thousands(num, buffer, format);
        return;
    }

    int millions_part = num / 1000000;
    int remainder = num % 1000000;
    char temp_buffer[256] = "";
    char remainder_buffer[256] = "";
    
    if (millions_part == 1) 
    {
        strcpy(temp_buffer, "en million");
    } 
    else 
    {
        convert_hundreds(millions_part, temp_buffer, format);
        strcat(temp_buffer, " millioner");
    }
    
    if (remainder != 0) 
    {
        convert_thousands(remainder, remainder_buffer, format);
        if (strlen(remainder_buffer) > 0) {
            strcat(temp_buffer, " ");
            strcat(temp_buffer, remainder_buffer);
        }
    }
    
    strcpy(buffer, temp_buffer);
}

void convert_billions(int num, char* buffer, NumberFormat format) 
{
    if (num < 1000000000) 
    {
        convert_millions(num, buffer, format);
        return;
    }

    int billions_part = num / 1000000000;
    int remainder = num % 1000000000;
    char temp_buffer[256] = "";

    if (billions_part == 1) 
    {
        strcpy(temp_buffer, "en milliard");
    } 
    else if (billions_part < 1000) 
    {
        convert_hundreds(billions_part, temp_buffer, format);
        strcat(temp_buffer, " milliarder");
    }
    else 
    {
        convert_billions(billions_part, temp_buffer, format);
        strcat(temp_buffer, " milliarder");
    }

    strcpy(buffer, temp_buffer);  

    if (remainder != 0) 
    {
        strcat(buffer, " ");
        convert_millions(remainder, buffer + strlen(buffer), format);
    }
}

void dansketal(int num, char* buffer, NumberFormat format) 
{
    if (num == 0) 
    {
        strcpy(buffer, "nul");
        return;
    }

    if (format.use_numeric_for_large && (num >= format.numeric_threshold || num <= -format.numeric_threshold))
    {
        sprintf(buffer, "%d", num);
        return;
    }

    if (num < 0) 
    {
        strcpy(buffer, "minus ");
        num = -num;
    } 
    else 
    {
        buffer[0] = '\0';
    }

    convert_billions(num, buffer + strlen(buffer), format);

    if (format.capitalize_first && strlen(buffer) > 0)
    {
        buffer[0] = toupper(buffer[0]);
    }
}