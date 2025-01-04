#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>


struct stack {
    char data ;
    struct stack *next;
};
struct stack *push (struct stack *top, char str) {
    struct stack *ptr ;
    ptr = (struct stack *) malloc(sizeof(struct stack*));
    ptr -> data= str;
    if (top==NULL) { 
        top = ptr; 
        top -> next = NULL ; 
    }
    else { 
        ptr-> next = top; 
        top = ptr; 
    }
    return top; 
}


// Example usage
int main() {
    struct stack *top = NULL;

    char word [15] ; 
    printf("Nasukan kata yang anda ingin balik: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0'; // Remove newline character


    for (int i = 0; word[i] != '\0'; i++) {
        top = push(top, word[i]); 
    }

    printf ("Hasil pembalikan adalah: ");

    struct stack *temp = top;
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    return 0;
}
