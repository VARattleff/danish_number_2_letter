#ifndef DANISH_NUMBER_H
#define DANISH_NUMBER_H

typedef enum {NEVER, EVERY, LAST} Occurrence;


typedef struct 
{
    Occurrence og;  
    int skip_one_thousand;  
} NumberFormat;

void dansketal(int num, char* buffer, NumberFormat format);

#endif 