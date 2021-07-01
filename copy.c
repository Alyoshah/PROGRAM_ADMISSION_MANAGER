#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
// - [x]PRINT OUT WHO GO ACCEPTED TO WHAT PROGRAM
// TODO:AUTO ACCEPT APPLICATIONS kinda works~
// TODO:SET FLAG FOR APPLICATION ACCEPTED
// TODO:COUNT MF ACCEPTED INTO PROGRAMS
// - [x] SEPERATE MENU FOR APPLYING AND ADMINS
// - [x] write to file
// - [x] read from file
// - [x] read individual file info

// Program Admission Manager

FILE *file;
FILE *file_count;

void read_file(FILE *file);
void write_file(FILE *file);
void detailed_view(FILE *file, FILE *file_count);
void create_limits();
void accept(FILE *file, FILE *file_count, int app_id);
void program_acceptance_details(FILE *file);

#define APP struct Form             // alias form as app
#define p_lim struct program_limits // alias for program acceptance limits

// structs
struct Birth // birth info
{
    int year;  // birth year
    int month; // birth month
    int day;   // birth day
};

struct app_date // save application date
{
    int year;  // application year
    int month; // application month
    int day;   // application day
};

struct Subjects // subject info
{

    int grade;      // subject grade
    char sname[50]; // subject name
};

struct Program_application_status // programs available
{
    int cs, cs_approval; // computer science
    int it, it_approval; // information technology
    int is, is_approval; // information systems
};

struct Form // application form
{
    int id;           // application id
    char name[20];    // applicant name
    char address[30]; // applicant address
    int sub_count;    // subject count
    int age;          // applicant age
    int status;       // applicant application status
    char gender[20];  // applicant gender M F

    struct Program_application_status pstat; // program selection struct
    struct Birth dob;                        // dob struct
    struct app_date app;                     // save the date applied
    struct Subjects subs[50];                // sub struct array to store subjects and grade
};
// acceptance limit

struct program_limits
{
    int cs_lim;                                // CS MAX APPLICATIONS
    int it_lim;                                // IT MAX APPLICATIONS
    int is_lim;                                // IS MAX APPLICATIONS
    int cs_accepted, it_accepted, is_accepted; // accepted to program of not
    int csgen_f, csgen_m;                      // mf count
    int itgen_f, itgen_m;
    int isgen_f, isgen_m;
};

// main
int main()
{
    system("COLOR 2"); // set console color

    int choice;
    FILE *file;
    FILE *file_count;

    if ((file = fopen("DB.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file = fopen("DB.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
            return 0;
        }
    }

    if ((file_count = fopen("LIMITS.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file_count = fopen("LIMITS.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
        }
    }
    while (1)
    {
        // main loop
        system("CLS");

        while (1)
        {

            // main menu loop
            printf("\n+==================================================+");
            printf("\n| DEPARTMENT OF COMPUTER SCIENCE                   |");
            printf("\n+==================================================+");
            printf("\n| ADMISSIONS MANAGER                               |");
            printf("\n+--------------------------------------------------+");
            printf("\n");
            printf("\n+--------------------------------------------------+");
            printf("\n| MENU                                             |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 1.APPLY                                          |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 2.ADMIN MENU                                     |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 3.EXIT THE PROGRAM                               |");
            printf("\n+--------------------------------------------------+");

            printf("\n\nChoice : ");
            scanf("%d", &choice);
            fflush(stdin);

            if (choice == 1)
            {
                write_file(file);
                break;
            }
            else if (choice == 2)
            {
                break;
            }

            else if (choice == 3)
            {
                return 0;
            }

            else
            {
                continue;
            }
        }

        while (1)
        {
            system("CLS");
            // admin menu loop
            printf("\n+==================================================+");
            printf("\n| DEPARTMENT OF COMPUTER SCIENCE                   |");
            printf("\n+==================================================+");
            printf("\n| ADMISSIONS MANAGER                               |");
            printf("\n+--------------------------------------------------+");
            printf("\n");
            printf("\n+--------------------------------------------------+");
            printf("\n| MENU                                             |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 1.READ ALL ENTRIES                               |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 2.VIEW AND PROCESS APPLICATIONS BY ID            |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 3.VIEW ACCEPTED ALLICANTS BY PROGRAM             |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 4.RETURN TO MAIN MENU                            |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 5.EXIT                                           |");
            printf("\n+--------------------------------------------------+");
            printf("\n| 6.SET PROGRAM APPLICATION LIMITS                 |");
            printf("\n+--------------------------------------------------+");

            printf("\n\nChoice : ");
            scanf("%d", &choice);
            fflush(stdin);

            if (choice == 1)
            {
                read_file(file);
            }
            else if (choice == 2)
            {
                detailed_view(file, file_count);
            }
            else if (choice == 6)
            {
                create_limits();
            }
            else if (choice == 4)
            {
                break;
            }
            else if (choice == 5)
            {
                return 0;
            }
            else if (choice == 3)
            {
                program_acceptance_details(file);
            }

            else
            {
                continue;
            }
        }
    }
    return 0;
}

// write data to file

void write_file(FILE *file)
{
    system("cls");

    int m, d, y;
    int i;

    APP a; // FORM -> APP -> A

    rewind(file);

    int tmpid = 100;

    while (fread(&a, sizeof(a), 1, file) == 1) // create an applicant id

    {
        if (a.id > 100)
        {
            tmpid++; // count how many ids are found
        }
    }

    int id = tmpid + 1; // increment id

    fseek(file, 0, SEEK_END); // goto END of file

    //time y m d
    time_t currentTime;
    time(&currentTime);

    struct tm *myTime = localtime(&currentTime); // time struct

    m = myTime->tm_mon + 1; // months count from 0,so we add 1
    d = myTime->tm_mday;
    y = myTime->tm_year + 1900; // time starts from 1900

    a.id = id; // APPLICANT ID = ID

    printf("\n+==================================================+");
    printf("\n| FORM                                             |");
    printf("\n+==================================================+");

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

    // set date in form
    a.app.year = y, a.app.month = m, a.app.day = d;
    //set age
    a.age = (int)a.app.year - a.dob.year;

    for (i = 0; i < a.sub_count; i++)
    {

        printf("\n %d.SUBJECT NAME : ", i + 1);
        scanf("%[^\n]s", &a.subs[i].sname); // tmp // need to use somthing else instead of scanf
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
    scanf("%d", &a.pstat.cs);
    fflush(stdin);

    printf("\n APPLY FOR IT :");
    scanf("%d", &a.pstat.it);
    fflush(stdin);

    printf("\n APPLY FOR IS :");
    scanf("%d", &a.pstat.is);
    fflush(stdin);

    // set status on application
    if (a.pstat.cs == 1 || a.pstat.it == 1 || a.pstat.is == 1)
    {
        a.status = 1;
    }
    else if (a.pstat.cs == 0 && a.pstat.it == 0 && a.pstat.is == 0)
    {
        a.status = 0;
    }
    a.pstat.cs_approval = 0, a.pstat.it_approval = 0, a.pstat.is_approval = 0;
    fwrite(&a, sizeof(a), 1, file); // write info to file

    if (fwrite != 0)
    { // print message if file written or not

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
    system("cls");
    char a_status[20];
    APP a;

    system("CLS");
    fseek(file, 0, SEEK_SET); // READ FROM THE TOP OF THE FILE

    printf("+================================================================================================================================================+\n");
    printf("|ID   NAME               DATE OF BIRTH       AGE                 GENDER              NO.SUBJECTS         STATUS              DATE APPLIED        |\n");
    printf("+================================================================================================================================================+");

    // printf("\n");

    while (fread(&a, sizeof(a), 1, file) == 1)

    { //insert logic to set status
        // printf("\nSTATUS:%d", a.status);

        switch (a.status)
        {
        case 0:
            strcpy(a_status, "ERROR");
            break;
        case 1:
            strcpy(a_status, "PENDING");
            break;

        case 2:
            strcpy(a_status, "ACCEPTED");
            break;
        case 3:
            strcpy(a_status, "DENIED");
            break;

        default:
            break;
        }

        // convert date to strings
        char a_date[20];
        char b_date[20];

        sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
        sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);

        printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a_status, a_date);
        printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
    }

    printf("\n\n");
    system("pause");
}

// view detailed info on one person
void detailed_view(FILE *file, FILE *file_count)
{
    system("cls");
    char status[3][20];
    int found, i;
    int srch_id;
    int appid;
    int chce;
    APP a;

    while (1)
    {

        printf("\n+==================================================+");
        printf("\n| SEARCH                                           |");
        printf("\n+==================================================+");
        printf("\n\nEnter ID : ");
        scanf("%d", &srch_id);
        fflush(stdin);

        rewind(file);

        while (fread(&a, sizeof(a), 1, file) == 1)
        {

            int pid = a.id;

            if (pid == srch_id) //  CHECK IF SEARCH MATCHES ANY IDS IN THE FILE
            {

                found = 1; // BREAK OUT OF SEARCH LOOP IF ID IS FOUND
                break;
            }
        }

        if (found == 1)
        {

            char b_date[20];
            sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);

            printf("\n+==================================================+");
            printf("\n| INFORMATION                                      |");
            printf("\n+==================================================+");
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
            //checking the approval status of each program
            char status_check[3][20];
            char approval_status[3][20];
            // switch to set string

            ///////////
            switch (a.pstat.cs)

            {
            case 0:
                strcpy(status_check[0], "NOT APPLIED");

            case 1:
                strcpy(status_check[0], "APPLIED");

                break;

            default:
                break;
            }
            /////////
            switch (a.pstat.it)
            {
            case 0:
                strcpy(status_check[1], "NOT APPLIED");
                break;
            case 1:
                strcpy(status_check[1], "APPLIED");

                break;

            default:
                break;
            }
            /////////
            switch (a.pstat.is)
            {

            case 0:
                strcpy(status_check[2], "NOT APPLIED");
                break;

            case 1:
                strcpy(status_check[2], "APPLIED");

                break;

            default:
                break;
            }
            ////////////////////////////////////////////////////////

            switch (a.pstat.cs_approval)
            {
            case 0:
                strcpy(approval_status[0], "PENDING");
                break;

            case 1:
                strcpy(approval_status[0], "ACCEPTED");
                break;
            case 2:
                strcpy(approval_status[0], "DENIED");
                break;

            case 3:
                strcpy(approval_status[0], "");
                break;

            default:
                break;
            }

            /////
            switch (a.pstat.it_approval)
            {
            case 1:
                strcpy(approval_status[1], "ACCEPTED");
                break;
            case 2:
                strcpy(approval_status[1], "DENIED");
                break;
            case 0:
                strcpy(approval_status[1], "PENDING");
                break;
            case 3:
                strcpy(approval_status[1], "");
                break;

            default:
                break;
            }

            //////
            switch (a.pstat.is_approval)
            {
            case 1:
                strcpy(approval_status[2], "ACCEPTED");
                break;
            case 2:
                strcpy(approval_status[2], "DENIED");
                break;
            case 0:
                strcpy(approval_status[2], "PENDING");
                break;
            case 3:
                strcpy(approval_status[2], "");
                break;

            default:
                break;
            }

            printf("\n");
            printf("\n+==================================================================+");
            printf("\n| PROGRAM       PROGRAM APPLICATION       APPLICATION STATUS       |");
            printf("\n+==================================================================+");
            printf("\n| CS            %-20s      %-20s     |", status_check[0], approval_status[0]);
            printf("\n+------------------------------------------------------------------+");
            printf("\n| IT            %-20s      %-20s     |", status_check[1], approval_status[1]);
            printf("\n+------------------------------------------------------------------+");
            printf("\n| IS            %-20s      %-20s     |", status_check[2], approval_status[2]);
            printf("\n+------------------------------------------------------------------+");
            printf("\n\n");

            if (a.pstat.cs_approval != 0 || a.pstat.it_approval != 0 || a.pstat.is_approval != 0)
            {
                printf("\n+--------------------------------------------------+");
                printf("\n| OPTIONS                                          |");
                printf("\n+--------------------------------------------------+");
                printf("\n| 1. RETURN TO MAIN MENU                           |");
                printf("\n+--------------------------------------------------+");

                do
                {
                    printf("\nCHOICE : ");

                } while (scanf("%d", &chce) != 1 || chce < 1 || chce > 2);

                if (chce == 1)
                {

                    break;
                }
            }
            else
            {
                printf("\n+--------------------------------------------------+");
                printf("\n| OPTIONS                                          |");
                printf("\n+--------------------------------------------------+");
                printf("\n| 1. AUTOMATICALLY ACCEPT APPLICATION              |");
                printf("\n+--------------------------------------------------+");
                printf("\n| 2. RETURN TO MAIN MENU                           |");
                printf("\n+--------------------------------------------------+");

                do
                {
                    printf("\nCHOICE : ");

                } while (scanf("%d", &chce) != 1 || chce < 1 || chce > 2);
                if (chce == 1)
                {
                    accept(file, file_count, a.id);
                    break;
                }
                else if (chce == 2)
                {
                    break;
                }
            }
        }

        else
        {
            printf("\n+--------------------------------------------------+");
            printf("\n| ERROR NO APPLICANT FOUND FOR THAT ID             |");
            printf("\n+--------------------------------------------------+");
        }

        printf("\n\n\n");
        system("pause");

        break;
    }
}

void accept(FILE *file, FILE *file_count, int app_id)
{
    // printf("AID=%d", app_id);
    if ((file_count = fopen("LIMITS.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file_count = fopen("LIMITS.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
        }
    }
    p_lim pl;
    APP a;
    int start_processing;
    int cs, it, is;
    int s = sizeof(a); //size of struct
    int p = sizeof(pl);

    fread(&pl, sizeof(pl), 1, file_count); // read limit file
    rewind(file);
    rewind(file_count);

    // printf("\n%d %d %d", cs, it, is);

    while (fread(&a, sizeof(a), 1, file) == 1)
    {

        if (a.id == app_id)
        {
            start_processing = 1; // same as when reading the file , if id is found do what has to be done

            break;
        }
    }
    // APPLICATION ACCEPTANCE
    if (start_processing == 1) // process data

    {
        fseek(file, -s, SEEK_CUR); // set file position to the block of data with applicant info

        char math[20] = "math";   // string to search for math
        char english[20] = "eng"; // string to search for english
        char sub[20];             // copy applicant subject names temp here to check for a match
        char *check1, *check2;    // pointers for string comparison

        int math_pass = 0;  // changes to 1 if math is found with a passed grade
        int eng_pass = 0;   // changes to 1 if eng is found with a passed grade
        int pass_count = 0; // counts how many subjects the application has that are between grades 1-3
        int req_met;        // requirements met == 1 when subjects >5 pass >5 + eng and math
        int applied_to_all; // true if applicant applied to all programs

        for (int i = 0; i < a.sub_count; i++)

        {

            strcpy(sub, a.subs[i].sname); // copy applicant sub name to var for comparison

            //printf("\nin file:%s", sub);

            for (int j = 0; sub[j]; j++)
            {
                sub[j] = tolower(sub[j]); // make subject name lower case to compare it
                // printf("\nconverted:%s", sub);
            }

            check1 = strstr(sub, math);
            if (check1 && (a.subs[i].grade >= 1 && a.subs[i].grade <= 3)) // CHECK IF MATHS IS FOUND AND GRADE IS 1-3 and set math_pass to 1
            {
                // printf("\nFOUND %s GRADE :%d", math, a.subs[i].grade);
                math_pass = 1;
            }

            check2 = strstr(sub, english); // make subject name lower case to compare it

            if (check2 && (a.subs[i].grade >= 1 && a.subs[i].grade <= 3)) // CHECK IF ENGLISH IS FOUND AND GRADE IS 1-3 and set eng_pass to 1
            {
                // printf("\nFOUND %s GRADE :%d", english, a.subs[i].grade);
                eng_pass = 1;
            }

            if (a.subs[i].grade >= 1 && a.subs[i].grade <= 3)
            {
                pass_count++;
            }
        }
        // printf("\nMATH %d", math_pass);
        // printf("\nENG %d", eng_pass);
        //printf("\nPassCount:%d", pass_count);

        ///////////////////////////////////////////////////////////////////////////////////////////////
        //// ACCEPTANCE
        ///////////////////////////////////////////////////////////////////////////////////////////////
        // NO PROGRAM CAN ACCEPT MORE THAN 20

        if (a.sub_count < 5 || a.age < 16) // DECLINE IF LESS THAN 5 SUBS
        {
            a.status = 3;
            if (a.pstat.cs == 1)
            {
                a.pstat.cs_approval = 2;
            }
            else
            {
                a.pstat.cs_approval = 3;
            }
            if (a.pstat.it = 1)
            {
                a.pstat.it_approval = 2;
            }
            else
            {
                a.pstat.it_approval = 3;
            }
            if (a.pstat.is = 1)
            {
                a.pstat.is_approval = 2;
            }
            else
            {
                a.pstat.is_approval = 3;
            }
        }

        if (a.pstat.cs == 1 && a.pstat.it == 1 && a.pstat.is == 1)
        // set if the applicant applied to all
        {
            applied_to_all = 1;
        }

        if (a.pstat.cs == 0 && a.pstat.it == 0 && a.pstat.is == 0) // IF THEY FAILED TO SELECT A PROGRAM TO APPLY FOR
        {
            a.status = 0;
        }

        //check if all basic requirements are met to get accepted into all programs
        if (pass_count >= 5 && math_pass == 1 && eng_pass == 1 && a.age >= 16) // requirements for all three programs
        {
            req_met = 1;
        }

        // set status here if requiremenets are met
        if (req_met == 1 && (pl.cs_accepted < pl.cs_lim) && a.pstat.cs == 1)
        {
            a.status = 2;
            pl.cs_accepted++;
            a.pstat.cs_approval = 1;

            if (strcmp(a.gender, "m") == 0 || strcmp(a.gender, "M") == 0)
            {
                pl.csgen_m++;
            }
            if (strcmp(a.gender, "f") == 0 || strcmp(a.gender, "F") == 0)
            {
                pl.csgen_f++;
            }
        }
        if (req_met == 1 && (pl.it_accepted < pl.it_lim) && a.pstat.it == 1)
        {
            a.status = 2;
            pl.it_accepted++;
            a.pstat.it_approval = 1;

            if (strcmp(a.gender, "m") == 0 || strcmp(a.gender, "M") == 0)
            {
                pl.itgen_m++;
            }
            if (strcmp(a.gender, "f") == 0 || strcmp(a.gender, "F") == 0)
            {
                pl.itgen_f++;
            }
        }
        if (req_met == 1 && (pl.is_accepted < pl.is_lim) && a.pstat.is == 1)
        {
            a.status = 2;
            pl.is_accepted++;
            a.pstat.is_approval = 1;

            if (strcmp(a.gender, "m") == 0 || strcmp(a.gender, "M") == 0)
            {
                pl.isgen_m++;
            }
            if (strcmp(a.gender, "f") == 0 || strcmp(a.gender, "F") == 0)
            {
                pl.isgen_f++;
            }
        }
        //printf("\nCS - %d\nIT - %d\nIS - %d", cs_can_accept, it_can_accept, is_can_accept);

        //////////////////////////////////////////////////////////////////////

        fseek(file_count, -p, SEEK_CUR);

        //////////////////////////////////////////////////////////////////////

        //printf("\nSubcount:%d", a.sub_count);

        ////////////////////////////////////////////////////////////////

        fwrite(&a, sizeof(a), 1, file); // write info to file

        fwrite(&pl, sizeof(pl), 1, file_count);
        fclose(file_count);

        if (fwrite != 0)
        { // print message if file written or not

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
}

// func to set program limits
void create_limits()

{
    if ((file_count = fopen("LIMITS.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((file_count = fopen("LIMITS.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
        }
    }
    p_lim pl;
    int plsiz = sizeof(pl);
    fread(&pl, sizeof(pl), 1, file_count); // read limit file

    printf("\nCSLIM %d \nITLIM %d \nISLIM %d ", pl.cs_lim, pl.it_lim, pl.is_lim);
    printf("\nCS ACCPTED %d \nIT ACCEPTED %d\nIS ACCEPTED %d", pl.cs_accepted, pl.it_accepted, pl.it_accepted);
    printf("\ncsm:%d\ncsf:%d\nitm:%d\nitf%d\nism:%d\nisf:%d", pl.csgen_m, pl.csgen_f, pl.itgen_m, pl.itgen_f, pl.isgen_m, pl.isgen_f);

    fseek(file_count, -plsiz, SEEK_CUR);

    printf("\nENTER ACCEPTANCE LIMIT FOR CS:");
    scanf("%d", &pl.cs_lim);

    printf("\nENTER ACCEPTANCE LIMIT FOR IT:");
    scanf("%d", &pl.it_lim);

    printf("\nENTER ACCEPTANCE LIMIT FOR IS:");
    scanf("%d", &pl.is_lim);
    int ch;
    printf("\n1.RESET APPLICATION COUNT:");
    scanf("%d", &ch);

    if (ch == 1)
    {
        pl.csgen_f = 0;
        pl.csgen_m = 0;

        pl.itgen_f = 0;
        pl.itgen_m = 0;

        pl.isgen_f = 0;
        pl.isgen_m = 0;

        pl.cs_accepted = 0;
        pl.is_accepted = 0;
        pl.it_accepted = 0;
    }

    fwrite(&pl, sizeof(pl), 1, file_count);
    fclose(file_count);
}
// print who got accepted to the prorams
void program_acceptance_details(FILE *file)

{
    system("CLS");
    while (1)
    {
        int ch;
        printf("\n");
        printf("\n+--------------------------------------------------+");
        printf("\n| MENU                                             |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 1.VIEW APPROVED CS APPLICANTS                    |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 2.VIEW APPROVED IT APPLICANTS                    |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 3.VIEW APPROVED IS APPLICANTS                    |");
        printf("\n+--------------------------------------------------+");
        printf("\n| 4.EXIT THIS MENU                                 |");
        printf("\n+--------------------------------------------------+");

        printf("\nCHOICE : ");
        scanf("%d", &ch);
        if (ch == 4)
        {
            break;
        }

        char a_status[20];
        APP a;

        fseek(file, 0, SEEK_SET); // READ FROM THE TOP OF THE FILE

        printf("+================================================================================================================================================+\n");
        if (ch == 1)
        {
            printf("|COMPUTER SCIENCE - APPROVED APPLICANTS                                                                                                          |\n");
        }
        else if (ch == 2)
        {
            printf("|INFORMATION TECHNOLOGY - APPROVED APPLICANTS                                                                                                    |\n");
        }
        else if (ch == 3)
        {
            printf("|INFORMATION SYSTEMS - APPROVED APPLICANTS                                                                                                       |\n");
        }

        printf("+================================================================================================================================================+\n");
        printf("|ID   NAME               DATE OF BIRTH       AGE                 GENDER              NO.SUBJECTS         STATUS              DATE APPLIED        |\n");
        printf("+================================================================================================================================================+");

        while (fread(&a, sizeof(a), 1, file) == 1)

        { //insert logic to set status
            // printf("\nSTATUS:%d", a.status);
            if (ch == 1 && a.pstat.cs == 1 && a.pstat.cs_approval == 1)
            {
                /* code */

                switch (a.status)
                {
                case 0:
                    strcpy(a_status, "ERROR");
                    break;
                case 1:
                    strcpy(a_status, "PENDING");
                    break;

                case 2:
                    strcpy(a_status, "ACCEPTED");
                    break;
                case 3:
                    strcpy(a_status, "DENIED");
                    break;

                default:
                    break;
                }

                // convert date to strings
                char a_date[20];
                char b_date[20];

                sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
                sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
                printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a_status, a_date);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
            }

            if (ch == 2 && a.pstat.it == 1 && a.pstat.it_approval == 1)
            {
                /* code */

                switch (a.status)
                {
                case 0:
                    strcpy(a_status, "ERROR");
                    break;
                case 1:
                    strcpy(a_status, "PENDING");
                    break;

                case 2:
                    strcpy(a_status, "ACCEPTED");
                    break;
                case 3:
                    strcpy(a_status, "DENIED");
                    break;

                default:
                    break;
                }

                // convert date to strings
                char a_date[20];
                char b_date[20];

                sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
                sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
                printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a_status, a_date);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
            }
            if (ch == 3 && a.pstat.is == 1 && a.pstat.is_approval == 1)
            {
                /* code */

                switch (a.status)
                {
                case 0:
                    strcpy(a_status, "ERROR");
                    break;
                case 1:
                    strcpy(a_status, "PENDING");
                    break;

                case 2:
                    strcpy(a_status, "ACCEPTED");
                    break;
                case 3:
                    strcpy(a_status, "DENIED");
                    break;

                default:
                    break;
                }

                // convert date to strings
                char a_date[20];
                char b_date[20];

                sprintf(a_date, "%i-%i-%i", a.app.year, a.app.month, a.app.day);
                sprintf(b_date, "%d-%d-%d", a.dob.year, a.dob.month, a.dob.day);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
                printf("\n|%-5d%-20s%-20s%-19d%-20s%-20d%-20s%-20s|", a.id, a.name, b_date, a.age, a.gender, a.sub_count, a_status, a_date);
                printf("\n+------------------------------------------------------------------------------------------------------------------------------------------------+");
            }
        }
    }
}

// https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fwrite.htm
// https://www.eecis.udel.edu/~sprenkle/cisc105/making_columns.html
// https://fresh2refresh.com/c-programming/c-file-handling/fseek-seek_set-seek_cur-seek_end-functions-c/
// https://www.delftstack.com/howto/c/read-binary-file-in-c/
