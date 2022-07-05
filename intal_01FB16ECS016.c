#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "intal.h"
#include<string.h>
void* remove_zeros(void* intal1)
{
    if(intal1==NULL)
        return NULL;
    char* str1=intal2str(intal1);
    char *p1 = str1;
    while (*(p1+1) && (*p1 == '0'))
        p1++;
    void* intal2=(void*)p1;
    return intal2;
}

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
            if(str[0]<'0' || str[0]>'9')
            {
               char* zero=(char*)malloc(sizeof(char)*2);
               zero[0]='0';
               zero[1]='\0';
               void* tmp=(void*)zero;                   
	       return tmp;
               
            }
	    else
	    {
	        int k=0;
                while(k<n && str[k]>='0' && str[k]<='9')
                {
                     s[k]=str[k];
                     k++;
                }
                      
                s[k]='\0'; 
                void* tmp=(void*)s;                   
	        return remove_zeros(tmp);
	    }
	 }
}


char* intal2str(void* intal)
{
    if(intal==NULL)
        return "NaN";
    char* s=(char*)intal;
    char *s1=(char*)malloc(sizeof(char)*(strlen(s)+1));
    strcpy(s1,s);
    return s1;
}


void* intal_add(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return NULL;
    if(intal_compare(intal1,intal_create("0"))==0)
        return intal2;
    if(intal_compare(intal2,intal_create("0"))==0)
        return intal1;
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
    free(str1);
    free(str2);
    return remove_zeros((void*)(result));
}

 
// Function for finding difference of larger numbers
void* intal_diff(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return NULL;
    if(intal_compare(intal1,intal_create("0"))==0)
        return intal2;
    if(intal_compare(intal2,intal_create("0"))==0)
        return intal1;
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
    free(str1);
    free(str2);
    return remove_zeros((void*)(result)); 
}

void intal_destroy(void* intal)
{
	if(intal==NULL)
		return;
	if(intal!=NULL)
	{
     	    char *str=intal2str(intal);
            free(str);            
        }
}


void* intal_increment(void* intal)
{
    if(intal==NULL)
        return NULL;
    char* one="1";
    void* intal1=intal_create(one);
    return intal_add(intal,intal1);
}

void* intal_decrement(void* intal)
{
    if(intal==NULL)
        return NULL;
    if(intal_compare(intal,intal_create("0"))==0)
       return intal_create("0");
    char* one="1";
    void* intal1=intal_create(one);
    return intal_diff(intal,intal1);
}

int intal_compare(void* intal1, void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return -2;
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
        if(intal1==NULL || intal2==NULL)
            return NULL;
	int i = 0;
	//long long unsigned int j = 0;
	int comp = intal_compare(intal1,intal2);
	void *p1;
	void *p2;
	if(comp == -1)
	{
		p1 = intal_create(intal2str(intal2));
		p2 = intal_create(intal2str(intal1));	
	}
	else
	{
		p1 = intal_create(intal2str(intal1));
		p2 = intal_create(intal2str(intal2));
	}
	int l1 = strlen(intal2str(p1));
	int l2 = strlen(intal2str(p2));
	if(l1==0)
		return p1;
	else if(l2==0)
		return p2;
	int sum = 0;
	char *str3 = (char*)malloc(sizeof(char)*(l1+l2+1));
	for(;i<(l1+l2);i++)
	{
		str3[i] = '0';
	}
	str3[++i]='\n';
	
	int offset = l1+l2-1;
	char *str1 = intal2str(p1);
	char *str2 = intal2str(p2);
	
	for(i = l2-1;i>=0;i--)
	{
		int carry = 0;
		int k = 0;
		int j = 0;
		for(j = l1-1;j>=0;j--)
		{
			sum = (str2[i]-'0')*(str1[j]-'0');
			sum = sum + carry + (str3[offset-k]-'0');
			carry = sum/10;
			str3[offset-k] = (sum%10) + '0';
			k = k+1;
		}
		if(carry > 0)
		{
			str3[offset-k] = carry + '0';
		}
		offset = offset-1;
	}
        intal_destroy(p1);
        intal_destroy(p2);
        free(str1);
        free(str2);
	return(remove_zeros(intal_create(str3)));
	
}
char* calculate_multiplier(char* remainder,void* intal,int* count)
{
    int flag=intal_compare((void*)(remainder),intal);
    *count=0;
    while(flag==1)
    {
       (*count)++;
       remainder=intal_diff((void*)(remainder),intal);
       flag=intal_compare((void*)(remainder),intal);
    }
    if(flag==0)
    {
        (*count)++;
        remainder=intal_diff((void*)(remainder),intal);
    }
    return remainder;
}
void* intal_divide(void* intal1,void* intal2)
{
    if(intal1==NULL || intal2==NULL)
        return NULL;
    if(intal_compare(intal2,intal_create("0"))==0)
        return NULL;
    if(intal_compare(intal1,intal2)==-1)
        return intal_create("0");
    char* str1=intal2str(remove_zeros(intal1));   
    char* str2=intal2str(remove_zeros(intal2));   
    int n1=strlen(str1);
    int n2=strlen(str2);
    char* remainder=(char*)malloc(sizeof(char)*(n2+1));
    char* quotient=(char*)malloc(sizeof(char)*(n1));
    int i,k=0;
    for(i=0;i<n2;i++)
    { 
        remainder[i]=str1[i];
    }
    int length,count;
    while(i<=n1)
    {
        remainder=calculate_multiplier(remainder,intal2,&count);
        quotient[k++]=count+48;
        length=strlen(remainder);
        remainder[length]=str1[i++];
        remainder[length+1]='\0';
     }
     quotient[k]='\0';
     free(str1);
     free(str2);
     return remove_zeros((void*)(quotient));
}
        

void* intal_pow(void* intal1, void* intal2)
{
   if(intal1==NULL || intal2==NULL)
        return NULL;
   void* zero=intal_create("0");
   void* two=intal_create("2");
   if(intal_compare(intal1,zero)==0)
      return intal_create("0");
   if(intal_compare(intal2,zero)==0)
      return intal_create("1");
   void* p=intal_pow(intal1,intal_divide(intal2,two));
   p=intal_multiply(p,p);
   char* str2=intal2str(intal2);
   if((str2[strlen(str2)-1])=='1'||(str2[strlen(str2)-1])=='3'||(str2[strlen(str2)-1])=='5'||(str2[strlen(str2)-1])=='7'||(str2[strlen(str2)-1])=='9')
       p=intal_multiply(p,intal1);
   return p;
}

