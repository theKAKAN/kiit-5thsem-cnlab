#include <stdio.h>
#include <stdlib.h>

struct DOB {
    int day, month, year;
};

struct Student {
    int sno, roll;
    char name[100];
    char gender; // F - Female, M - Male
    struct DOB dob;
    long mobile;
    int phy, chem, math; // Marks
};

struct Student* input(int i){
    struct Student* temp = (struct Student*)malloc( sizeof(struct Student*) );
    temp->sno = i+1;
    printf("Enter roll, name, gender(M/F), mobile no, phy, chem, math marks: \n");
    scanf("%d %s %c %ld %d %d %d", 
            &temp->roll, 
            temp->name, 
            &temp->gender, 
            &temp->mobile,
            &temp->phy,
            &temp->chem,
            &temp->math );
    printf("Enter DOB: " );
    scanf("%d %d %d", &temp->dob.day, &temp->dob.month, &temp->dob.year);
    return temp;
}

void display(struct Student** stud, int n){
    printf("\nPrinting stud info: \n");
    printf("\tSno.\tRoll\tName\tGender\tD. O. B.\tMobile\tPhy\tChem\tMath\n");
    for( int i = 0; i < n; i++ ){
        struct Student* temp = stud[i];
        printf("\t%03d\t%d\t%s\t%c\t%2d/%02d/%2d\t%ld\t%d\t%d\t%d\n", 
                temp->sno, temp->roll, 
                temp->name, temp->gender, 
                temp->dob.day, temp->dob.month, temp->dob.year,
                temp->mobile,
                temp->phy, temp->chem, temp->math );
    }
}

// M for male, F for female
void displayByGender(struct Student** stud, int n, char gender){
    printf("\nPrinting stud info for gender %c: \n", gender);
    printf("\tSno.\tRoll\tName\tGender\tD. O. B.\tMobile\tPhy\tChem\tMath\n");
    for( int i = 0; i < n; i++ ){
        struct Student* temp = stud[i];
        if( temp->gender != gender )
            continue;
        
        // If it's the correct gender, print
        printf("\t%03d\t%d\t%s\t%c\t%2d/%02d/%2d\t%ld\t%d\t%d\t%d\n", 
                temp->sno, temp->roll, 
                temp->name, temp->gender, 
                temp->dob.day, temp->dob.month, temp->dob.year,
                temp->mobile,
                temp->phy, temp->chem, temp->math );
    }
}

// Function to swap two students
void swap(struct Student **a, struct Student **b) {
    struct Student *temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort the array of students based on the sum of marks
void sortByMarksSum(struct Student* arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int sum1 = arr[j]->phy + arr[j]->chem + arr[j]->math;
            int sum2 = arr[j + 1]->phy + arr[j + 1]->chem + arr[j + 1]->math;
            if (sum1 < sum2) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Display number ending in 042
void displayEnding042(struct Student** stud, int n){
    printf("\nPrinting stud info: \n");
    printf("\tSno.\tRoll\tName\tGender\tD. O. B.\tMobile\tPhy\tChem\tMath\n");
    for( int i = 0; i < n; i++ ){
        struct Student* temp = stud[i];
        // Check if number ends in 042
        if( temp->mobile % 1000 != 42 )
            continue;
        
        printf("\t%03d\t%d\t%s\t%c\t%2d/%02d/%2d\t%ld\t%d\t%d\t%d\n", 
                temp->sno, temp->roll, 
                temp->name, temp->gender, 
                temp->dob.day, temp->dob.month, temp->dob.year,
                temp->mobile,
                temp->phy, temp->chem, temp->math );
    }
}

// Function to find the highest and lowest marks in a chosen subject
void findHighestAndLowestMarks(struct Student* students[], int n, int subjectChoice) {
    int highestMark = 0;
    int lowestMark = 100;
    int currentSubjectMark;

    switch (subjectChoice) {
        case 1:
            for (int i = 0; i < n; i++) {
                currentSubjectMark = students[i]->phy;
                if (currentSubjectMark > highestMark) {
                    highestMark = currentSubjectMark;
                }
                if (currentSubjectMark < lowestMark) {
                    lowestMark = currentSubjectMark;
                }
            }
            break;
        case 2:
            for (int i = 0; i < n; i++) {
                currentSubjectMark = students[i]->chem;
                if (currentSubjectMark > highestMark) {
                    highestMark = currentSubjectMark;
                }
                if (currentSubjectMark < lowestMark) {
                    lowestMark = currentSubjectMark;
                }
            }
            break;
        case 3:
            for (int i = 0; i < n; i++) {
                currentSubjectMark = students[i]->math;
                if (currentSubjectMark > highestMark) {
                    highestMark = currentSubjectMark;
                }
                if (currentSubjectMark < lowestMark) {
                    lowestMark = currentSubjectMark;
                }
            }
            break;
        default:
            printf("Invalid subject choice.\n");
            return;
    }

    printf("\nHighest Mark in the chosen subject: %d\n", highestMark);
    printf("Lowest Mark in the chosen subject: %d\n", lowestMark);
}

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    struct Student* stud[n];
    int choice = 0, i = 0;
    printf("0. Quit\n1. Store student data\n2. Display student data\n");
    printf("3. Display male and female categories separately\n");
    printf("4. Display student data along with %% mark sorted in %% mark\n");
    printf("5. Display the student date having a mobile number ending with 042\n");
    printf("6. Display the highest and lowest mark in any subject as per the user's wish\n");
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch( choice ){
            case 0: /*Silence is golden*/ break;
            case 1: {
                if( i >= n ){
                    printf("Student capacity exceeded.\n");
                    break;
                }
                stud[i] = input(i);
                i++;
                break;
            }
            case 2: 
                display( stud, n ); 
                break;
            case 3: 
                displayByGender( stud, n, 'M' );
                displayByGender( stud, n, 'F' );
                break;
            case 4:
                sortByMarksSum( stud, n );
                display( stud, n );
                break;
            case 5:
                displayEnding042( stud, n );
                break;
            case 6: {
                int subjectChoice;
                printf("\nEnter the subject to find highest and lowest marks:\n");
                printf("1. Physics\n2. Chemistry\n3. Mathematics\n");
                scanf("%d", &subjectChoice);
                findHighestAndLowestMarks(stud, n, subjectChoice);
                break;
            }
            default: 
                printf("Wrong input\n"); 
                break;
        }
    } while( choice != 0 );
    
    return 0;
}