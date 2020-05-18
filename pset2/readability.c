#include<stdio.h>
#include<cs50.h>
#include<math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main()
{
    string text=get_string("Text: ");
    float L,S,index;
    int grade;
    L=((float)count_letters(text)/(float)count_words(text))*100;
    S=((float)count_sentences(text)/(float)count_words(text))*100;
    index=(0.0588 * L) - (0.296 * S) - 15.8 ;
    grade=(int)round(index);

    if(index<1)
        printf("Before Grade 1\n");
    else if(index>=16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n",grade);
}
int count_letters(string text)
{
    int i=0,count=0;
    while(text[i]!='\0')
    {
        if((text[i]>64 && text[i]<91)||(text[i]>96 && text[i]<123))
            count++;
        i++;
    }
    return count;
}
int count_words(string text)
{
    int i=0,count=1;
    while(text[i]!='\0')
    {
        if(text[i]==' ')
            count++;
        i++;
    }
    return count;
}
int count_sentences(string text)
{
    int i=0,count=0;
    while(text[i]!='\0')
    {
        if(text[i]=='.' ||text[i]=='?' ||text[i]=='!')
            count++;
        i++;
    }
    return count;
}