#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.h>
#define up 72
#define down 80
#define enter 13
#define null -32
int id =0;

struct nodeName
{
    char name[20];
    int id ;
    struct nodeName* next;
    struct nodeName* prev;
};

struct nodePhone
{
    char phone[11];
    int id;
    struct nodePhone* next;
    struct nodePhone* prev;
};

struct nodeName* headn =NULL;
struct nodeName * tailn =NULL;
struct nodePhone* headp =NULL;
struct nodePhone * tailp =NULL;

void textattr(int i)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);

}
void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),coord);
}

char *get_name()
{
    system("cls");
    char*name;
   // int exist=0;
    name=(char*)malloc(21*sizeof(char));

    do
    {
        printf("enter name between 10&20 char: ");
        _flushall();
        gets(name);
    }
    while(strlen(name)<10||strlen(name)>21);

    return name;
}

char *get_phone()
{
    int len=0;
    int flag=0;
    char *phone_num,ch;
   // int exist=0;
    phone_num=(char*)malloc(12*sizeof(char));

    do
    {
        flag=0;
        printf("enter phone consist of 11 digit: ");
        _flushall();
        gets(phone_num);
        len=strlen(phone_num);
        for(int i=0; i<len; i++)
        {
            if(phone_num[i] < 48 || phone_num[i] > 57)
            {
                   flag=1;
                break;
            }
        }

    }
    while((strlen(phone_num)!=11) || flag==1);


    return phone_num;
}


int search_by_name(char sname[21])
{
    struct nodeName* ptemp;
    ptemp=headn;
    int exist;
    while( ptemp!=NULL)
    {
        if (strcmpi(sname, ptemp->name)==0)
        {
            exist=1;
            break;
        }
        ptemp=ptemp->next;
    }
    if(ptemp==NULL)
    {
        exist=0;
       // printf("name not exist before\n");
    }

    else
    {
        int kid=ptemp->id;
        struct nodePhone* ptemp2;
        ptemp2 =headp;
        while(ptemp2!=NULL)
        {
            if(kid==ptemp2->id)
            {
                printf("number=%s\n",ptemp2->phone);
            }
            ptemp2=ptemp2->next;
        }
    }
    return exist;
}
int search_by_phone(char sphone[12])
{
    struct nodePhone* ptemp;
    ptemp=headp;
    int exist;
    while( ptemp!=NULL)
    {
        if (strcmp(sphone, ptemp->phone)==0)
        {
            break;
        }
        ptemp=ptemp->next;
    }
    if(ptemp==NULL)
    { exist=0;
       // printf("phone not exist before\n");

    }

    else
    {
        int kid=ptemp->id;
        struct nodeName* ptemp2;
        ptemp2 =headn;
        while(ptemp2!=NULL)
        {
            if(kid==ptemp2->id)
            {
                printf("name = %s\n",ptemp2->name);
            }
            ptemp2=ptemp2->next;
        }
    }return exist;
}


void modifyName(char name[])
{
    char newname[21];
    char sname[21];
     struct nodeName* temp;
    temp=headn;
    while( temp!=NULL)
    {
        if (strcmpi(name, temp->name)==0)
        {
            break;
        }
        temp=temp->next;
    }
    if(temp==NULL)
        printf("the name you want to modify not exists\n");
    else
    {

        printf("\n Enter the new name : ");
        int exist;
        do
            {exist=0;
                strcpy(newname,get_name()) ;
                exist=search_by_name(newname);
                if (exist==1)
                printf("\n this name is already in the system : ");
            }while(exist==1);

        if(exist==0)
        {
            strcpy( temp -> name,newname );
        printf("\n The name updated successfully!");
        }

    }
}
struct sim_call
{
    char phone[12];
    struct sim_call* prev;
};
struct sim_call* tos=null;

void dis_sim_call()
{
    struct sim_call* pparse;
    pparse=tos;
    if(pparse==null)
        {
            printf("no call logs yet\n\n");
        }
    else
        {
            do
            {
               printf("%s\n\n",pparse->phone);
               pparse=pparse->prev ;
            }while(pparse!=null);
        }
}
void push (char phone[])
{
    struct sim_call* temp;
    temp=(struct sim_call*)malloc(sizeof(struct sim_call));
    strcpy(temp->phone,phone);
    if(tos==null)
    {
        tos=temp;
        temp->prev=null;
    }
    else
    {
        temp->prev=tos;
        tos=temp;
    }
}

void delete_by_name(char sname[21])
{

                struct nodeName* ptemp,*pntemp,*pptemp;
                ptemp=headn;

                struct nodePhone* ph_ptemp,*ph_pntemp,*ph_pptemp;
                ph_ptemp=headp;

                while( ptemp!=NULL)
                    {
                        if (strcmpi(sname, ptemp->name)==0)
                            {
                                break;
                            }
                        ptemp=ptemp->next;
                    }
                if(ptemp==NULL)
                    printf("not found\n");
                else
                {
                    int kid=ptemp->id;
                    //-------------delete---------

                    pntemp=ptemp->next;
                    pptemp=ptemp->prev;
                    free(ptemp);
                    if(pptemp==NULL)
                        headn=pntemp;
                    else if(pntemp==NULL)
                        tailn=pptemp;
                    else
                    {
                        pptemp->next = pntemp;
                        pntemp->prev = pptemp;
                    }

                    while( ph_ptemp!=NULL)
                        {
                            if (ph_ptemp->id==kid)
                                {
                                    ph_pntemp=ph_ptemp->next;
                                    ph_pptemp=ph_ptemp->prev;
                                    free(ptemp);
                                    if(ph_pptemp==NULL)
                                        headp=ph_pntemp;
                                    else if(ph_pntemp==NULL)
                                        tailp=ph_pptemp;
                                    else
                                        {
                                            ph_pptemp->next = ph_pntemp;
                                            ph_pntemp->prev = ph_pptemp;
                                        }
                                                }
                            ph_ptemp=ph_ptemp->next;
                        }


                }
       // printf("the phone number( %s )are deleted",sphone);


}

void delete_by_phone(char sphone[12])
{

                struct nodePhone* ptemp,*pntemp,*pptemp;
                ptemp=headp;
                if(ptemp==NULL)
                {
                    printf("not found\n");
                    return;
                }
                else
                {
                //-------------delete---------
                    while( ptemp!=NULL)
                        {
                            if (strcmpi(sphone, ptemp->phone)==0)
                                {
                                    break;
                                }
                            ptemp=ptemp->next;
                        }
                    pntemp=ptemp->next;
                    pptemp=ptemp->prev;
                    free(ptemp);
                    if(pptemp==NULL)
                        headp=pntemp;
                    else if(pntemp==NULL)
                        tailp=pptemp;
                    else
                        {
                            pptemp->next = pntemp;
                            pntemp->prev = pptemp;
                        }

                }
        printf("the phone number( %s )are deleted",sphone);
        return;
}



void modifyPhone(char phone[12])
{
    char newphone[12];
     struct nodePhone* temp,*temp2;
    temp=headp;
    while( temp!=NULL)
    {
        if (strcmp(phone, temp->phone)==0)
        {
            break;
        }
        temp=temp->next;
    }
    if(temp==NULL)
        printf("The phone you want to update not exists\n");
    else
    {
        int exist=0;
        printf("\n Enter the new phone : ");

        do
        {
            exist=0;
             strcpy(newphone,get_phone()) ;
             temp2=headp;
                while( temp2!=NULL)
                {
                    if (strcmp(newphone, temp2->phone)==0)
                    {
                        exist=1;
                        break;
                    }
                    temp2=temp2->next;
                }
             if (exist==1)
                printf("\n this phone is already in the system : ");

        }while(exist==1);



        if(exist==0)
        {
            strcpy ( temp->phone, newphone );
        printf("\n The phone updated successfully!");
        }
    }
}
int appendName(char name [])
{
    struct nodeName * temp ;
    temp = (struct nodeName * )malloc( sizeof (struct nodeName )) ;
    if(temp == NULL)
    {
        return;
    }
    else
    {
        id++;
        strcpy ( temp -> name,name );
        temp ->id = id ;
        if ( headn  == NULL)
        {
            headn = tailn = temp ;
            temp -> next = NULL ;
            temp -> prev = NULL ;
        }
        else
        {
            temp-> next = NULL ;
            temp -> prev = tailn ;
            tailn -> next = temp ;
            tailn = temp ;
        }
    }
    return 0;
}


void appendPhone(char phone [])
{
    struct nodePhone * tempp ;
    struct nodeName *tempn;
    tempp = (struct nodePhone * )malloc ( sizeof (struct nodePhone )) ;
    if(tempp == NULL)
    {
        return;
    }
    else
    {
        tempp->id = id;
        strcpy ( tempp -> phone, phone );
        if ( headp  == NULL)
        {
            headp = tailp = tempp ;
            tempp -> next = NULL ;
            tempp -> prev = NULL ;
        }
        else
        {
            tempp-> next = NULL ;
            tempp -> prev = tailp ;
            tailp -> next = tempp ;
            tailp = tempp ;
        }
    }
}

int count()
{
    int c=0;
    struct nodeName * temp =headn;
    while(temp !=NULL)
    {
        c++;
        temp=temp->next;
    }
    return c;
}

void display()
{
    struct nodeName* temp=headn;
    while(temp !=NULL)
    {
        printf("%i , %s  ",temp->id,temp->name);
        temp=temp->next;
    }
}
char** temparr;
 char** marr;
void merg(char* marr,int start,int mid,int end)
{
    int st1=start,st2=mid+1,i=start;
    while(st1<=mid && st2<=end)
    {
       // while(arr[st1]<arr[st2] && st1<=mid && st2<=end)
       while((strcmpi(marr[st1],marr[st2])<0) && st1<=mid && st2<=end )
        {
            strcpy(temparr[i],marr[st1]);
            i++;
            st1++;
        }
        //while(arr[st2]<arr[st1] && st2<=end && st1<=mid)
        while((strcmpi(marr[st2],marr[st1])<0) && st2<=end && st1<=mid )
        {
            strcpy(temparr[i],marr[st2]);
            i++;
            st2++;
        }
    }
    while(st1<=mid)
    {
        temparr[i++]=marr[st1++];
    }
    while(st2<=end)
    {
        temparr[i++]=marr[st2++];
    }
    for(i=start; i<=end; i++)
    {
        marr[i]=temparr[i];
    }
}

void merg_sort(char* marr,int start,int end)
{
    if(start<end)
    {
        int mid=(start+end)/2;
        merg_sort(marr,start,mid);
        merg_sort(marr,mid+1,end);
        merg(marr,start,mid,end);
    }

}

int main()
{
    char menu[12][20]= {"append","count","search_by_name","search_by_phone","display","Modify_by_name","Modify_by_phone","bubble sort","delete by name","delete by phone","call","merge sort"},ch,name[21],phone[12],c;
    int i,counter=0, flag=0;
//for sorting
struct nodeName* arr;
struct nodeName *bubblesort;
bubblesort=NULL;
struct nodeName *parse;
parse=headn;
    do
    {
        system("cls");
        for(i=0; i<12; i++)
        {
            gotoxy(10,2+2*i);
            if(i==counter)
                textattr(0x70);
            _cprintf("%s",menu[i]);
            textattr(0x07);
        }
        ch=_getch();
        switch(ch)
        {
        case-32:
            ch=_getch();
            switch(ch)
            {
            case up:
                counter--;
                if(counter<0)
                    counter=11;
                break;
            case down:
                counter++;
                if(counter>11)
                    counter=0;
                break;
            }
            break;
        case enter :
            //append
            if(counter==0)
            {int exist=0;
                char* name;
                char*num;
                system("cls");

                _flushall();
                do{
                    name=get_name();
                    exist=search_by_name(name);
                   if(exist!=0)
            {
                printf("\nthis name already exists in the system. please,renter the name...\n");
            }

                }while(exist!=0);

                appendName(name);

                do{

                    num=get_phone();
            exist=search_by_phone(num);
                    if(exist!=0)
            {
                printf("\nthis phone already exists in system... plz re enter ur phone\n");
            }
                }while(exist!=0);

                appendPhone(num);
                printf("If you want to add another number press a \n");
                c=_getch();
                while(c==97)
                {
                    printf("\n");
                    do{
                        num=get_phone();
                        exist=search_by_phone(num);
                        if(exist!=0)
            {
                printf("\nthis phone already exists in system... plz re enter ur phone\n");
            }
                    }while(exist!=0);
                   // num=get_phone();
                    appendPhone(num);
                    printf("If you want to add another number press a");
                    c=_getch();
                }
            }
            else if(counter==1)
            {
                system("cls");
                int i = count();
                printf("the number of name you entered is: ");
                printf("%i",i);
                _getch();

            }
            else if (counter==2)
            {
                system("cls");

                char sname[21];
                printf("enter name you want to search : ");
                gets(sname);
                search_by_name(sname);
                _getch();
            }
            else if (counter==3)
            {
                system("cls");
                char sphone[12];
                printf("enter phone you want to search : ");
                scanf("%s",sphone);
                search_by_phone(sphone);
                _getch();
            }
            else if(counter==4)
            {
                system("cls");
                display();
                _getch();
            }
            //modify name
            else if(counter==5)
            {
                system("cls");
                char *mname;
                printf("enter name you want to update : ");
                mname=get_name();
                //gets(mname);
                modifyName(mname);
                _getch();
            }
             else if(counter==6)
            {
                system("cls");
                char *pnum;
                printf("enter phone you want to update : ");
                pnum=get_phone();
                //gets(pname);
                modifyPhone(pnum);
                _getch();
            }
            else if(counter==7)
            {
                system("cls");
                int count_node=0;
                count_node=count();
                if(count_node==0)
                {
                    printf("sorry no data to be sorted");
                    _flushall();
                            _getch();
                            _flushall();
                }
                else
                {
                    char** sarr;
                    parse=headn;
                    sarr=(char**)malloc(count_node*sizeof(char*));

                    for(int i=0;i<count_node;i++)
                    {
                    sarr[i]=parse->name;
                        parse=parse->next;

                    }
                    char* temp;
                    temp=(char*)malloc(21*sizeof(char));
                    int f;

                    for(int i=count_node-1; i>0; i--)
                    {
                        for(int j=0; j<i; j++)
                           {
                               if(strcmp(sarr[j],sarr[j+1]))
                            {
                                strcpy(temp,sarr[j]);
                                strcpy(sarr[j],sarr[j+1]);
                                strcpy(sarr[j+1],temp);
                                f=1;
                            }}
                        if(f==0)
                            break;
                    }
                    printf("name sorted is ");
                    for(int i=0; i<count_node; i++)
                       {
                           printf("\nelement name is %s",sarr[i]);
                       }
                 _flushall();
                    _getch();
                    _flushall();



                }
            }


            else if(counter==8)
            {
               system("cls");
                char sname[21];

                printf("enter name  you want to delete: ");
                scanf("%s",sname);

                delete_by_name(sname);
                printf("contacts of %s are deleted",sname);
                _getch();
            }

            else if(counter==9)
            {
               system("cls");
                char sphone[12];

                printf("enter phone  you want to delete: ");
                _flushall();
                gets(sphone);
                _flushall();
                delete_by_phone(sphone);
                _getch();
            }
            if(counter==10)
                {
                    char ex;
                    do
                    {
                        system("cls");
                        char sphone[12];
                        printf("recently called numbers:\n\n");
                        dis_sim_call();
                        _flushall();
                        printf("enter the phone you wanr=t to call:  ");
                        gets(sphone);
                        _flushall();
                        push(sphone);
                        _flushall();
                        printf("\npress e to exit call: ");
                        ex=_getch();
                    }while(ex!='e');
                }
            if(counter==11)
            {
                system("cls");
                int count_node=0;
                count_node=count();
                if(count_node==0)
                {
                    printf("sorry no data to be sorted");
                    _flushall();
                            _getch();
                            _flushall();
                }
                else
                {

                    parse=headn;
                    marr=(char**)malloc(count_node*sizeof(char*));
                    temparr=(char**)malloc(count_node*sizeof(char*));

                    for(int i=0;i<count_node;i++)
                    {
                    marr[i]=parse->name;
                        parse=parse->next;

                    }
                    merg_sort(marr,0,count_node);
                    /*
                    char* temp2;
                    temp2=(char*)malloc(21*sizeof(char));
                    int f;

                    for(int i=count_node-1; i>0; i--)
                    {
                        for(int j=0; j<i; j++)
                           {
                               if(strcmp(sarr[j],sarr[j+1]))
                            {
                                strcpy(temp,sarr[j]);
                                strcpy(sarr[j],sarr[j+1]);
                                strcpy(sarr[j+1],temp);
                                f=1;
                            }}
                        if(f==0)
                            break;
                    }
    */
                    printf("name sorted is ");
                    for(int i=0; i<count_node; i++)
                       {
                           printf("\nelement name is %s",marr[i]);
                       }
                 _flushall();
                    _getch();
                    _flushall();
                }

            }

            break;
        }
    }
    while(flag==0);
}
