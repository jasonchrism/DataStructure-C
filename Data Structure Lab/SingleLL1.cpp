#include <stdio.h>
#include <stdlib.h>

// define the data/node
struct Food{
    int price;
    struct Food *next; //address dari next data
}*head = NULL, *tail = NULL;

// function to create the data
struct Food *createFood(int price){
    // Pesen memori sebesar Food* (Memory Allocation)
    // Typecast void* jadi Food*
    struct Food *food = (struct Food*)malloc(sizeof(struct Food*));
    // assign value
    food->price = price; // (*food).price = 30000;
    food->next = NULL;

    return food;
}

void pushHead(int price){
    struct Food *newFood = createFood(price);
    // head == NULL
    if (!head){
        head = tail = newFood;
    } else {
        newFood->next = head; // data baru nunjuk ke head
        head = newFood; // head jadi data baru
    }
    return;
}

void pushTail(int price){
struct Food *newFood = createFood(price);
    // head == NULL
    if (!head){
        head = tail = newFood;
    } else {
        tail->next = newFood; // tail nunjuk ke data yang baru
        tail = newFood; // data yang baru jadi tail
    }
    return;    
}

void pushMid(int price){
    if (!head || price < head->price){
        pushHead(price);
    } else if (price >= tail->price){
        pushTail(price);
    } else {
        struct Food *newFood = createFood(price);
        struct Food *curr = head;

        while (curr->next != NULL && curr->next->price < price){
            curr = curr->next;
        }      
        newFood->next = curr->next; // newFood nunjuk data di curr ke next
        curr->next = newFood;  // curr ke next jadi newFood
        // 1  2   4  5
    }
}

void popHead(){
    if (!head){
        return;
    } else if (head == tail){
        free(head);
        head = tail = NULL;
    } else {
        struct Food *temp = head->next; // calon head barunya (data di sebelah head)
        free(head); // free head / deallocate memori head
        head = temp; // head jadi temp
    }
}

void popTail(){
    if (!head){
        return;
    } else if (head == tail){
        free(head);
        head = tail = NULL;
    } else {
        struct Food *curr = head; 
        while (curr->next != tail){ // jalan sampai satu data sebelum tail
            curr = curr->next;
        }
        free(tail); // deallocate memori tail
        curr->next = NULL; // curr nunjuk null krna tail udh gaada
        tail = curr; // tail jadi curr
    }
}

void popMid(int price){
    if (!head){
        return;
    } else if (price == head->price){
        popHead();
    } else if (price == tail->price){
        popTail();
    } else {
        struct Food *curr = head; 
        while (curr->next != NULL && curr->next->price != price){ // selama data yang mau dicari belum ketemu
            curr = curr->next;
        }
        if (curr->next == NULL || curr->next->price != price){
            printf("Data to be deleted is not found!\n");
        } else {
            struct Food *temp = curr->next->next;
            free(curr->next);
            curr->next = temp;
        }
    }
}

void printFoods(){
    struct Food *curr = head;
    while (curr != NULL){ 
        printf("%d -> ", curr->price);
        curr = curr->next;
    }
    printf("\n");
}



int main(){

    // pushHead(1);
    // pushTail(2);
    // pushTail(3);
    // pushTail(4);
    // pushHead(5);
    // pushHead(6);
    // pushTail(7);

    pushMid(30000);
    pushMid(17000);
    pushMid(28000);
    pushMid(20000);
    pushMid(25000);
    // printFoods();
    // popHead();
    // printFoods();
    // popTail();
    printFoods();
    popMid(28000);
    printFoods();
    popMid(16000);
    printFoods();

}