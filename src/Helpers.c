#include <stdio.h>
#include <string.h>

void get_input(char *input_message, char *input_var)
{
    printf("%s > ",input_message);
    fgets(input_var, 100, stdin);
    input_var[strlen(input_var) -1] = '\0';
}

void separator(char input , int count)
{
    for (int i=0; i!=count; i++){
        printf("%c", input);
    }
    printf("\n");
}
