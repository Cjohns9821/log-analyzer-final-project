#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 1024

typedef struct Entry {
    char ip[50];
    int count;
    struct Entry *next;
} Entry;

Entry *table[TABLE_SIZE] = {NULL};

unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}

void update_ip(char *ip)
{
    unsigned int index = hash(ip);

    Entry *current = table[index];

    while (current != NULL)
    {
        if (strcmp(current->ip, ip) == 0)
        {
            current->count++;
            return;
        }

        current = current->next;
    }

    Entry *newEntry = malloc(sizeof(Entry));

    if (newEntry == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(newEntry->ip, ip);
    newEntry->count = 1;

    newEntry->next = table[index];
    table[index] = newEntry;
}

void free_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Entry *current = table[i];

        while (current != NULL)
        {
            Entry *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./optimized filename\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    char ip[50];
    char page[100];

    clock_t start = clock();

    while (fscanf(file, "%49s %99s", ip, page) == 2)
    {
        update_ip(ip);
    }

    clock_t end = clock();

    printf("Execution Time: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    printf("\nIP Address Counts:\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Entry *current = table[i];

        while (current != NULL)
        {
            printf("%s -> %d\n",
                   current->ip,
                   current->count);

            current = current->next;
        }
    }

    free_table();

    fclose(file);

    return 0;
}
