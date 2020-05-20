#include <stdio.h>
#include <stdlib.h>

typedef struct variables
{
    float decimal_part;
    double stored_nmb;
    int integer_part;
    int buffer[20];
    int index;
    int count;
} variables;

void ask_for_number(variables *var_list)
{
    double temp_double;
    printf("Enter any number:");
    scanf("%lf", &temp_double);
    var_list->stored_nmb = temp_double;
}

void store_integer_part(variables *var_list)
{
    var_list->integer_part = var_list->stored_nmb;
}

void store_decimal_part(variables *var_list)
{
    var_list->decimal_part = var_list->stored_nmb - var_list->integer_part;
}

void convert_integer_to_binary(variables *var_list)
{
    int i = 0;
    int binary_value = 0;
    while (var_list->integer_part != 0)
    {

        binary_value = var_list->integer_part % 2;
        var_list->integer_part /= 2;
        var_list->buffer[i] = binary_value;
        var_list->count += 1;
        i++;
    }
    var_list->index = i;
}

void print_from_binary(variables *var_list)
{
    int i = 0;
    for (i = var_list->count - 1; i >= 0; i--)
    {
        printf("%d", var_list->buffer[i]);
    }
}

void convert_decimal_to_binary(variables *var_list)
{
    int precision;
    int i = var_list->index;
    int temp;

    for (precision = 1; precision <= 8; precision++)
    {
        var_list->decimal_part = var_list->decimal_part * 2;

        temp = var_list->decimal_part;
        printf("%d", temp);
        var_list->buffer[i] = temp;
        i++;
        if (temp == 1)
            var_list->decimal_part = var_list->decimal_part - temp;
    }
}

void main()
{

    variables *var_list = (variables *)malloc(1 * (sizeof(variables)));
    ask_for_number(var_list);
    store_integer_part(var_list);
    store_decimal_part(var_list);
    convert_integer_to_binary(var_list);
    print_from_binary(var_list);
    printf(".");
    var_list->buffer[var_list->index++] = '.';
    convert_decimal_to_binary(var_list);
}