/*
Islam Jihad Joma
1191375
section 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
    int cof;
    int pwr;
    struct node* Next;
    struct node* pre;
};
struct node* L[100];  //array of linked list

//linked list functions
struct node* MakeEmpty(struct node* L);
int IsEmpty(struct node* L);
int IsLast(struct node* P, struct node* L);
struct node* Find(int cof, int pwr, struct node* L);
struct node* FindPrevious(int cof, int pwr, struct node* L);
void Insert(int cof, int pwr, struct node* L, struct node* P);
void PrintList(struct node* L);
void DeleteList(struct node* L);
int size( struct node* L);

//the code privete functions
void readFile();
void onePeice(char str[],int i);
void decide(char* equ, struct node* L);
void print_all_equ();
void add(int x);
void sub(int x);
char  blank[100][50];
int i=0;
int globalcof=NULL,globalpwr=NULL;


int main()
{
    // the user menu to chose operation
    int x;
    printf("enter the operation to do:\n1-read file\t2-show equations\t3-perform add\t4-perform sub\t5-perform mult\t6-exit\n");
    scanf("%d",&x);

    while(x!=6)
    {
        if(x==1)
        {
            readFile();

        }
        else if(x==2)
        {
            print_all_equ();
        }
        else if(x==3)
        {
            add(scanf("%d"));
        }
        else if(x==4)
        {
            sub(scanf("%d"));
        }
        else if(x==5)
        {

        }
        else
        {
            printf("please chose a number from 1-6 only\n");
        }



        printf("enter the operation to do:\n 1-read file\t2-show equations\t3-perform add\t4-perform sub\t5-perform mult\t6-exit\n");
        scanf("%d",&x);
    }







    return 0;
}

// I made some changes to get double linked list insted of single linked list, I didne't use them all but they will be usful in the future

struct node* MakeEmpty(struct node* L)
{
    if(L != NULL)
        DeleteList( L );

    L = (struct node*)malloc(sizeof(struct node));
    struct node* tail= (struct node*)malloc(sizeof(struct node));
    if(L == NULL)
        printf("Out of memory!\n");

    L->Next = tail;
    tail->pre=L;
    L->pre=NULL;
    tail->Next=NULL;
    return L;
}


int IsEmpty(struct node* L)
{
    return L->Next == NULL;
}


int IsLast(struct node* P, struct node* L)
{
    return P->Next==NULL;
}


struct node* Find(int cof, int pwr, struct node* L)
{
    struct node* P;
    P = L->Next;
    while((P != NULL )&& (P->cof != cof )&& (P->pwr!= pwr))
        P= P->Next;
    return P;
}


struct node* FindPrevious(int cof, int pwr, struct node* L)
{
    struct node* P;
    P = L;
    while((P->Next != NULL) && (P->Next->cof != cof)&& (P->Next->pwr!=pwr))
        P = P->Next;
    return P;
}

void Delete(int cof, int pwr, struct node* L)
{
    struct node *temp;

    temp = Find(cof,pwr, L);
    if(!(temp==NULL))
    {
        temp->pre->Next = temp->Next;
        temp->Next->pre = temp->pre;
        free(temp);
    }
}

void Insert(int cof, int pwr, struct node* L, struct node* P)
{

    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));

    temp->cof = cof;
    temp->pwr = pwr;
    temp->Next = P->Next;
    P->Next->pre= temp;
    P->Next = temp;
    temp->pre= P;
}


void PrintList(struct node* L)
{
    struct node* P = L->Next;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
        while(P->Next!=NULL)
        {
            printf("cof: %d\tpwr: %d\n", P->cof,P->pwr);
            P=P->Next;
        }

    printf("\n");
}


void DeleteList(struct node* L)
{
    struct node* P, *temp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL)
    {
        temp = P->Next;
        free(P);
        P=temp;
    }
}


int size( struct node* L)
{
    struct node* p = L->Next;
    int count = 0;
    while(p != NULL )
    {
        count++;
        p = p->Next;
    }
    return count;
}
















/*this fuction read from the file charecter by charecter and remove spaces and store the fixed string in a 2 dimential array
as every index contain a fixed line from the file*/
void readFile()
{

    int counter=0;
    char c;

    FILE *fptr=fopen("equations.txt","r");

    c=fgetc(fptr);
    while(c!= EOF)
    {
        if (!(c == ' '))
        {
            blank[i][counter] =c;
            counter++;
        }
        if(c=='\n')
        {
            blank[i][counter] = '\0';
            onePeice(blank[i],i);
            i++;
            counter=0;
        }
        c=fgetc(fptr);
    }
    fclose(fptr);




}

/*this function define every index of the global array of linked listes
and replace eveery - sign with +- sign to make it easier to use strtok function on + sign
only and send every part to the next function*/

void onePeice(char str[],int i)
{
    L[i]=MakeEmpty(NULL);
    char c;
    char ary[100]="\0";
    int count=0;
    c=str[count];

    while(c!='\0')
    {
        c=str[count];
        if(c=='-')
        {
            char s[2]="+-";
            strncat(ary,s,2);
            count++;
        }
        else
        {
            strncat(ary,&c,1);
            count++;
        }
    }


    char * token = strtok(ary, "+");
    while( token != NULL )
    {

        decide(token,L[i]);
        token = strtok(NULL, "+");

    }

}


/*this function get the algebraic limit and start to calculate the coficant and power
and cast it into integers from strings then save them in there index in the struct node*/
void decide(char* equ, struct node* L)
{
    int cofc=0, pwrc=0, counter=0;
    char c= equ[counter];
    char pwrn[6];
    while(c!='x')
    {

        if(c=='\0')
        {
            break;
        }
        cofc++;
        counter++;
        c=equ[counter];
    }


    int a=cofc+2;

    while(a<strlen(equ)&& (c!='\0'))
    {
        pwrc++;
        a++;
    }


    for(int j=0; j<=pwrc; j++)
    {
        pwrn[j]=equ[j+2+cofc];
    }



    int p,f;
    if(cofc==0)
    {
        f=1;
        p=atoi(pwrn);
    }
    else if(cofc==strlen(equ))
    {
        f=atoi(equ);
        p=0;
    }
    else if(cofc==0 && pwrc==0)
    {
        f=1;
        p=1;
    }
    else
    {
        f=atoi(equ);
        p=atoi(pwrn);
    }
    printf("\n%s\n",equ);
    printf("cof: %d\tpwr: %d\n",f,p);

    /*   struct node* temp = Find( globalcof, globalpwr, L);
       Insert(f, p, L, temp);
       globalcof=f;
       globalpwr=p;*/


}
// print the equations from the file
void print_all_equ()
{

    for(int j=0; j<i; j++)
    {
        printf("%s\n",blank[j]);
    }
}

//this function add the cofitiant with the same power level to each other then calculate it
void add(int x)
{
    struct node* sum=MakeEmpty(NULL);
    for(int j=0; j<i; j++)
    {
        for(int k=0; k<size(L[j]); k++)
        {
            if(L[j]->Next->pwr==L[j]->Next->Next->pwr)
                sum = L[j]->Next->cof+L[j]->Next->Next->cof;
        }
    }
    x=pow(x,sum->pwr)*sum->cof;
    printf("%dx^%d\t=%d\n",sum->cof,sum->pwr,x);

}

//this function subtract the cofitiant with the same power level to each other then calculate it
void sub(int x)
{
    struct node* sub=MakeEmpty(NULL);
    for(int j=0; j<i; j++)
    {
        for(int k=0; k<size(L[j]); k++)
        {
            if(L[j]->Next->pwr==L[j]->Next->Next->pwr)
                sub = (L[j]->Next->cof)-(L[j]->Next->Next->cof);
        }
    }
    x=pow(x,sub->pwr)*sub->cof;
    printf("%dx^%d\t=%d\n",sub->cof,sub->pwr,x);

}





