#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;

typedef struct variables
{
    float decimal_part;
    double stored_nmb;
    int integer_part;
    int temp_integer_part;
    int buffer[30];
    int index;
    int count;
    int final[32];
    int count_integer;
    int count_decimal;
    int nmb_sign;
    int printMantissaInteger;
} variables;

void ask_for_number(variables *var_list)
{
    double temp_double = 45.45;
    //printf("Enter any number:");
    //scanf("%lf", &temp_double);
    var_list->stored_nmb = temp_double;
    if (temp_double > 0)
    {
        printf("Sign: 0");
        var_list->final[0] = 0;
    }
    else
    {
        printf("Sign: 1");
        var_list->final[0] = 1;
    }
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
    var_list->count_integer = 0;
    while (var_list->integer_part != 0)
    {

        binary_value = var_list->integer_part % 2;
        var_list->integer_part /= 2;
        var_list->final[9 + i] = binary_value;
        var_list->count_integer++;
        i++;
    }
    var_list->index = i;
}

void convert_integer_to_binary_for_mantissa(variables *var_list)
{
    if (var_list->printMantissaInteger == 0)
        printf(" Mantissa integer part: ");
    int first_one = 1;
    int i = 0;
    int l = 0;
    int binary_value = 0;
    int temp_integer_part = var_list->integer_part;
    var_list->count_integer = 0;
    while (temp_integer_part != 0)
    {

        binary_value = temp_integer_part % 2;
        temp_integer_part /= 2;
        if (binary_value == 1)
        {
            if (first_one == 1)
                first_one = 0;
            else
            {
                var_list->final[9 + l] = binary_value;
                var_list->count_integer++;
                l++;
                if (var_list->printMantissaInteger == 0)
                    printf("%d", binary_value);
            }
        }
        else
        {
            if (first_one == 0)
            {
                var_list->final[9 + l] = binary_value;
                var_list->count_integer++;
                l++;
                if (var_list->printMantissaInteger == 0)
                    printf("%d", binary_value);
            }
        }

        i++;
    }
    var_list->index = l;
}

void store_exponent(variables *var_list)
{
    printf(" Exponent: ");

    int exponent = 127 + var_list->count_integer;
    int i = 0;
    int binary_value;

    int first_one = 1;
    int l = 0;
    int bit_to_fill = 8;
    while (exponent != 0)
    {

        binary_value = exponent % 2;
        exponent /= 2;
        if (binary_value == 1)
        {
            if (first_one == 1)
            {
                first_one = 0;
                var_list->final[1 + l] = binary_value;
                l++;
                printf("%d", binary_value);
                bit_to_fill--;
            }

            else
            {
                var_list->final[1 + l] = binary_value;

                l++;
                printf("%d", binary_value);
                bit_to_fill--;
            }
        }
        else
        {
            if (first_one == 0)
            {
                var_list->final[1 + l] = binary_value;

                l++;
                printf("%d", binary_value);
                bit_to_fill--;
            }
        }
    }

    while (bit_to_fill > 0)
    {
        var_list->final[1 + l] = 0;
        bit_to_fill--;
        printf("%d", 0);
    }
    var_list->printMantissaInteger = 0;
}

void convert_decimal_to_binary(variables *var_list)
{
    int j;
    int precision = 24 - var_list->count_integer;
    int i = 9 + var_list->count_integer;
    int temp;

    printf(" Mantissa decimal part: ");
    for (j = 1; j <= precision; j++)
    {
        var_list->decimal_part = var_list->decimal_part * 2;

        temp = var_list->decimal_part;
        var_list->final[i] = temp;
        i++;
        if (temp == 1)
            var_list->decimal_part = var_list->decimal_part - temp;
        printf("%d", temp);
    }
    printf("\n");
}

void main()
{

    variables *var_list = (variables *)malloc(1 * (sizeof(variables)));
    var_list->printMantissaInteger = 1;
    ask_for_number(var_list);
    store_integer_part(var_list);
    store_decimal_part(var_list);
    convert_integer_to_binary_for_mantissa(var_list);
    store_exponent(var_list);
    convert_integer_to_binary_for_mantissa(var_list);
    convert_decimal_to_binary(var_list);
}
