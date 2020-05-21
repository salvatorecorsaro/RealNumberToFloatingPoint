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
} variables;


void ask_for_number(variables *var_list) {
    double temp_double = 1245.4567;
    int number_sign = temp_double > 0 ? 0 : 1;
    temp_double = temp_double > 0 ? temp_double : temp_double * -1;
    //printf("Enter any number:");
    //scanf("%lf", &temp_double);
    var_list->stored_nmb = temp_double;
    var_list->final[0] = number_sign;
}

void store_integer_part(variables *var_list) {
    var_list->integer_part = var_list->stored_nmb;
}

void store_decimal_part(variables *var_list) {
    var_list->decimal_part = var_list->stored_nmb - var_list->integer_part;
}




void convert_integer_to_binary_for_mantissa(variables *var_list) {
    int first_one = 1;
    int i, j = 0;
    int binary_value;
    int temp_integer_part = var_list->integer_part;
    var_list->count_integer = 0;


    while (temp_integer_part != 0) {

        binary_value = temp_integer_part % 2;
        temp_integer_part /= 2;
        if (binary_value == 1) {
            if (first_one == 1)
                first_one = 0;
            else {
                var_list->final[9 + j] = binary_value;
                var_list->count_integer++;

                j++;
            }
        } else {
            if (first_one == 0) {
                var_list->final[9 + j] = binary_value;
                var_list->count_integer++;
                j++;

            }
        }

        i++;
    }
}

void store_exponent(variables *var_list) {
    printf("%d\n", var_list->count_integer);
    int exponent = 127 + var_list->count_integer;
    int binary_value;

    int first_one = 1;
    int l = 0;
    int bit_to_fill = 8;
    while (exponent != 0) {

        binary_value = exponent % 2;
        exponent /= 2;
        if (binary_value == 1) {
            if (first_one == 1) {
                first_one = 0;
                var_list->final[1 + l] = binary_value;
                l++;
                bit_to_fill--;
            } else {
                var_list->final[1 + l] = binary_value;
                l++;
                bit_to_fill--;
            }
        } else {
            if (first_one == 0) {
                var_list->final[1 + l] = binary_value;

                l++;
                bit_to_fill--;
            }
        }
    }

    while (bit_to_fill > 0) {
        var_list->final[1 + l] = 0;
        bit_to_fill--;
        l++;
    }
}

void convert_decimal_to_binary(variables *var_list) {
    int j;
    int precision = 23 - var_list->count_integer;
    int i = 9 + var_list->count_integer;
    int temp;

    for (j = 1; j <= precision; j++) {
        var_list->decimal_part = var_list->decimal_part * 2;

        temp = var_list->decimal_part;
        var_list->final[i] = temp;
        i++;
        if (temp == 1)
            var_list->decimal_part = var_list->decimal_part - temp;
    }
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
    while (++i < size) {
        putchar(var_list->final[i] + 48);
    }
}

void main() {

    variables *var_list = generate_variables_list();
    ask_for_number(var_list);
    extract_data_from_number(var_list);
    convert_integer_to_binary_for_mantissa(var_list);
    store_exponent(var_list);
    convert_decimal_to_binary(var_list);
    print_floating_point_number(var_list);
    free(var_list);
}

/* need to check the binary converter it seems there is an error in the binary result.
 * need to invert the result number;
 */
