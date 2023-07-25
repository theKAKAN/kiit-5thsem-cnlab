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

int main(){
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    struct Student* stud[n];
    for( int i = 0; i < n; i++ ){
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
        stud[i] = temp;
    }

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