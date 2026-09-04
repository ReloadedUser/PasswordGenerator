#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int numbers, characters, symbols;


int* random_numbers(int *random_n) {
    srand(time(nullptr));

    for (int i = 0; i < numbers; i++) {
        random_n[i] = rand()%10;
    }
    return random_n;
}


char* random_characters(char *random_char) {
    srand(time(nullptr));

    char randomletter;
    for (int i=0; i<characters; i++) {
        randomletter = 'a' + rand() % 26;
        random_char[i]=randomletter;
    }
    random_char[characters]='\0';
    return random_char;
}


char* random_symbols(char *random_symb,char symbols_list_text[symbols]) {
    srand(time(nullptr));

    int random;
    for (int i = 0; i < symbols; i++) {
        random = rand()%32;
        random_symb[i]=symbols_list_text[random];
    }
    random_symb[symbols]='\0';
    return random_symb;
}


void user_input() {

    printf("\nINFO: the password length will be the sum of the numbers, characters and symbols.\n");
    printf("\nINFO: the amount of numbers, characters and symbols is approximate, because of the random algorithm.\n");
    printf("\nPlease check the DISCLAIMER and LICENSE.\n");

    printf("\nEnter the amount of numbers:");
    scanf("%d",&numbers);

    printf("\nEnter the amount of characters:");
    scanf("%d",&characters);

    printf("\nEnter the amount of symbols:");
    scanf("%d",&symbols);
}


char* generate_password(char *password,int *numbers_list,char *characters_list,char *symbols_list) {
    srand(time(nullptr));
    int length=numbers+characters+symbols;
    int current_element;

    for (int i = 0; i < length; i++) {
        current_element=rand()%(length-1);

        if (current_element>=0 && current_element<numbers) {
            password[i]=(char)(numbers_list[current_element]+'0');
        }
        if (current_element>=numbers && current_element<numbers+characters) {
            password[i]=characters_list[current_element-numbers];
        }
        if (current_element>=numbers+characters) {

            password[i]=symbols_list[current_element-(numbers+characters)];
        }
    }
    password[length]='\0';
    return password;
}


int main() {
    char list_text[] = "!@#$%^&*()_+-=[]\\{}|;':,.<>/?`~\"";

    user_input();

    int* numbers_list = malloc(numbers * sizeof(int));
    char* characters_list = malloc(characters * sizeof(char));
    char* symbols_list = malloc(symbols * sizeof(char));
    char* finalPassword=malloc((numbers+characters+symbols) * sizeof(char));

    numbers_list=random_numbers(numbers_list);
    characters_list=random_characters(characters_list);
    symbols_list=random_symbols(symbols_list,list_text);

    finalPassword=generate_password(finalPassword,numbers_list,characters_list,symbols_list);

    printf("Password:%s\n",finalPassword);

    free(numbers_list);
    free(characters_list);
    free(symbols_list);
    return 0;

}

