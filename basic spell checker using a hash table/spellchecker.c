#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100000
#define MAX_WORD_LEN 30

typedef struct node{
    char word[MAX_WORD_LEN];
    struct node* next;
}Node;

Node* hashtable[MAX_WORDS];

unsigned int hash(const char* word)
{
    unsigned int h = 0;
    for(; *word; word++)
    {
        h = h*31 + *word;
    }
    return h % MAX_WORDS;
}

int addWord(const char* word)
{
    unsigned int h = hash(word);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL)
    {
        return 0;
    }
    strcpy(newNode->word, word);
    newNode->next = hashtable[h];
    hashtable[h] = newNode;
    return 1;
}

int checkSpelling(const char* word)
{
    unsigned int h = hash(word);
    Node* current = hashtable[h];
    while(current != NULL)
    {
        if(strcmp(current->word, word) == 0)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main()
{
    // load dictionary into hash table
    FILE* fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
    {
        printf("Error: Could not open dictionary.txt\n");
        exit(1);
    }
    char word[MAX_WORD_LEN];
    while(fscanf(fp, "%s", word) != EOF)
    {
        addWord(word);
    }
    fclose(fp);

    // check spelling of words
    char input[MAX_WORD_LEN];
    while(1)
    {
        printf("Enter a word: ");
        scanf("%s", input);
        if(checkSpelling(input))
        {
            printf("The word is spelled correctly\n");
        }
        else
        {
            printf("The word is spelled incorrectly\n");
        }
    }
    return 0;
}
