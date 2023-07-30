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
void display_by_gender(struct Student** stud, int n, char gender){
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
                display_by_gender( stud, n, 'M' );
                display_by_gender( stud, n, 'F' );
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default: 
                printf("Wrong input\n"); 
                break;
        }
    } while( choice != 0 );

    
}