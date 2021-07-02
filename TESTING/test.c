#include <stdio.h>
#include <stdlib.h>

#define num struct numbers
#define ww struct wow
struct numbers
{
    int num1;
    int num2;
    int sum;
};

struct wow
{
    int ab;
    int bc;
};

void func(FILE *f, FILE *f2);
void sum(FILE *f);
void print_file(FILE *f, FILE *f2);

int main()
{
    FILE *f;
    FILE *f2;

    if ((f = fopen("test.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((f = fopen("test.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
            return 0;
        }
    }
    if ((f2 = fopen("test2.bin", "rb+")) == NULL) // create file if it doesn't exists or throw an error if it can't be created
    {
        if ((f2 = fopen("test2.bin", "wb+")) == NULL)
        {
            printf("\nFILE ERROR");
            return 0;
        }
    }

    func(f, f2);
    sum(f);
    print_file(f, f2);

    return 0;
}

void func(FILE *f, FILE *f2)
{
    num n;
    ww w;
    rewind(f);
    rewind(f2);

    printf("\n1.enter NUM1:");
    scanf("%d", &n.num1);
    fflush(stdin);

    printf("\n1.enter NUM2:");
    scanf("%d", &n.num2);
    fflush(stdin);

    printf("\nENTER A:");
    scanf("%d", &w.ab);
    fflush(stdin);

    printf("\nENTER B:");
    scanf("%d", &w.bc);
    fflush(stdin);

    fwrite(&n, sizeof(n), 1, f);
    if (fwrite != 0)
    {
        printf("\nworked");
    }

    fwrite(&w, sizeof(w), 1, f2);
    if (fwrite != 0)
    {
        printf("\nworked");
    }
}

void print_file(FILE *f, FILE *f2)
{
    rewind(f);
    rewind(f2);
    num n;
    ww w;

    fread(&w, sizeof(w), 1, f2); // must read file

    printf("\nNum 1:%d", n.num1);
    printf("\nNum2:%d", n.num2);
    printf("\nsum: %d", n.sum);

    printf("\nA:%d", w.ab);

    printf("\nB:%d", w.bc);

    printf("\n\n");

    system("pause");
}

void sum(FILE *f)
{
    rewind(f);
    num n;
    n.sum = n.num1 + n.num2;
    fwrite(&n, sizeof(n), 1, f);
}