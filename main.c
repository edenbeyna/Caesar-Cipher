#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINES 1024
#define CIPHER_LENGTH  5
#define TEST_LENGTH  2
#define BASE  10
const char command1[] = "encode";
const char command2[] = "decode";
const char command3[] = "test";


//////////////////////////////////////////////////////


int is_valid_command_encode_decode(char command[]){
    // this func checks if the command given my the user
    // matches the valid commands encode or decode//
    int bool_val1 = strcmp(command, command1);
    int bool_val2 = strcmp(command, command2);
    if (bool_val1 == 0){
        return 1;
    }
    else if (bool_val2 == 0){
        return 2;
    }
    else{
        return 0;
    }
}

int is_valid_test_command(char command[]){
    // this func checks if the command given my the user matches the valid command test//
    int bool_val1 = strcmp(command, command3);
    if (bool_val1 ==0){
        return 1;
    }
    else{
        return 0;
    }
}

int is_k_valid(char k[]) {
    //this func checks if the shift value given by the user is an integer//
    int i;
    char first_char = *(k+0);
    if (first_char == '-'){
        for (i = 1; k[i] != '\0'; i++)
            if (!isdigit(k[i])) {
                return 0;
            } else {
                continue;
            }
        return 1;
    }
    for (i = 0; k[i] != '\0'; i++)
        if (!isdigit(k[i])) {
            return 0;
        } else {
            continue;
        }
    return 1;
}

int is_file_valid(char input[], char * mode){
    // this func checks if the files given by the user are valid//
    FILE *file;
    file = fopen(input, mode);
    if (file == NULL){
        return 0;
    }
    else
    {
        fclose(file);
        return 1;
    }

}
void something_is_invalid(int k_value, int given_command){
    //this func prints out error messages corresponding to the different errors//
    if (!given_command){
        fprintf(stderr, "The given command is invalid.\n");
    }
    else if(!k_value){
        fprintf(stderr, "The given shift value is invalid.\n");

    }
    else{
        fprintf(stderr, "The given file is invalid.\n");
    }

}
void encode_decode(char input[], char output[], int command_num, int key){
    //this func reads the text in the input file given by the user,
    // encodes/decodes it and prints out the result to an output file//
    FILE *output_file;
    FILE *input_file;
    input_file = fopen(input, "r");
    output_file = fopen(output, "w");
    char text[MAX_LINES];
    while (fgets(text, MAX_LINES, input_file))
    {
        if(command_num == 1){
            encode(text, key);
        }
        else{
            decode(text, key);
        }
        fprintf( output_file, "%s", text);
    }
    fclose(input_file);
    fclose(output_file);
}
int passed_tests(){
    // this func checks that all tests have passed//
    int res = 0;
    int t1 = test_decode_cyclic_lower_case_negative_k();
    int t2 = test_decode_cyclic_lower_case_special_char_positive_k();
    int t3 = test_decode_cyclic_upper_case_positive_k();
    int t4 = test_decode_non_cyclic_lower_case_positive_k();
    int t5 = test_decode_non_cyclic_lower_case_special_char_negative_k();
    int t6 = test_encode_cyclic_lower_case_negative_k();
    int t7 = test_encode_cyclic_lower_case_special_char_positive_k();
    int t8 = test_encode_cyclic_upper_case_positive_k();
    int t9 = test_encode_non_cyclic_lower_case_positive_k();
    int t10 = test_encode_non_cyclic_lower_case_special_char_negative_k();
    res = res + t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + t9 + t10;
    if (res){
        return EXIT_FAILURE;

    }
    else{
        return EXIT_SUCCESS;
    }

}

int main(int argc, char *argv[]) {
    char *command = argv[1];
    char *remaining;
    if (argc == CIPHER_LENGTH){
        char *k = argv[2];
        char *input_file = argv[3];
        char *output_file = argv[4];
        int valid_command = is_valid_command_encode_decode(command);
        int valid_k = is_k_valid(k);
        int valid_input = is_file_valid(input_file, "r");
        int valid_output = is_file_valid(output_file, "w");
        if(valid_command&&valid_k&&valid_input&&valid_output){
            long k_value = strtol(k, &remaining, BASE);
            encode_decode(input_file, output_file,
                          valid_command, k_value);
            return EXIT_SUCCESS;

        }
        else{
            something_is_invalid(valid_k, valid_command);
            return EXIT_FAILURE;

        }
    }
    else if(argc == TEST_LENGTH){
        int my_test = is_valid_test_command(command);
        if (!my_test){
            fprintf(stderr, "Usage: cipher test\n");
            return EXIT_FAILURE;
        }
        else{
            return passed_tests();
        }

    }
    else{
        fprintf(stderr, "The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;
    }



}