#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"
#include<string.h>
void* intal_create(const char* str)
{
    if(str==NULL)
		return NULL;
    else
	{
            int n=strlen(str);
	    char *s=(char *)malloc(sizeof(char)*(n+1));
	    if(s==NULL)
	        return NULL;
	    else
	    {
	        strcpy(s,str);
	        return s;
	    }
	 }
}

char* intal2str(void* intal)
{
    
    char* s=(char*)intal;
    return s;
}

void* remove_zeros(void* intal1)
{
   
    char* str1=intal2str(intal1);
    char *p1 = str1;
    while (*(p1+1) && (*p1 == '0'))
        p1++;
    void* intal2=(void*)p1;
    return intal2;
}
void* intal_add(void* intal1, void* intal2)
{
    
    intal1=remove_zeros(intal1);
    intal2=remove_zeros(intal2);
    char* str1=intal2str(intal1);
    char* str2=intal2str(intal2);
    int n1=strlen(str1),n2=strlen(str2),max,c=0;
    // Before proceeding further, make sure length
    // of str2 is larger.
    if (intal_compare(intal1,intal2)==1)
    {
        max=n1;
        str1=intal2str(intal2);
        str2=intal2str(intal1);
    }
    else
        max=n2;    

    char* result=(char*)malloc(sizeof(char)*(max+2));
    n1=strlen(str1),n2=strlen(str2);
    int diff =n2 - n1;
     result[max+1]='\0';
    // Initialy take carry zero
    int carry = 0;
 
    // Traverse from end of both strings
    for (int i=n1-1; i>=0; i--)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i+diff]-'0')+carry);
        result[c++]=(char)(sum%10 + '0');
        carry = sum/10;
    }
 
    // Add remaining digits of str2[]
    for (int i=n2-n1-1; i>=0; i--)
    {
        int sum = ((str2[i]-'0')+carry);
        result[c++]=(char)(sum%10 + '0');
        carry = sum/10;
    }
 
    // Add remaining carry
    if (carry)
        result[c++]=(char)(carry+'0');
     result[c++]='\0';
     int n=strlen(result);
     for(int i=0;i<n/2;i++)
     {
         char tmp=result[i];
         result[i]=result[n-i-1];
         result[n-i-1]=tmp;
      }
     void* addition_answer=(void*)(result);
    return remove_zeros(addition_answer);
}

 
// Function for finding difference of larger numbers
void* intal_diff(void* intal1, void* intal2)
{
    
    intal1=remove_zeros(intal1);
    intal2=remove_zeros(intal2);
    char* str1=intal2str(intal1);
    char* str2=intal2str(intal2);
    int n1=strlen(str1),n2=strlen(str2),max=0;
    // Before proceeding further, make sure str1
    // is not smaller

    if (intal_compare(intal1,intal2)==-1)
    {
        max=n2;
	str1=intal2str(intal2);
        str2=intal2str(intal1);
     }
     else
        max=n1;       
 
    // Take an empty string for storing result
    char* result=(char*)malloc(sizeof(char)*(max+1));
 
    // Calculate lengths of both string
    n1=strlen(str1),n2=strlen(str2);
    int diff = n1 - n2,c=0;

    int borrow = 0;
 
    // Traverse from end of both strings
    for (int i=n2-1; i>=0; i--)
    {
        // Do school mathematics, compute difference of
        // current digits and carry
        int sub = ((str1[i+diff]-'0') -(str2[i]-'0') - borrow);
        if (sub < 0)
        {
            sub = sub+10;
            borrow = 1;
        }
        else
            borrow = 0;
 
        result[c++]=(char)(sub + '0');
    }
 
    // subtract remaining digits of str1[]
    for (int i=n1-n2-1; i>=0; i--)
    {
        if (str1[i]=='0' && borrow)
        {
            result[c++]='9';
            continue;
        }
        int sub = ((str1[i]-'0') - borrow);
        if (i>0 || sub>0) // remove preceding 0's
            result[c++]=sub+'0';
        borrow = 0;
 
    }
 
    // reverse resultant string

     result[c++]='\0';
     int n=strlen(result);
     for(int i=0;i<n/2;i++)
     {
         char tmp=result[i];
         result[i]=result[n-i-1];
         result[n-i-1]=tmp;
      }
     void* subtraction_answer=(void*)(result);
    return remove_zeros(subtraction_answer); 
}

void intal_destroy(void* intal)
{
	if(intal==NULL)
		return;
	if(intal!=NULL)
	{
     	    //free(intal);
        }
}


void* intal_increment(void* intal)
{
   
    char* one="1";
    void* intal1=intal_create(one);
    return intal_add(intal,intal1);
}

void* intal_decrement(void* intal)
{
    if(intal_compare(intal,intal_create("0"))==0)
       return intal_create("0");
    char* one="1";
    void* intal1=intal_create(one);
    return intal_diff(intal,intal1);
}

int intal_compare(void* intal1, void* intal2)
{
   
    char* str1=intal2str(intal1);
    char* str2=intal2str(intal2);
    char *p1 = str1, *p2 = str2;
    while (*(p1+1) && (*p1 == '0'))
        p1++;
    while (*(p2+1) && (*p2 == '0'))
        p2++;
    int n1=strlen(p1),n2=strlen(p2);
    if(n1>n2)
       return 1;
    else
    if(n1<n2)
       return -1;
    else
    {
	if (strcmp (p1, p2) == 0)
	    return 0;
	else
	if(strcmp(p1,p2)>0)
	    return 1;
	else
	    return -1;
     }
} 

void* intal_multiply(void* intal1, void* intal2)
{
    void* product=intal_create("0");
    void* zero=intal_create("0");
    while(intal_compare(intal2,zero)!=0)
    {
        product=intal_add(product,intal1);
        intal2=intal_decrement(intal2);
    }
    return product;        
}

char* compute_multiplier(char* rem,void* intal,int* cnt)
{
    int flag=intal_compare((void*)(rem),intal);
    *cnt=0;
    while(flag==1)
    {
       (*cnt)++;
       rem=intal_diff((void*)(rem),intal);
       flag=intal_compare((void*)(rem),intal);
    }
    if(flag==0)
    {
        (*cnt)++;
        rem=intal_diff((void*)(rem),intal);
    }
    return rem;
}
void* intal_divide(void* intal1,void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return NULL;
    if(intal_compare(intal2,intal_create("0"))==0)
        return NULL;
    if(intal_compare(intal1,intal2)==-1)
        return intal_create("0");
    char* no1=intal2str(remove_zeros(intal1));   
    char* no2=intal2str(remove_zeros(intal2));   
    int l1=strlen(no1);
    int l2=strlen(no2);
    char* rem=(char*)malloc(sizeof(char)*(l2+1));
    char* quo=(char*)malloc(sizeof(char)*(l1));
    int i,k=0;
    for(i=0;i<l2;i++)
    { 
        rem[i]=no1[i];
    }
    int len,cnt;
    while(i<=l1)
    {
        rem=compute_multiplier(rem,intal2,&cnt);
        quo[k++]=cnt+48;
        len=strlen(rem);
        rem[len]=no1[i++];
        rem[len+1]='\0';
     }
     quo[k]='\0';
     return remove_zeros((void*)(quo));
}


void* intal_pow(void* intal1, void* intal2)
{
	void *zero = intal_create("0");
	void *prod = intal_create("1");
        void* ten=intal_create("10");
        void* two=intal_create("2");
        void* one=intal_create("1");
	while(intal_compare(zero,intal2)!=0)
	{
 		char *ch2 = intal2str(intal2);
		int n = strlen(ch2);
		if((ch2[n-1]-'0')%2==1)
		{
			prod = intal_add(intal_multiply(prod,ten),one);
		}
		else
		{
			prod = intal_multiply(prod,ten);
		}
		intal2 = intal_divide(intal2,two);
	}
	void* exp=one;
        char* binary=intal2str(++prod);
	//printf("%s\n",binary);
        int len=strlen(binary);
	//printf("%d\n",len);
        for(int i=len-1;i>=0;i--)
        {
	    exp=intal_multiply(exp,exp);
            if(binary[i]=='1')
		{
                 exp=intal_multiply(exp,intal1);
		
		}
        }
	
         return exp;
	          
}
