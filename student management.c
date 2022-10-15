#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student
{
    char name[30];
    char course_name[20];
    int roll;
    float result;
} s;
FILE *fp;
long sz=sizeof(s);

int main()
{
    int choice;
    while(1)
    {
        system("cls");

        printf("Student Management\n");
        printf("1.Add Information\n");
        printf("2.Student Deteails\n");
        printf("3.Search\n");
        printf("4.Modify\n");
        printf("5.Delete Information\n");
        printf("0.Exit\n\n");
        printf("\nEnter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 0:
            exit(0);
        case 1:
            input();
            break;
        case 2:
            display();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            del();
            break;
        }
        getch();



    }


    return 0;
}
void input()
{



    fp = fopen("stud.txt","ab");
    printf("Enter a student name: ");
    fflush(stdin);
    gets(s.name);
    printf("Enter your Department name: ");
    fflush(stdin);
    gets(s.course_name);
    printf("Enter your roll: ");
    scanf("%d",&s.roll);
    printf("Enter your result: ");
    scanf("%f",&s.result);
    fwrite(&s, sz, 1, fp);
    printf("Saved successfull");
    fclose(fp);

}
void display()
{
    system("cls");
    printf("%-30s%-30s%-24s%-24s\n","Name","Department Name","Student ID","Result");
    fp = fopen("stud.txt","rb");
    while(fread(&s,sz,1,fp)==1)
    {
        printf("%-30s%-30s%-24d%-24.2f\n",s.name,s.course_name,s.roll,s.result);
    }
    fclose(fp);
}

void search()
{
    int ch;
    while(1)
    {
        system("cls");

        printf("<===Search==>\n\n");
        printf("1.Search By Roll\n");
        printf("2.Search By Name\n");
        printf("0.Back to Main Menu\n");
        printf("\n\nEnter your Choice");
        scanf("%d",&ch);

        switch(ch)
        {
        case 0:
            main();
            break;
        case 1:
            sbyroll();
            break;
        case 2:
            sbyname();
            break;
        default:
            printf("invalid choice");
        }

    }


}
void sbyroll()
{

    int rl, f=0;
    printf("Enter Your Roll: ");
    scanf("%d",&rl);
    printf("%-30s%-30s%-24s%-24s\n","Name","Department Name","Student ID","Result");
    fp = fopen("stud.txt","rb");
    while(fread(&s,sz,1,fp)==1)
    {
        if(rl==s.roll)
        {
            printf("%-30s%-30s%-24d%-24.2f\n",s.name,s.course_name,s.roll,s.result);
            f=1;
            break;
        }
    }
    fclose(fp);
    if(f==0)
    {
        printf("No records found");

    }

}
void sbyname()
{
    char na[30];
    int f=0;
    printf("Enter Your Name: ");
    fflush(stdin);
    gets(na);
    printf("%-30s%-30s%-24s%-24s\n","Name","Department Name","Student ID","Result");
    fp = fopen("stud.txt","rb");
    while(fread(&s,sz,1,fp)==1)
    {
        if(strcmpi(na,s.name)==0)
        {
            printf("%-30s%-30s%-24d%-24.2f\n",s.name,s.course_name,s.roll,s.result);
            f=1;
            break;
        }
    }
    fclose(fp);
    if(f==0)
    {
        printf("No records found");

    }

}
void modify()
{
    system("cls");

    int rl, f=0;
    printf("Enter Roll Modify: ");
    scanf("%d",&rl);
    fp = fopen("stud.txt","rb+");
    while(fread(&s,sz,1,fp)==1)
    {
        if(rl==s.roll)
        {
            f=1;
            printf("Enter new name: ");
            fflush(stdin);
            gets(s.name);
            printf("Enter new Department name: ");
            fflush(stdin);
            gets(s.course_name);
            printf("Enter new roll: ");
            scanf("%d",&s.roll);
            printf("Enter new result: ");
            scanf("%f",&s.result);
            fseek(fp,-sz,1);
            fwrite(&s, sz, 1, fp);
            fclose(fp);
            break;


        }
    }
    if(f==0)
    {
        printf("No records found");

    }
    else
    {
        printf("record modify successfully");
    }

}
void del()
{

    system("cls");

    int rl, f=0;
    printf("Enter Roll to Delete: ");
    scanf("%d",&rl);
    FILE *ft;
    fp = fopen("stud.txt","rb+");
    ft = fopen("temp.txt","ab");
    while(fread(&s,sz,1,fp)==1)
    {
        if(rl==s.roll)
        {
            f=1;
        }
        else
        {

            fwrite(&s, sz, 1, ft);
        }
    }
    fclose(fp);
    fclose(ft);
    remove("stud.txt");
    rename("temp.txt", "stud.txt");
    if(f==0)
    {
        printf("No records found");

    }
    else
    {
        printf("record deleted successfully");
    }
}

