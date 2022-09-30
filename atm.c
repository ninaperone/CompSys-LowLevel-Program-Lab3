//  atm.c
//  Nina Perone, 9/8/22, CIS2107 sec 002, tul44843
//  Lab 3 "ATM": Write a C Program for an ATM machine by implementing functions (balance, withdrawal, deposit, quit).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printBalance(double balance);
double withdrawal(double withdrawalLimit, double balance);
double deposit(double depositLimit, double balance);
void quit(int transactionNum);

int main( void ) {
    printf("Welcome to the ATM\n");
    int pin;
    double balance = 5000;
    double withdrawalLimit = 0;
    double depositLimit = 0;
    int transactionNum = 0;
    int attempts = 0;
    
    // enter pin
    while(attempts < 3) {
        printf("\tEnter PIN #: ");
        scanf("%d", &pin);
        if(pin == 3014) {
            break;
        }
        else{
            attempts++;
            if(attempts == 3) {
                printf("\nInvalid PIN # entered too many times.\nAccess denied.");
                exit(0);
            }
        }
    }
    
    // atm menu
    while(pin == 3014) {
        printf("\nATM Transaction Types: ");
        printf("\n\t1. Balance.");
        printf("\n\t2. Cash withdrawal.");
        printf("\n\t3. Cash deposition.");
        printf("\n\t4. Quit.\n");
        
        // select transaction
        int transactionType;
        printf("\nEnter transaction type #: ");
        scanf("%d", &transactionType);
        
        // perform transaction
        if(transactionType == 1) {
            printBalance(balance);
        }
        else if(transactionType == 2) {
            double amount = withdrawal(withdrawalLimit, balance);
            withdrawalLimit += amount;
            balance -= amount;
            transactionNum++;
        }
        else if(transactionType == 3) {
            double amount = deposit(depositLimit, balance);
            depositLimit += amount;
            balance += amount;
            transactionNum++;
        }
        else if(transactionType == 4) {
            quit(transactionNum);
            exit(0);
        }
    }
    
}




//functions

// balance
void printBalance(double balance) {
    printf("\tYour balance is: $%.2lf\n", balance);
}

double withdrawal(double withdrawalLimit, double balance) {
    double withdrawalAmount;
    int attempts = 0;
    while(attempts < 3) {
        printf("\n\tEnter withdrawal amount: ");
        scanf("%lf", &withdrawalAmount);
        if(withdrawalAmount < 20 || (int)withdrawalAmount % 20 != 0) {
            attempts++;
            if(attempts == 3) {
                printf("\nError: Invalid withdrawal amount entered too many times.");
                exit(1);
            }
            printf("\n\tInvalid withdrawal amount.\n\tPlease try again.\n");
        }
        else if(withdrawalLimit + withdrawalAmount > 1000) {
            printf("\nCannot perform transaction as withdrawal exceeds limit.\n");
            withdrawalAmount = 0;
            break;
        }
        else {
            // receipt
            printf("\n\tWould you like a receipt? Yes(1) or No(2): ");
            int receipt;
            scanf("%d", &receipt);
            if(receipt == 1) {
                printf("\n\tReceipt printing...\n");
            }
            break;
        }
    }
    
    return withdrawalAmount;
}


// make sure doesnt take change
double deposit(double depositLimit, double balance) {
    double depositAmount;
    double intPart;
    int attempts = 0;
    while(attempts < 3) {
        printf("\n\tEnter deposit amount: ");
        scanf("%lf", &depositAmount);
        if(depositAmount < 1 || modf(depositAmount ,  &intPart) > 0) {
            attempts++;
            if(attempts == 3) {
                printf("\nError: Invalid deposit amount entered too many times.");
                exit(1);
            }
            printf("\n\tInvalid deposit amount.\n\tPlease try again.\n");
        }
        else if(depositLimit + depositAmount > 10000) {
            printf("\nCannot perform transaction as deposit exceeds limit.\n");
            depositAmount = 0;
            break;
        }
        else {
            // receipt
            printf("\n\tWould you like a receipt? Yes(1) or No(2): ");
            int receipt;
            scanf("%d", &receipt);
            if(receipt == 1) {
                printf("\n\tReceipt printing...\n");
            }
            break;
        }
    }
    
    return depositAmount;
}

void quit(int transactionNum) {
    printf("\tNumber of transactions: %d\n", transactionNum);
    printf("\nThank you for using the ATM!");
}
