#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define DEBUG 1

int people = 50, court = 50, found = 50;
int counter = 0;
struct problems_node {
    int problem_id;
    char problem1[200];
    char decision1[200];
    int efpeople1, efcourt1, effound1;
    char decision2[200];
    int efpeople2, efcourt2, effound2;
    int problem_counter;
    struct problems_node *next;
};
struct player {
    char player_name[100];
    int condition;
    int probelity_of_problems[100];
    int people;
    int court;
    int found;
};
struct player_ranking {
    char player_namae[100];
    int people;
    int court;
    int found;
};

void print(struct problems_node p) {
    printf("%s \n", p.problem1);
    printf("1)%s \n", p.decision1);
    printf("%d %d %d \n", p.efpeople1, p.efcourt1, p.effound1);
    printf("2)%s \n", p.decision2);
    printf("%d %d %d \n", p.efpeople2, p.efcourt2, p.effound2);


}

void print_player(struct player p) {
    printf("\n %s \n", p.player_name);
    printf("\n player condition %d", p.condition);
    for (int i = 0; i < 7; i++) {
        printf("\n question %dth pprobabilityis: %d", (i + 1), p.probelity_of_problems[i]);
    }
    printf("\n people : %d", p.people);
    printf("\n court : %d", p.court);
    printf("\n found : %d", p.found);

}


struct problems_node *create_node(struct problems_node p);

struct problems_node *read_problems(int *problem_number) {

    (*problem_number) = 0;
    char prob_file_name[100];
    FILE *fpfileName = fopen("CHOICES.txt", "r");
    if (fpfileName == NULL) {
        printf("couldnt open file");
        exit(-1);
    }
    int id_counter = 0;
    struct problems_node *list = NULL, *current = NULL;
    while (fgets(prob_file_name, 200, fpfileName) != NULL) {


        if (prob_file_name[strlen(prob_file_name) - 1] == '\n') {
            prob_file_name[strlen(prob_file_name) - 1] = '\0';
        }
        FILE *fpProblem;
        fpProblem = fopen(prob_file_name, "r");
        if (fpProblem == NULL) {
            printf("couldnt open problem file");
            exit(-1);
        }
        struct problems_node p;
        fgets(p.problem1, 201, fpProblem);
        fgets(p.decision1, 201, fpProblem);
        fscanf(fpProblem, "%d%d%d\n", &p.efpeople1, &p.efcourt1, &p.effound1);
        // fgetc(fpProblem);

        fgets(p.decision2, 200, fpProblem);
        fscanf(fpProblem, "%d%d%d\n", &p.efpeople2, &p.efcourt2, &p.effound2);
        p.problem_counter = 3;
        p.problem_id = id_counter;
        if (list == NULL) {
            list = create_node(p);
            current = list;
        } else {
            current->next = create_node(p);
            current = current->next;
        }
        (*problem_number)++;

        fclose(fpProblem);
        id_counter++;
    }
    fclose(fpfileName);
    return list;
}

struct problems_node *create_node(struct problems_node p) {
    struct problems_node *nn;
    nn = (struct problems_node *) malloc(sizeof(p));
    strcpy(nn->problem1, p.problem1);
    strcpy(nn->decision1, p.decision1);
    nn->efpeople1 = p.efpeople1;
    nn->efcourt1 = p.efcourt1;
    nn->effound1 = p.effound1;
    strcpy(nn->decision2, p.decision2);
    nn->efpeople2 = p.efpeople2;
    nn->efcourt2 = p.efcourt2;
    nn->effound2 = p.effound2;
    nn->problem_counter = 3;
    nn->problem_id = p.problem_id;
    nn->next = NULL;
    return nn;
}

struct problems_node *remove_node(struct problems_node *removable, struct problems_node **list) {
    struct problems_node *curent;
    curent = *list;
    if (curent == removable) {
        (*list) = (*list)->next;
        free(removable);
        return (*list);
    }

    while (curent->next != removable) {
        curent = curent->next;
    }
    curent->next = curent->next->next;
    free(removable);
    return curent;
}

void check_linked_listed(struct problems_node **list, int *problem_number) {

    struct problems_node *current;
    for (current = (*list); current != NULL;) {
        if (current->problem_counter == 0) {
            current = remove_node(current, list);
            (*problem_number)--;
            counter++;
        } else
            current = current->next;

    }
    return;

}

void
clear(void) {
    while (getchar() != '\n');
}

int check_parametrs() {
    if (people <= 0 || court <= 0 || found <= 0 || people + court + found <= 30) {
        printf("you lost the game");
        return 0;
    }
    return 1;
}

int make_it_correct(int a) {
    if (a > 100) {
        a = 100;
        return a;
    } else if (a < 0) {
        a = 0;
        return a;
    }
}

char exit_game() {
    char exit_charechter;
    scanf("%c", &exit_charechter);
    return exit_charechter;
}

#ifdef DEBUG

#endif

void save_game(struct player p) {
    FILE *fp_save;
    fp_save = fopen(p.player_name, "wb");
    fwrite(&p, sizeof(p), 1, fp_save);
    fclose(fp_save);
    FILE *fpall_save = fopen("allSave", "ab");
    fwrite(p.player_name, sizeof(p.player_name), 1, fpall_save);
    fwrite(&p.people, sizeof(int), 1, fpall_save);
    fwrite(&p.court, sizeof(int), 1, fpall_save);
    fwrite(&p.found, sizeof(int), 1, fpall_save);
}

void ranking() {
    struct player_ranking arp[100];
    FILE *fpread_all_save = fopen("allSave", "rb");
    int i = 0;
    while (!feof(fpread_all_save)) {
        fread(&arp[i], sizeof(arp[0]), 1, fpread_all_save);
        i++;
    }
    puts("\n if you want sort them by total point press 1 \n");
    puts("\n if you want sort them by people point press 2 \n");
    puts("\n if you want sort them by court point press 3 \n");
    puts("\n if you want sort them by found point press 4 \n");
    clear();
    char choise;
    scanf("%c", &choise);
    clear();
    switch (choise) {

        case '1' : {
            struct player_ranking temp;
            for (int t = 0; t < i; t++) {
                for (int j = t + 1; j < i; j++) {
                    if ((arp[t].found) + (arp[t].people) + (arp[t].court) >
                        (arp[j].found) + (arp[j].people) + (arp[j].court)) {
                        temp = arp[t];
                        arp[t] = arp[j];
                        arp[j] = temp;
                    }

                }
            }
            for (int p = 0; p < i; p++) {
                int w = 0;
                for (int t = p + 1; t < i; t++) {
                    if (strcmp(arp[p].player_namae, arp[t].player_namae) == 0)
                        w = 1;
                }
                if (w == 0)
                    printf(" \n %s  :%d \n ", arp[p].player_namae, (arp[p].people) + (arp[p].court) + (arp[p].found));

            }
            break;
        }
        case '2': {

            struct player_ranking temp;
            for (int t = 0; t < i; t++) {
                for (int j = t + 1; j < i; j++) {
                    if ((arp[t].people) < (arp[j].people)) {
                        temp = arp[t];
                        arp[t] = arp[j];
                        arp[j] = temp;

                    } else if ((arp[t].people) == (arp[j].people)) {

                        if ((arp[t].court) < (arp[j].court)) {
                            temp = arp[t];
                            arp[t] = arp[j];
                            arp[j] = temp;
                        } else if ((arp[t].court) == (arp[j].court)) {
                            if ((arp[t].found) < (arp[j].found)) {
                                temp = arp[t];
                                arp[t] = arp[j];
                                arp[j] = temp;
                            }

                        }
                    }
                }

            }


            for (int p = 0; p < i; p++) {
                int w = 0;
                for (int t = p + 1; t < i; t++) {
                    if (strcmp(arp[p].player_namae, arp[t].player_namae) == 0)
                        w = 1;
                }
                if (w == 0)
                    printf(" \n %s  :%d \n ", arp[p].player_namae, (arp[p].people));


            }
            break;
        }
    }

}

void playGame(struct problems_node **list, int *problem_number, struct player *p) {
    int number_of_total_problem = 0;

    struct problems_node *current;
    while (1) {
        srand(time(NULL));
        current = (*list);
        int random = rand() % (*problem_number);
        for (int i = 0; i < random; i++) {
            if (current->next == NULL)
                current = (*list);
            if ((*list)->next != NULL)
                current = current->next;
        }

        printf("\n problem id: %d \n", current->problem_id);
        print(*current);
        printf(" \n problem counter: %d \n", current->problem_counter);

        char answer;
        clear();
        scanf("%c", &answer);
        if (answer != '1' && answer != '2') {
            printf("\n you entered false input \n");
            printf("\n if you want finish the game press q \n");
            printf("\n  if you want continue press 1 or 2 \n");
            exit_game();
            if (exit_game() == 'q') {
                printf(" \n people: %d \n court: %d \n found: %d \n", people, court, found);
                p->condition = 1;
                // save_game(*p);
                printf("\n you leave the game \n");
                printf("\n do you want save the game (y/n) \n");
                char save_game_char;
                clear();
                scanf("%c", &save_game_char);
                if (save_game_char == 'y')
                    save_game(*p);
                return;
            } else {
                clear();
                scanf("%c", &answer);
            }

        } else if (answer == '2') {
            people += current->efpeople2;
            people = make_it_correct(people);
            p->people = people;
            court += current->efcourt2;
            court = make_it_correct(court);
            p->court = court;
            found += current->effound2;
            found = make_it_correct(found);
            p->found = found;
        } else if (answer == '1') {
            people += current->efpeople1;
            people = make_it_correct(people);
            p->people = people;
            court += current->efcourt1;
            court = make_it_correct(court);
            p->court = court;
            found += current->effound1;
            found = make_it_correct(found);
            p->found = found;
        }
        current->problem_counter--;
        p->probelity_of_problems[current->problem_id]--;


        printf("%d\n%d\n%d\n", people, court, found);

        check_linked_listed(list, problem_number);
        if ((*problem_number) == 0) {
            (*list) = read_problems(problem_number);
            for (int i = 0; i < (*problem_number); i++)
                p->probelity_of_problems[i] = 3;
            counter = 0;
        }
        if (!check_parametrs()) {
            p->condition = 0;
            printf("\n do you want save the game (y/n) \n");
            char save_game_char;
            clear();
            scanf("%c", &save_game_char);
            if (save_game_char == 'y')
                save_game(*p);
            return;

        }
        number_of_total_problem++;
        printf("\n number of total problem : %d", number_of_total_problem);

    }

}

int main() {
    // struct player p;
    //struct player *pp;
    puts("\t\t\t\t\t\t\t\t\t\t\twelcome to your kingdom\n");


    struct player p;
    struct player *pp = &p;
    int problem_number;
    int *pproblem_number = &problem_number;
    struct problems_node *list = read_problems(pproblem_number);
    struct problems_node *current;
    for (int i = 0; i < (*pproblem_number); i++) {
        p.probelity_of_problems[i] = 3;
    }
    puts("\n please enter your profile name \n");
    gets(p.player_name);

    puts("if you want start a new game press 1");
    puts("if you want continue your game press 2 ");
    puts("if you want ranking press 3 ");

    char make_decision;
    scanf("%c", &make_decision);
    switch (make_decision) {

        case '1': {
            for (int i = 0; i < (*pproblem_number); i++) {
                printf("\n question %dth probability is: %d", (i + 1), p.probelity_of_problems[i]);
            }
            printf("\n people= 50 \n court= 50 \n found= 50 \n");
            playGame(&list, pproblem_number, pp);
            print_player(p);
            break;
        }
        case '2': {
            FILE *load = fopen(p.player_name, "rb");
            if (load == NULL) {
                printf("sorry king there is not any save by this profile name");
                break;
            }


            fread(p.player_name, sizeof(p.player_name), 1, load);
            fread(&p.condition, sizeof(p.condition), 1, load);
            if (p.condition == 0) {
                p.people = 50;
                p.found = 50;
                p.court = 50;
            } else {
                fread(p.probelity_of_problems, sizeof(p.probelity_of_problems), 1, load);
                fread(&p.people, sizeof(int), 1, load);
                fread(&p.court, sizeof(int), 1, load);
                fread(&p.found, sizeof(int), 1, load);
                int i = 0;
                for (current = list; current != NULL; i++, current = current->next) {
                    current->problem_counter = p.probelity_of_problems[i];
                }
                check_linked_listed(&list, pproblem_number);
                people = p.people;
                court = p.court;
                found = p.found;
            }
            print_player(p);
            playGame(&list, pproblem_number, pp);
            print_player(p);
            break;

        }
        default:
            ranking();


    }

    return 0;
}