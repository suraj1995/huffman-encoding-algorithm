/*

Program Statement : Implementation of Huffman Tree

Description : By Designing the Huffman Tree it is possible to encode the given sentence based on the occurrence of the character in the
string

*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"characterFrequency.h"
#define MAXSIZE 15

//structure declaraction to store the code word generated from the huffman tree
struct Code
{
        char ch;                //to store the character
        char code[MAXSIZE];     //TO store the code word for respective character

};
typedef struct Code CODE;

//structure declaraction to store the tree datastructure
struct Tree
{       
        char character;         //variable to hold the character
        float prob;             //To store the probability of occurrence of the respective character in the given text
        struct Tree *left;
        struct Tree *right;
};

typedef struct Tree TREE;

//structure to store the information about the collection of data and intermediate trees
struct Node
{
        TREE *root;             //pointer variable to hold the root of the tree
        struct Node *link;      //link to the next node

};
typedef struct Node NODE;


//set of global variables
CODE code[MAXSIZE];
int pointer;            //variable to hold the count of how many code word has been generated for particular character
FREQUENCY fre[MAXSIZE];     //array of structure declared in user defined header file which contins the information about frequency and
                        // probability of occurrence of characters in the given text.

NODE *n=NULL,*backup;   //n is a pointer to hold the address of first node
        

//Function to generate the node by allocating the memory for each node.
NODE *getNode()
{
        NODE *temp;
        temp = (NODE *)malloc(sizeof(NODE *));
        temp->root = (TREE *) malloc(sizeof(TREE *));
        temp->link=NULL;
        temp->root->left = NULL;
        temp->root->right = NULL;
        return temp;
        
}

void insert(char,float);                //function to insert character and its probability into linked list
void constructTree(NODE *,NODE *);      //function to construct the huffman tree 
void insertTree(NODE *);                //function to insert intermediate tree into the list
void inorder(TREE *);                   //Process the inorder traversal of huffman tree
void display();
void encode(TREE *,int [],int);         //encode the set of character based on the generated huffman tree
void diplayEncodedString(char []);      //display the encoded string

int main()
{
        int num,i;
        char c;
        char sentence[MAXSIZE];
        int top=0,arr[MAXSIZE];
        
        NODE *temp1,*temp2;
        
        printf("Enter the sentence to be encoded : ");
        scanf("%[^\n]",sentence);
        
        num = calculateFre(fre,sentence);       //calculate the frequency of occurrence
                
        displayFre(fre);                        //displayFre() function present in the header file.
       
        for(i=0;i<num;i++)
        {
                insert(fre[i].ch,fre[i].prob);  //insert every character into linked list
        }
        
        //display();
        
        while(n->link != NULL)
        {
                temp1=n;
                temp2 = n->link;
                n=n->link->link;
                constructTree(temp1,temp2);
                
        }
      
        encode(n->root,arr,top);
       
        diplayEncodedString(sentence);
        //inorder(n->root);


}

void insert(char ch,float prob)
{
        NODE *prev,*cur,*temp;
        prev=NULL;
        temp = getNode();
        temp->root->prob = prob;
        temp->root->character = ch;
        if(n == NULL)
        {
            n=temp;    
                
        }
        else if((n->root->prob) > prob)
        {
                temp->link = n;
                n=temp;
        }
        else if(n->link == NULL)
        {
                cur = n;
                cur->link = temp;
        }
        else
        {
               
               cur = n;
                
                while(cur != NULL)
                {
                        if((cur->root->prob) > prob)
                        {
                           
                                temp->link = prev -> link;
                                prev->link = temp;
                                break;                          
                        }       
                        prev = cur;
                        cur = cur->link;
        
                }
                
                if(cur==NULL)
                {
                        prev->link=temp;
                }
                
        }
        
}

void constructTree(NODE *temp1,NODE *temp2)
{
        NODE *temp;
        
        temp = getNode();
        temp->root->left=temp1->root;
        temp->root->right=temp2->root;
        temp->root->prob = temp1->root->prob + temp2->root->prob;
        insertTree(temp);
        

}

void insertTree(NODE *temp)
{
        NODE *cur,*prev;
        
        if(n==NULL)
        {
               n=temp;
               return;
        }
        
        else if(n->root->prob > temp->root->prob)
        {
                temp->link = n;
                n=temp;
                return;
        }
        else if(n->link == NULL)
        {
                n->link = temp;
        }
        else
        {
                prev=NULL;
                cur = n;
        
                while(cur!=NULL)
                {
                        if(temp->root->prob < cur->root->prob)
                        {
                                
                                temp->link = prev->link;
                                prev->link = temp;
                                break;
                        }
                        prev = cur;
                        cur = cur->link;
                }
                if(cur == NULL)
                {
                        prev->link = temp;
                }
        }

}

void inorder(TREE *root)
{
        if(root!=NULL)
        {
                inorder(root->left);
                //printf("%f------%c\n",root->prob,root->character);
                inorder(root->right);
        } 

}

void display()
{
        NODE *test;
        
        test = n;
        
        while(test!=NULL)
        {
                printf("%f------%c\n",test->root->prob,test->root->character);
                test = test->link;
        }
}

void encode(TREE *head,int arr[],int top)
{
      
      char temp[MAXSIZE];
      
      
      if(head->left != NULL)
      {
                arr[top] = 0;
                encode(head->left,arr,top+1);
      } 
      if(head->right != NULL)
      {
                arr[top] = 1;
                encode(head->right,arr,top+1);
      }  
      if(head->left==NULL && head->right==NULL)
      {
                int i;
                
                for(i=0;i<top;i++)
                {
                        temp[i] = arr[i]+48;
                }
                temp[i] = '\0';
                strcpy(code[pointer].code,temp);
                code[pointer].ch = head->character;
                //printf("%c   %s\n",head->character,code[pointer].code); 
                pointer++;
                
      }  
}

void diplayEncodedString(char string[])
{       
        char codeWord[100];
        int i,j;
        codeWord[0]='\0';
        printf("\nCHARACTER\tCODEWORD\n");
        for(i=0;i<pointer;i++)
        {
                j=0;
                while(j<pointer)
                {
                        if(string[i] == code[j].ch)
                        {
                                
                                strcat(codeWord,code[j].code);
                                break;
                        }
                        j++;
                        
                }
                printf("\n%c\t\t%s\n",code[i].ch,code[i].code); 
        }
        
        printf("Encoded string for the given string %s is \n%s\n",string,codeWord);
}
