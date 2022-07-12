/**************************************
# Author: Jesse Hassell
# Date: Sept, 2021
# Purpose: This file is a list of useful functions
# that are shared amongst the program.
**************************************/

#include "utilities.h"
namespace Utilities {
    std::string chunkInstruction(std::string instructions, char* element) {
        // Peel off first word and return them both
        sscanf(instructions.c_str(), "%s", element);
        return instructions.substr(instructions.find_first_of(" \t") + 1);
    }

    void toLower(char* input, int inputSize) {
        // Branchless method for converting a string to lowercase
        for (int i = 0; i < inputSize; i++) {
            input[i] += 32 * (input[i] >= 'A' && input[i] <= 'Z');
        }
    }

    void toUpperbl(char* str, int count) {
        // Branchless method for converting a string to lowercase
        for (int i = 0; i < count; i++) {
            str[i] -= 32 * (str[i] >= 'a' && str[i] <= 'z');
        }
    }

    int wordCount(char* input) {
        /*
        # Count the number of words in a string
        # This function was derived from the following URL:
        # https://www.tutorialspoint.com/count-words-in-a-given-string-in-cplusplus
        */
        int number_of_words = 0, sentinal = 0;
        while (*input) {
            if (*input == ' ' || *input == '\n' || *input == '\t') {
                sentinal = 0;
            } else if (sentinal == 0) {
                sentinal = 1;
                number_of_words++;
            }
            ++input;
        }
        return number_of_words;
    }

    void loadOptions(int inputSize, char* options[], std::map<std::string, int> &kvpairs) {
        // Load options into object mappings for quick lookups
        for (int i = 0; i < inputSize; i++) {
            kvpairs.insert(std::pair<std::string, int>(options[i], i));
        }
    }

    int invertTwosCompliment(unsigned int input) {
        int x = log2(input);
        int b = 1 << x;
        b = b | b - 1;
        input = input ^ b;
        return input;
    }

    unsigned int invertTwosCompliment(int input) {
        int x = log2(input);
        int b = 1 << x;
        b = b | b - 1;
        input = input ^ b;
        return input;
    }

    void print_binary(int nbytes, int number) {
        int b;
        for (int i = (nbytes-1); i >= 0; i--) {
            b = number >> i;
            printf("%d", (b&1) ? 1 : 0);
        }
        printf("\n");
    }
}
