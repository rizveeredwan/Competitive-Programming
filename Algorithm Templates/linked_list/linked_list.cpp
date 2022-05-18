#include <stdio.h>
#include <assert.h>

struct LinkedList {
    int value;
    LinkedList *next=nullptr;
    LinkedList *prev=nullptr;

};

struct LinkedList *head;

struct LinkedList * return_search_node(int sr_value, bool last_node){
    struct LinkedList *current = head;
    while(current != nullptr){
        //printf("value %d \n", current->value);
        if(last_node == true) {
            if(current->next == nullptr) return current;
        }
        else {
            if(current->value == sr_value) return current;
        }
        current = current->next;
    }
    return current;
};

struct LinkedList * create_new_node(int new_value){
    struct LinkedList *elm = new LinkedList();
    elm->value = new_value;
    elm->next = nullptr;
    return elm;
    /*
     (*elm).value = new_value; (*elm).next = nullptr;
    */
};

void insert_func(int new_value, int put_after){
    struct LinkedList *elm = create_new_node(new_value);
    if(put_after == -1) { // insert after head
        if((*head).next == nullptr) { // head->next or (*head).next
            (*elm).prev = head;
            (*head).next = elm;
        }
        else {
            elm->next = head->next;
            elm->prev = head;
            head->next->prev=elm;
            head->next = elm;
        }
    }
    else if(put_after == -2){ // putting in the last
        // (a) to (a -> b)
        struct LinkedList *current = return_search_node(new_value, true);
        assert(current != nullptr);
        elm->prev = current;
        current->next = elm;
    }
    else { // putting in arbitrary places
        // (a -> c) to (a -> b ->c)
        struct LinkedList *current = return_search_node(put_after, false);
        assert(current != nullptr);
        elm->prev = current;
        elm->next = current->next;
        current->next->prev = elm;
        current->next = elm;
    }
}

void delete_func(int value){
    struct LinkedList *current = return_search_node(value, false); // does not have issue for last_node parameter
    if (current->next != nullptr) current->next->prev = current->prev;
    current->prev->next = current->next;
    if(current != nullptr) delete(current);
    return;
}

void replace_func(int old_value, int new_value){
    struct LinkedList *current = return_search_node(old_value, false);
    assert(current != nullptr);
    current->value = new_value;
    return;
}

void print_list(){
    struct LinkedList *current = head;
    printf("\n\nprinting\n");
    while(current != nullptr){
        printf("value = %d\n", current->value);
        current = current->next;
    }
}

int main(void){
    head = new LinkedList();
    (*head).value = -1;
    print_list();

    /* different type of insertion */
    insert_func(10, -1);
    print_list();
    insert_func(30, -1);
    print_list();
    insert_func(20, 30);
    print_list();
    insert_func(50, -2);
    print_list();

    /*deletion*/
    delete_func(20);
    print_list();

    /*replace*/
    replace_func(30, 70);
    print_list();

    return 0;

}
