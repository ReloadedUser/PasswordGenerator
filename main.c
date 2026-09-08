#include <stdio.h>
#include <stdlib.h>
#include <time.h>



struct input_length {
    int numbers;
    int characters;
    int symbols;
};


int* random_numbers(int *random_n,struct input_length s0) {
    srand(time(nullptr));

    for (int i = 0; i < s0.numbers; i++) {
        random_n[i] = rand()%10;
    }

    return random_n;
}


char* random_characters(char *random_char,struct input_length s1) {
    srand(time(nullptr));
    char randomletter;

    for (int i=0; i< s1.characters; i++) {
        randomletter = 'a' + rand() % 26;
        random_char[i]=randomletter;
    }
    random_char[s1.characters]='\0';

    return random_char;
}


char* random_symbols(char *random_symb,char symbols_list_text[2],struct input_length s2) {
    srand(time(nullptr));
    int random;

    for (int i = 0; i < s2.symbols; i++) {
        random = rand()%32;
        random_symb[i]=symbols_list_text[random];
    }
    random_symb[s2.symbols]='\0';

    return random_symb;
}


struct input_length user_input() {
    struct input_length input;

    printf("\nINFO: the password length will be the sum of the numbers, characters and symbols.\n");
    printf("\nINFO: the amount of numbers, characters and symbols is approximate, because of the random algorithm.\n");
    printf("\nPlease check the DISCLAIMER and LICENSE.\n");

    printf("\nEnter the amount of numbers:");
    scanf("%d",&input.numbers);

    printf("\nEnter the amount of characters:");
    scanf("%d",&input.characters);

    printf("\nEnter the amount of symbols:");
    scanf("%d",&input.symbols);

    return input;
}


char* generate_password(char *password,int *numbers_list,char *characters_list,char *symbols_list,struct input_length input) {
    srand(time(nullptr));
    int length=input.numbers+input.characters+input.symbols;
    int current_element;

    for (int i = 0; i < length; i++) {
        current_element=rand()%(length-1);

        if (current_element>=0 && current_element<input.numbers) {
            password[i]=(char)(numbers_list[current_element]+'0');
        }
        if (current_element>=input.numbers && current_element<input.numbers+input.characters) {
            password[i]=characters_list[current_element-input.numbers];
        }
        if (current_element>=input.numbers+input.characters) {

            password[i]=symbols_list[current_element-(input.numbers+input.characters)];
        }
    }
    password[length]='\0';

    return password;
}



int main() {

    char list_text[] = "!@#$%^&*()_+-=[]\\{}|;':,.<>/?`~\"";
    struct input_length user_input_length=user_input();

    int* numbers_list = malloc(user_input_length.numbers * sizeof(int));
    char* characters_list = malloc(user_input_length.characters * sizeof(char));
    char* symbols_list = malloc(user_input_length.symbols * sizeof(char));
    char* finalPassword=malloc((user_input_length.numbers+user_input_length.characters+user_input_length.symbols) * sizeof(char));

    numbers_list=random_numbers(numbers_list,user_input_length);
    characters_list=random_characters(characters_list,user_input_length);
    symbols_list=random_symbols(symbols_list,list_text,user_input_length);

    finalPassword=generate_password(finalPassword,numbers_list,characters_list,symbols_list,user_input_length);
    printf("Password:%s\n",finalPassword);

    free(numbers_list);
    free(characters_list);
    free(symbols_list);

    return 0;
}

