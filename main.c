#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


typedef struct
{
    int index;
    int bookID;
    int year;
    int month;
    int date;
}bInfo;

typedef struct
{
    int bID;
    char bName[50];
    int copies;
}books;

typedef struct
{
    char name[100];
    char nic[50];
    int phone;
    int index;

}peron;

bInfo *dublicateBinfoptr;
bInfo *bInfoptr;
books *booksPtr;
peron *personPtr;

void mainMenue(); ///explain cases
void authenticate(); /// sensor the password and stuff
void addFilebInfo(); ///after hand overing a borrowed book this funnction updates the bookinfo file
void getOverduedetails(); ///load details of over due books
void loadRegisterdetails(); ///loading registration details to person struct
void displayBookinfo(); /// getting latest info about books in the library
void nibmLogo();

void updatingBinfo(); ///load details of borrow info to binfo struct
void bookInfo(); ///load book info to books struct
void Registration(); ///registering customers
int personcount(); ///reading registration file and return the number of registered customers
void borrowBooks(); ///reserving books

int bookCount(); ///reading book info file and returning the number of different books
int borrowCount(); ///reading borrow info file and getting the number of customers who borrowed books
void abstractFilebInfo(int bookID); ///deducting a book copy from the book info file when a customer borrow a book
void handOvering(); ///this function is used to hand over books
int dateDifference(int y1,int m1,int d1); ///return the difference between purchase date and hand over date




//---------------------------------------------------MAIN FUNCTION--------------------------------------------------------
int main()
{
    system("color 8F"); //4F 8F


    authenticate();
    //mainMenue();


}
//-----------------------------------------------------------------------------------------------------------------------

void mainMenue()
{
    int choice;


        nibmLogo();

        printf("\n\t1.TO REGISTER: \n");
        printf("\t2.TO BORROW BOOKS: \n");
        printf("\t3.TO HANDOVER BOOKS: \n");
        printf("\t4.BOOK INFOMATION: \n");
        printf("\t5.OVERDUE BOOKS: \n");
        printf("\t6.EXIT\n");
        printf("-----------------------------------------------------------------------------------------------------------------------\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d",&choice);


        switch(choice)
        {
          case 1:
          Registration();
          break;

          case 2:
          borrowBooks();
          break;

          case 3:
          handOvering();
          break;

          case 4:
          displayBookinfo();
          break;

          case 5:
          getOverduedetails();
          break;

          case 6:
          system("CLS");
          printf("\n                                                        LOGGING OUT...");
          sleep(2);
          system("CLS");
          printf("\n                                              LOGOUT COMPLETE. HAVE A NICE DAY <3\n");
          sleep(2);
          //printf("                                                           \U0001F600\n");

          authenticate();

          break;

          default:
          printf("WRONG INPUT, TRY AGAIN!!! :(");
          sleep(2);
          system("CLS");
          main();
          break;
        }





}

void authenticate()
{

    system("CLS");

    int i = 0;
    char admin[] = "admin123";
    char password[10];

    nibmLogo();

    printf("\n                                                 ENTER ADMIN PASSWORD: ");

    while (i < 10) {
        char pass = _getch();
        // here _getch() from conio.h is used to stop from echoing chars in console

        // and also to use backspace as an eraser

        if (pass == '\r') {
            break;    // If Enter is pressed, stop reading
        } else if (pass == '\b' && i > 0)
        {
            // Handle backspace by erasing the character

            printf("\b \b");
            i--;
            continue;
        }
        password[i++] = pass;
        printf("*");
        // Print '*' for masking
    }
    password[i] = '\0'; //null terminate the password

    if (strcmp(admin, password) == 0)
    {
        printf("\n\n                                                        LOGGING IN...");
        sleep(2);
        system("CLS");
        mainMenue();



    } else

    {
        printf("\n                                             WRONG PASSWORD! PLEASE TRY AGAIN :(\n");
        sleep(2);
        system("CLS");
        authenticate();

        //  call for re-entering password

    }

}

void Registration()
{
    system("CLS");
    nibmLogo();

    printf("\n                                                      ~ REGISTRATION ~\n\n");

    FILE *reg;
    reg=fopen("Registration.txt","a");

    char name[50],nic[20],address[100],gName[50],gID[20];
    int age,phoneN,gPhone,index=100,conf;

    printf("\tENTER NAME: ");
    scanf("%s",&name);
    if(strcmp(name,"99")==0)
    {
        system("CLS");
        mainMenue();
    }

    printf("\tENTER PHONE NUMBER: ");
    scanf("%d",&phoneN);

    printf("\tENTER AGE: ");
    scanf("%d",&age);

    int count = personcount();
    int pIndex = index+count;

    //auto generating pIndex

    if(age>18)
    {
        printf("\tENTER NIC NUMBER: ");
        scanf("%s",&nic);

        printf("\tENTER ADDRESS: ");
        scanf("%s",&address);

        nibmLogo();

        printf("REGISTRATION DETAILS >\n\n");
        printf("\tNAME         - %s\n",name);
        printf("\tPHONE NUMBER - %d\n",phoneN);
        printf("\tNIC          - %s\n",nic);
        printf("\nTO CONFIRM PRESS (1), BACK (0): ");
        scanf("%d",&conf);

        if(conf==1)
        {
            fprintf(reg,"%s\n%s\n%d\n%d\n",name,nic,phoneN,pIndex);
            printf("REGISTRATION SUCCESSFUl <3\n");
            sleep(2);

        }else if(conf==0)
        {
            Registration();
        }

    }else
    {
        printf("\tENTER GUARDIAN NAME: ");
        scanf("%s",&gName);

        printf("\tENTER GUARDIAN PHONE NUMBER: ");
        scanf("%d",&gPhone);

        printf("\tENTER GUARDIAN NIC NUMBER: ");
        scanf("%s",&gID);

        nibmLogo();

        printf("REGISTRATION DETAILS >\n\n");
        printf("\tNAME         - %s\n",name);
        printf("\tPHONE NUMBER - %d\n",phoneN);
        printf("\tGUARDIAN NIC - %s\n",gID);
        printf("\nTO CONFIRM (1), BACK (0): ");
        scanf("%d",&conf);

        if(conf==1)
        {
            fprintf(reg,"%s\n%s\n%d\n%d\n",name,gID,phoneN,pIndex);
            printf("REGISTRATION SUCCESSFUl <3\n");
            sleep(2);

        }else if(conf==0)
        {
            Registration();
        }

    } fclose(reg);

    system("CLS");
    mainMenue();


}

int personcount()
{
    char ch[100];
    int num,count=0;

    FILE *reg;
    reg=fopen("Registration.txt","r");

    // calculating the number of registered people and returning the count.

    while(fscanf(reg,"%s",&ch)==1)
    {
        fscanf(reg,"%s",&ch);
        fscanf(reg,"%d",&num);
        fscanf(reg,"%d",&num);
        count++;

    }
    fclose(reg);

    return count;

}

void borrowBooks()
{
    system("CLS");
    nibmLogo();

    printf("\n                                                      ~ BORROW BOOKS ~\n");

    updatingBinfo();

    //getting book count

    int bBcount=borrowCount();
    int index,bCount=0,bBorrow;
    int bill;
    int confirmO;

    printf("\tENTER INDEX: ");
    scanf("%d",&index);

    if(index==99)
    {
        system("CLS");
        mainMenue();
    }

    for(int i=0;i<bBcount;i++)
    {
        if(bInfoptr[i].index==index)
        {
            bCount++;
        }
    }
    //printf("%d",bCount);
    if(bCount==3)
    {
        printf("\tNOT ALLOWED TO BORROW MORE BOOKS\n");
        system("CLS");
        mainMenue();
    }else
    {
        FILE *ptr;
        ptr=fopen("Borrowinfo.txt","a");

        printf("\n\tALLOWED TO BORROW MORE BOOKS\n");

        printf("\n\tENTER BOOK ID: ");
        scanf("%d",&bBorrow);

        int nOfbooks=bookCount();

        bookInfo();

        for(int i=0;i<nOfbooks;i++)
        {
            if(bBorrow==booksPtr[i].bID)
            {
                if(booksPtr[i].copies>=3)
                {

                    time_t t=time(NULL);
                    struct tm tm=*localtime(&t);

                    printf("\n\tORDER DETAILS >\n\n");
                    printf("\tDate - %d %02d %02d\n\n",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
                    printf("\tTO CONFIRM PRESS (1), BACK (0): ");
                    scanf("%d",&confirmO);

                    if(confirmO==1)
                    {
                        printf("\n\tBILL IS Rs.200/= (PAID - 1, NO - 0): ");
                        scanf("%d",&bill);

                        if(bill==1)
                        {
                        printf("------------------------------------------------------------------------------------------------------------------------");
                        printf("\n\tBILL PAYMENT CONFIRMED!!!");

                        sleep(2);

                        fprintf(ptr,"\n%d\n%d\n",index,bBorrow);
                        fprintf(ptr,"%02d %02d %d",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
                        fclose(ptr);
                        abstractFilebInfo(bBorrow);
                        system("CLS");
                        mainMenue();

                        }else
                        {

                         system("CLS");
                         mainMenue();
                        }

                    }else if(confirmO==0)
                    {
                        system("CLS");
                        mainMenue();
                    }



                    fclose(ptr);

                }else
                {
                    printf("\tBOOK NOT AVAILABLE  -_-");
                    sleep(2);
                    system("CLS");
                    mainMenue();
                }
            }
        }


    }

}

void updatingBinfo()
{
    int bBcount=borrowCount();
    bInfoptr=(bInfo*)malloc(bBcount*sizeof(bInfo));

    //getting borrow count and updating the relevant data to the struct.

    //bInfo bInfoptr[100];
    int i = 0 ;
    FILE *ptr;
    ptr=fopen("Borrowinfo.txt","r");

    while(fscanf(ptr,"%d",&bInfoptr[i].index)==1)
    {
        fscanf(ptr,"%d",&bInfoptr[i].bookID);
        fscanf(ptr,"%d",&bInfoptr[i].year);
        fscanf(ptr,"%d",&bInfoptr[i].month);
        fscanf(ptr,"%d",&bInfoptr[i].date);
        i++;                                                        //borrow books load krno struct ekata


    }
    fclose(ptr);

    /*for(int i=0;i<bBcount;i++)
    {
        printf("---------------------------------\n");
        printf("%d\n%d\n%d %d %d\n",bInfoptr[i].index,bInfoptr[i].bookID,bInfoptr[i].year,bInfoptr[i].month,bInfoptr[i].date);
    }*/



}

int bookCount()
{
    char bk[100];
    int num1,count=0;

    FILE *ptr;
    ptr=fopen("BookInfo.txt","r");

    while(fscanf(ptr,"%d",&num1)==1)
    {
        fscanf(ptr,"%s",&bk);
        fscanf(ptr,"%d",&num1);
        count++;

    }
    fclose(ptr);

    return count;

    //getting book count
}

void bookInfo()
{

    int bCount=bookCount();

    booksPtr=(books*)malloc(bCount*sizeof(books));

    int i=0;

    FILE *ptr;
    ptr=fopen("BookInfo.txt","r");

    while(fscanf(ptr,"%d",&booksPtr[i].bID)==1)
    {
        fscanf(ptr,"%s",&booksPtr[i].bName);
        fscanf(ptr,"%d",&booksPtr[i].copies);
        i++;
    }

    fclose(ptr);

    /*for(i=0;i<bCount;i++)
    {
        printf("%d\n%d\n",booksPtr[i].bID,booksPtr[i].copies);
    }*/

    //getting latest book information

}

int borrowCount()
{
    int bBcount=0,num2;

    FILE *ptr;
    ptr=fopen("Borrowinfo.txt","r");

    while(fscanf(ptr,"%d",&num2)==1)
    {
        fscanf(ptr,"%d",&num2);
        fscanf(ptr,"%d",&num2);
        fscanf(ptr,"%d",&num2);
        fscanf(ptr,"%d",&num2);
        bBcount++;
    }
    fclose(ptr);

    return bBcount;

    //getting book borrow count
}

void abstractFilebInfo(int bookID)
{
    FILE *ptr;
    ptr=fopen("BookInfo.txt","r+");


    bookInfo();

    int booksC=bookCount();
    //printf("\n%d",booksC);

    for(int i=0;i<booksC;i++)
    {
        if(booksPtr[i].bID==bookID)
        {

            int copy=booksPtr[i].copies;
            copy = copy-1;
            booksPtr[i].copies=copy;

        }

    }
    for(int i=0;i<booksC;i++)
    {

        int bIDD,bCopies;
        char bNname[50];
        bIDD=booksPtr[i].bID;
        strcpy(bNname,booksPtr[i].bName);
        bCopies=booksPtr[i].copies;

        //printf("%d\n",bIDD);
        //printf("%s\n",bNname);
        //printf("%d\n",bCopies);

        fprintf(ptr,"%d\n",bIDD);
        fprintf(ptr,"%s\n",bNname);
        fprintf(ptr,"%d\n",bCopies);

    }

    fclose(ptr);

    //updating the bookinfo file after borrowing books
}

void handOvering()
{
    system("CLS");
    nibmLogo();

    printf("\n                                                      ~ HAND OVERING ~\n");

    FILE *ptr;

    int index,boID;


    printf("\n\tENTER USER ID: ");
    scanf("%d",&index);

    if(index==99)
    {
        system("CLS");
        mainMenue();
    }

    printf("\n\tENTER BOOK ID: ");
    scanf("%d",&boID);

    updatingBinfo();

    int count;
    count = borrowCount();

    int indexStatus = 0 ;
    for(int i=0;i<count;i++)
    {
        if(bInfoptr[i].index==index && bInfoptr[i].bookID==boID )
        {
                indexStatus = 1 ;
                int year,month,date;
                year=bInfoptr[i].year;
                month=bInfoptr[i].month;
                date=bInfoptr[i].date;

                int dateDiff=dateDifference(year,month,date);
                //printf("%d\n",dateDiff);

                int dueDate=dateDiff-14;

                //getting date difference and substracting 14 to get overdue dates.

                bInfoptr[i].index=0;
                bInfoptr[i].bookID=0;
                bInfoptr[i].year=0;
                bInfoptr[i].month=0;
                bInfoptr[i].date=0;

                if(dueDate>0)
                {
                    int fineBill=dueDate*50;
                    printf("\t%d DAYS BEHIND\n\t\n\tDUE PAYMENT IS RS.%d.00/= (PAID - 1, NO - 0): ",dueDate,fineBill);
                    int choice ;
                    scanf("%d",&choice);
                    if (choice == 1)
                    {
                        printf("\n\tBILL PAYMENT CONFIRMED!!!");
                        sleep(2);
                    }

                }
                break;

        }
    }

    if (indexStatus == 1)
    {
        int hCount=count-1;

        dublicateBinfoptr=(bInfo*)malloc(hCount*sizeof(bInfo));

        int status=0;
        for(int i=0;i<count;i++)
        {
            if(bInfoptr[i].index==0)
            {
                //printf("Here!!!\n");
                status=1;
                //printf("%d\n",status);

                continue;
            }
            else
            {
                if(status==1)
                {
                   dublicateBinfoptr[i-1].index = bInfoptr[i].index;
                   dublicateBinfoptr[i-1].bookID = bInfoptr[i].bookID;
                   dublicateBinfoptr[i-1].year = bInfoptr[i].year;
                   dublicateBinfoptr[i-1].month = bInfoptr[i].month;
                   dublicateBinfoptr[i-1].date = bInfoptr[i].date;

                }
                else
                {
                   dublicateBinfoptr[i].index = bInfoptr[i].index;
                   dublicateBinfoptr[i].bookID = bInfoptr[i].bookID;
                   dublicateBinfoptr[i].year = bInfoptr[i].year;
                   dublicateBinfoptr[i].month = bInfoptr[i].month;
                   dublicateBinfoptr[i].date = bInfoptr[i].date;
                }
            }
        }


        ptr=fopen("Borrowinfo.txt","w");
        fclose(ptr);

        ptr=fopen("Borrowinfo.txt","r+");





        for(int i=0;i<hCount;i++)
        {
            int index,bookID,year,month,date;

            index = dublicateBinfoptr[i].index;
            bookID = dublicateBinfoptr[i].bookID;
            year = dublicateBinfoptr[i].year;
            month = dublicateBinfoptr[i].month;
            date = dublicateBinfoptr[i].date;


            fprintf(ptr,"%d\n%d\n%d %d %d\n",index,bookID,year,month,date);
            //printf("*************************************\n");
            //printf("%d\n%d\n%d %d %d\n",dublicateBinfoptr[i].index,dublicateBinfoptr[i].bookID,dublicateBinfoptr[i].year,dublicateBinfoptr[i].month,dublicateBinfoptr[i].date);
        }
        fclose(ptr);

        printf("\n\tPROCEEDING...");
        sleep(2);

        nibmLogo();

        printf("\n\tHANDOVERING SUCCESSFUL!!! :)");

        addFilebInfo(boID);
        sleep(2);
        system("CLS");
        mainMenue();
    }
    else
    {
        system("CLS");
        printf("\nINVALID RECORD !!!!!!\n");
        sleep(2);
        handOvering();
    }



}

int dateDifference(int y1,int m1,int d1)
{
    //printf("book date = %d %d %d\n",y1,m1,d1);

    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
    int d2,d,m2,m,y2,y;

    y2=tm.tm_year+1900;
    m2=tm.tm_mon+1;
    d2=tm.tm_mday;

   // printf("system date = %d %d %d\n",y2,m2,d2);



	if(d2<d1)
	{
		if(m2==3)
		{
			if(y2%100!=0 && y2%4==0  ||  y2%400==0) //check for leap year
				d2=d2+29;
			else
				d2=d2+28;
		}
		else if(m2==5 || m2==7 || m2==10 || m2==12)
			d2=d2+30;
		else
			d2=d2+31;
		m2=m2-1;
	}
	if(m2<m1)
	{
		y2=y2-1;
		m2=m2+12;
	}
	y=y2-y1;
	m=m2-m1;
	d=d2-d1;

	//printf("dif = %d %d %d\n",y,m,d);

	int ddays=(y*365)+(m*30)+(d);

    //printf("late = %d\n",ddays);

	return ddays;

}

void addFilebInfo(int bookID)
{
    FILE *ptr;
    ptr=fopen("BookInfo.txt","r+");


    bookInfo();

    int booksC=bookCount();
    //printf("\n%d",booksC);

    for(int i=0;i<booksC;i++)
    {
        if(booksPtr[i].bID==bookID)
        {

            int copy=booksPtr[i].copies;
            copy = copy+1;
            booksPtr[i].copies=copy;

        }

    }
    for(int i=0;i<booksC;i++)
    {
        //printf("test\n");
        int bIDD,bCopies;
        char bNname[50];
        bIDD=booksPtr[i].bID;
        strcpy(bNname,booksPtr[i].bName);
        bCopies=booksPtr[i].copies;

        //printf("%d\n",bIDD);
        //printf("%s\n",bNname);
       // printf("%d\n",bCopies);

        fprintf(ptr,"%d\n",bIDD);
        fprintf(ptr,"%s\n",bNname);
        fprintf(ptr,"%d\n",bCopies);

    }

    fclose(ptr);

    //adding handed over book copy to number of copies

}

void nibmLogo()
{
        system("CLS");

        printf("                                            ####   ##  ######  ######   ##   ##\n");
        printf("                                            ## ##  ##    ##    ##   ##  ### ###\n");
        printf("                                            ##  ## ##    ##    ######   ## # ##\n");
        printf("                                            ##    ###    ##    ##   ##  ##   ##\n");
        printf("                                            ##     ##  ######  ######   ##   ##\n\n");
        printf("                                                        ~ LIBRARY ~               \n");
        printf("                                                    POWERING GREAT MINDS         \n");
        printf("========================================================================================================================\n");

}

void getOverduedetails()
{
    FILE* ptr;
    ptr=fopen("OverdueBooks.txt","w");
    fclose(ptr);
    ptr=fopen("OverdueBooks.txt","a");

    updatingBinfo();
    loadRegisterdetails();
    int pCount=personcount();

    fprintf(ptr,"                                            ####   ##  ######  ######   ##   ##\n");
    fprintf(ptr,"                                            ## ##  ##    ##    ##   ##  ### ###\n");
    fprintf(ptr,"                                            ##  ## ##    ##    ######   ## # ##\n");
    fprintf(ptr,"                                            ##    ###    ##    ##   ##  ##   ##\n");
    fprintf(ptr,"                                            ##     ##  ######  ######   ##   ##\n\n");
    fprintf(ptr,"                                                        ~ LIBRARY ~               \n");
    fprintf(ptr,"                                                    POWERING GREAT MINDS         \n");
    fprintf(ptr,"========================================================================================================================\n");


    for(int i=0;i<pCount;i++)
    {
        int year,month,date;

        year=bInfoptr[i].year;
        month=bInfoptr[i].month;
        date=bInfoptr[i].date;

        int diff=dateDifference(year,month,date);

        diff=diff-14;

        if(diff>0)
        {
            for(int j=0;j<pCount;j++)
            {
                if(bInfoptr[i].index==personPtr[j].index)
                {
                    int index,phone,boID;
                    char nName[100],nic[50];

                    strcpy(nName,personPtr[j].name);
                    index = personPtr[j].index;
                    strcpy(nic,personPtr[j].nic);
                    phone = personPtr[j].phone;
                    boID = bInfoptr[i].bookID;


                    fprintf(ptr,"-------------------------------------");
                    fprintf(ptr,"\t\nNAME         - %s",nName);
                    fprintf(ptr,"\t\nINDEX        - %d",index);
                    fprintf(ptr,"\t\nNIC          - %s",nic);
                    fprintf(ptr,"\t\nPHONE NUMBER - %d",phone);
                    fprintf(ptr,"\t\nBOOK ID      - %d",boID);
                    fprintf(ptr,"\n-------------------------------------\n");

                    printf("-------------------------------------");
                    printf("\t\nNAME         - %s",nName);
                    printf("\t\nINDEX        - %d",index);
                    printf("\t\nNIC          - %s",nic);
                    printf("\t\nPHONE NUMBER - %d",phone);
                    printf("\t\nBOOK ID      - %d",boID);
                    printf("\n-------------------------------------\n");



                }
            }
        }

    }

    fclose(ptr);

    char Press = _getch();

    if(Press == '\r' || Press == '\b')
    {
        mainMenue();
    }

    //manipulating enter and backspace


}

void loadRegisterdetails()
{
    FILE* ptr;
    ptr=fopen("Registration.txt","r");

    int pCount=personcount();

    personPtr=(peron*)malloc(pCount*sizeof(peron));

    int i=0;

    while(fscanf(ptr,"%s",&personPtr[i].name)==1)
    {
        fscanf(ptr,"%s",&personPtr[i].nic);
        fscanf(ptr,"%d",&personPtr[i].phone);
        fscanf(ptr,"%d",&personPtr[i].index);
        i++;

    }
    fclose(ptr);

    /*for(int i=0;i<pCount;i++)
    {
        printf("%s\n%s\n%d\n%d\n",personPtr[i].name,personPtr[i].nic,personPtr[i].phone,personPtr[i].index);
    }*/


}

void displayBookinfo()
{
    int bCount=bookCount();

    booksPtr=(books*)malloc(bCount*sizeof(books));

    bookInfo();

    printf("\n                                       |--------------------|----------------------|");
    printf("\n                                       |      BOOK ID       |  AVAILABLE QUANTITY  |    \n");
    printf("                                       |--------------------|----------------------|\n");


    for(int i=0;i<bCount;i++)
    {
        printf("                                       |       %d         |         %d            |\n",booksPtr[i].bID,booksPtr[i].copies);
    }
    printf("                                       |-------------------------------------------|\n\n");

    char press = _getch();

    if(press=='\b'||press=='\r')
    {
        system("CLS");
        mainMenue();
    }
}















































