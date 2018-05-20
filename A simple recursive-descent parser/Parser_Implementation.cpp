#include<iostream>
#include<stdio.h>
#include<ctype.h>
using namespace std;

//Lexical

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

void addChar();
void getChar();
void getNonBlank();
int lex();

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define INDET 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

int lookup(char ch){
    switch(ch){
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

void addChar(){
    if(lexLen <= 98){
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        cout<<"Error - lexeme is too long"<<endl;
}

void getChar(){
    if((nextChar = getc(in_fp)) != EOF){
        if(isalpha(nextChar))
            charClass = LETTER;
        else if(isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank(){
    while(isspace(nextChar))
        getchar();
}


int lex()
{
    lexLen = 0;
    getNonBlank();

    getChar();
    switch (charClass){
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INDET;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT){
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] =  0;
        break;
    }
    cout<<"Next token is: "<<nextToken<<", Next lexeme is "<<lexeme<<endl;
    return nextToken;
}

//Recursive-Descent Parser



int main(){
    return 0;
}
