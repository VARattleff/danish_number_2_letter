#ifndef DANISH_NUMBER_H
#define DANISH_NUMBER_H

typedef enum {NEVER, EVERY, LAST} Occurrence;
typedef enum {NORMAL, FORMAL, CASUAL} Style;

typedef struct
{
    Occurrence og;
    int skip_one_thousand;
    Style style;
    int capitalize_first;
    int use_numeric_for_large;
    long long numeric_threshold;
} NumberFormat;

void dansketal(int num, char* buffer, NumberFormat format);
void set_default_format(NumberFormat* format);

#endif