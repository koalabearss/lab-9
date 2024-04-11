#include <stdio.h>
#include <stdlib.h> // for malloc and free

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Define the maximum size of the hash table
#define HASH_SIZE 100

// Define the structure for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// Hash table structure
struct HashType
{
    struct Node* head; // Array of pointers to linked lists
};

// Initialize the hash table
void initHashTable(struct HashType* hashTable, int size)
{
    hashTable->head = (struct Node*)malloc(size * sizeof(struct Node));
    for (int i = 0; i < size; ++i)
    {
        hashTable->head[i].next = NULL; // Initialize each list as empty
    }
}

// Compute the hash function
int hash(int x)
{
    // A simple hash function example
    return x % HASH_SIZE;
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    // Implementation remains the same...
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    // Implementation remains the same...
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType* pHashArray, int hashSz)
{
    // Implementation to iterate through the hash table and print records
    for (int i = 0; i < hashSz; ++i)
    {
        struct Node* current = pHashArray->head[i].next; // Skip the head node
        printf("Index %d -> ", i);
        while (current != NULL)
        {
            printf("%d, %c, %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    struct HashType hashTable;
    initHashTable(&hashTable, HASH_SIZE);

    // Insert records into the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int h = hash(pRecords[i].id); // Compute the hash value
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node)); // Create a new node
        newNode->data = pRecords[i]; // Copy the data to the node
        newNode->next = hashTable.head[h].next; // Insert at the beginning of the list
        hashTable.head[h].next = newNode; // Update the head pointer
    }

    // Display records stored in the hash table
    displayRecordsInHash(&hashTable, HASH_SIZE);

    // Free memory
    // Remember to free the memory allocated for each linked list
    for (int i = 0; i < HASH_SIZE; ++i)
    {
        struct Node* current = hashTable.head[i].next;
        while (current != NULL)
        {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable.head);

    return 0;
}
