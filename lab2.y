%{
	/*definition*/
	#include<iostream>
	#include<cstdio>
	#include<string>
	#include<map>
	#include<cmath>
	#include"ParseTree.h"
	#define YYSTYPE node*
	using namespace std;
	ParseTree T;
	extern map<string, double> table;
	extern string name;
	extern double num_val;
	extern "C"
	{
		int yyparse();
		int yywrap();
		int yylex();
		void yyerror(char* s);
	}
	double value;//value of the expression
%}


%token VAR 
%token NUMBER
%left '+' '-' 
%left '*' '/'
%left '^'
%token EXP LN SIN COS


%%


REV_AutoDiff	:	func_def 
					{
						T.level_walk();
						cout << "press ctrl+D to exit..." << endl;
					}
				;

func_def		:	'f' '(' var_list ')' ':' expr '\n'
					{
						T.set_root($6);
						cout << "val = " << $6->value << endl;
					}
				;

var_init		:	VAR '=' NUMBER	
				;

var_list		:	var_init
				|	var_list ',' var_init
				;

expr			:	VAR
					{//VAR
						$$ = T.makeleaf(ID, table[name]);
						$$->var_id = name;
					}			
					

				|	NUMBER
					{//NUMBER
						$$ = T.makeleaf(NUM, num_val);
								
					}
				|	expr '+' expr
					{//ADD
						$$ = T.makenode(ADD, $1, $3, $1->value + $3->value);
					}
						
				|	expr '-' expr
					{//SUB
						$$ = T.makenode(SUB, $1, $3, $1->value - $3->value);
					}
					
				|	expr '*' expr
					{//MUL
						$$ = T.makenode(MUL, $1, $3, $1->value * $3->value);
					}
				
				|	expr '/' expr
					{//DIV
						$$ = T.makenode(DIV, $1, $3, $1->value / $3->value);
					}
				|	'-' expr
					{//MINUS
						$$ = T.makenode(MINUS, nullptr, $2, -($2->value));
					}
				|	'(' expr ')'
					{
						$$ = $2;
					}
				|	expr '^' expr
					{
						$$ = T.makenode(POW, $1, $3, pow($1->value, $3->value));
					}
				|	EXP	'(' expr ')'
					{
						$$ = T.makenode(EXP_, nullptr, $3, exp($3->value));
					}
				|	LN '(' expr ')'
					{
						$$ = T.makenode(LN_, nullptr, $3, log($3->value));
					}
				|	SIN '(' expr ')'
					{
						$$ = T.makenode(SIN_, nullptr, $3, sin($3->value));
					}
				|	COS '(' expr ')'
					{
						$$ = T.makenode(COS_, nullptr, $3, cos($3->value));
					}
				;
				
%%

int main()
{

	printf("please input a legal function: \n");
	yyparse();
	//cout << "val = " << value << endl;
}

void yyerror(char *s)
{
   printf("%s\n", s ); 
}
