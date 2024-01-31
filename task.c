#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCRIPTION_LENGTH 100
#define MAX_TASKS 100

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char description[MAX_DESCRIPTION_LENGTH];
    Date date;
    int priority;
    int status; 
} Task;

Task tasks[MAX_TASKS];
int taskCount = 0;


void addTask();
void displayTasks();
void modifyTask();
void deleteTask();
void sortTasksAscending();
void sortTasksDescending();
void filterTasksByPriority(int priority);
void filterTasksByStatus(int status);
void saveTasksToFile();
void loadTasksFromFile();
int main() {
    loadTasksFromFile();
    int choice;
    int ch;
    int priority;
    int status;

    do {
        printf("\n**************************\n");
        printf("*        Menu           *\n");
        printf("* 1. Ajouter une tache  *\n");
        printf("* 2. Afficher la liste  *\n");
        printf("* 3. Modifier une tache *\n");
        printf("* 4. Supprimer une tache*\n");
        printf("* 5. Ordonner les taches*\n");
        printf("* 6. Filtrer par priorite*\n");
        printf("* 7. Filtrer par statut *\n");
        printf("* 0. Quitter pour sauvgarder*\n");
        printf("**************************\n");

        printf("Choisissez une option : ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayTasks();
                break;
            case 3:
                modifyTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("1. Trier par ordre croissant\n2. Trier par ordre decroissant\n");
                printf("Choisissez une option : ");
                scanf("%d", &ch);
                if (ch == 1) {
                    sortTasksAscending();
                } else if (ch == 2) {
                    sortTasksDescending();
                }
                break;
            case 6:
                printf("Entrez la priorite pour le filtrage : ");
                scanf("%d", &priority);
                filterTasksByPriority(priority);
                break;
            case 7:
                printf("Entrez le statut pour le filtrage (0: Incompl�te, 1: Compl�te) : ");
                scanf("%d", &status);
                filterTasksByStatus(status);
                break;
            case 0:
                saveTasksToFile();
                printf("Au revoir!\n");
                break;
            default:
                printf("Option invalide. Veuillez r�essayer.\n");
        }
    } while (choice != 0);

    return 0;
}


void addTask() {
    printf("Entrez la description de la tache : ");
    scanf("%s", tasks[taskCount].description);

    printf("Entrez la date limite de la tache (JJ MM AAAA) : ");
    scanf("%d %d %d", &tasks[taskCount].date.day, &tasks[taskCount].date.month, &tasks[taskCount].date.year);

    printf("Entrez la priorit� de la tache : ");
    scanf("%d", &tasks[taskCount].priority);

    printf("Entrez le statut de la tache (0: Incompl�te, 1: Compl�te) : ");
    scanf("%d", &tasks[taskCount].status);

    taskCount++;
}

void displayTasks() {
    printf("Liste des t�ches :\n");
    for (int i = 0; i < taskCount; i++) {
        printf("Tache %d :\n", i + 1);
        printf("Description : %s\n", tasks[i].description);
        printf("Date limite : %d/%d/%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
        printf("Priorit� : %d\n", tasks[i].priority);
        printf("Statut : %s\n", tasks[i].status ? "Compl�te" : "Incompl�te");
        printf("--------------------\n");
    }
}

void modifyTask() {
    int index;
    printf("Entrez le num�ro de la t�che que vous souhaitez modifier : ");
    scanf("%d", &index);

    if (index > 0 && index <= taskCount) {
        printf("Entrez la nouvelle description de la t�che : ");
        scanf("%s", tasks[index - 1].description);

        printf("Entrez la nouvelle date limite de la t�che (JJ MM AAAA) : ");
        scanf("%d %d %d", &tasks[index - 1].date.day, &tasks[index - 1].date.month, &tasks[index - 1].date.year);

        printf("Entrez la nouvelle priorit� de la t�che : ");
        scanf("%d", &tasks[index - 1].priority);

        printf("Entrez le nouveau statut de la t�che (0: Incompl�te, 1: Compl�te) : ");
        scanf("%d", &tasks[index - 1].status);

        printf("La t�che a �t� modifi�e avec succ�s.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

void deleteTask() {
    int index;
    printf("Entrez le numero de la tache que vous souhaitez supprimer : ");
    scanf("%d", &index);

    if (index > 0 && index <= taskCount) {
        for (int i = index - 1; i < taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }

        taskCount--;

        printf("La tache a �t� supprim�e avec succes.\n");
    } else {
        printf("Numero de tache invalide.\n");
    }
}

void sortTasksAscending() {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            // Comparaison bas�e sur la date d'�ch�ance
            if (tasks[j].date.year > tasks[j + 1].date.year ||
                (tasks[j].date.year == tasks[j + 1].date.year &&
                 tasks[j].date.month > tasks[j + 1].date.month) ||
                (tasks[j].date.year == tasks[j + 1].date.year &&
                 tasks[j].date.month == tasks[j + 1].date.month &&
                 tasks[j].date.day > tasks[j + 1].date.day)) {
                // �change des t�ches si elles ne sont pas dans l'ordre
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Les t�ches ont �t� tri�es par date d'�ch�ance en ordre croissant.\n");
}

// Fonction pour trier les t�ches par date en ordre d�croissant
void sortTasksDescending() {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            // Comparaison bas�e sur la date d'�ch�ance (en ordre inverse)
            if (tasks[j].date.year < tasks[j + 1].date.year ||
                (tasks[j].date.year == tasks[j + 1].date.year &&
                 tasks[j].date.month < tasks[j + 1].date.month) ||
                (tasks[j].date.year == tasks[j + 1].date.year &&
                 tasks[j].date.month == tasks[j + 1].date.month &&
                 tasks[j].date.day < tasks[j + 1].date.day)) {
                // �change des t�ches si elles ne sont pas dans l'ordre
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("Les t�ches ont �t� tri�es par date d'�ch�ance en ordre d�croissant.\n");
}

void filterTasksByPriority(int priority) {
    printf("T�ches avec priorit� %d :\n", priority);
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].priority == priority) {
            printf("Tache %d :\n", i + 1);
            printf("Description : %s\n", tasks[i].description);
            printf("Date limite : %d/%d/%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
            printf("Priorit� : %d\n", tasks[i].priority);
            printf("Statut : %s\n", tasks[i].status ? "Complete" : "Incomplete");
            printf("--------------------\n");
        }
    }
}

void filterTasksByStatus(int status) {
    printf("T�ches avec statut %s :\n", status ? "Complete" : "Incomplete");
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].status == status) {
            printf("Tache %d :\n", i + 1);
            printf("Description : %s\n", tasks[i].description);
            printf("Date limite : %d/%d/%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
            printf("Priorite : %d\n", tasks[i].priority);
            printf("Statut : %s\n", tasks[i].status ? "Complete" : "Incomplete");
            printf("--------------------\n");
        }
    }
}
void saveTasksToFile() {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }

    fprintf(file, "Liste des taches :\n");
    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "Tache %d :\n", i + 1);
        fprintf(file, "Description : %s\n", tasks[i].description);
        fprintf(file, "Date d'echeance : %d/%d/%d\n", tasks[i].date.day, tasks[i].date.month, tasks[i].date.year);
        fprintf(file, "Priorite : %d\n", tasks[i].priority);
        fprintf(file, "Statut : %s\n", tasks[i].status ? "Complete" : "Incomplete");
        fprintf(file, "--------------------\n");
    }

    fclose(file);
}

void loadTasksFromFile() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("Le fichier de sauvegarde n'existe pas encore.\n");
        return;
    }

    taskCount = 0;

    while (fscanf(file, "Tache %*d :\nDescription : %s\nDate d'echeance : %d/%d/%d\nPriorite : %d\nStatut : %*s\n--------------------\n",
                  tasks[taskCount].description, &tasks[taskCount].date.day, &tasks[taskCount].date.month,
                  &tasks[taskCount].date.year, &tasks[taskCount].priority) != EOF) {
        char status[20];
        fscanf(file, "Statut : %s\n--------------------\n", status);
        tasks[taskCount].status = (strcmp(status, "Complete") == 0) ? 1 : 0;
        taskCount++;
    }

    fclose(file);
}
