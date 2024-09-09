#include <stdio.h>
#include <string.h>
#include "danish_number.h"

void convert_units(int num, char* buffer) 
{
    const char* ones[] = {"nul", "et", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
    strcpy(buffer, ones[num]);
}

void convert_tens(int num, char* buffer) 
{
    const char* ones[] = {"nul", "et", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"};
    const char* teens[] = {"ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten"};
    const char* tens[] = {"", "", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems"};
    
    if (num < 10) 
    {
        convert_units(num, buffer);
    } 
    else if (num < 20) 
    {
        strcpy(buffer, teens[num - 10]);
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
            sprintf(buffer, "%sog%s", ones[units_part], tens[tens_part]);
        }
    }
}

void convert_hundreds(int num, char* buffer) 
{
    const char* ones[] = {"nul", "et", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni"}; 
    if (num < 100) 
    {
        convert_tens(num, buffer);
    } else 
    {
        int hundreds_part = num / 100;
        int remainder = num % 100;
        char temp_buffer[256] = "";  

        if (hundreds_part == 1) 
        {
            strcpy(temp_buffer, "et hundrede");
        } else 
        {
            sprintf(temp_buffer, "%s hundrede", ones[hundreds_part]);
        }
        if (remainder == 0) 
        {
            strcpy(buffer, temp_buffer);
        } else 
        {    
            if (remainder < 10)
            {
                sprintf(buffer, "%s og ", temp_buffer);
            }
            else
            {
                sprintf(buffer, "%s ", temp_buffer);
            }
            convert_tens(remainder, buffer + strlen(buffer));
        }
    }
}

void convert_thousands(int num, char* buffer) 
{
    int thousands_part = num / 1000;
    int remainder = num % 1000;
    char temp_buffer[256] = "";  

    if (thousands_part == 1) 
    {
        strcpy(temp_buffer, "et tusind");
    } else 
    {
        convert_units(thousands_part, temp_buffer);
        strcat(temp_buffer, " tusind");
    }
    if (remainder == 0) 
    {
        strcpy(buffer, temp_buffer);
    } else 
    {
        strcat(buffer, temp_buffer);
        strcat(buffer, " ");
        convert_hundreds(remainder, buffer + strlen(buffer));
    }
}

void dansketal(int num, char* buffer, NumberFormat format) 
{    
    if (num < 0) 
    {
        strcpy(buffer, "minus ");
        num = -num;
    } else 
    {
        buffer[0] = '\0';  
    }

    if (num < 10) 
    {
        convert_units(num, buffer + strlen(buffer));
    } else if (num < 100) 
    {
        convert_tens(num, buffer + strlen(buffer));
    } else if (num < 1000) 
    {
        convert_hundreds(num, buffer + strlen(buffer));
    } else if (num < 10000) 
    {
        convert_thousands(num, buffer + strlen(buffer));
    }
    
    size_t len = strlen(buffer);

    if (len >= 4 && strcmp(buffer + len - 4, " og ") == 0) 
    {
        buffer[len - 4] = '\0';
    }
}