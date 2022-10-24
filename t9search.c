#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool check_for_match(char *str, char arg[]);
bool check_for_sequence(char *str,int start_point1,char *arg, int startpoint2);
bool compare_chars(char a, char b);
bool string_compare(char *str1, char *str2);

int string_length(char *str);
bool check_for_correct_input(char *name, char *number, int MAX_CHAR);
bool is_digits_valid(char *num);
bool is_in_range(char *str, int MAX_CHAR);

int main(int argc, char **argv)
{

    if (argc == 3){
        // argument in console must be in digit
        if((is_digits_valid(argv[2]) == false) || (string_compare(argv[1], "-s") == false)){
            fprintf(stderr,"Invalid arguments input\n");
            return 1;
        }
        // max symbols that a string can have
        const int MAX_CHAR = 100;
        // maximum symbols for fgets function (with \n) + 1 so that we knew it out of length
        const int ENTRY_MAX = MAX_CHAR + 2;

        bool found_match = false;
        //the contact
        char name[MAX_CHAR], number[MAX_CHAR];
        // getting first two strings - one names another phone number
        while (fgets(name, ENTRY_MAX, stdin) != NULL)
        {
            fgets(number, ENTRY_MAX, stdin);

            // checks for correct input
            if(!(check_for_correct_input(name, number, MAX_CHAR))){
                return 1;
            }

            else {
                //replace \n in the name string with \0
                name[string_length(name) - 1] = '\0';
                number[string_length(number) - 1] = '\0';
                //check for match
                if(check_for_sequence(number, 0, argv[2], 0) || check_for_sequence(name, 0, argv[2], 0)){
                    printf("%s, %s\n", name, number);
                    found_match = true;
                }
            }
        }
        if(found_match == false){
            printf("Not found");
        }
        return 0;
    }
    if (argc == 2){
        // argument in console must be in digit
        if(!(is_digits_valid(argv[1]))){
            fprintf(stderr,"Invalid arguments - non digit search argument");
            return 1;
        }
        // max symbols that a string can have
        const int MAX_CHAR = 100;
        // maximum symbols for fgets function (with \n) + 1 so that we knew it out of length
        const int ENTRY_MAX = MAX_CHAR + 2;

        bool found_match = false;
        //the contact
        char name[MAX_CHAR], number[MAX_CHAR];
        // getting first two strings - one names another phone number
        while (fgets(name, ENTRY_MAX, stdin) != NULL)
        {
            fgets(number, ENTRY_MAX, stdin);

            // checks for correct input
            if(!(check_for_correct_input(name, number, MAX_CHAR))){
                return 1;
            }

            else {
                //replace \n in the name string with \0
                name[string_length(name) - 1] = '\0';
                number[string_length(number) - 1] = '\0';
                //check for match
                if (check_for_match(name,  argv[1]) || check_for_match(number,  argv[1])) {
                    printf("%s, %s\n", name, number);
                    found_match = true;
                }
            }
        }
        if(found_match == false){
            printf("Not found");
        }
        return 0;
    }
    //if no arguments were given except for the file
    else if(argc == 1){
        const int MAX_CHAR = 100;
        // maximum symbols for fgets function (with \n) + 1 so that we knew it out of length
        const int ENTRY_MAX = MAX_CHAR + 2;
        //the contact
        char name[MAX_CHAR], number[MAX_CHAR];
        //get a string name from a stdin
        while (fgets(name, ENTRY_MAX, stdin) != NULL) {
            //get a string number from a stdin
            fgets(number, ENTRY_MAX, stdin);

            // checks for correct input
            if(!(check_for_correct_input(name, number, MAX_CHAR))){
                return 1;
            }
            else {
                //replace \n in the name string with \0 for prettier output
                name[string_length(name) - 1] = '\0';
                number[string_length(number) - 1] = '\0';
                //print the result
                printf("%s, %s\n", name, number);
            }
        }
        return 0;
    }
    else if(argc < 1){
        fprintf(stderr, "No args given");
        return 1;
    }
    else if(argc > 3){
        fprintf(stderr, "Too many args");
        return 1;
    }

}

bool check_for_match(char *str, char *arg){
    for (int i = 0; i < string_length(str); i++){
            if(compare_chars(str[i], arg[0])) {
                for (int count = 1; count <= string_length(arg); count++){
                    if (compare_chars(str[count + i], arg[count])) {
                        if(count == string_length(arg) - 1){
                            return true;
                        }
                    }
                    else{
                        break;
                    }

                }
            }
        }
    return false;
}

// search if there are a match in a string even if there are some other symbols between the searched ones(-s func)
bool check_for_sequence(char *str,int start_point1,char *arg, int start_point2){
    for (int i = start_point1; i < string_length(str); i++){
        //checking if two chars match
         if(compare_chars(str[i], arg[start_point2])){
            start_point1 = i + 1;
            //end of rekursion if the function found the last searched variable
            if(start_point2 == (string_length(arg) - 1)){
                return true;
            }
            start_point2++;
            //rekursion with startpoints so that we knew where to start a shorter and preciser search
            if(check_for_sequence(str, start_point1, arg, start_point2) == true){
                return true;
            }
        }
    }
    return false;
}

//checks if a character matches any other character that represents a digit
bool compare_chars(char a, char b) {
    char reprCisla[10][6] = {"0+", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9wxyz"};
    int row = b - '0';
    int len = string_length(reprCisla[row]);
    for (int i = 0; i < len; i++) {
        if (tolower(a) == reprCisla[row][i]) {
            return true;
        }
    }
    return false;
}

bool check_for_correct_input(char *name, char *number, int MAX_CHAR){
    if (string_length(name) <= 1 || string_length(number) <= 1){
        fprintf( stderr, "Incorrect input, length is 0\n");
        return false;
    }
    if( !(is_in_range(name, MAX_CHAR)) || !(is_in_range(number, MAX_CHAR))){
        fprintf( stderr, "Incorrect input, length is more than %d\n", MAX_CHAR);
        return false;
    }

    if(!is_digits_valid(number) ){
        fprintf( stderr, "Incorrect input, number contain non digit symbol");
        return false;
    }
    return true;
}

bool is_digits_valid(char *num){
    for (int i = 0; i < string_length(num); i++){
        if(num[i] == '\n' || num[i] == '\0'){
            continue;
        }
        else if(!('0' <= num[i] && num[i] <= '9')){
            if(!(i == 0 && num[i] == '+')) // in case there will be a "+" at the start of the number
                return false;
        }
    }
    return true;
}

bool is_in_range(char *str, int MAX_CHAR){
    int len = string_length(str);
    char a = str[len - 1];
    if(len <= 0){
        return false;
    }
    if(len > MAX_CHAR) {
        if (a == '\n') {
            return true;
        } else {
            return false;
        }
    }
    return true;
}

bool string_compare(char *str1, char *str2){
    for(int i=0; str1[i]!='\0' || str2[i]!='\0'; i++) {
        if(str1[i] != str2[i]) {
            return false;
        }
    }
    return true;
}

int string_length(char *str){
    int len = 0;
    while(str[len] != '\0'){
        len++;
    }
    return len;
}
