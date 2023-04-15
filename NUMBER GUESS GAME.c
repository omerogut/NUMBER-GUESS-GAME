#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct Node{
  int data;
  struct Node *next;
};


void append(struct Node** head_ref, int new_data){
    /* 1. allocate node */
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;  /* used in step 5*/
  
    /* 2. put in the data  */
    new_node->data  = new_data;
 
    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    } 
      
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
  
    /* 6. Change the next of last node */
    last->next = new_node;
    return;   
}

/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}


void bubbleSort(struct Node *start)
{
    int swapped, i;
    struct Node *ptr1;
    struct Node *lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
  

void printList(struct Node* node)
{
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}


int Pow(int a, int b){ // returns a^b
    int result = 1;
int i;
    for ( i = 0; i < b; i++)
        result = result * a;

    return result;
}

int getRandomNumber(int digitCount){
    int randomNumber = 0;
    int digits[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int randomIndex;

    srand(time(NULL));

    randomIndex = (rand() % 9) + 1;
    randomNumber = digits[randomIndex] * Pow(10,digitCount-1);
    digits[randomIndex] = -1;
int i;
    for (i = (digitCount - 2); i >= 0; i--){
        while (1){
            randomIndex = (rand() % 10);
            if (digits[randomIndex] != -1){
                randomNumber = randomNumber + (digits[randomIndex] * Pow(10, i));
                digits[randomIndex] = -1;
            
                break;
            }
       }
    }
    return randomNumber;
}



int main(void){
    printf("==================================\n");
    printf("========NUMBER GUESS GAME=========\n");
    printf("==================================\n");
    
    // kullanicidan basamak sayisini aliyoruz
    int digitCount;
    printf("Enter the number of digits for the game 4-10: ");
    scanf("%d", &digitCount);

    // random sayimizi uretiyoruz
    int randomNumber = getRandomNumber(digitCount);

    // karsilastirmasi kolay olsun diye random sayimizin string halini uretiyoruz
    char randomNumberStringVersion[digitCount]; 
    sprintf(randomNumberStringVersion, "%d", randomNumber); 

    
// basamaklarin dogruluklarini kontrol eden degiskenleri tanimliyoruz
    int correctLocation = 0;
    int wrongLocation = 0;

    

    // kullanicinin girecegi sayiyi string turunde tutuyoruz ki basamak karsilastirma islemini kolayca yapalim
    int userGuess;
    char userGuessStringVersion[digitCount];

    // girilen tahminleri tutacagimiz adresleri isaret edecek pointer
    struct Node* startAddress = (struct Node*) malloc(sizeof(struct Node));

    // girilen tahmin sayisini tutacak degisken
    int guessCount = 0;
    while (1){

        // kullanicidan tahminini aliyoruz
        printf("Enter a guess: ");
        scanf("%d", &userGuess);
        guessCount = guessCount + 1;
        append(&startAddress, userGuess);

        sprintf(userGuessStringVersion, "%d", userGuess); 

int i, j;
        for ( i = 0; i < digitCount; i++){
            for ( j = 0; j < digitCount; j++){
                if (randomNumberStringVersion[i] == userGuessStringVersion[j]){
                    if(i == j)
                        correctLocation = correctLocation + 1;
                    else
                        wrongLocation = wrongLocation + 1;
                }
            }
        }

        printf("+%d-%d\n", correctLocation, wrongLocation);
        

        if (correctLocation == digitCount){
            printf("Congratz you won the game\n");
            break;
        }

        correctLocation = 0;
        wrongLocation = 0;

        
        

    }

    printf("total number of tries:%d\n", guessCount);
    printf("all guesses from smallest to largest:\n");

    bubbleSort(startAddress);
    printList(startAddress);
    

    
    return 0;   
}
