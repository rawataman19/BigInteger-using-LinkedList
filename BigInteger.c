#include "BigInteger.h"

void Additiontolinkedlist(struct Node ** head, int val){
    struct Node * newnode=(struct Node * )malloc(sizeof(struct Node));
    newnode->data=val;
    newnode->next=NULL;
    if(!(*head)){
        *head=newnode;
        return ;
    }
    struct Node* itr=(*head);
    while(itr->next)  
        itr=itr->next;

    itr->next=newnode;
}
struct BigInteger initialise(char * s){
    struct BigInteger b;
    b.head=NULL;
    int l=0;
    for(l=0;s[l]!='\0';l++);
    for(int i=l-1;i>=0;i--){
        int digit=s[i]-'0';
        if(digit>=0 && digit<=9){
            Additiontolinkedlist(&b.head,digit);//insert at end
        }
    }
    return b;
}
struct Node * reverse(struct Node * head){
    if(head==NULL || head->next==NULL)
    return head;

    struct Node * curr=head;
    struct Node * prev=NULL;
    struct Node * currnxt=head->next;
    while(curr){
        curr->next=prev;
        prev=curr;
        curr=currnxt;
        if(currnxt)
        currnxt=currnxt->next;
    }
    return prev;
}
int count(struct Node * head){
    int c=0;
    while(head){
        head=head->next;
        c++;
    }
    return c;
}
void display(struct Node* head){
    while(head){
        printf("%d",head->data);
        head=head->next;
    }
}
void Addition(struct Node* head1,struct Node* head2, struct Node** addhead){
    *addhead=NULL;//FOR MULTIPLYING AdditionITION
    int carry=0;
    struct Node* itr=*addhead;
    while(head1 || head2 || carry){

        int sum=carry;
        if(head1){
            sum+=head1->data;
            head1=head1->next;
        }
        if(head2){
            sum+=head2->data;
            head2=head2->next;
        }
        
        int nodevalue=sum%10;
        carry=sum/10;
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        newNode->data=nodevalue;
        newNode->next=NULL;

        if((*addhead)==NULL)
        {
            (*addhead)=newNode;
            itr=newNode;
        }
        else{
            itr->next=newNode;
            itr=newNode;
        }
    }
}
void subtract(struct Node* head1, struct Node* head2, struct Node** subtracthead){
    //now i would put the larger value in head1 and smaller value in head2 and change the sign to negative if head2 is bigger
    if(head2==NULL){
        *subtracthead=head1;
        return ;
    }
    struct Node* itr=(*subtracthead);

    while(head1){
        int x=head1->data;
        int y=0;
        if(head2)
        y=head2->data;
        int diff=x-y;
        if(diff<0){//means diff is negative
            diff+=10;
            head1->next->data-=1;
        }
        struct Node * newNode=(struct Node* )malloc(sizeof(struct Node));
        newNode->data=diff;
        newNode->next=NULL;

        if((*subtracthead)==NULL){
            *subtracthead=newNode;
            itr=newNode;
        }
        else{
            itr->next=newNode;
            itr=newNode;
        }
        head1=head1->next;
        if(head2)
        head2=head2->next;
    }

}
struct Node* multiplyhelper(struct Node* head1, int number,int zeroes){
    struct Node* ans=NULL;
    struct Node* itr=NULL;
    while(zeroes){
        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        newNode->data=0;
        newNode->next=NULL;
        if(ans==NULL){
            ans=newNode;
            itr=newNode;
        }
        else{
            itr->next=newNode;
            itr=newNode;
        }
        zeroes--;
    }
    int carry=0;
    while(head1|| carry){
        int value=0;
        if(head1)
        value+=head1->data;

        value=value*number+carry;
        carry=value/10;
        value=value%10;

        struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
        newNode->data=value;
        newNode->next=NULL;
        if(ans==NULL){
            ans=newNode;
            itr=newNode;
        }
        else{
            itr->next=newNode;
            itr=newNode;
        }
        if(head1)
        head1=head1->next;
    }
    return ans;
}
void multiply(struct Node * head1,struct Node* head2, struct Node** multiplyhead){//head1,head2,multiplyhead all points to ones position
    
    int zeroes=0;
    while(head2){
        int multiplier=head2->data;
        struct Node* solomul=multiplyhelper(head1,multiplier,zeroes);
        zeroes++;
        Addition(*multiplyhead,solomul,multiplyhead);
        head2=head2->next;
    }
}
void linkedlistcreator(struct Node * newNode,struct Node** dividedhead){
    if((*dividedhead)==NULL){
        (*dividedhead)=newNode;
        return ;
    }
    struct Node* itr=(*dividedhead);
    while(itr->next){
        itr=itr->next;
    }
    itr->next=newNode;
}
int subtractforquotient(struct Node * first, struct Node * second){
    if(count(first)<count(second))
    return 0;
    if(count(first)>count(second))
    return 1;
    while(first){
        if(first->data>second->data)
        return 1;
        else if(first->data<second->data)
        return 0;
        first=first->next;
        second=second->next;
    }
    return 1;


}
struct Node * frontzeroterminator(struct Node * head){
    while(head && head->data==0)
        head=head->next;

    return head;
}
int quotientteller(struct Node * a,struct Node * product){
    if(product==NULL)
    return 0;
    //a * ans=product 

    struct Node * ansnode=(struct Node * )malloc(sizeof(struct Node));
    ansnode->next=NULL;
    int ans=0;

    for(int i=1;i<10;i++){

        ansnode->data=i;
        struct Node * multipliedvalue=NULL;
        multiply(a,ansnode,&multipliedvalue);
        multipliedvalue=reverse(multipliedvalue);
        multipliedvalue=frontzeroterminator(multipliedvalue);

        //returns 1 if a-multipliedvalue is positive value
        if(subtractforquotient(product,multipliedvalue)==1)
        ans=i;
        else
        break;

    }
    return ans;
}
int isallzero(struct Node * head){
    while(head &&head->data==0)
        head=head->next;
    
    if(head)    return 0;//sare zero nahi h 
    return 1;
}
void divide(struct Node * head1, struct Node * head2, struct Node** dividedhead){
    head1=frontzeroterminator(head1);
    if(head2==NULL || frontzeroterminator(head2)==NULL){
        *dividedhead=NULL;
        return ;
    }
    if(head1==NULL )
    {
        struct Node * zero=(struct Node *)malloc(sizeof(struct Node));
        zero->data=0;
        zero->next=NULL;
        *dividedhead=zero;
        return ;
    }
    struct Node * remainderhead=NULL;

    int val=head1->data;
    struct Node *newnode=(struct Node * )malloc(sizeof(struct Node));
    newnode->data=val;
    newnode->next=NULL;
    remainderhead=newnode;
    head1=head1->next;


    while(head1){
        int quotient=quotientteller(head2,frontzeroterminator(remainderhead));
        

        struct Node* multipliedvalue=NULL;
        if((*dividedhead)==NULL && quotient==0){
            //EAT 5-STAR ...DO NOTHING            
        }
        else{
            struct Node * xyz=(struct Node *)malloc(sizeof(struct Node));
            xyz->data=quotient;
            xyz->next=NULL;

            linkedlistcreator(xyz,dividedhead);
            struct Node * head2temp=head2;
            multiply(head2temp,xyz,&multipliedvalue);
            multipliedvalue=reverse(multipliedvalue);\
        }
        

        struct Node* temp=NULL;
        if(isallzero(remainderhead)==0){//mtlb agar sab 0 nhi h means !=0 whole value
            remainderhead=frontzeroterminator(remainderhead);
        }
        
        multipliedvalue=frontzeroterminator(multipliedvalue);
        subtract(reverse(remainderhead),reverse(multipliedvalue),&temp);
        remainderhead=reverse(temp);

        struct Node * iterator=remainderhead;
        while(iterator->next){
            iterator=iterator->next;
        }
        int value=head1->data;
        head1=head1->next;
        struct Node * creatingnode=(struct Node *)malloc(sizeof(struct Node));
        creatingnode->data=value;
        creatingnode->next=NULL;
        iterator ->next=creatingnode;
        
        if(isallzero(remainderhead)==0){//mtlb agar sab 0 nhi h means !=0 whole value
            remainderhead=frontzeroterminator(remainderhead);
        }
        
    }
    int quotient=quotientteller(head2,frontzeroterminator(remainderhead));

    struct Node* multipliedvalue=NULL;
    if((*dividedhead)==NULL && quotient==0){
            //EAT 5-STAR ...DO NOTHING            
    }
    else{
        struct Node * xyz=(struct Node *)malloc(sizeof(struct Node));
        xyz->data=quotient;
        xyz->next=NULL;

        linkedlistcreator(xyz,dividedhead);
    }      
}
void modulus(struct Node * head1,struct Node * head2, struct Node** modulushead){
    struct Node *head1dividedhead2=NULL;
    divide(head1,head2,&head1dividedhead2);
    
    struct Node * multiplied=NULL;
    multiply(reverse(head1dividedhead2),head2,&multiplied);
    struct Node* ans=NULL;
    subtract(reverse(head1),multiplied,&ans);
    ans=reverse(ans);
    ans=frontzeroterminator(ans);
    (*modulushead)=ans;
}
struct BigInteger add(struct BigInteger a, struct BigInteger b){
    struct BigInteger ans;
    ans.head=NULL;
    Addition(a.head,b.head,&ans.head);
    ans.head=reverse(ans.head);
    return ans;
}
struct BigInteger sub(struct BigInteger a , struct BigInteger b){
    struct BigInteger ans;
    ans.head=NULL;
    subtract(a.head,b.head,&ans.head);
    ans.head=reverse(ans.head);
    return ans;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b){
    struct BigInteger ans;
    ans.head=NULL;
    multiply(a.head,b.head,&ans.head);
    ans.head=reverse(ans.head);
    return ans;
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b){
    struct BigInteger ans;
    ans.head=NULL;
    a.head=reverse(a.head);
    divide(a.head,b.head,&ans.head);
    a.head=reverse(a.head);
    return ans;
}
struct BigInteger mod(struct BigInteger a , struct BigInteger b){
    struct BigInteger ans;
    ans.head=NULL;
    a.head=reverse(a.head);
    modulus(a.head,b.head,&ans.head);
    a.head=reverse(a.head);
    return ans;
}
