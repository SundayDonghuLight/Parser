#include<iostream>
#include<string>
#include<stdio.h>
#include<ctype.h>
using namespace std;

//Lexical analysis

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
#define DOT 2
#define UNKNOWN 99

#define INT_LIT 10
#define INDET 11
#define REAL_LIT 12

#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMICOLON 27
#define POWER 28


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
    case ';':
        addChar();
        nextToken = SEMICOLON;
        break;
    case '^':
        addChar();
        nextToken = POWER;
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
        else if(nextChar=='.')
            charClass = DOT;
        else charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

void getNonBlank(){
    while(isspace(nextChar))
        getChar();
}


int lex()
{
    lexLen = 0;
    getNonBlank();
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
        if (charClass == DOT){
            addChar();
            getChar();
            while (charClass == DIGIT){
                addChar();
                getChar();
            }
            nextToken = REAL_LIT;
        }
        else
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

void exprs();
void expr();
void term();
void factor();
void exp();



void exprs(){
    expr();
    if(nextToken == SEMICOLON){
        lex();
        while(nextToken != EOF){
            expr();
            if(nextToken == SEMICOLON)
                lex();
            else
                cout<<"error333";
        }
        cout<<"parse succeed"<<endl;
    }
    else
        cout<<"error22";
}

void expr(){
    term();
    while(nextToken == ADD_OP || nextToken == SUB_OP){
        lex();
        term();
    }
}

void term(){
    factor();
    while(nextToken == MULT_OP || nextToken == DIV_OP){
        lex();
        factor();
    }
}

void factor(){
    exp();
    while(nextToken == POWER){
        lex();
        exp();
    }
}

void exp(){
    if(nextToken == INDET)
        lex();
    else if(nextToken == INT_LIT)
        lex();
    else if(nextToken == REAL_LIT)
        lex();
    else if(nextToken == LEFT_PAREN){
        lex();
        expr();
        if(nextToken == RIGHT_PAREN)
            lex();
        else
            cout<<"error";
    }
    else
        cout<<"error1";
}


int main(){
    if((in_fp = fopen("C:\\Users\\Mr-Fish\\Desktop\\input.txt", "r")) == NULL)
        cout<<"ERROR - cannot open input.txt"<<endl;
    else{
        getChar();
        lex();
        exprs();
    }

    return 0;
}
