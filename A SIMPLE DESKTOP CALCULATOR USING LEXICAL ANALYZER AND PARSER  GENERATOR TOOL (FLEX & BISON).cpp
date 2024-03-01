lexanalyzer.l 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "y.tab.h" 
#define TABSIZE 1000 
#define true 1 
#define false 0 

// JUGAAD CPP CODE (Run in seperate PowerShell)



#include <bits/stdc++.h>
using namespace std;

// Function to find precedence of
// operators.
int precedence(char op){
	if(op == '+'||op == '-')
	return 1;
	if(op == '*'||op == '/')
	return 2;
	return 0;
}

// Function to perform arithmetic operations.
int applyOp(int a, int b, char op){
	switch(op){
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/': return a / b;
	}
}

// Function that returns value of
// expression after evaluation.
int evaluate(string tokens){
	int i;
	
	// stack to store integer values.
	stack <int> values;
	
	// stack to store operators.
	stack <char> ops;
	
	for(i = 0; i < tokens.length(); i++){
		
		// Current token is a whitespace,
		// skip it.
		if(tokens[i] == ' ')
			continue;
		
		// Current token is an opening
		// brace, push it to 'ops'
		else if(tokens[i] == '('){
			ops.push(tokens[i]);
		}
		
		// Current token is a number, push
		// it to stack for numbers.
		else if(isdigit(tokens[i])){
			int val = 0;
			
			// There may be more than one
			// digits in number.
			while(i < tokens.length() &&
						isdigit(tokens[i]))
			{
				val = (val*10) + (tokens[i]-'0');
				i++;
			}
			
			values.push(val);
			
			// right now the i points to
			// the character next to the digit,
			// since the for loop also increases
			// the i, we would skip one
			// token position; we need to
			// decrease the value of i by 1 to
			// correct the offset.
			i--;
		}
		
		// Closing brace encountered, solve
		// entire brace.
		else if(tokens[i] == ')')
		{
			while(!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();
				
				int val1 = values.top();
				values.pop();
				
				char op = ops.top();
				ops.pop();
				
				values.push(applyOp(val1, val2, op));
			}
			
			// pop opening brace.
			if(!ops.empty())
			ops.pop();
		}
		
		// Current token is an operator.
		else
		{
			// While top of 'ops' has same or greater
			// precedence to current token, which
			// is an operator. Apply operator on top
			// of 'ops' to top two elements in values stack.
			while(!ops.empty() && precedence(ops.top())
								>= precedence(tokens[i])){
				int val2 = values.top();
				values.pop();
				
				int val1 = values.top();
				values.pop();
				
				char op = ops.top();
				ops.pop();
				
				values.push(applyOp(val1, val2, op));
			}
			
			// Push current token to 'ops'.
			ops.push(tokens[i]);
		}
	}
	
	// Entire expression has been parsed at this
	// point, apply remaining ops to remaining
	// values.
	while(!ops.empty()){
		int val2 = values.top();
		values.pop();
				
		int val1 = values.top();
		values.pop();
				
		char op = ops.top();
		ops.pop();
				
		values.push(applyOp(val1, val2, op));
	}
	
	// Top of 'values' contains result, return it.
	return values.top();
}

int main() {
	string inputbuf;
	cout<<"Enter input String\n";
	cin>>inputbuf;
	cout<<evaluate(inputbuf)<<endl;
	return 0;
}


//END OF JUGAAD CODE HERE




char* var_names[TABSIZE]; // where the variable names will be stored int var_def[TABSIZE]; // flag to determine whether a var is defined int n_of_names = 0; // counter of variables 
void reset() { 
 /* this will just reset all the flags to false */ 
 int j; 
 for(j = 0; j < TABSIZE; j++) 
 var_def[j] = false; 
} 
int install(char *txt) { 
 int j; char *s; 
 /* if the table of var_names is still empty */ 
 /* add the first record at 0 and return 0 */ 
 if(n_of_names == 0) { 
 s = strdup(txt); 
 var_names[0] = s; 
 ++n_of_names; 
 return 0; 
 } 
  
 /* if the table has contents already, return the index */  for(j = 0; j < n_of_names; ++j) { 
 if(strcmp(txt, var_names[j]) == 0) { 
 return j; 
 } 
 }
 /* if the table is not empty and the var name is not yet listed */  /* list the new var name and return the index */  s = strdup(txt); 
 var_names[j] = s; 
 ++n_of_names; 
 return j; 
} 
%} 
ALPHA [a-z]|[a-z][a-z] 
NUM [0-9]|[0-9][0-9] 
%% 
[ \n\t] { } 
[0-9][0-9]*(\.[0-9]+)? { 
 /* convert yytext to a double and return it */ 
 yylval.num = atof(yytext); 
 return NUMBER; 
} 
{ALPHA}|{ALPHA}{NUM} { 
 /* install the variable found to the array and return the index */  yylval.index = install(yytext); 
 return VARIABLE; 
} 
. { 
 return yytext[0]; 
} 
%% 
int yywrap(void) 
{ 
 return 1; 
}



parserGrammar.y 
%{ 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include "y.tab.h" 
#define TABSIZE 1000 
#define true 1 
#define false 0 
/* the following were defined in lexanalyzer.l */ 
extern char* var_names[TABSIZE]; 
extern int var_def[TABSIZE]; 
extern int n_of_names; 
extern int install(char *txt); 
extern void reset(); 
/* variables for the grammar file */ 
int invalid = false; // just added for error checking double var_values[TABSIZE]; // array where all the values are stored 
int yyerror(const char *p)  
{ 
 fprintf(stderr, "%s\n", p); // print the error message  invalid = true; 
} 
%} 
%union { 
 /* this will be used for the yylval. */ 
 /* it is a union since two data types will be used */ 
 double num; // the number provided by the user  int index; // index of the variable name inside the array };
%start manycmds 
%token <index> VARIABLE 
%token <num> NUMBER 
%type <num> onecmd 
%type <num> expression 
%type <num> assignment 
%type <num> term 
%type <num> factor 
%type <num> primary 
%% 
manycmds : onecmd { } 
| manycmds onecmd { } 
; 
onecmd : expression ';' { if(!invalid) fprintf(stderr, "%lf\n", $1); invalid = 0; } | assignment ';' { if(!invalid) fprintf(stderr, "%lf\n", $1); invalid = 0; } 
expression : term { $$ = $1; } 
| '-' term { $$ = -$2; } 
| expression '+' term { $$ = $1 + $3; } 
| expression '-' term { $$ = $1 - $3; } 
; 
term : factor { $$ = $1; } 
| term '*' factor { $$ = $1 * $3; } 
| term '/' factor { if($3 == 0) yyerror("undefined"); else $$ = $1 / $3; } ; 
factor : primary { $$ = $1; } 
| primary '^' factor { $$ = pow($1, $3); } 
; 
primary : NUMBER { $$ = $1; } 
| VARIABLE { if(!var_def[$1]) yyerror("undefined"); else $$ =  var_values[$1]; } 
| '(' expression ')' { $$ = $2; } 
;
assignment : '@' VARIABLE '=' expression { $$ = var_values[$2] = $4; var_def[$2] = 1; } ; 
%% 
int main(void) 
{ 
 /* reset all the definition flags first */ 
 reset(); 
 yyparse(); 
 return 0; 
} 
