#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false,
    true
} bool;

typedef struct variables {
    float decimal_part;
    double stored_nmb;
    int integer_part;
    int final[32];
    int count_integer;
    int i;
    int j;
    int count;
    int bit_to_fill;
    int exponent_decimal_value;
    int binary_value;
    int temp_exponent[16];
    int temp_mantissa[32];
    bool first_one_into_mantissa;
    int mantissa_size;
    int precision;
} variables;


void insert_sign(variables *var_list, int number_sign) { var_list->final[0] = number_sign; }

void ask_for_number(variables *var_list) {
    double temp_double;
    temp_double = temp_double > 0 ? temp_double : temp_double * -1;
    printf("CONVERTER * Real number to floating point (IEEE 754 standard)\n");
    printf("Enter the number you want to convert:");
    scanf("%lf", &temp_double);
    int number_sign = temp_double > 0 ? 0 : 1;
    temp_double = temp_double > 0 ? temp_double : temp_double * -1;
    var_list->stored_nmb = temp_double;
    insert_sign(var_list, number_sign);
}

void store_integer_part(variables *var_list) {
    var_list->integer_part = var_list->stored_nmb;
}

void store_decimal_part(variables *var_list) {
    var_list->decimal_part = var_list->stored_nmb - var_list->integer_part;
}

void insert_mantissa(variables *var_list, int j, int count, int *temp_mantissa) {
    var_list->final[9 + j] = temp_mantissa[count];
    var_list->count_integer++;
}

void prepare_to_calculate_integer_mantissa(variables *var_list) {
    var_list->first_one_into_mantissa = false;
    var_list->j = 0;
    var_list->count_integer = 0;
    var_list->count = 0;
    var_list->mantissa_size = 23;
}

void convert_integer_part_into_binary(variables *var_list) {
    while (var_list->integer_part != 0) {

        var_list->binary_value = var_list->integer_part % 2;
        var_list->integer_part /= 2;
        var_list->temp_mantissa[var_list->count] = var_list->binary_value;
        var_list->count++;
    }
    var_list->count--;
}

void insert_integer_part_into_mantissa(variables *var_list) {
    while (var_list->count >= 0) {
        if (var_list->temp_mantissa[var_list->count] == 1 && var_list->first_one_into_mantissa == false) {
            var_list->first_one_into_mantissa = true;
            var_list->count--;
        } else {
            insert_mantissa(var_list, var_list->j, var_list->count, var_list->temp_mantissa);
            var_list->j++;
            var_list->count--;
        }
    }
}

void processing_integer_part_of_mantissa(variables *var_list) {
    prepare_to_calculate_integer_mantissa(var_list);
    convert_integer_part_into_binary(var_list);
    insert_integer_part_into_mantissa(var_list);

}


void prepare_to_calculate_exponent(variables *var_list) {
    var_list->j = 0;
    var_list->bit_to_fill = 8;
    var_list->count = 0;
    var_list->exponent_decimal_value = 127 + var_list->count_integer;
}

void convert_exponent_to_binary(variables *var_list) {
    while (var_list->exponent_decimal_value != 0) {
        var_list->binary_value = var_list->exponent_decimal_value % 2;
        var_list->exponent_decimal_value /= 2;
        var_list->temp_exponent[var_list->count] = var_list->binary_value;
        var_list->count++;
    }
    var_list->count--;
}

void insert_exponent(variables *var_list) {
    while (var_list->count >= 0) {
        var_list->final[1 + var_list->j] = var_list->temp_exponent[var_list->count];
        var_list->j++;
        var_list->count--;
        var_list->bit_to_fill--;
    }
    while (var_list->bit_to_fill > 0) {
        var_list->final[1 + var_list->j] = 0;
        var_list->bit_to_fill--;
        var_list->j++;
    }
}

void store_exponent(variables *var_list) {
    prepare_to_calculate_exponent(var_list);
    convert_exponent_to_binary(var_list);
    insert_exponent(var_list);
}


void prepare_to_convert_decimal_part(variables *var_list) {
    var_list->j = 0;
    var_list->precision = var_list->mantissa_size - var_list->count_integer;
    var_list->i = 9 + var_list->count_integer;
}

void convert_decimal_mantissa_to_binary(variables *var_list) {
    while (++var_list->j <= var_list->precision) {
        var_list->decimal_part = var_list->decimal_part * 2;
        var_list->binary_value = var_list->decimal_part;
        var_list->final[var_list->i] = var_list->binary_value;
        var_list->i++;
        if (var_list->binary_value == 1)
            var_list->decimal_part = var_list->decimal_part - var_list->binary_value;
    }
}

void process_decimal_part_of_mantissa(variables *var_list) {
    prepare_to_convert_decimal_part(var_list);
    convert_decimal_mantissa_to_binary(var_list);
}

variables *generate_variables_list() {
    variables *var_list = (variables *) malloc(1 * (sizeof(variables)));
    return var_list;
}

void extract_data_from_number(const variables *var_list) {
    store_integer_part(var_list);
    store_decimal_part(var_list);
}

void print_floating_point_number(variables *var_list) {
    int size = 32;
    int i = -1;
    printf("The real number %f has been converted to floating point\n", var_list->stored_nmb);
    while (++i < size) {
        putchar(var_list->final[i] + 48);
    }
    printf("\n[ 1 ] = sign, [ 2-8 ] = exponent, [ 9-32 ] = mantissa\n");
}

void convert_real_number_to_floating_point(const variables *var_list) {
    extract_data_from_number(var_list);
    processing_integer_part_of_mantissa(var_list);
    store_exponent(var_list);
    process_decimal_part_of_mantissa(var_list);
}

void main() {

    variables *var_list = generate_variables_list();
    ask_for_number(var_list);
    convert_real_number_to_floating_point(var_list);
    print_floating_point_number(var_list);
    free(var_list);
}
