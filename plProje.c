#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_KEYWORD_LENGTH 100

int isKeyword(char buffer[]) //generate isKeyword() method to find keywords
{
    char keywords[9][10] = {"move","to","size","int","out","loop","times","newline","from"};


    int i, flag = 0;

    for(i = 0; i <9; ++i)
    {
        if(strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}
int isOperator(char buffer[]) //generate isOperator() method to find operators
{
    char operators[2][10] = {"add","sub"};

    int i, flag = 0;

    for(i = 0; i <2; ++i)
    {
        if(strcmp(operators[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }

    return flag;
}
int isDigit(char buffer[]) //generate isDigit() method to find integer constants
{
    int flag=1;
    int i;

    for(i=0; i<sizeof(buffer)/4; i++)
    {

        if(isdigit(buffer[i])==0)
        {
            flag=0;
        }
    }
    return flag;
}
int isParenthesis(char c)    //generate isParenthesis() method to find open and close parenthesis
{

    char delimiters[] = {'[', ']'};
    int i;
    int result = 0; // false

    for (i = 0; i < 2; i++)
    {
        if (delimiters[i] == c)
        {
            if(c=='[')
            {
                result=1;

            }
            else if(c==']')
            {
                result=2;
            }

        }
    }
    return result;
}


int main()
{

    char ch, buffer[73],error[73],out_list[73],file[MAX_KEYWORD_LENGTH];
    FILE *fp,*fp2;
    int j=0,i=0,x=0,counter1=0,counter2=0,y,parant_num = 0,point_num = 0,line_num=1;
    char new_file[MAX_KEYWORD_LENGTH]="AnalyzeFile.txt";

    printf("Please enter the name of the file you want to analyze\n");

    fgets(file, 99, stdin);
    char *p = strchr(file, '\n'); // p will point to the newline in filename
    if(p) *p = 0;

    fp = fopen(file, "r");
    fp2=fopen(new_file,"w");




    if (fp)
    {

        while((ch = fgetc(fp)) != EOF)
        {

            if(isalnum(ch))
            {
                buffer[j++] = ch;
            }
            else if(ch=='{')
            {
                do
                {
                    ch = fgetc(fp);

                }
                while (ch != '}');
                ch=fgetc(fp);
                continue;
            }
            else if(ch=='“')
            {
                ch=fgetc(fp);
                while(ch !='”')
                {
                    out_list[x]=ch;
                    x++;
                    ch=fgetc(fp);

                }
                out_list[x]='\0';
                x=0;
                printf("'%s' is output list\n\n",out_list);
                fprintf(fp2,"'%s' is output list\n\n",out_list);

            }
            else if(ch == '+'||ch=='-')    //errors
            {
                error[i]=ch;
                i++;
                ch= fgetc(fp);
                error[i]=ch;
                i++;
                do
                {
                    ch= fgetc(fp);
                    error[i]=ch;
                    i++;

                }
                while(ch!=' ');
                error[i]='\0';
                i=0;
                printf("LINE %d : %s is not a valid integer [ERROR]\n\n",line_num,error);
                fprintf(fp2,ruba"LINE %d : %s is not a valid integer [ERROR]\n\n",line_num,error);

            }

            else if((ch == ' ' || ch == '\n' || ch=='.') && (j != 0))
            {
                if(isDigit(buffer)==1 && ch=='.')
                {
                    // to do not buffer[j]='\0'
                }
                else
                {
                    buffer[j] = '\0';
                    j = 0;
                }

                if(isOperator(buffer) == 1)
                {
                    printf("%s is operator\n\n", buffer);
                    fprintf(fp2,"%s is operator\n\n", buffer);
                }
                else if(isKeyword(buffer) == 1)
                {
                    printf("%s is keyword\n\n", buffer);
                    fprintf(fp2,"%s is keyword\n\n", buffer);
                    counter1++;
                }
                else if(isDigit(buffer)==1)
                {
                    if(ch=='.')
                    {
                        buffer[j]='.';
                        j++;
                        do
                        {
                            ch=fgetc(fp);
                            buffer[j]=ch;
                            j++;

                        }
                        while(ch!=' ');
                        buffer[j]='\0';
                        j=0;
                        printf("LINE %d : %s is not a valid integer [ERROR]\n\n",line_num,buffer);
                        fprintf(fp2,"LINE %d : %s is not a valid integer [ERROR]\n\n",line_num,buffer);
                        buffer[j]='\0';
                        j=0;

                    }
                    else
                    {
                        printf("%s is integer constant\n\n",buffer);
                        fprintf(fp2,"%s is Integer constant\n\n", buffer);
                    }
                }

                else
                {
                    printf("%s is identifier\n\n", buffer);
                    fprintf(fp2,"%s  is identifier\n\n", buffer);
                    counter2++;
                }

            }

            if ((ispunct(ch) || ch=='\n') )
            {
                if (isParenthesis(ch)==1)
                {
                    printf("'[' is open paranthesis \n\n");
                    fprintf(fp2,"']' is open paranthesis\n\n");
                    parant_num++;
                }
                if (isParenthesis(ch)==2)
                {
                    printf("']' is close paranthesis \n\n");
                    fprintf(fp2,"']' is close paranthesis\n\n");
                    parant_num++;
                }

                if (ch=='.') //generate isEndOfLine() method to find '.' end of the line
                {

                    printf("'.' is end of line character \n\n");
                    fprintf(fp2,"'.' is end of line character \n\n");
                    point_num++;
                    line_num++;
                    ch=fgetc(fp);

                }
                else
                {

                    line_num++;
                }


            }
        }
        printf("\nThe number of the following lexeme types\n");
        printf("------------------------------------------");
        printf("\nIdentifiers :%d\nParenthesis: %d\nKeywords :%d\nEnd of line characters: %d \n",counter2,parant_num,counter1,point_num);
        fclose(fp);
        fclose(fp2);
    }
    else
    {
        printf("File not found");

    }

    return 0;

}
