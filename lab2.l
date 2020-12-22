%{
	#include<iostream>
	#include<cstdlib>
	#include<string>
	#include<map>
	#include"y.tab.h"
	using namespace std;
	/* C declaration */
	string name;
	double num_val;
	map<string, double> table;
	bool assignment;
	extern "C"
	{
		int yylex();
		int yywrap();
	}
%}

digit	[0-9]

digits	{digit}+

NUMBER   ({digits}"."{digits})|{digits}

letter 	[a-zA-Z]

VAR		{letter}({letter}|{digit})*

%%

f			{//keyword f
				//cout << "test  f" << endl;
				return 'f';
			}//end of f

ln			{//keyword ln
				//cout << "test ln " << endl;
				return LN;
			}//end of ln			

sin			{//keyword sin
				//cout << "test sin " << endl;
				return SIN;
			}//end of sin			
			
cos 		{//keyword cos
				//cout << "test cos " << endl;
				return COS;
			}//end of cos

exp			{//keyword exp
				//cout << "test exp " << endl;
				return EXP;
			}

=			{	// assignment
				//cout << "test = " << endl;
				assignment = true;
				return '=';
			}

[ \t]+		{	// WHITE SPACE
				/*skip*/
				
			} // end of WHITE SPACE
			
{VAR}		{	// VAR
				name.assign(yytext);
				//cout << "test VAR : " << name << endl;
				return VAR;
			} // end of VAR

{NUMBER}	{	// NUMBER
				double d = atof(yytext);
				//cout << "test  number: " << d << endl;
				if(assignment == true)
				{
					table.emplace(name, d);
					assignment = false;
				}
				num_val = d;
				return NUMBER;
			}// end of NUMBER

\n			{	// end of a function
				// output the table
				map<string, double>::iterator iter;
				for (iter = table.begin(); iter != table.end(); iter++)
				{
					cout << iter->first << " equals " << iter->second << endl;
				} 
				return '\n';
			} // end of \n
		
.			{	// any other character except \n
				return (yytext[0]);
			}			
%%

int yywrap()
{
	return 1;
}	

