/*multithread listtest file, test sycnrhonized list*/

#include <unistd.h>

#include "simulator.h"

List *list;
#define NELEMENTS 5

void printsurvivor(Survivor *s) {
    printf("info: %.25s\n", s->info);
    printf("Location: (%d, %d)\n", s->coord.x, s->coord.y);
}
void printsurvivor_withmsg(Survivor *s, char *msg) {
    char str[256];
    sprintf(str, "msg:%.100s, info: %.25s-location: (%d, %d)\n", 
            msg, s->info, s->coord.x, s->coord.y);
    printf("%.256s", str);
}

/*thread function that adds elements*/
void *add_elements(void *args) {
    printf("\n\nadding elements to the list\n");
    for (int i = 0; i < NELEMENTS; i++) {
        Survivor s;
        sprintf(s.info, "id:%d-aname", i);
        s.coord.x = rand() % 1000;
        s.coord.y = rand() % 100;
        Node *n = list->add(list, &s);
        Survivor *sp = (Survivor *)n->data;
        printsurvivor_withmsg(&s, "added");
    }
}

/*thread function that removes elements*/
void *remove_elements(void *args) {
    printf("\ntest by removing m elements\n");
    Survivor s;

    for (int i = 0; i < NELEMENTS; i++) {
        if (list->pop(list, &s) != NULL) {
            printsurvivor_withmsg(&s, "removed");
        }
    }
}
int init_list() { 
    list = create_list(sizeof(Survivor), NELEMENTS); 
    return 0;
}

int init_threads() { 
    /*TODO: use pthread create init threads */ 
    return 0;
}
int destroy_threads() { /*you can call pthread_cancel to destroy threads*/ }
int main() {
    init_list();
    init_threads();
    
    /*you can run printlist, printsurvivor, printsurvivor_withmsg etc for
     * testing*/
    
    /*fflush(stdout); may be necessary to see immediate out,
    or send the output to a file*/

    /* you can also use Node *npeek = list->peek(list);
     or and sleep() to see printed listed after addition and removals*/
    for (int i = 1; i < NELEMENTS; i++) {
        printlist(list, (void (*)(void *))printsurvivor);
        printf("from tail\n\n");
        printlistfromtail(list, (void (*)(void *))printsurvivor);
        sleep(5); /*print list every x secconds*/
    }

    destroy_threads();
    list->destroy(list);
    printf("Bye Bye\n");
}