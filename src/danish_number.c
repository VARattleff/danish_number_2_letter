#include <stdio.h>
#include <string.h>
#include "danish_number.h"


void convert_units_and_teens(int num, char* buffer) 
{
    const char* ones_and_teens[] = {
        "nul", "et", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni", "ti", "elleve", "tolv", 
        "tretten", "fjorten", "femten", "seksten", 
        "sytten", "atten", "nitten"
    };
    strcpy(buffer, ones_and_teens[num]);
}

void convert_tens(int num, char* buffer) 
{
    const char* ones[] = {
        "nul", "et", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni"
    };
    
    const char* tens[] = {
        "", "", "tyve", "tredive", "fyrre", "halvtreds", 
        "tres", "halvfjerds", "firs", "halvfems"
    };
    
    if (num < 20) 
    {
        convert_units_and_teens(num, buffer);
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
    const char* ones[] = {
        "nul", "et", "to", "tre", "fire", "fem", "seks", 
        "syv", "otte", "ni"
    }; 
    
    if (num < 100) 
    {
        convert_tens(num, buffer);
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
            strcat(temp_buffer, remainder < 10 ? " og " : " ");
            strcpy(buffer, temp_buffer);
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
    } 
    else 
    {
        convert_units_and_teens(thousands_part, temp_buffer);
        strcat(temp_buffer, " tusind");
    }
    
    if (remainder == 0) 
    {
        strcpy(buffer, temp_buffer);
    } 
    else 
    {
        strcat(buffer, temp_buffer);
        strcat(buffer, " ");
        convert_hundreds(remainder, buffer + strlen(buffer));
    }
}

void convert_millions(int num, char* buffer) 
{
    if (num < 1000000) 
    {
        convert_thousands(num, buffer);
    } 
    else 
    {
        int millions_part = num / 1000000;
        int remainder = num % 1000000;
        
        if (millions_part == 1) 
        {
            strcpy(buffer, "en million");
        } 
        else 
        {
            convert_units_and_teens(millions_part, buffer);
            strcat(buffer, " millioner");
        }
        
        if (remainder != 0) 
        {
            strcat(buffer, " ");
            convert_thousands(remainder, buffer + strlen(buffer));
        }
    }
}

void convert_billions(int num, char* buffer) 
{
    if (num < 1000000000) 
    {
        convert_millions(num, buffer);
    } 
    else 
    {
        int billions_part = num / 1000000000;
        int remainder = num % 1000000000;
        
        if (billions_part == 1) 
        {
            strcpy(buffer, "en milliard");
        } 
        else 
        {
            convert_units_and_teens(billions_part, buffer);
            strcat(buffer, " milliarder");
        }
        
        if (remainder != 0) 
        {
            strcat(buffer, " ");
            convert_millions(remainder, buffer + strlen(buffer));
        }
    }
}

void dansketal(int num, char* buffer, NumberFormat format) 
{
    if (num < 0) 
    {
        strcpy(buffer, "minus ");
        num = -num;
    } 
    else 
    {
        buffer[0] = '\0';
    }

    if (num < 20) 
    {
        convert_units_and_teens(num, buffer + strlen(buffer));
    } 
    else if (num < 100) 
    {
        convert_tens(num, buffer + strlen(buffer));
    } 
    else if (num < 1000) 
    {
        convert_hundreds(num, buffer + strlen(buffer));
    } 
    else if (num < 1000000) 
    {
        convert_thousands(num, buffer + strlen(buffer));
    } 
    else if (num < 1000000000) 
    {
        convert_millions(num, buffer + strlen(buffer));
    } 
    else 
    {
        convert_billions(num, buffer + strlen(buffer));
    }
}