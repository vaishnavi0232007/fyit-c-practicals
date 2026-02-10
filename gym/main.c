#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure for member
struct Member {
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char plan[20];
};

void addMember();
void viewMembers();
void searchMember();

int main() {
    int choice;
    while (1) {
        printf("\n=== Gym Management System ===\n");
        printf("1. Add Member\n");
        printf("2. View All Members\n");
        printf("3. Search Member\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMember(); break;
            case 2: viewMembers(); break;
            case 3: searchMember(); break;
            case 4: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// add member
void addMember() {
    struct Member m;
    FILE *fp = fopen("gym.dat", "ab");
    if (!fp) { printf("File error!\n"); return; }

    printf("Enter ID: "); scanf("%d", &m.id);
    getchar(); // clear buffer
    printf("Enter Name: "); fgets(m.name, 50, stdin);
    m.name[strcspn(m.name, "\n")] = 0;
    printf("Enter Age: "); scanf("%d", &m.age);
    printf("Enter Gender: "); scanf("%s", m.gender);
    printf("Enter Phone: "); scanf("%s", m.phone);
    printf("Enter Plan: "); scanf("%s", m.plan);

    fwrite(&m, sizeof(m), 1, fp);
    fclose(fp);
    printf("Member added!\n");
}

// view members
void viewMembers() {
    struct Member m;
    FILE *fp = fopen("gym.dat", "rb");
    if (!fp) { printf("No records!\n");
     return;
     }

    printf("\n--- Member List ---\n");
    while (fread(&m, sizeof(m), 1, fp)) {
        printf("ID:%d | %s | Age:%d | %s | %s | %s\n",
               m.id, m.name, m.age, m.gender, m.phone, m.plan);
    }
    fclose(fp);
}

// search member
void searchMember() {
    int id, found = 0;
    struct Member m;
    FILE *fp = fopen("gym.dat", "rb");
    if (!fp) { printf("No records!\n"); return; }

    printf("Enter ID to search: "); scanf("%d", &id);
    while (fread(&m, sizeof(m), 1, fp)) {
        if (m.id == id) {
            printf("Found: %s | Age:%d | Plan:%s\n",
                   m.name, m.age, m.plan);
            found = 1;
             break;
        }
    }
    if (!found) printf("Member not found!\n");
    fclose(fp);

}
