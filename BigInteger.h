#ifndef BIGINTEGER_H
#define BIGINTEGER_H
#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node* next;
};
struct BigInteger{
    struct Node * head;
};


void Additiontolinkedlist(struct Node ** head, int val);
struct BigInteger initialise(char * s);
struct Node * reverse(struct Node * head);
int count(struct Node * head);
void display(struct Node* head);
void Addition(struct Node* head1,struct Node* head2, struct Node** addhead);
void subtract(struct Node* head1, struct Node* head2, struct Node** subtracthead);
struct Node* multiplyhelper(struct Node* head1, int number,int zeroes);
void multiply(struct Node * head1,struct Node* head2, struct Node** multiplyhead);
void linkedlistcreator(struct Node * newNode,struct Node** dividedhead);
int subtractforquotient(struct Node * first, struct Node * second);
struct Node * frontzeroterminator(struct Node * head);
int quotientteller(struct Node * a,struct Node * product);
int isallzero(struct Node * head);
void divide(struct Node * head1, struct Node * head2, struct Node** dividedhead);
void modulus(struct Node * head1,struct Node * head2, struct Node** modulushead);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a , struct BigInteger b);

#endif