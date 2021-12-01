/*Assesment Two started from the  front.c file as a template */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
char pastChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp;
int _float = 0; 

/* Function declarations */
int lookup(char ch);
void addChar(void);
void getChar(void);
void getNonBlank(void);
int lex(void);
void mainTest(void);
void factor(void);
void voidTest(void);
void blockTest(void);
void statement(void);


/* Character classes */
#define LETTER 0
#define DIGIT 1
#define FLOAT 2
#define FOR 3

#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SWITCH_CODE 27
#define FOREACH_CODE 28
#define FOR_CODE 29
#define WHILE_CODE 30
#define DOWHILE_CODE 31
#define LEFT_BLOCK 32
#define RIGHT_BLOCK 33
#define IF_CODE 34
#define ELSE_CODE 35
#define RETURN_CODE 36
#define INT_CODE 37
#define FLOAT_CODE 38
#define MOD_OP 39
#define LESS_CODE 40 
#define GREATER_THAN_CODE 41  
#define SEMICOLON_CODE 42
#define COLON_CODE 43
#define IN_CODE 44



/******************************/
// Error function
/******************************/
void error(void){
  printf("Error\n");
  nextToken = EOF;
}

/******************************************************/
/* main driver */
int main(void) {
	/* Open the input data file and process its contents */
	 if ((in_fp = fopen("front.in", "r")) == NULL)
	 	printf("ERROR - cannot open front.in \n");
	 else {
	 	getChar();
     printf("Enter <program>\n");
	 do {
	 	lex();
     voidTest();


	 } while (nextToken != EOF);

	 }
   printf("Exit <program>\n");
	 return 0;
}


/******************************************************/
/* lookup - a function to look up operators and
 parentheses and return the token
 
 using the template from Front.c
 
  */
int lookup(char ch) {
  
	 switch (ch) {
	  case ':':
			 addChar();
			 nextToken = COLON_CODE;
       
			 break;
      case ';':
			 addChar();
			 nextToken = SEMICOLON_CODE;
       
			 break;
      case '=':
			 addChar();
			 nextToken = ASSIGN_OP;
       
			 break;
      case '{':
			 addChar();
			 nextToken = LEFT_BLOCK;
       
			 break;
	  case '}':
			 addChar();
			 nextToken = RIGHT_BLOCK;
			 break;
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

      case '%':
			 addChar();
			 nextToken = MOD_OP;
			 break;
       
	  default:
			 addChar();
			 nextToken = EOF;
			 break;
	 }
	 return nextToken;
}

/******************************************************/
// addChar - a function to add nextChar to lexeme 
/******************************************************/
void addChar(void) {
  
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
    //printf("%c",nextChar);
    lexeme[lexLen] = '\0';
    
	}
   
   else
	printf("Error - lexeme is too long \n");
}


/******************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
/******************************************************/
void getChar(void) {
    
	 if ((nextChar = getc(in_fp)) != EOF) {
		 if (isalpha(nextChar))
		 	charClass = LETTER;
		 else if (isdigit(nextChar) ){
       charClass = DIGIT;
       }
       else if (nextChar=='.' ){
         charClass = FLOAT;
       }
       
       
		 else
		 	charClass = UNKNOWN;
	 } else
	 	charClass = EOF;
}


/******************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
/******************************************************/ 
void getNonBlank(void) {
  
	while (isspace(nextChar))
	getChar();  

}

/******************************************************/

 void term(void) {
	 printf("Enter <term>\n");
	/* Parse the first factor */
	 factor();
	/* As long as the next token is * or /, get the
	 next token and parse the next factor */
	 while (nextToken == MULT_OP || nextToken == DIV_OP|| nextToken == MOD_OP|| nextToken == ASSIGN_OP) {
		 lex();
		 factor();
	 }
	 printf("Exit <term>\n");
}
int lex(void) {
 
	 lexLen = 0;
	 getNonBlank();
	 switch (charClass) {
		/* Identifiers */
		 case LETTER:
     addChar();
     getChar();
      
			 while (charClass == LETTER ||charClass == DIGIT ||nextChar == '.'   ||nextChar =='e'||nextChar =='E') {
         addChar();
         getChar();
         
			 }

         //These are for all the different Tokens for the statements


       if(lexeme[0] == 'f'&& lexeme[1] == 'o'&& lexeme[2] == 'r' && lexeme[3]!='e'){
           nextToken = FOR_CODE;
			 break;
         }else if(lexeme[0] == 'i'&& lexeme[1] == 'f'){
           nextToken = IF_CODE;
			 break;
         }else if(lexeme[0] == 'w'&& lexeme[1] == 'h'&& lexeme[2] == 'i' && lexeme[3] == 'l'&& lexeme[4] == 'e'){
           nextToken = WHILE_CODE;
			 break;
         }else if(lexeme[0] == 'd'&& lexeme[1] == 'o'){
           nextToken = DOWHILE_CODE;
			 break;
         }else if(lexeme[0] == 's'&& lexeme[1] == 'w'&& lexeme[2] == 'i' && lexeme[3] == 't'&& lexeme[4] == 'c' && lexeme[5] == 'h'){
           nextToken = SWITCH_CODE;
			 break;
         }else if(lexeme[0] == 'f'&& lexeme[1] == 'o'&& lexeme[2] == 'r' && lexeme[3] == 'e'&& lexeme[4] == 'a' && lexeme[5] == 'c' && lexeme[6]=='h'){
           nextToken = FOREACH_CODE;
			 break;
         }else if(lexeme[0] == 'r'&& lexeme[1] == 'e'&& lexeme[2] == 't' && lexeme[3] == 'u'&& lexeme[4] == 'r' && lexeme[5] == 'n'){
           nextToken = RETURN_CODE;
			 break;
         }else if(lexeme[0] == 'f'&& lexeme[1] == 'l'&& lexeme[2] == 'o' && lexeme[3] == 'a'&& lexeme[4] == 't'){
           nextToken = FLOAT_CODE;
			 break;
         }else if(lexeme[0] == 'e'&& lexeme[1] == 'l'&& lexeme[2] == 's' && lexeme[3] == 'e'){
           nextToken = ELSE_CODE;
			 break;
         }else if(lexeme[0] == 'i'&& lexeme[1] == 'n' && lexeme[2] == 't'){
           nextToken = INT_CODE;
			 break;
         }

         else{
			 nextToken = IDENT;
			 break;}

		// Int literals 
		 case DIGIT:
			 addChar();
			 getChar();
      
       while (charClass == DIGIT||nextChar =='.'||nextChar =='e'||nextChar =='E') {
         if(nextChar =='.'||nextChar == 'e' || nextChar =='E' ){
           if(_float!=1){
             _float=1;
           }else{
             
           }
           
         }
				 addChar();
				 getChar();
			 }

       if(_float!=1){
        nextToken = INT_LIT;
        
        }
        else{
       nextToken = FLOAT;}
		 	break;

       // floating point literals
       case FLOAT:
			 addChar();
			 getChar();
			 
       while (charClass == DIGIT) {
				 addChar();
				 getChar();
			 }

			 nextToken = FLOAT;
       
		 	break;
       
       //for
       case FOR:
			 addChar();
			 getChar();
			 
       while (charClass == FOR) {
				 addChar();
				 getChar();
			 }

			 nextToken = FOR;
       
		 	break;


		// operators and parenthesis

        
		 case UNKNOWN:
			 lookup(nextChar);
			 getChar();
			 break;


		// lex
		case EOF:
			 nextToken = EOF;
			 lexeme[0] = 'E';
			 lexeme[1] = 'O';
			 lexeme[2] = 'F';
			 lexeme[3] = '\0';
		 	break;
	 }


   printf("\n");
	 printf("Next token is: %d, Next lexeme is %s\n",
	 nextToken, lexeme);
	 return nextToken;
} 
void voidTest(void) {
	 
	 if (nextToken == IDENT && lexeme[0] == 'v'&& lexeme[1] == 'o'&& lexeme[2] == 'i'&& lexeme[3] == 'd'){
		
           printf("Enter <void>\n");
           lex();
           mainTest();
		
	 }else{
     
      printf("Missing <void> ");
      error();
    
		
   }
	 printf("Exit <void>\n");
   
   error();
}
void mainTest(void) {
	 

	 if (nextToken == IDENT && lexeme[0] == 'm'&& lexeme[1] == 'a'&& lexeme[2] == 'i'&& lexeme[3] == 'n'){
		
           printf("Enter <main>\n");
           lex();
           if (nextToken == LEFT_PAREN) {
		       lex();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       blockTest();
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
		
	 }else{
     
      printf("Missing <main> ");
      error();
    
		
   }
	 printf("Exit <main>\n");
}

void blockTest(void) {
	 
	
    if (nextToken == LEFT_BLOCK) {
      printf("Enter <BlOCK>\n");
		  lex();
      
      while(nextToken != RIGHT_BLOCK){
        statement();
        lex();
      }
      
		if (nextToken == RIGHT_BLOCK){
   
      
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <BlOCK>\n");
       
     }

void expr(void) {
	 printf("Enter <expr>\n");
	/* Parse the first term */
	 term();
	/* As long as the next token is + or -, get
	 the next token and parse the next term */
	 while (nextToken == ADD_OP || nextToken == SUB_OP ||nextToken==COLON_CODE ) {
		 lex();
		 term();
	 }
	 printf("Exit <expr>\n");
}


void statement(){
switch(nextToken) {

    

    //using rule <forstmt> -> for ([<expression>] ';' [<expression>] ';' [<expression>]) <statement>
   case FOR_CODE  :
   printf("Enter <For>\n");
   lex();

     if (nextToken == LEFT_PAREN) {
       lex();
       printf("%d <For>\n",nextToken);
       while(nextToken != SEMICOLON_CODE){
         expr();
      }
       
       lex();
       while(nextToken != SEMICOLON_CODE){
         expr();
      }
      lex();
      while(nextToken != RIGHT_PAREN){
         expr();
      }
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }

    else{
       printf("Missing <Left Parenthesis> ");
		error();
     }
     
if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
    
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <For>\n");
       lex();
     
     
      
       
      break; 
	
 
 
  //based on rule <lftblock> -> <block>
   case LEFT_BLOCK  :
     
       blockTest();
      break; 
    



    case RIGHT_BLOCK  :
     
       
      break; 
  
  
  
  
  // using the rule <ifstmt> -> if (<boolexpr>) <statement>
  //                [else <statement>]
  case IF_CODE  :
  printf("Enter <IF>\n");
     lex();

     if (nextToken == LEFT_PAREN) {
       lex();
       expr();  
       
	if (nextToken == RIGHT_PAREN){
		lex();
       
     }
    else{
		error();
       }
		 }

     else{
        error();
     }

     if (nextToken == LEFT_BLOCK) {
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
	 	 
     }
     
        else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }
         
        else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
     
	     printf("Exit <IF>\n");
       lex();
       
    //For when there is an optional else
    
    if(nextToken==ELSE_CODE){
        lex();
        if (nextToken == LEFT_BLOCK) {
            lex();
            statement();
            if (nextToken == RIGHT_BLOCK){
                printf("Exit <else>\n");
		 	    lex();
         
      }
      else{ 
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		  }

        else{
      printf("Missing <Left BLOCK> ");
		 	error();
      }
       }
      break; 
  
  
  
  // using the rule <dowhilestmt> -> do <statement> while (<expression>)

  case DOWHILE_CODE  :
  printf("Enter <DO-While>\n");
     lex();
       if (nextToken == LEFT_BLOCK) {
         lex();
        statement();
        if (nextToken == RIGHT_BLOCK){
       lex();
		 	 if(nextToken == WHILE_CODE){
       printf("Enter <while>\n");
       lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
     if (nextToken == RIGHT_PAREN){
		 	
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
        }else{
           printf("Missing <while>\n ");
        }
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
     
     
	     printf("Exit <do-while>\n");
       lex();
      break;
  
  
  // using the rule  <whilestmt> -> while '(' <arithexpr> ')' <statement>
  
  case WHILE_CODE  :
      printf("Enter <while>\n");
     lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
      if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <while>\n");
       lex();
      break;
  
  
  //using the rule returnstmt -> return [<expression>]
  case RETURN_CODE  :
  printf("Enter <return>\n");
     lex();
     expr();
     printf("Exit <return>\n");
       
      break; 
  
  
  
  // rule for switch code switchstmt -> switch (<expression>)
  case SWITCH_CODE  :
     
        printf("Enter <switch>\n");
   lex();

     if (nextToken == LEFT_PAREN) {
       lex();
       expr();
       //lex();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
       
     }else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }

     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <switch>\n");
       lex();
     
      break; 


// using the rule assignstmt -> = <expression>
  case ASSIGN_OP  :
  printf("Enter <Assign>\n");
     lex();
     expr();
     
     
       printf("Exit <Assign>\n");
      break;

    //for each using the rule foreachstmt -> for (<expression> in <expression>) based on python's example of for x in fruits;
    case FOREACH_CODE  :
      printf("Enter <foreach>\n");
     
     lex();
     if (nextToken == LEFT_PAREN) {
       lex();
       expr();

      if (nextToken == IN_CODE){
          lex();
	   if (nextToken == RIGHT_PAREN){
		 	lex();  
     }
     else{
       printf("Missing <Right Parenthesis> ");
		 	error();
       }
		 }
     else{
       printf("Missing <In> ");
		 	error();
       }
       }else{
       printf("Missing <Left Parenthesis> ");
		 	error();
     }
     if (nextToken == LEFT_BLOCK) {
      
		  lex();
      statement();
      
		if (nextToken == RIGHT_BLOCK){
		 	 
     }else{
       
      printf("Missing <Right BLOCK> ");
		 	error();
       }
		 }else{
      printf("Missing <Left BLOCK> ");
		 	error();
     }
	     printf("Exit <foreach>\n");
       lex();
      break; 
      
      default: 
      lex();
      statement();
      break;

}
 
}


void factor(void) {
	 printf("Enter <factor>\n");
	/* Determine which RHS */
	 if (nextToken == IDENT || nextToken == INT_LIT){
		/* Get the next token */
		 lex();
		/* If the RHS is ( <expr> ), call lex to pass over the
		 left parenthesis, call expr, and check for the right
		 parenthesis */
	 }else { 
     if (nextToken == LEFT_PAREN) {
		 lex();
		 expr();
		 if (nextToken == RIGHT_PAREN){
		 	lex();
     }else{
		 	error();
       }
		 }
		/* It was not an id, an integer literal, or a left
		 parenthesis */
		 else{
		  
	 }
	 printf("Exit <factor>\n");
}}




