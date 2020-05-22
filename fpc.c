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
    double temp_double = -532.49;
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

    int count = 0;
    int test_integer = temp_integer_part;
    int test_binary_value;
    int arr_mant[128];
    while (test_integer != 0) {

        test_binary_value = test_integer % 2;
        test_integer /= 2;
        arr_mant[count] = test_binary_value;
        count++;
    }
    count--;
    while (count >= 0) {
        if (arr_mant[count] == 1) {
            if (first_one == 1) {
                first_one = 0;
                count--;
            } else {
                var_list->final[9 + j] = arr_mant[count];
                var_list->count_integer++;
                j++;
                count--;
            }
        } else {
            if (first_one == 0) {
                var_list->final[9 + j] = arr_mant[count];
                var_list->count_integer++;
                j++;
                count--;

            }
        }
    }

}

void store_exponent(variables *var_list) {
    printf("%d\n", var_list->count_integer);
    int exponent = 127 + var_list->count_integer;
    int binary_value;
    printf("%d\n", exponent);

    int j = 0;
    int bit_to_fill = 8;
    int count = 0;
    int test_integer = exponent;
    int test_binary_value;
    int arr_mant[20];
    while (test_integer != 0) {

        test_binary_value = test_integer % 2;
        test_integer /= 2;
        arr_mant[count] = test_binary_value;
        count++;
    }
    count--;
    while (count >= 0) {
        if (arr_mant[count] == 1) {

            var_list->final[1 + j] = arr_mant[count];
            j++;
            count--;
            bit_to_fill--;

        } else {

            var_list->final[1 + j] = arr_mant[count];
            j++;
            count--;
            bit_to_fill--;

        }
    }


    while (bit_to_fill > 0) {
        var_list->final[1 + j] = 0;
        bit_to_fill--;
        j++;
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
