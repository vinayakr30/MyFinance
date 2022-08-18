#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50
#define M 30
double currentincome=0;
double currentexpense=0;

struct node
{
char date[M];
double amount;
char category[N];
struct node *next;
}*income=NULL,*expense=NULL;

struct record
{
double x,y;
}*point=NULL;


void create(char x[],double y,char z[],struct node **temp);
void display(int a3);
struct node *readnext(struct node *ptr,FILE *fpointer);
void writeincome(struct node *ptr);
void writeexpense(struct node *ptr);
void deleterecord(struct node *ptr);
struct node *readincome(struct node *ptr);
struct node *readexpense(struct node *ptr);
void write(struct record *point);
struct record *readrecord();


int main()
{
int option,value;

double b;
char c[N],a[M];
char s1[15],s2[15],s3[15]; //to store date-month-year



if(fopen("Record.bin","rb")!=NULL)/*first time it will give null because there is no file name record.bin,therefore it will not take income
                     and expense from file,assign value will be displayed i.e 0,0..after creating income and expense first time
                      user exits then record.bin
                     will be create and again  when user runs program then this if will execute and take income and expense from file*/ 
{
point=readrecord();
currentincome=point->x;
currentexpense=point->y;
}

if(fopen("myincome.bin","rb")!=NULL)/*it means file is already created and some data is already there,and we have to get that and create
                                         linked list,address of first node will be in income pointer. step bcoz if we dont do this than 
                                     after closing terminal if we create inome and saved it than previous data will be deleted and it 
                                   overwrites in file...after doing this income will point to first node and all data will be come in ram
                                    in form linked list*/
{
income=readincome(income);
}

if(fopen("myexpense.bin","rb")!=NULL)
{
expense=readexpense(expense);
}


do{

printf("                                           _______________________________________________\n  " );
printf("                                         |     YOUR INCOME   =      %.2lf INR      \n ",currentincome);      
printf("                                          |     YOUR EXPENSE  =      %.2lf INR     \n ",currentexpense);
printf("                                          |     YOUR BALANCE  =      %.2lf INR     \n ",currentincome-currentexpense);
printf("                                          |_______________________________________________\n");
printf("ENTER THE OPTION FROM THE BELOW \n\n");
printf("1.INSERT INCOME \n");
printf("2.INSERT EXPENSE \n");
printf("3.VIEW INCOME RECORD \n");
printf("4.VIEW EXPENSE RECORD \n");
printf("5.EXIT\n");
scanf("%d",&option);
printf("\n\n\n");

switch(option)
{
case 1:
printf("**************   ADD INCOME   *****************\n\n");
printf("Enter The Date(e.g day month year)\n");
scanf("%s %s %s",s1,s2,s3);//gets,fgets and other functions are not working thats why these stepes have done 
  strcpy(a,"");
  strcat(a,s1);
  strcat(a," ");
  strcat(a,s2);
  strcat(a," ");
  strcat(a,s3);
printf("Enter The Amount\n");
scanf("%lf",&b);
printf("Enter the Category\n");
scanf("%s",c);
  
//a->date, b->amt, c->cat
currentincome=currentincome+b;
create(a,b,c,&income);
writeincome(income);

break;
case 2:
printf("**************    ADD EXPENSE   *****************\n\n");
printf("Enter The Date(e.g day month year)\n");

scanf("%s %s %s",s1,s2,s3);
  strcpy(a,"");
  strcat(a,s1);
  strcat(a," ");
  strcat(a,s2);
  strcat(a," ");
  strcat(a,s3);

printf("Enter The Amount\n");
scanf("%lf",&b);
printf("Enter The Category\n");
scanf("%s",c);


currentexpense=currentexpense+b;
create(a,b,c,&expense);
writeexpense(expense);

break;
case 3:
printf("*********   YOUR INCOME RECORD IS   *******\n\n");
display(3);
break;
case 4:
printf("*********   YOUR EXPENSE RECORD IS   *******\n\n");
display(4);
break;
case 5:
point=(struct record*)malloc(sizeof(struct record));
point->x=currentincome;
point->y=currentexpense;
write(point);
break;
default:
printf("WRONG OPTION SELECTED -Enter Valid Option");
break;
}
}while(option!=5);


return 0;
}



void create(char x[],double y,char z[],struct node **temp)        /* it is okay to write *temp if we pass only income rather than &income*/
{
    struct node *newnode,*ptr;
    newnode=(struct node*)malloc(sizeof(struct node));
    if(*temp==NULL)
    {
      strcpy(newnode->date,x);
      newnode->amount=y;
      strcpy(newnode->category,z);
      newnode->next=NULL;
      *temp=newnode;
    }
    else
    {
      ptr=*temp;
      while(ptr->next!=NULL)
      {
        ptr=ptr->next;
      }
      strcpy(newnode->date,x);
      newnode->amount=y;
      strcpy(newnode->category,z);
      newnode->next=NULL;
      ptr->next=newnode;
    }
}

void deleterecord(struct node *ptr)
{
    struct node *freeme =ptr;
    struct node *holdme=NULL;
  while(freeme!=NULL)
  {
    holdme=freeme->next;
    free(freeme);
    freeme=holdme;
  }
}





//===================================================================================================================================
//helper fn of read income and read expense
struct node *readnext(struct node *ptr,FILE *fpointer)
{

    if(ptr==NULL)
    {
        ptr=(struct node *)malloc(sizeof(struct node));
        fread(ptr,sizeof(struct node),1,fpointer);//ptr points to the first node from data
        ptr->next=NULL;
    }
    else
    {
            struct node *ptr1=ptr; //ptr2 makes a new node and stores the data of node where fpointer is pointing to.
            struct node *ptr2=(struct node *)malloc(sizeof(struct node));
        while(ptr1->next!=NULL)
        {//ptr1 is last node till now in the new linked list that we are making with (ptr head)
          ptr1=ptr1->next;
        }
        //This function first, reads count number of objects, each one with a size of size bytes from the given input stream.
        //fread(void * buffer, size_t size, size_t count, FILE * stream)
            // buffer: it specifies the pointer to the block of memory with a size of at least (size*count) bytes to store the objects.
            // size: it specifies the size of each objects in bytes. size_t is an unsigned integral type.
            // count: it specifies the number of elements, each one with a size of size bytes.
            // stream: it specifies the file stream to read the data from.

        //ptr2 makes a new node and stores the data of node where fpointer is pointing to.
        fread(ptr2,sizeof(struct node),1,fpointer);
        ptr1->next=ptr2;//ptr1 is last node till now in the new linked list that we are making with (ptr head).
        //so next node from database(ptr2) is added to ptr1.
        ptr2->next=NULL;
    }
    return ptr;//(ptr is head of current linked list). 
    //During this function call (node* income =ptr) actually. So income is the actual head outside this fn
}

//fseek() is used to move file pointer associated with a given file to a specific position.
// int fseek(FILE *pointer, long int offset, int position)
// pointer: pointer to a FILE object that identifies the stream.
// offset: number of bytes to offset from position
// position: position from where offset is added.

// SEEK_END : It denotes end of the file.
// SEEK_SET : It denotes starting of the file.
// SEEK_CUR : It denotes file pointer’s current position.
//==============================================================================================================================================

struct node *readincome(struct node *ptr)
{
//By this function, we make a linked list from the data stored in myincome.bin(that same linked list that we stored in it).
FILE *fpointer;
fpointer=fopen("myincome.bin","rb");
if(fpointer!=NULL)
{
    deleterecord(ptr); //on being asked again to read income, then ptr has to come to inital
    // point i.e NULL and start adding nodes from databse to itself(ptr) to make new linked list from starting to end. 
    //Thus ideally we need to clear the old list that ptr stores before assigning it null. So delete
    ptr=NULL;
    fseek(fpointer,0,SEEK_END); //pointer pointing at 0 bytes from end of file, i.e. point at end on file
   // ftell() in C is used to find out the position of file pointer(fpointer,which we just moved it to end of file in this case) in the file with respect to starting of the file.
    long filesize=ftell(fpointer); //counts letters till end of file i.e it shows size of file
    rewind(fpointer); //moves the file pointer (fpointer) back to the starting of file
    int entries=(int)(filesize/(sizeof(struct node))); //no. of income nodes in myincome.bin
    for(int i=0;i<entries;i++)
    {
      fseek(fpointer,(sizeof(struct node)*i),SEEK_SET);
      ptr=readnext(ptr,fpointer);
    }
}
else
{
    printf("ERROR IN OPENINNG FILE\n");
}
    return ptr;
}



//===================================================================================================================================

void display(int a3)
{   //PRINT INCOME RECORD
   if(a3==3)//if case 3 is executed,we have to print income record
    {
                   
                 if(fopen("myincome.bin","rb")==NULL)/*if user try to view record when there is no any record,i.e when user runs program
                                                       first time and wants to view record i.e there is no any
                                                        file created yet as myincome.bin,then it will =NULL */

                         {
                             printf("NO RECORDS AVAILABLE\n\n");
         printf("________________________________________________________________________________________________________________\n\n");
            
                        }
                else
              { 
                   //income=readincome(income);
                   //HERE income is head of income linked list that we created in income=readincome(income) execution at start of prgramme
                     struct node *ptr2=income;
                    while(ptr2!=NULL)
                        {
                              printf("Date: %s\nAmount: %.2lf INR\nCategory: %s\n\n",ptr2->date,ptr2->
                             amount,ptr2->category);
                              ptr2=ptr2->next;
                        }
            printf("________________________________________________________________________________________________________________\n\n");

               }
} 
//PRINT EXPENSE RECORD
else if(a3==4)//if case 4 is executed then we have to print expenese record
   {
               
                 if(fopen("myexpense.bin","rb")==NULL)/*if user try to view record when there is no any record,i.e when user runs program
                                                       first time and wants to view record i.e there is no any
                                                        file created yet as myexpense.bin,then it will =NULL */
               
                          {
                             printf("NO RECORDS AVAILABLE\n\n");
         printf("________________________________________________________________________________________________________________\n\n");     
                           }
                else 
                      { 

                        //   expense=readexpense(expense);
                           struct node *ptr2=expense;
                                    while(ptr2!=NULL)
                                    {
                                         printf("Date: %s\nAmount: %.2lf INR\nCategory: %s\n\n",ptr2->date,ptr2->
                                        amount,ptr2->category);
                                        ptr2=ptr2->next;
                                     }
               printf("________________________________________________________________________________________________________________\n\n");


                       } 

  } 

}


//===================================================================================================================================
//everytime we write into file,it will overwrite the data......
//entire linked list with 'income' head is now written in myincome.bin 
void writeincome(struct node *ptr)
{
  FILE *fpointer;
  fpointer=fopen("myincome.bin","wb");    
  if(fpointer!=NULL)
  {
    struct node *ptr1=ptr;
    struct node *holdnext=NULL;

  while(ptr1!=NULL)
  {
    holdnext=ptr1->next;
    ptr1->next=NULL;
    fseek(fpointer,0,SEEK_END);
    fwrite(ptr1,sizeof(struct node),1,fpointer);/*everytime we write into file,it will overwrite the data......                                                      whole data will be deleted and new data willl be written intofile*/
    ptr1->next=holdnext;
    holdnext=NULL;
    ptr1=ptr1->next;
  }
  fclose(fpointer);
  fpointer=NULL;
  printf("\nINCOME SAVED SUCCESSFULLY\n\n");
  printf("________________________________________________________________________________________________________________\n\n");

  }

  else{
    printf("\nCANNOT SAVE INCOME..TRY AGAIN\n");
    printf("________________________________________________________________________________________________________________\n\n");

  }
}



//===================================================================================================================================
/*everytime we write into file,it will overwrite the data.....
 whole data will be deleted and new data willl be written intofile myexpense.bin*/

void writeexpense(struct node *ptr)
{
    FILE *fpointer;
    fpointer=fopen("myexpense.bin","wb");    
    if(fpointer!=NULL)
    {
      struct node *ptr1=ptr;
      struct node *holdnext=NULL;
    while(ptr1!=NULL)
    {
        holdnext=ptr1->next;
        ptr1->next=NULL;
        fseek(fpointer,0,SEEK_END);//writes data of ptr1 to end of file. fpointer points to end of file on each iteration of this while loop
        fwrite(ptr1,sizeof(struct node),1,fpointer);/*everytime we write into file,it will overwrite the data.....
                                                            whole data will be deleted and new data willl be written intofile*/
        ptr1->next=holdnext;
        holdnext=NULL;
        ptr1=ptr1->next;
    }
    fclose(fpointer);
    fpointer=NULL;
    printf("\nEXPENSE SAVED SUCCESSFULLY\n\n");
    printf("________________________________________________________________________________________________________________\n\n");

    }
    else{
        printf("\nCANNOT SAVE EXPENSE..TRY AGAIN\n\n");
        printf("________________________________________________________________________________________________________________\n\n");

    }
}


//===================================================================================================================================

struct node *readexpense(struct node *ptr)
{
FILE *fpointer;
fpointer=fopen("myexpense.bin","rb");
if(fpointer!=NULL)
{
deleterecord(ptr);
ptr=NULL;
fseek(fpointer,0,SEEK_END);
long filesize=ftell(fpointer);
rewind(fpointer);
int entries=(int)(filesize/(sizeof(struct node)));
for(int i=0;i<entries;i++)
{
fseek(fpointer,(sizeof(struct node)*i),SEEK_SET);
ptr=readnext(ptr,fpointer);
}
}
else
{
printf("cannonot open file\n");

}
return ptr;
}


//===================================================================================================================================
//Record.bin stores the point current point of situation i.e current income and expense
//writing into record.bin on exit
// point=(struct record*)malloc(sizeof(struct record));
// point->x=currentincome;
// point->y=currentexpense;
// write(point);
void write(struct record *point)
{
FILE *fpointer;
fpointer=fopen("Record.bin","wb");    
if(fpointer!=NULL)
{

fseek(fpointer,0,SEEK_END);//fpointer at distance zero from end of file
fwrite(point,sizeof(struct record),1,fpointer);/*everytime we write into file,it will overwrite the data.....
                                                     whole data will be deleted and new data willl be written intofile*/
}
else{
printf("FILEOPEN ERROR\n");
}
fclose(fpointer);
fpointer=NULL;

}



//===================================================================================================================================


//reads Record.bin for obtaing current point of data(i.e current income and expense)


struct record *readrecord()
{
FILE *fpointer;
fpointer=fopen("Record.bin","rb");
struct record *ptr=NULL;

if(fpointer!=NULL)
{

fseek(fpointer,0,SEEK_SET);

ptr=(struct record *)malloc(sizeof(struct record));
fread(ptr,sizeof(struct record),1,fpointer);


}
else
{
printf("CANNOT OPEN FILE\n");
}
return ptr;//ptr stores node that contain current total income and current total expenses
}

