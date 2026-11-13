#ifndef TYPES_H
#define TYPES_H

typedef enum{
    STRING,
    INT,
    FLOAT,
    VOID
} clic_type;

bool clic_to_int(const char *argv[], int argc, int *out);
bool clic_to_float(const char *argv[], int argc, float *out);

#endif