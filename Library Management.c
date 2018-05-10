#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stu_sec();
void book_sec();
void book_is();
void ch_pass();
void see_rec();
void add_rec();
void add2_rec();
void del_rec();
void del2_rec();
void sear_stu();
void see_brec();
void add_brec();
void add2_brec();
void del_brec();
void del2_brec();
void sear_book();
void b_is();
void see_is_b();
void sear_is_b();
void sub_book();
char o_pass[20];

int main()  //TO PRINT WELCOME MESSAGE AND MAIN MENU
{
    system("cls");
    printf("\t\t\t\t\t\t**********************************************************************\n");
    printf("\t\t\t\t\t\t\tWELCOME TO THE LIBRARY MANAGEMENT SYSTEM OF RCCIIT\n");
    printf("\t\t\t\t\t\t**********************************************************************\n\n\n\n");
    printf("\t\t\tPress <1> to go to STUDENT SECTION\n");
    printf("\t\t\tPress <2> to go to BOOK SECTION\n");
    printf("\t\t\tPress <3> to issue book\n");
    printf("\t\t\tPress <4> to change password\n");
    printf("\t\t\tPress <5> to EXIT\n");
    printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tNOTE: Use underscore(_) instead of space\n\n");
	int x;
	do
	{
		scanf("%d",&x);
		switch(x)
		{
			case 1:
				stu_sec();
				break;
			case 2:
				book_sec();
				break;
			case 3:
				book_is();
				break;
            case 4:
                ch_pass();
                break;
			case 5:
				exit(0);
			default:
				printf("Invalid selection");
		}
		getch();
	}
	while(x!=5);
	return 0;
}
//START OF STUDENT SECTION//
void stu_sec()
{
    system("cls");
   printf("\t\t\t\t\t\t\t\t\t**********************\n");
   printf("\t\t\t\t\t\t\t\t\t   STUDENT SECTION\n");
   printf("\t\t\t\t\t\t\t\t\t**********************\n\n\n");
   printf("\t\t\tPress <1> to see student record\n");
   printf("\t\t\tPress <2> to add student record(Password required)\n");
   printf("\t\t\tPress <3> to delete student record(Password required)\n");
   printf("\t\t\tPress <4> to search student\n");
   printf("\t\t\tPress <5> to to go back to main menu\n");
   printf("\t\t\tPress <6> to to exit\n");
   int y;
   do
   {
       printf("\nEnter your choise\n");
       scanf("%d",&y);
       switch(y)
       {
           case 1:
               see_rec();
               break;
           case 2:
               add_rec();
               break;
           case 3:
               del_rec();
               break;
           case 4:
               sear_stu();
               break;
           case 5:
               main();
               break;
           case 6:
               exit(0);
               break;
           default:
               printf("Invalid selection\n");
       }
       fflush(stdin);
   }
   while(y==0);
}
char stu_iname[30];
char stu_iid[20];
void add_rec()  //TO VERIFY PASSWORD BEFORE ADDING STUDENTS
{
    system("cls");
    int x;
    do
        {
            FILE *fp1;
            char pas[20];
            fp1=fopen("password.txt","r");
            if(fscanf(fp1,"%s",o_pass)==EOF)
            {
                printf("\n\n\t\t\t\tNo password set\n\n");
                printf("\t\t\t\tCan't modify data without password\n\n");
                printf("\t\t\t\tPress 1 to change password\n\t\t\t\tPress 2 to go back\n\t\t\t\tPress any no to exit\n");
                int p;
                scanf("%d",&p);
                if(p==1)
                {
                    ch_pass();
                }
                else if(p==2)
                {
                    stu_sec();
                }
                else
                    exit(0);
            }
            fclose(fp1);
            printf("\n\n\t\t\t\tEnter password\n");
            scanf("%s",pas);
            fp1=fopen("password.txt","r");
            while(fscanf(fp1,"%s",o_pass)!=EOF)
                {
                    if(strcmp(pas,o_pass)==0)
                    {
                        add2_rec();
                        x=0;
                    }
                }
        if(x!=0)
            {
                printf("\t\t\t\tWrong password\n\n");
                printf("\t\t\t\tEnter 3 to retry or any key to abort\n");
                scanf("%d",&x);
            }
    }
    while(x==3);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                stu_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void add2_rec()  //TO ADD STUDENTS
{
    int a;
    do{
    system("cls");
    FILE *fp;
    char stu_name[30],stu_id[20];
    int p=1;
    printf("\n\n\t\t\t\tEnter Student Name\n");
    scanf("%s",stu_name);
    fflush(stdin);
    printf("\n\n\t\t\t\tEnter Student ID\n");
    scanf("%s",stu_id);
    fflush(stdin);
    fp=fopen("record.txt","r");
    while(fscanf(fp,"%s %s",stu_iname,stu_iid)!=EOF)
        {
            if(strcmp(stu_id,stu_iid)==0)
                {
                    p=0;
                    printf("\n\t\t\t\tID already used\n");
                }
        }
    fclose(fp);
    if(p!=0)
        {
            fp=fopen("record.txt","a");
            fprintf(fp,"%s %s\n",stu_name,stu_id);
            printf("\n\t\t\t\tRecord added succesfully\n");
        }
    fclose(fp);
    printf("\nPress 1 to continue with this section or any other no to abort\n");
    scanf("%d",&a);
    }
    while(a==1);
}
void see_rec()  //TO SEE STUDENT RECORD
{
    system("cls");
    FILE *fp;
    fp=fopen("record.txt","r");
    int found=1;
    printf("\n\t\t\t\t\t\t\t\t\t\tSTUDENTS RECORD\n\n");
    while(fscanf(fp,"%s %s",stu_iname,stu_iid)!=EOF)
    {
        found=0;
        printf("\n\t\t\t\t\t\t\t\t  Student Name:- %s     ID:- %s\n\n\n",stu_iname,stu_iid);
    }
    if(found!=0)
    {
        printf("\n\n\t\t\t\t\t\t\t\tNo records found\n");
    }
    fclose(fp);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                stu_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void del_rec()  //TO VERIFY PASSWORD BEFORE DELETING STUDENT RECORD
{
     system("cls");
    int x;
    do
        {
            FILE *fp1;
            char pas[20];
            fp1=fopen("password.txt","r");
            if(fscanf(fp1,"%s",o_pass)==EOF)
            {
                printf("\n\n\t\t\t\tNo password set\n\n");
                printf("\t\t\t\tCan't modify data without password\n\n");
                printf("\t\t\t\tPress 1 to change password\n\t\t\t\tPress 2 to go back\n\t\t\t\tPress any no to exit\n");
                int p;
                scanf("%d",&p);
                if(p==1)
                {
                    ch_pass();
                }
                else if(p==2)
                {
                    stu_sec();
                }
                else
                    exit(0);
            }
            fclose(fp1);
            printf("\n\n\t\t\t\tEnter password\n");
            scanf("%s",pas);
            fp1=fopen("password.txt","r");
            while(fscanf(fp1,"%s",o_pass)!=EOF)
                {
                    if(strcmp(pas,o_pass)==0)
                    {
                        del2_rec();
                        x=0;
                    }
                }
        if(x!=0)
            {
                printf("\t\t\t\tWrong password\n\n");
                printf("\t\t\t\tEnter 3 to retry or any key to abort\n");
                scanf("%d",&x);
            }
    }
    while(x==3);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                stu_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void del2_rec()  //TO DELETE STUDENTS RECORD
{
    int a;
    do{
    system("cls");
    FILE *fp,*fp1;
    char id[20];
    int p=1,q=1;
    printf("\n\n\t\t\t\tEnter the ID of the student to be removed\n");
    scanf("%s",id);
    fp=fopen("record.txt","r");
    fp1=fopen("temp.txt","a");
    while(fscanf(fp,"%s %s",stu_iname,stu_iid)!=EOF)
    {
        if(strcmp(id,stu_iid)==0)
        {
            printf("\n\t\t\t\tStudent Name:- %s   ID:- %s  Record deleted\n",stu_iname,stu_iid);
            p=0;
        }
        else
        {
            fprintf(fp1,"%s %s\n",stu_iname,stu_iid);
        }
        q=0;
    }
    if(q!=0)
    {
        printf("\n\t\t\t\tRecords are empty\n");
    }
    else if(p!=0)
        {
            printf("\n\t\t\t\tID not found\n");
        }
    fclose(fp);
    fclose(fp1);
    fp=fopen("record.txt","w");
    fclose(fp);
    fp=fopen("record.txt","a");
    fp1=fopen("temp.txt","r");
    while(fscanf(fp1,"%s %s",stu_iname,stu_iid)!=EOF)
    {
        fprintf(fp,"%s %s\n",stu_iname,stu_iid);
    }
    fclose(fp1);
    fclose(fp);
    fp1=fopen("temp.txt","w");
    fclose(fp1);
    printf("\nPress 1 to continue with this section or any other no to abort\n");
    scanf("%d",&a);
    }
    while(a==1);
}
void sear_stu()  //TO SEARCH STUDENTS
{
    system("cls");
    FILE *fp;
    char id[20];
    int p=1,q=1;
    printf("\n\n\t\t\t\tEnter the ID of the student to be searched\n");
    scanf("%s",id);
    fp=fopen("record.txt","r");
    while(fscanf(fp,"%s %s",stu_iname,stu_iid)!=EOF)
    {
        if(strcmp(id,stu_iid)==0)
        {
            printf("\n\t\t\t\tStudent Name:- %s   ID:- %s\n\n",stu_iname,stu_iid);
            p=0;
        }
        q=0;
    }
    if(q!=0)
    {
        printf("\t\t\t\tRecords are empty\n\n");
    }
    else if(p!=0)
        {
            printf("\t\t\t\tID not found\n\n");
        }
    fclose(fp);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                stu_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}//END OF STUDENT SECTION//
//START OF BOOK SECTION//
void book_sec()
{
    system("cls");
   printf("\t\t\t\t\t\t\t\t\t**********************\n");
   printf("\t\t\t\t\t\t\t\t\t   BOOK SECTION\n");
   printf("\t\t\t\t\t\t\t\t\t**********************\n\n\n");
   printf("\t\t\tPress <1> to see book record\n");
   printf("\t\t\tPress <2> to add book record(Password required)\n");
   printf("\t\t\tPress <3> to delete book record(Password required)\n");
   printf("\t\t\tPress <4> to search book\n");
   printf("\t\t\tPress <5> to to go back to main menu\n");
   printf("\t\t\tPress <6> to to exit\n");
   int y;
   do
   {
       printf("\nEnter your choise\n");
       scanf("%d",&y);
       switch(y)
       {
           case 1:
               see_brec();
               break;
           case 2:
               add_brec();
               break;
           case 3:
               del_brec();
               break;
           case 4:
               sear_book();
               break;
           case 5:
               main();
               break;
           case 6:
               exit(0);
               break;
           default:
               printf("Invalid selection\n");
       }
       fflush(stdin);
   }
   while(y==0);
}
char book_iname[50];
char book_iauth[30];
char book_iid[20];
int iqty;
void add_brec() //TO VERIFY PASSWORD BEFORE ADDING BOOKS
{
     system("cls");
    int x;
    do
        {
            FILE *fp1;
            char pas[20];
            fp1=fopen("password.txt","r");
            if(fscanf(fp1,"%s",o_pass)==EOF)
            {
                printf("\n\n\t\t\t\tNo password set\n\n");
                printf("\t\t\t\tCan't modify data without password\n\n");
                printf("\t\t\t\tPress 1 to change password\n\t\t\t\tPress 2 to go back\n\t\t\t\tPress any no to exit\n");
                int p;
                scanf("%d",&p);
                if(p==1)
                {
                    ch_pass();
                }
                else if(p==2)
                {
                    book_sec();
                }
                else
                    exit(0);
            }
            fclose(fp1);
            printf("\n\n\t\t\t\tEnter password\n");
            scanf("%s",pas);
            fp1=fopen("password.txt","r");
            while(fscanf(fp1,"%s",o_pass)!=EOF)
                {
                    if(strcmp(pas,o_pass)==0)
                    {
                        add2_brec();
                        x=0;
                    }
                }
        if(x!=0)
            {
                printf("\t\t\t\tWrong password\n\n");
                printf("\t\t\t\tEnter 3 to retry or any key to abort\n");
                scanf("%d",&x);
            }
    }
    while(x==3);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void add2_brec()  //TO ADD BOOKS
{
    int a;
    do{
    system("cls");
    FILE *fp;
    char book_name[50],book_auth[30],book_id[20];
    int p=1,qty;
    printf("\n\n\t\t\t\tEnter Book Name\n");
    scanf("%s",book_name);
    fflush(stdin);
    printf("\n\n\t\t\t\tEnter Author Name\n");
    scanf("%s",book_auth);
    fflush(stdin);
    printf("\n\n\t\t\t\tEnter Book ID\n");
    scanf("%s",book_id);
    fflush(stdin);
    printf("\n\n\t\t\t\tEnter book quantity\n");
    scanf("%d",&qty);
    fflush(stdin);
    fp=fopen("bookrecord.txt","r");
    while(fscanf(fp,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
    {
        if(strcmp(book_id,book_iid)==0)
        {
            p=0;
            printf("\n\t\t\t\tID already used\n");
        }
    }
    fclose(fp);
    if(p!=0)
    {
        fp=fopen("bookrecord.txt","a");
        fprintf(fp,"%s %s %s %d\n",book_name,book_auth,book_id,qty);
        printf("\n\t\t\t\tRecord added succesfully\n");
    }
    fclose(fp);
    printf("\nPress 1 to continue with this section or any other no to abort\n");
    scanf("%d",&a);
    }
    while(a==1);
}
void see_brec()  //TO SEE BOOK RECORDS
{
    system("cls");
    FILE *fp;
    fp=fopen("bookrecord.txt","r");
    int found=1;
    printf("\n\t\t\t\t\t\t\t\tBOOK RECORDS\n");
    while(fscanf(fp,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
    {
        found=0;
        printf("\n\t\t\t\tBook Name:- %s     Author:- %s     ID:- %s    Quantity:- %d\n\n\n",book_iname,book_iauth,book_iid,iqty);
    }
    if(found!=0)
    {
        printf("\n\n\t\t\t\tNo records found\n");
    }
    fclose(fp);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void del_brec() //TO VERIFY PASSWORD BEFORE DELETING BOOKS
{
     system("cls");
    int x;
    do
        {
            FILE *fp1;
            char pas[20];
            fp1=fopen("password.txt","r");
            if(fscanf(fp1,"%s",o_pass)==EOF)
            {
                printf("\n\n\t\t\t\tNo password set\n\n");
                printf("\t\t\t\tCan't modify data without password\n\n");
                printf("\t\t\t\tPress 1 to change password\n\t\t\t\tPress 2 to go back\n\t\t\t\tPress any no to exit\n");
                int p;
                scanf("%d",&p);
                if(p==1)
                {
                    ch_pass();
                }
                else if(p==2)
                {
                    book_sec();
                }
                else
                    exit(0);
            }
            fclose(fp1);
            printf("\n\n\t\t\t\tEnter password\n");
            scanf("%s",pas);
            fp1=fopen("password.txt","r");
            while(fscanf(fp1,"%s",o_pass)!=EOF)
                {
                    if(strcmp(pas,o_pass)==0)
                    {
                        del2_brec();
                        x=0;
                    }
                }
        if(x!=0)
            {
                printf("\t\t\t\tWrong password\n\n");
                printf("\t\t\t\tEnter 3 to retry or any key to abort\n");
                scanf("%d",&x);
            }
    }
    while(x==3);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void del2_brec()  //TO DELETE BOOKS
{
    int a;
    do{
    system("cls");
    FILE *fp,*fp1;
    char id[20];
    int p=1,q=1;
    printf("\n\n\t\t\t\tEnter the ID of the book to be removed\n");
    scanf("%s",id);
    fp=fopen("bookrecord.txt","r");
    fp1=fopen("booktemp.txt","a");
    while(fscanf(fp,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
    {
        if(strcmp(id,book_iid)==0)
        {
            printf("\n\t\t\t\tBook Name:- %s   Author:- %s   ID:- %s   Quantity:- %d  Record deleted\n",book_iname,book_iauth,book_iid,iqty);
            p=0;
        }
        else
        {
            fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
        }
        q=0;
    }
    if(q!=0)
    {
        printf("\n\t\t\t\tRecords are empty\n");
    }
    else if(p!=0)
        {
            printf("\n\t\t\t\tID not found\n");
        }
    fclose(fp);
    fclose(fp1);
    fp=fopen("bookrecord.txt","w");
    fclose(fp);
    fp=fopen("bookrecord.txt","a");
    fp1=fopen("booktemp.txt","r");
    while(fscanf(fp1,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
    {
        fprintf(fp,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
    }
    fclose(fp1);
    fclose(fp);
    fp1=fopen("booktemp.txt","w");
    fclose(fp1);
    printf("\nPress 1 to continue with this section or any other no to abort\n");
    scanf("%d",&a);
    }
    while(a==1);
}
void sear_book() //TO SEARCH BOOKS
{
    int c;
    do{
    system("cls");
    FILE *fp;
    char id[20];
    int p=1,q=1;
    printf("\n\n\t\t\t\tEnter the ID of the Book to be searched\n");
    scanf("%s",id);
    fp=fopen("bookrecord.txt","r");
    while(fscanf(fp,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
    {
        if(strcmp(id,book_iid)==0)
        {
            printf("\n\t\t\t\tBook Name:- %s   Author:- %s   ID:- %s   Quantity:- %d\n\n",book_iname,book_iauth,book_iid,iqty);
            p=0;
        }
        q=0;
    }
    if(q!=0)
    {
        printf("\t\t\t\tRecords are empty\n\n");
    }
    else if(p!=0)
        {
            printf("\t\t\t\tID not found\n\n");
        }
    fclose(fp);
    printf("\nPress <1> to continue with this section or any no to abort\n");
    scanf("%d",&c);
    }
    while(c==1);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_sec();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}//END OF BOOK SECTION//
//START OF BOOK ISSUE SECTION//
void book_is()
{
    system("cls");
    printf("\n\t\t\t\tPress <1> to issue books\n\t\t\t\tPress <2> to see issued books\n\t\t\t\tPress <3> to see issued books by ID\n\t\t\t\tPress <4> to submit books\n\t\t\t\tPress <5> to back to main menu\n\t\t\t\tPress <0> to exit\n");
    int c;
    do
    {
        printf("Enter your choice\n");
        scanf("%d",&c);
        switch(c)
        {
        case 1:
            b_is();
            break;
        case 2:
            see_is_b();
            break;
        case 3:
            sear_is_b();
            break;
        case 4:
            sub_book();
            break;
        case 5:
            main();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Invalid selection\n");
        }
    }
    while(c!=4);
}
char is_date[11];
void b_is()   //TO ISSUE BOOKS
{
    int a;
    do
    {
    system("cls");
    int p=1,q=1,r=1;
    char stu_id[20],book_id[20];
        FILE *fp,*fp1,*fp2;
        printf("\nEnter student ID\n");
        scanf("%s",stu_id);
        fp=fopen("record.txt","r");
        while(fscanf(fp,"%s %s",stu_iname,stu_iid)!=EOF)
        {
            if(strcmp(stu_id,stu_iid)==0)
            {
                p=0;
            }
        }
        fclose(fp);
        fp1=fopen("booktemp.txt","a");
        fp=fopen("bookrecord.txt","r");
        if(p==0)
        {
            printf("\nEnter book ID\n");
            scanf("%s",book_id);
            //fp=fopen("bookrecord.txt","r");
            //fp1=fopen("booktemp.txt","a");
            while(fscanf(fp,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
            {
                if(strcmp(book_id,book_iid)==0)
                {
                    q=0;
                }
                else
                {
                    fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
                }
            }
            //fclose(fp);
        }
        else
        {
            printf("\nWrong student ID\n");
        }
        fclose(fp);
        fp=fopen("bookissuerecord.txt","r");
        if(q==0)
        {
            //fp=fopen("bookissuerecord.txt","r");
            while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
            {
                if(strcmp(stu_id,stu_iid)==0&&strcmp(book_id,book_iid)==0)
                {
                    printf("\nThis book is already issued to this student ID\n");
                    r=0;
                    fp2=fopen("bookrecord.txt","r");
                    while(fscanf(fp2,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
                    {
                        if(strcmp(book_id,book_iid)==0)
                        {
                            fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
                        }
                    }
                    fclose(fp2);
                }
            }
        }
        else if(p==0&&q!=0)
        {
            printf("\nWrong book ID\n");
        }
        fclose(fp);
        if(q==0&&r!=0&&iqty>0)
        {
            fp=fopen("bookissuerecord.txt","a");
            printf("\nEnter date of issuing\n");
            scanf("%s",is_date);
            fp2=fopen("bookrecord.txt","r");
            while(fscanf(fp2,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
            {
                if(strcmp(book_id,book_iid)==0)
                {
                    fprintf(fp,"%s %s %s ",book_iname,book_iauth,book_iid);
                    printf("\nBook issued\n\n");
                    fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,(iqty-1));
                    //fclose(fp1);
                }
            }
            fclose(fp1);
            fclose(fp2);
            fp2=fopen("record.txt","r");
            while(fscanf(fp2,"%s %s",stu_iname,stu_iid)!=EOF)
            {
                if(strcmp(stu_id,stu_iid)==0)
                {
                    fprintf(fp,"%s %s %s\n",stu_iname,stu_iid,is_date);
                }
            }
            fclose(fp);
            fclose(fp2);
        }
        else if(iqty==0)
        {
            printf("\nNot enough books available\n");
        }
        fclose(fp1);
        fp1=fopen("bookrecord.txt","w");
        fclose(fp1);
        fp=fopen("booktemp.txt","r");
        while(fscanf(fp,"%s %s %s %d\n",book_iname,book_iauth,book_iid,&iqty)!=EOF)
        {
            fp1=fopen("bookrecord.txt","a");
            fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
            fclose(fp1);
        }
        fclose(fp);
        fp=fopen("booktemp.txt","w");
        fclose(fp);
        printf("\nPress 1 to to continue with this section\n");
        scanf("%d",&a);
    }
    while(a==1);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int c;
    do
    {
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                book_is();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(c!=0);
}
void see_is_b()  //TO SEARCH ISSUED BOOKS BY STUDENT ID
{
    system("cls");
    FILE *fp;
    int p=1;
    fp=fopen("bookissuerecord.txt","r");
    while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
    {
        p=0;
        printf("\n\n\tBook Name:- %s  Author:- %s  Book ID:- %s  Student Name:- %s  Student ID:- %s  Issuing Date:- %s\n\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
    }
    if(p!=0)
    {
        printf("\t\t\tNo records found\n\n\n");
    }
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_is();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);

}
void sear_is_b()
{
    int c;
    do{
    system("cls");
    FILE *fp;
    char id[20];
    int p=1,q=1;
    printf("\n\n\t\t\t\tEnter the ID of the Student\n");
    scanf("%s",id);
    fp=fopen("bookissuerecord.txt","r");
    while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
    {
        if(strcmp(id,stu_iid)==0)
        {
            printf("\n\t\t\t\tStudent Name:- %s  ID:- %s   Book Name:- %s  Author:- %s  Book ID:- %s  Issuing Date:- %s\n\n",stu_iname,stu_iid,book_iname,book_iauth,book_iid,is_date);
            p=0;
        }
        q=0;
    }
    if(q!=0)
    {
        printf("\t\t\t\tRecords are empty\n\n");
    }
    else if(p!=0)
        {
            printf("\t\t\t\tNo book is issued to this ID\n\n");
        }
    fclose(fp);
    printf("\nPress <1> to continue with this section or any no to abort\n");
    scanf("%d",&c);
    }
    while(c==1);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
    do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                book_is();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
void sub_book() //TO SUBMIT BOOKS
{
    int a;
    do
    {
    system("cls");
    int p=1,q=1;
    char stu_id[20],book_id[20];
        FILE *fp,*fp1,*fp2,*fp3;
        printf("\nEnter student ID\n");
        scanf("%s",stu_id);
        printf("\nEnter book ID\n");
        scanf("%s",book_id);
        fp=fopen("bookissuerecord.txt","r");
        fp1=fopen("booktemp.txt","a");
        fp2=fopen("bookrecord.txt","r");
        fp3=fopen("bookistemp.txt","a");
        while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
        {
            if(strcmp(stu_id,stu_iid)==0)
            {
                p=0;
            }
            if(strcmp(stu_id,stu_iid)==0&&strcmp(book_id,book_iid)!=0)
            {
                fprintf(fp3,"%s %s %s %s %s %s\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
            }
            if(strcmp(stu_id,stu_iid)!=0&&strcmp(book_id,book_iid)==0)
            {
                fprintf(fp3,"%s %s %s %s %s %s\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
            }
            if(strcmp(stu_id,stu_iid)!=0&&strcmp(book_id,book_iid)!=0)
            {
                fprintf(fp3,"%s %s %s %s %s %s\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
            }
        }
        if(p!=0)
        {
            printf("No book is issued to this ID\n");
        }
        if(p==0)
        {
            while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
            {
                if(strcmp(book_id,book_iid)==0&&strcmp(stu_id,stu_iid)==0)
                {
                    q=0;
                }
                else if(strcmp(stu_id,stu_iid)==0&&strcmp(book_id,book_iid)!=0)
                {
                    fprintf(fp3,"%s %s %s %s %s %s\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
                }
            }
        }
        fclose(fp);
        fclose(fp3);
        while(fscanf(fp2,"%s %s %s %d",book_iname,book_iauth,book_iid,&iqty)!=EOF)
        {
            if(strcmp(book_id,book_iid)==0&&p==0&&q==0)
            {
                fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty+1);
            }
            else
            {
                fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
            }
        }
        fclose(fp1);
        fclose(fp2);
        fp=fopen("bookissuerecord.txt","r");
        while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
            {
                if(strcmp(stu_id,stu_iid)==0&&strcmp(book_id,book_iid)==0)
                {
                    printf("\nBook Name:- %s  Author:- %s  ID:- %s  Book submitted\n",book_iname,book_iauth,book_iid);
                    q=0;
                }
            }
        if(p==0&&q!=0)
        {
            printf("\nThe book is not issued to this ID\n");
        }
        fclose(fp);
        fp1=fopen("bookrecord.txt","w");
        fclose(fp1);
        fp2=fopen("bookissuerecord.txt","w");
        fclose(fp2);
        fp=fopen("booktemp.txt","r");
        while(fscanf(fp,"%s %s %s %d\n",book_iname,book_iauth,book_iid,&iqty)!=EOF)
        {
            fp1=fopen("bookrecord.txt","a");
            fprintf(fp1,"%s %s %s %d\n",book_iname,book_iauth,book_iid,iqty);
            fclose(fp1);
        }
        fclose(fp);
        fp=fopen("bookistemp.txt","r");
        while(fscanf(fp,"%s %s %s %s %s %s",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date)!=EOF)
        {
            fp1=fopen("bookissuerecord.txt","a");
            fprintf(fp1,"%s %s %s %s %s %s\n",book_iname,book_iauth,book_iid,stu_iname,stu_iid,is_date);
            fclose(fp1);
        }
        fclose(fp);
        fp=fopen("booktemp.txt","w");
        fclose(fp);
        fp=fopen("bookistemp.txt","w");
        fclose(fp);
        printf("\nPress 1 to to continue with this section\n");
        scanf("%d",&a);
    }
    while(a==1);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <2> to go to main menu\n");
    printf("\t\t\tPress <0> to exit\n");
    int c;
    do
    {
        scanf("%d",&c);
        switch(c)
        {
            case 1:
                book_is();
                break;
            case 2:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(c!=0);
}
void ch_pass() //TO CHANGE PASSWORD
{
    system("cls");
    FILE *fp,*fp1;
    char o_pas[20],pass[20];
    int p;
    do
    {
        fp=fopen("password.txt","r");
        if(fscanf(fp,"%s",o_pass)==EOF)
        {
            printf("\nNo password set\n\n");
            printf("Set password for the first time\n\n");
            printf("Enter password\n");
            scanf("%s",o_pas);
            fp1=fopen("password.txt","w");
            fprintf(fp1,"%s",o_pas);
            printf("\nPassword is set\n");
            fclose(fp1);
        }
        else{
        printf("\n\t\t\tEnter current password\n");
        scanf("%s",pass);
        fp=fopen("password.txt","r");
        while(fscanf(fp,"%s",o_pass)!=EOF)
            {
                if(strcmp(o_pass,pass)==0)
                {
                    printf("\n\t\t\tEnter new password\n\n");
                    scanf("%s",o_pas);
                    fp1=fopen("password.txt","w");
                    fprintf(fp1,"%s\n",o_pas);
                    printf("\n\t\t\tPassword changed\n");
                    fclose(fp1);
                    p=0;
                }
            }
                if(p!=0)
                    {
                        printf("\n\t\t\tWrong password\n");
                        printf("\n\t\t\tPress <5> to retry or any key to abort\n");
                        scanf("%d",&p);
                    }
                    fclose(fp);
        }
    }
    while(p==5);
    printf("\t\t\tPress <1> to go back\n");
    printf("\t\t\tPress <0> to exit\n");
    int a;
     do
    {
        scanf("%d",&a);
        switch(a)
        {
            case 1:
                main();
                break;
            case 0:
                exit(0);
                break;
        }
    }
    while(a!=0);
}
