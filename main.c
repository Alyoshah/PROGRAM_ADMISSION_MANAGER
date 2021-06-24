#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// TODO:-[]AUTO ACCEPT APPLICATIONS
// - [x] write to file
// - [x] read from file
// - [x] read individual file info

// Program Admission Manager
FILE *file;
FILE *file_count;

void read_file(FILE *file);
void write_file(FILE *file);
void detailed_view(FILE *file);
void auto_accept(FILE *file, FILE *file_count);

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

struct application_status
{

    char cs[20];
    char it[20];
    char is[20];
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

    struct application_status app_stat;
    struct Program pgm;       // program selection struct
    struct Birth dob;         // dob struct
    struct app_date app;      // save the date applied
    struct Subjects subs[50]; // sub struct array to store subjects and grade
};

// main
int main()
{

    int choice;

    FILE *file;

    if ((file = fopen("DB.bin", "rb+")) == NULL) //create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file = fopen("DB.bin", "wb+")) == NULL)
        {
            printf("\n\t\tERROR CREATING FILE!!");
            return 0;
        }
    }

    // system("CLS");

    while (1)
    {

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

        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:

            write_file(file);
            break;

        case 2:

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

void write_file(FILE *file)
{

    int m, d, y;
    int i;

    APP a;

    rewind(file);

    int tmpid = 100;

    while (fread(&a, sizeof(a), 1, file) == 1) // create an applicant id

    {
        if (a.id > 100)
        {
            tmpid++; // count how many ids are found
        }
    }

    int id = tmpid + 1;

    fseek(file, 0, SEEK_END); // goto END of file

    //time y m d
    time_t currentTime;
    time(&currentTime);

    struct tm *myTime = localtime(&currentTime);

    m = myTime->tm_mon + 1; // months count from 0,so we add 1
    d = myTime->tm_mday;
    y = myTime->tm_year + 1900; // time starts from 1900

    a.id = id;

    printf("\n+--------------------------------------------------+");
    printf("\n| FORM                                             |");
    printf("\n+--------------------------------------------------+");

    printf("\n ENTER NAME : ");
    fgets(a.name, 20, stdin);
    fflush(stdin);
    a.name[strlen(a.name) - 1] = '\0'; // remove new line from buffer

    printf("\n ENTER ADDRESS : ");
    fgets(a.address, 50, stdin);
    fflush(stdin);
    a.address[strlen(a.address) - 1] = '\0'; // remove new line from buffer

    printf("\n ENTER GENDER : ");
    scanf("%c", &a.gender);
    fflush(stdin);

    // loop while user enters wrong or dates that are out of range
    do
    {
        printf("\n ENTER BIRTH YEAR : ");

    } while (scanf("%d", &a.dob.year) != 1 || a.dob.year < 1000 || a.dob.year > 3000);
    fflush(stdin);

    do
    {
        printf("\n ENTER BIRTH MONTH : ");
    } while (scanf("%d", &a.dob.month) != 1 || a.dob.month < 0 || a.dob.month > 12);
    fflush(stdin);

    do
    {
        printf("\n ENTER BIRTH DAY : ");
    } while (scanf("%d", &a.dob.day) != 1 || a.dob.day < 0 || a.dob.day > 31);
    fflush(stdin);

    printf("\n ENTER SUBJECT COUNT : ");
    scanf("%d", &a.sub_count);
    fflush(stdin);

    //set date in form
    a.app.year = y, a.app.month = m, a.app.day = d;
    //set age
    a.age = (int)a.app.year - a.dob.year;

    //SET STATUS
    strcpy(a.status, "PENDING");

    for (i = 0; i < a.sub_count; i++)
    {

        printf("\n %d.SUBJECT NAME : ", i + 1);
        scanf("%[^\n]s", &a.subs[i].sname); // tmp// need to use somthing else instead of scanf
        fflush(stdin);

        do
        {
            printf("\n %d.ENTER GRADE : ", i + 1);
        } while (scanf("%d", &a.subs[i].grade) != 1 || a.subs[i].grade < 1 || a.subs[i].grade > 6);
        fflush(stdin);
    }

    printf("\n");
    printf(" SELECT PROGRAMS TO APPLY FOR\n");
    printf(" ENTER 1 FOR YES AND 0 FOR NO\n");

    printf("\n APPLY FOR CS :");
    scanf("%d", &a.pgm.cs);
    fflush(stdin);

    printf("\n APPLY FOR IT :");
    scanf("%d", &a.pgm.it);
    fflush(stdin);

    printf("\n APPLY FOR IS :");
    scanf("%d", &a.pgm.is);
    fflush(stdin);

    if (a.pgm.cs == 1)

    {
        strcpy(a.app_stat.cs, "PENDING APPROVAL");
    }
    else
    {
        strcpy(a.app_stat.cs, "NOT APPLIED");
    }

    if (a.pgm.it == 1)

    {
        strcpy(a.app_stat.it, "PENDING APPROVAL");
    }
    else
    {
        strcpy(a.app_stat.it, "NOT APPLIED");
    }

    if (a.pgm.is == 1)

    {
        strcpy(a.app_stat.is, "PENDING APPROVAL");
    }
    else
    {
        strcpy(a.app_stat.is, "NOT APPLIED");
    }

    fwrite(&a, sizeof(a), 1, file); //write info to file

    if (fwrite != 0)
    { //print message if file written or not

        printf("\n+--------------------------------------------------+");
        printf("\n| DONE                                             |");
        printf("\n+--------------------------------------------------+");
    }
    else
    {
        printf("\n+--------------------------------------------------+");
        printf("\n| ERROR                                            |");
        printf("\n+--------------------------------------------------+");
    }
}

// read data from file
void read_file(FILE *file)
{

    APP a;

    system("CLS");
    fseek(file, 0, SEEK_SET);

    printf("+------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|ID   NAME               DATE OF BIRTH       AGE                 GENDER              NO.SUBJECTS         STATUS              DATE APPLIED        |\n");
    printf("+------------------------------------------------------------------------------------------------------------------------------------------------+");

    //printf("\n");

    while (fread(&a, sizeof(a), 1, file) == 1)

    {

        //convert date to strings
        char a_date[20];
        char b_date[20];

        sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
        sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);

        printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a.status, a_date);
        printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
    }

    printf("\n\n");
    system("pause");
}

//view detailed info on one person
void detailed_view(FILE *file)
{

    int found, i;
    int srch_id;
    APP a;

    while (1)
    {

        printf("\n+--------------------------------------------------+");
        printf("\n| SEARCH                                           |");
        printf("\n+--------------------------------------------------+");
        printf("\n\nEnter ID : ");
        scanf("%d", &srch_id);
        fflush(stdin);

        rewind(file);

        while (fread(&a, sizeof(a), 1, file) == 1)
        {

            int pid = a.id;

            if (pid == srch_id)
            {

                found = 1;
                break;
            }
        }

        if (found == 1)
        {

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

            for (i = 0; i < a.sub_count; i++)
            {

                printf("\n| %-20s    %1d                        |", a.subs[i].sname, a.subs[i].grade);
                printf("\n+--------------------------------------------------+");
            }

            printf("\n");
            printf("\n+--------------------------------------------------+");
            printf("\n| PROGRAM                 APPLICATION STATUS       |");
            printf("\n+--------------------------------------------------+");
            printf("\n| CS                      %-20s     |", a.app_stat.cs);
            printf("\n+--------------------------------------------------+");
            printf("\n| IT                      %-20s     |", a.app_stat.it);
            printf("\n+--------------------------------------------------+");
            printf("\n| IS                      %-20s     |", a.app_stat.is);
            printf("\n+--------------------------------------------------+");
        }
        else
        {
            printf("\n+--------------------------------------------------+");
            printf("\n| ERROR NO APPLICANT FOUND FOR THAT ID             |");
            printf("\n+--------------------------------------------------+");
        }

        int ach;

        // while (1) // testing

        // {
        //     printf("\n");
        //     printf("\n");
        //     printf("\n+--------------------------------------------------+");
        //     printf("\n| APPLICATION PROCESSING MENU                      |");
        //     printf("\n+--------------------------------------------------+");
        //     printf("\n| 1:AUTOMATICALLY ACCEPT INTO APPROPRIATE PROGRAM  |");
        //     printf("\n+--------------------------------------------------+");
        //     printf("\n| 2.EXIT                                           |");
        //     printf("\n+--------------------------------------------------+");

        //     do
        //     {
        //         printf("\nCHOICE : ");

        //     } while (scanf("%d", &ach) != 1 || ach < 0 || ach > 2);
        //     fflush(stdin);

        //     switch (ach)
        //     {
        //     case 1:
        //         printf("\naccepted\n");
        //         break;

        //     case 2:
        //         break;

        //     default:
        //         break;
        //     }
        //     //system("pause");
        //     break;
        // }

        printf("\n\n\n");
        system("pause");

        break;
    }
}

void auto_accept(FILE *file, FILE *file_count)
{

    printf("WORKING"); // need to think about this later
}

// https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
// https://www.eecis.udel.edu/~sprenkle/cisc105/making_columns.html