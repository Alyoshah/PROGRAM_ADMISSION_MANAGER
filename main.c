#include <stdio.h>

#include <string.h>

#include <time.h>

#include <stdlib.h>


// TODO:
// - [x] write to file
// - [x] read from file
// - [x] read individual file info
// - []AUTO ACCEPT APPLICATIONS 

// Program Admission Manager

FILE * file;
void read_file(FILE * file);
void write_file(FILE * file);
void detailed_view(FILE * file);
void auto_accept(FILE * file);

#define APP struct Form

struct Birth // birth info
{
    int year;
    int month;
    int day;
};

struct app_date // save application date
{
    int year;
    int month;
    int day;
};

struct Subjects // subject info
{

    int grade;
    char sname[50];
};

struct Program // programs available
{
    int cs;
    int it;
    int is;
};

struct Form // application form
{
    int id;
    char name[20];
    char address[30];
    int sub_count;
    int age;
    char status[10];
    char gender[20];
    
    struct Program pgm; // program selection struct
    struct Birth dob; // dob struct
    struct app_date app; // save the date applied
    struct Subjects subs[50]; // sub struct array to store subjects and grade

};

// main 
int main()

{

    int choice;

    FILE * file;

    if ((file = fopen("DB.bin", "rb+")) == NULL) //create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file = fopen("DB.bin", "wb+")) == NULL) {
            printf("\n\t\tERROR CREATING FILE!!");
            return 0;
        }
    }

    // system("CLS");

    while (1) {

        // main menu loop
        printf("\n+--------------------------------------------------+");
        printf("\n| DEPARTMENT OF COMPUTER SCIENCE                   |");
        printf("\n+--------------------------------------------------+");
        printf("\n| ADMISSIONS MANAGER                               |");
        printf("\n+--------------------------------------------------+");
        printf("\n\n");
        printf("\n+--------------------------------------------------+");
        printf("\n| MENU                                             |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 1.APPLY                                          |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 2.READ ALL ENTRIES                               |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 3.VIEW DETAILED INFO ON A SINGLE ENTRY           |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 4.EXIT                                           |");
        printf("\n+--------------------------------------------------+");
        printf("\n\nChoice : ");

        scanf("%d", & choice);
        fflush(stdin);

        switch (choice) {
        case 1:
            system("CLS");
            write_file(file);
            break;

        case 2:
            system("CLS");
            read_file(file);
            break;

        case 3:

            detailed_view(file);
            break;

        case 4:
            fclose(file);
            return 0;
            break;

        default:
            break;
        }

    }

    return 0;
}

//write data to file
void write_file(FILE * file) {

    int m, d, y;
    int i;
    APP a;

    srand(time(NULL));
    int id = rand() % 999; 
    // not the greatest way to generate an id 
    // a proper way would be to save every number generated and compare the news to the old ones 
    // and generate another if it matches
    // to ensure every number is unique
    
    

    fseek(file, 0, SEEK_END); // goto END of file

    //time y m d
    time_t currentTime;
    time( & currentTime);

    struct tm * myTime = localtime( & currentTime);

    m = myTime -> tm_mon + 1; //months count from 1
    d = myTime -> tm_mday;
    y = myTime -> tm_year + 1900; //time starts from 1900

    a.id = id;

    printf("\nENTER NAME:");
    fgets(a.name, 20, stdin);
    fflush(stdin);
    a.name[strlen(a.name) - 1] = '\0'; // remove new line from buffer

    printf("\nENTER ADDRESS:");
    fgets(a.address, 50, stdin);
    fflush(stdin);
    a.address[strlen(a.address) - 1] = '\0'; // remove new line from buffer

    printf("\nENTER GENDER:");
    scanf("%c", & a.gender);
    fflush(stdin);

    printf("\nENTER BIRTH YEAR:");
    scanf("%d", & a.dob.year);
    fflush(stdin);

    printf("\nENTER BIRTH MONTH:");
    scanf("%d", & a.dob.month);
    fflush(stdin);

    printf("\nENTER BIRTH DAY:");
    scanf("%d", & a.dob.day);
    fflush(stdin);

    printf("\nENTER SUBJECT COUNT:");
    scanf("%d", & a.sub_count);
    fflush(stdin);

    //set date in form
    a.app.year = y, a.app.month = m, a.app.day = d;
    //set age
    a.age = (int) a.app.year - a.dob.year;

    //SET STATUS
    strcpy(a.status, "PENDING");

    for (i = 0; i < a.sub_count; i++) {

        printf("\n%d.SUBJECT NAME:", i + 1);
        scanf("%[^\n]s", & a.subs[i].sname); // tmp// need to use somthing else instead of scanf        
        fflush(stdin);

        printf("\n%d.ENTER GRADE:", i + 1);
        scanf("%d", & a.subs[i].grade);
        fflush(stdin);

    }

    printf("\n");
    printf("SELECT PROGRAMS TO APPLY FOR\n");
    printf("ENTER 1 FOR YES AND 0 FOR NO\n");

    printf("\nAPPLY FOR CS :");
    scanf("%d", & a.pgm.cs);
    fflush(stdin);

    printf("\nAPPLY FOR IT :");
    scanf("%d", & a.pgm.it);
    fflush(stdin);

    printf("\nAPPLY FOR IS :");
    scanf("%d", & a.pgm.is);
    fflush(stdin);

    fwrite( & a, sizeof(a), 1, file); //write info to file

    if (fwrite != 0) { //print message if file written or not

        printf("\n+------------------------------------------------+");
        printf("\n| DONE                                           |");
        printf("\n+------------------------------------------------+");

    } else {
        printf("\n+------------------------------------------------+");
        printf("\n| ERROR                                          |");
        printf("\n+------------------------------------------------+");
    }
}

// read data from file
void read_file(FILE * file) {

    // system("CLS");
    APP a;

    fseek(file, 0, SEEK_SET);

    printf("\n");
    printf("+------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|ID   NAME               DATE OF BIRTH       AGE                 GENDER              NO.SUBJECTS         STATUS              DATE APPLIED        |\n");
    printf("+------------------------------------------------------------------------------------------------------------------------------------------------+");

    while (fread( & a, sizeof(a), 1, file) == 1)

    {

        //convert date to strings
        char a_date[20];
        char b_date[20];

        sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
        sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);

        printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a.status, a_date);
        printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");

    }

    printf("\n");
    system("pause");

}

//view detailed info on one person
void detailed_view(FILE * file) {

    int found, i;
    int srch_id;
    APP a;

    while (1) {

        printf("\n+--------------------------------------------------+");
        printf("\n| SEARCH                                           |");
        printf("\n+--------------------------------------------------+");
        printf("\n\nEnter ID : ");
        scanf("%d", & srch_id);

        fflush(stdin);

        rewind(file);
        while (fread( & a, sizeof(a), 1, file) == 1) {

            int pid = a.id;

            if (pid == srch_id) {

                found = 1;
                break;
            }
        }

        if (found == 1) {

            system("CLS");

            char b_date[20];
            sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);

            printf("\n+--------------------------------------------------+");
            printf("\n| INFORMATION                                      |");
            printf("\n+--------------------------------------------------+");
            printf("\n| NAME : %-20s                      |", a.name);
            printf("\n+--------------------------------------------------+");
            printf("\n| ADDRESS : %-30s         |", a.address);
            printf("\n+--------------------------------------------------+");
            printf("\n| D.O.B : %-20s                     |", b_date);
            printf("\n+--------------------------------------------------+");
            printf("\n| AGE : %-20d                       |", a.age);
            printf("\n+--------------------------------------------------+");
            printf("\n");
            printf("\n+--------------------------------------------------+");
            printf("\n| SUBJECT                 GRADE                    |");
            printf("\n+--------------------------------------------------+");

            for (i = 0; i < a.sub_count; i++) {

                printf("\n| %-20s    %1d                        |", a.subs[i].sname, a.subs[i].grade);
                printf("\n+--------------------------------------------------+");
            }
            printf("\n");
            printf("\n+--------------------------------------------------+");
            printf("\n| PROGRAM                 APPLICATION STATUS       |");
            printf("\n+--------------------------------------------------+");
            printf("\n| CS                                               |");
            printf("\n+--------------------------------------------------+");
            printf("\n| IT                                               |");
            printf("\n+--------------------------------------------------+");
            printf("\n| IS                                               |");
            printf("\n+--------------------------------------------------+");

        } else {
            printf("\n+--------------------------------------------------+");
            printf("\n| ERROR NO APPLICANT FOUND FOR THAT ID             |");
            printf("\n+--------------------------------------------------+");
        }

        printf("\n\n\n");
        system("pause");
        break;
    }
}

void auto_accept(FILE * file) {
    printf("WORKING"); // need to think about this later
}

// https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
// https://www.eecis.udel.edu/~sprenkle/cisc105/making_columns.html