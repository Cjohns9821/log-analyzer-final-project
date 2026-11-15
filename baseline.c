#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char ip[50];
    int count;
    struct Node *next;
} Node;

Node* find(Node *head, char *ip)
{
    while (head != NULL)
    {
        if (strcmp(head->ip, ip) == 0)
        {
            return head;
        }

        head = head->next;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./baseline filename\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    Node *head = NULL;

    char ip[50];
    char page[100];

    clock_t start = clock();

    while (fscanf(file, "%49s %99s", ip, page) == 2)
    {
        Node *existing = find(head, ip);

        if (existing != NULL)
        {
            existing->count++;
        }
        else
        {
            Node *newNode = malloc(sizeof(Node));

            strcpy(newNode->ip, ip);
            newNode->count = 1;
            newNode->next = head;

            head = newNode;
        }
    }

    clock_t end = clock();

    printf("Execution Time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    Node *current = head;

    printf("\nIP Address Counts:\n");

    while (current != NULL)
    {
        printf("%s -> %d\n",
               current->ip,
               current->count);

        current = current->next;
    }

    current = head;

    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }

    fclose(file);

    return 0;
}
