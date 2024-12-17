#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

typedef struct Directory {
    char name[MAX_NAME_LENGTH];
    struct Directory* next;
    struct Directory* subdir;
} Directory;

typedef struct Stack {
    Directory* dir;
    struct Stack* next;
} Stack;

Directory* createDirectory(const char* name);
int push(Stack* stack, Directory* dir);
int pop(Stack* stack);
int addSubdirectory(Directory* parent, Directory* sub);
void printDirectoryContents(Directory* dir, int level);
void deleteDirectoryList(Directory* dir);
void deleteStack(Stack* stack);

int main() {
    char command;
    char dirName[MAX_NAME_LENGTH];
    Directory* root = createDirectory("C:");
    Stack stack = { root, NULL };
    Directory* currentDir = root;

    printf("1 - Napravi direktorij\n2 - Promijeni direktorij\n3 - Idi na roditeljski direktorij\n4 - Prikaži sadržaj\n5 - Izlaz\n");

    while (1) {
        printf("\nUnesite naredbu: ");
        scanf(" %c", &command);

        switch (command) {
        case '1':
            printf("Unesite ime direktorija: ");
            scanf(" %s", dirName);
            Directory* newDir = createDirectory(dirName);
            addSubdirectory(currentDir, newDir);
            printf("Direktorij %s napravljen.\n", dirName);
            break;

        case '2':
            printf("Unesite ime direktorija za promjenu: ");
            scanf(" %s", dirName);
            Directory* temp = currentDir->subdir;
            while (temp != NULL && strcmp(temp->name, dirName) != 0) {
                temp = temp->next;
            }
            if (temp != NULL) {
                push(&stack, temp);
                currentDir = temp;
                printf("Promijenjeno u direktorij %s.\n", dirName);
            }
            else {
                printf("Direktorij nije prona?en.\n");
            }
            break;

        case '3':
            if (pop(&stack)) {
                currentDir = stack.dir;
                printf("Premješteno u roditeljski direktorij: %s\n", currentDir->name);
            }
            else {
                printf("Ve? ste u korijenskom direktoriju.\n");
            }
            break;

        case '4':
            printf("Sadržaj direktorija %s:\n", currentDir->name);
            printDirectoryContents(currentDir->subdir, 0);
            break;

        case '5':
            deleteDirectoryList(root);
            deleteStack(&stack);
            printf("Izlaz iz programa.\n");
            return 0;

        default:
            printf("Nevaže?a naredba. Pokušajte ponovo.\n");
        }
    }

    return 0;
}

Directory* createDirectory(const char* name) {
    Directory* newDir = (Directory*)malloc(sizeof(Directory));
    if (newDir == NULL) {
        printf("Neuspjelo dodjeljivanje memorije.\n");
        exit(1);
    }
    strcpy(newDir->name, name);
    newDir->next = NULL;
    newDir->subdir = NULL;
    return newDir;
}

int addSubdirectory(Directory* parent, Directory* sub) {
    sub->next = parent->subdir;
    parent->subdir = sub;
    return 0;
}

void printDirectoryContents(Directory* dir, int level) {
    while (dir != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("%s\n", dir->name);
        printDirectoryContents(dir->subdir, level + 1);
        dir = dir->next;
    }
}

void deleteDirectoryList(Directory* dir) {
    while (dir != NULL) {
        Directory* temp = dir;
        dir = dir->next;
        deleteDirectoryList(temp->subdir);
        free(temp);
    }
}

void deleteStack(Stack* stack) {
    while (stack != NULL) {
        Stack* temp = stack;
        stack = stack->next;
        free(temp);
    }
}

int push(Stack* stack, Directory* dir) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    if (newStack == NULL) {
        printf("Neuspjelo dodjeljivanje memorije.\n");
        exit(1);
    }
    newStack->dir = dir;
    newStack->next = stack->next;
    stack->next = newStack;
    return 0;
}

int pop(Stack* stack) {
    if (stack->next == NULL) return 1;
    Stack* temp = stack->next;
    stack->next = stack->next->next;
    free(temp);
    return 0;
}
