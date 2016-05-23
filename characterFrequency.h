#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct frequency
{
        char ch;
        int freq;
        float prob;
};
typedef struct frequency FREQUENCY;


int top;

int calculateFre(FREQUENCY fre[],char sentence[])
{
        int i,j;
        int length = strlen(sentence);
        
        fre[0].ch = sentence[0];
        fre[0].freq = fre[0].freq+1;
        top++;
        for(i=1;i<length;i++)
        {
               j=0;
               while(j<top)
               {
                        if(fre[j].ch == sentence[i])
                        {
                             fre[j].freq = fre[j].freq+1;  
                             break; 
                        }
                        j++;      
               } 
               if(j==top)
               {
                        
                        fre[top].ch = sentence[i];
                        fre[top].freq = 1;
                        top++;
               }
        }
        
        for(i=0;i<top;i++)
        {
               fre[i].prob = (float)fre[i].freq / length; 
        }
        
        return top;

}

void displayFre(FREQUENCY fre[])
{
        int i;
        
        printf("\ncharacter\tfrequency\tprobability\n");
        for(i=0;i<top;i++)
        {
                
                printf("%c\t\t%d\t\t%f\n",fre[i].ch,fre[i].freq,fre[i].prob);
                
        }

}
