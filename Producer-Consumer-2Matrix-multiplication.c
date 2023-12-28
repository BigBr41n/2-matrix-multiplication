#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define MIN_ROWS_COLS 3
#define MAX_ROWS_COLS 6
#define MAX_VALUE 9
#define BUFFER_SIZE 10 



// i definde a new type to aviod any data confilt in the product phase ; 
typedef struct IndexesOfThreadsDate {
    int row;
    int column;
    int data;
} IndexesOfThreadsDate;




// semaphores of producer consumer logic 
sem_t full, empty, mutex;


//Mat_Brows_Acolumns ? we know in the product of 2 matrix we should have a shar>
int MatA_Rows, MatB_Columns, Mat_Brows_Acolumns;



int matrixA[MAX_ROWS_COLS][MAX_ROWS_COLS]; // matrix A 
int matrixB[MAX_ROWS_COLS][MAX_ROWS_COLS]; // matrix B 
int matrixResult[MAX_ROWS_COLS][MAX_ROWS_COLS]; // the result matrix :  A * B 




int ip = 0, ic = 0; // those are the indexes ip for the producer deplacement
IndexesOfThreadsDate buffer[BUFFER_SIZE]; // i made the buffer of new type that has to data inside it to avoid any data confilt in the product phase also when we put of take data from the buffer 




/*
here we have the generate method which generate 
random numbers of rows and colums for both matrix a and b 

also generate the shared row and columns between the tow matrix ; 
*/ 


void generate() {
    srand(time(NULL));

    MatA_Rows = rand() % (MAX_ROWS_COLS - MIN_ROWS_COLS + 1) + MIN_ROWS_COLS; // random number for rows between 3 ,6 ; 
    MatB_Columns = rand() % (MAX_ROWS_COLS - MIN_ROWS_COLS + 1) + MIN_ROWS_COLS; // random number for columns 
    Mat_Brows_Acolumns = rand() % (MAX_ROWS_COLS - MIN_ROWS_COLS + 1) + MIN_ROWS_COLS;  //random number and same number for both A columns and B rows 

    for (int i = 0; i < MatA_Rows; ++i) {
        for (int j = 0; j < Mat_Brows_Acolumns; ++j) {
            matrixA[i][j] = rand() % (MAX_VALUE + 1);
        }
    }

    for (int i = 0; i < Mat_Brows_Acolumns; ++i) {
        for (int j = 0; j < MatB_Columns; ++j) {
            matrixB[i][j] = rand() % (MAX_VALUE + 1);
        }
    } 
    
    
    
    // printing phase i just made it to make the program more clear 

    printf("the Matrix A : \n") ; 
    for (int i = 0; i < MatA_Rows; ++i) {
        for (int j = 0; j < Mat_Brows_Acolumns; ++j) {
            printf("%d\t" , matrixA[i][j] ) ; 
        }
        printf("\n");
    }
    
    
    
    printf("=======================================================\n the Matrix B : \n") ; 
    for (int i = 0; i < Mat_Brows_Acolumns; ++i) {
        for (int j = 0; j < MatB_Columns; ++j) {
            printf("%d\t" , matrixB[i][j] ) ; 
        }
        printf("\n");
    } 
    
    
    printf("\n\n\n");
    
}








//  producer function that take parameter of which row and column should operates the product on ; 
void *producer(void *arg) {
    IndexesOfThreadsDate *args = (IndexesOfThreadsDate *)arg;

    args->data = 0;
    for (int i = 0; i < Mat_Brows_Acolumns; i++) {
        args->data += matrixA[args->row][i] * matrixB[i][args->column];
    }

    sem_wait(&empty);
    sem_wait(&mutex);

    buffer[ip] = *args;
    ip = (ip + 1) % BUFFER_SIZE;

    sem_post(&full);
    sem_post(&mutex);
}





// the consumer function and its own logic
void *consumer(void *arg) {
    
    
    for (int i = 0; i < MatA_Rows * MatB_Columns; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        matrixResult[buffer[ic].row][buffer[ic].column] = buffer[ic].data;
        ic = (ic + 1) % BUFFER_SIZE;

        sem_post(&empty);
        sem_post(&mutex);
    }
} 





//printing the result matrix ;
void printTheResultMatrix() {
    
    
    printf("The result is : \n\n"); 
    for (int i = 0; i < MatA_Rows; i++) {
        for (int j = 0; j < MatB_Columns; j++) {
            printf("%d\t", matrixResult[i][j]);
        }
        printf("\n");
    }
}
 
 
 
 
 
 
int main() {
    
    
    
    generate(); //generate the two matrix A , B 
    

    int resultMatSize = MatA_Rows * MatB_Columns;  // how many element will be in the matrix of result ; 
    IndexesOfThreadsDate vector[resultMatSize];
    
    
    
    //initialize our semaphores ; 
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    
    
    //creating the threads identifiers 
    pthread_t producers[resultMatSize];
    pthread_t consumers; 
    
    
    // indexes to presise where to put data to avoid any type of error in the matrix 
    int rowsOfMatrix_A = 0;
    int columnsOfMatrix_B = 0;
    
    
    
    // fill the indexes in the vector 
    for (int i = 0; i < resultMatSize; i++) {
        vector[i].row = rowsOfMatrix_A;
        vector[i].column = columnsOfMatrix_B;

        columnsOfMatrix_B++;

        if (columnsOfMatrix_B == MatB_Columns) {
            columnsOfMatrix_B = 0;
            rowsOfMatrix_A++;
        }
    }
    
    
    
    //creating threades of producer to do the product ; 
    for (int i = 0; i < resultMatSize; i++) {
        pthread_create(&producers[i], NULL, &producer, (void *)&vector[i]);
    }
    
    
    
    // thread of consumers ; 
    pthread_create(&consumers, NULL, &consumer, NULL);




    //waiting to finish the work 
    for (int i = 0; i < resultMatSize; i++) {
        pthread_join(producers[i], NULL);
    }

    pthread_join(consumers, NULL);
    
    
    
    
    //calling to print the result  ; 
    printTheResultMatrix();

    return 0;
}
