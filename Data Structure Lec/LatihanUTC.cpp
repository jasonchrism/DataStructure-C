#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char custName[100];
char membName[100];

struct Membership{
    char name[100];
    Membership *left;
    Membership *right;
}*membRoot;

struct Customer{
    char name[55];
    char membership[100];
    Customer *left;
    Customer *right;
}*custRoot;

struct Membership *createMembNode(char membershipName[]){
    struct Membership *temp = (struct Membership*)malloc(sizeof(Membership));
    strcpy(temp->name, membershipName);
    temp->right = temp->left = NULL;
    return temp;
}

struct Customer *createNode(char custName[], char membName[]){
    struct Customer *temp = (struct Customer*)malloc(sizeof(Customer));
    strcpy(temp->name, custName);
    strcpy(temp->membership, membName);
    temp->left = temp->right = NULL;
    return temp;
}

struct Membership *insertMembNode(Membership *curr, Membership *memb){
    if (curr == 0){
        return memb;
    } else if (strcmp(memb->name, curr->name) < 0){
        curr->left = insertMembNode(curr->left, memb);
    } else if (strcmp(memb->name, curr->name) > 0){
        curr->right = insertMembNode(curr->right, memb);
    }
    return curr;
}

struct Customer *insertCustNode(Customer *curr, Customer *cust){
    if (curr == 0){
        return cust;
    } else if (strcmp(cust->name, curr->name) < 0){
        curr->left = insertCustNode(curr->left, cust);
    } else if (strcmp(cust->name, curr->name) > 0){
        curr->right = insertCustNode(curr->right, cust);
    }
    return curr;
}

int searchCust(Customer *curr, char custName[]){
    if (curr == 0){
        return 0;
    }

    if (strcmp(curr->name, custName) == 0){
        return 1;
    }

    if (strcmp(membName, curr->name) < 0){
        return searchCust(curr->left, custName);
    } else {
        return searchCust(curr->right, custName);
    }
}

int searchMemb(Membership *curr, char membName[]){
    if (curr == 0){
        return 0;
    }
    
    if (strcmp(curr->name, membName) == 0){
        return 1;
    }

    if (strcmp(membName, curr->name) < 0){
        return searchMemb(curr->left, membName);
    } else {
        return searchMemb(curr->right, membName);
    }
}

struct Customer *deleteCustomer(Customer *curr, char custName[]){
    if (curr == 0){
        printf("The Root is Empty!\n");
        printf("Press enter to continue..."); getchar();
        return curr;
    } else if (strcmp(custName, curr->name) < 0){
        curr->left = deleteCustomer(curr->left, custName);
    } else if (strcmp(custName, curr->name) > 0){
        curr->right = deleteCustomer(curr->right, custName);
    } else {
        if (curr->left == 0 && curr->right == 0){
            free(curr);
            curr = NULL;
        } else if (curr->left == 0){
            Customer *temp = curr;
            curr = curr->right;
            free(temp);
        } else if (curr->right == 0){
            Customer *temp = curr;
            curr = curr->left;
            free(temp);
        } else {
            Customer *temp = curr->left;
            while (temp->right){
                temp = temp->right;
            }
            strcpy(curr->name, temp->name);
            strcpy(curr->membership, temp->membership);
            curr->left = deleteCustomer(curr->left, temp->name);
        }
    }
    return curr;
}

void infixOrderMemb(Membership *curr){
    if (!curr){
        return;
    }
    infixOrderMemb(curr->left);
    printf("%s -> ", curr->name);
    infixOrderMemb(curr->right);
}

void infixOrderCust(Customer *curr){
    if (!curr){
        printf("null");
        return;
    }
    infixOrderCust(curr->left);
    printf("%s (%s) -> ", curr->name, curr->membership);
    infixOrderCust(curr->right);
}

int main(){
    membRoot = insertMembNode(membRoot, createMembNode("Non Member"));
    membRoot = insertMembNode(membRoot, createMembNode("Bronze"));
    membRoot = insertMembNode(membRoot, createMembNode("Silver"));
    membRoot = insertMembNode(membRoot, createMembNode("Gold"));
    membRoot = insertMembNode(membRoot, createMembNode("Platinum"));
    // infixOrderMemb(membRoot);
    // printf("\n");
    int input;
    int searchCustomer;
    int searchMember;
    char deleteCust[55];
    char updateCust[55];
    char newMemb[100];
    do {
        printf("\nChoose Your Day : \n");
        printf("1. Add New Customer\n");
        printf("2. View Customer\n");
        printf("3. Delete Customer\n");
        printf("4. Update Customer\n");
        printf("0. Exit\n");
        printf(">> ");
        scanf("%d", &input); getchar();
        if (input == 1){
            do {
                printf("Input Your Name : ");
                scanf("%[^\n]", custName); getchar();
            } while (strlen(custName) < 3 || strlen(custName) > 50);

            do {
                printf("Choose Your Membership [case sensitive]: \n");
                printf("1. Non-Member\n");
                printf("2. Bronze\n");
                printf("3. Silver\n");
                printf("4. Gold\n");
                printf("5. Platinum\n");
                printf(">> ");
                scanf("%[^\n]", membName); getchar();
                searchMember = searchMemb(membRoot, membName);
            } while (searchMember != 1);
            custRoot = insertCustNode(custRoot, createNode(custName, membName));
            printf("Customer Membership Added to BST!\n");
        } else if (input == 2){
            infixOrderCust(custRoot);
        } else if (input == 3){
            do {
                printf("Input Customer Name You Want to Delete [case sensitive]: ");
                scanf("%[^\n]", deleteCust); getchar();
                searchCustomer = searchCust(custRoot, deleteCust);
            } while (searchCustomer != 1);
            custRoot = deleteCustomer(custRoot, deleteCust);
        } else if (input == 4){
            do {
                printf("Input Customer Name You Want to Update [case sensitive]: ");
                scanf("%[^\n]", updateCust); getchar();
                searchCustomer = searchCust(custRoot, updateCust);
            } while (searchCustomer != 1);
            do {
                printf("Input New Membership : ");
                scanf("%[^\n]", newMemb); getchar();
                searchMember = searchMemb(membRoot, newMemb);
            } while (searchMember != 1);
            
        }
    } while (input != 0);

}