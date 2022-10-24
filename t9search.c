#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool check_for_match(char *str, char arg[]);
bool check_for_sequence(char *str,int start_point1,char *arg, int startpoint2);
bool check_char_for_match(char a, char b);


bool check_for_correct_input(char *name, char *number, int MAX_CHAR);
bool is_digits_valid(char *num);
bool is_in_range(char *str, int MAX_CHAR);

void tolow(char *str);
void toup(char *str, int i, int j);


int main(int argc, char **argv)
{

    if (argc == 3){
        // argument in console must be in digit
        if(!(is_digits_valid(argv[2])) && argv[1] == "-s"){
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
                name[strlen(name) - 1] = '\0';
                number[strlen(number) - 1] = '\0';
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
                name[strlen(name) - 1] = '\0';
                number[strlen(number) - 1] = '\0';
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
                name[strlen(name) - 1] = '\0';
                number[strlen(number) - 1] = '\0';
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

bool check_for_match(char *str, char arg[]){
    for (int i = 0; i < strlen(str); i++){
            if(check_char_for_match(str[i], arg[0])) {
                str[i] = toupper(str[i]);
                for (int count = 1; count < strlen(arg); count++){
                    if (check_char_for_match(str[count + i], arg[i])) {
                        str[count + i] = toupper(str[count + i]);
                        if(count == strlen(arg) - 1){
                            return true;
                        }
                    }
                }
            }
        }
    tolow(str);
    return false;
}

////checks if the contact contains a search result regardless of sequence(-s function)
//bool check_for_match_ws(char *name, char *number, char arg[]) {
//    //check if there were any match to the search argument in the phone number or name
//    if(check_for_sequence(number, 0, arg, 0) || check_for_sequence(name, 0, arg, 0)){
//        return true
//    }
//    return false;
//}


// search if there are a match in a string even if there are some other symbols between the searched ones(-s func)
bool check_for_sequence(char *str,int start_point1,char *arg, int start_point2){
    for (int i = start_point1; i < strlen(str); i++){
        //checking if two chars match
         if(check_char_for_match(str[i], arg[start_point2])){
            str[i] = toupper(str[i]);
            start_point1 = i + 1;
            //end of rekursion if the function found the last searched variable
            if(start_point2 == (strlen(arg) - 1)){
                return true;
            }
            start_point2++;
            //rekursion with startpoints so that we knew where to start a shorter and preciser search
            if(check_for_sequence(str, start_point1, arg, start_point2) == true){
                return true;
            }
        }
    }
    //if nothing found make the string as it was before
    tolow(str);
    return false;
}

//checks if a character matches any other character that represents a digit
bool check_char_for_match(char a, char b) {
    char reprCisla[10][6] = {"0+", "1", "2abc", "3def", "4ghi", "5jkl", "6mno", "7pqrs", "8tuv", "9wxyz"};
    int row = b - '0';
    int len = strlen(reprCisla[row]);
    for (int i = 0; i < len; i++) {
        if (tolower(a) == reprCisla[row][i]) {
            return true;
        }

    }
    return false;
}

bool check_for_correct_input(char *name, char *number, int MAX_CHAR){
    if (strlen(name) <= 1 || strlen(number) <= 1){
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
    for (int i = 0; i < strlen(num); i++){
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
    int len = strlen(str);
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

//makes a string in lower case
void tolow(char *str) {
    for(int i = 0; str[i] != '\0'; i++){
        if('A' <= str[i] && str[i] <= 'Z'){
            str[i] = tolower(str[i]);
        }
    }
}

//makes a string in upper case
void toup(char *str, int i, int j) {
    int howmany = i + j;
    for(i; i < howmany; i++){
        str[i] = toupper(str[i]);
        // make if aspace doesnt matter
    }
}
