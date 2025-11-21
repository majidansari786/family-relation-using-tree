#include <stdio.h>
#include <string.h>

#define MAX 50
char NONE[MAX] = "NONE";

struct Person {
    char name[50];
    char parent[50];
};

struct Person family[MAX];
int count = 0;

void addMember() {
    if (count >= MAX) {
        printf("\nFamily tree is full!\n");
        return;
    }

    struct Person p;
    printf("\nEnter name of person: ");
    scanf("%s", p.name);

    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].name, p.name) == 0) {
            printf("Person '%s' already exists!\n", p.name);
            return;
        }
    }

    if (count == 0) {
        strcpy(p.parent, NONE);
        printf("Added as root member (no parent).\n");
    } else {
        printf("Enter parent name: ");
        scanf("%s", p.parent);
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(family[i].name, p.parent) == 0) {
                found = 1; break;
            }
        }
        if (!found) {
            printf("Parent '%s' not found. Add parent first or try again.\n", p.parent);
            return;
        }
    }

    family[count++] = p;
    printf("Member added successfully!\n");
}

void findParent() {
    char name[50];
    int found = 0;

    printf("\nEnter name: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].name, name) == 0) {
            found = 1;
            if (strcmp(family[i].parent, NONE) == 0)
                printf("%s has no parent (root of family).\n", name);
            else
                printf("Parent of %s is %s\n", name, family[i].parent);
            break;
        }
    }

    if (!found)
        printf("Person not found in family tree!\n");
}

void findChildren() {
    char name[50];
    int found = 0;

    printf("\nEnter parent's name: ");
    scanf("%s", name);

    printf("Children of %s: ", name);
    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].parent, name) == 0) {
            printf("%s ", family[i].name);
            found = 1;
        }
    }

    if (!found)
        printf("No children found!");
    printf("\n");
}

void findSiblings() {
    char name[50];
    char parent[50];
    int found = 0;

    printf("\nEnter name: ");
    scanf("%s", name);

    // find parent of that person
    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].name, name) == 0) {
            strcpy(parent, family[i].parent);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Person not found!\n");
        return;
    }

    if (strcmp(parent, NONE) == 0) {
        printf("%s has no siblings (root member).\n", name);
        return;
    }

    printf("Siblings of %s: ", name);
    int sib = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].parent, parent) == 0 && strcmp(family[i].name, name) != 0) {
            printf("%s ", family[i].name);
            sib = 1;
        }
    }

    if (!sib)
        printf("No siblings found!");
    printf("\n");
}

void displayFamily() {
    printf("\n--- Family Members ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s (Parent: %s)\n", i + 1, family[i].name, family[i].parent);
    }
}

int findRootIndex() {
    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].parent, NONE) == 0) return i;
    }
    return -1;
}

void printSubtree(const char *name, int level) {
    for (int i = 0; i < level; i++) printf("    ");
    printf("|-- %s\n", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(family[i].parent, name) == 0) {
            printSubtree(family[i].name, level + 1);
        }
    }
}

void visualize() {
    if (count == 0) {
        printf("Family is empty.\n");
        return;
    }
    int rootIdx = findRootIndex();
    if (rootIdx == -1) {
        printf("No root (person with parent NONE) found. Cannot visualize.\n");
        return;
    }
    printf("\nFamily Tree:\n");
    printSubtree(family[rootIdx].name, 0);
}

int main() {
    int choice;

    printf("===== FAMILY RELATION =====\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Member\n");
        printf("2. Find Parent\n");
        printf("3. Find Children\n");
        printf("4. Find Siblings\n");
        printf("5. Display Family\n");
        printf("6. Visualize\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMember(); break;
            case 2: findParent(); break;
            case 3: findChildren(); break;
            case 4: findSiblings(); break;
            case 5: displayFamily(); break;
            case 6: visualize(); break;
            case 8: printf("Thank you!\n"); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

