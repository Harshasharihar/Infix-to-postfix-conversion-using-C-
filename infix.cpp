//stack application for infix to postfix conversion

#include<iostream>
#include<string.h>
using namespace std;
#define MAX 50
#define null 0

class infix2postfix
{
	private:
			char target[MAX], stack[MAX];
			char *s, *t;
			int top;
	public:
			infix2postfix();        
			void myexpr(char *str);
			void push(char c);   
			char pop();          
			void convert();
			int priority(char c);
			void show();		
};

infix2postfix::infix2postfix()
{
	cout<<"Inside constructor function\n";
	top = -1;
	strcpy(target, "");
	strcpy(stack, "");
	t = target;
	s = null;
}

void infix2postfix::myexpr(char *str)
{
	s = str;
}

void infix2postfix::push(char c)
{
	
	if(top == MAX-1)  
	{
		cout<<"ERROR...stack is full\n";
		return;
	}

	top++;
	stack[top] = c;
}

char infix2postfix::pop() 
{
	char myval;
	
	if(top == -1)
	{
		cout<<"ERROR....stack is empty\n";
		return -1;
	}
	
	myval = stack[top];              
	top--;
	return myval;
}

void infix2postfix::convert()
{
	while(*s)
	{
		cout<<*s;
		if((*s)== ' ' || (*s)== '\t')
		{
			s++;
			continue;
		}
		if(isdigit(*s) || isalpha(*s))
		{
			while(isdigit(*s)|| isalpha(*s))
			{
				*t = *s;
				s++;
				t++;	
			}
		}
		if(*s == '(')
		{
			push(*s);
			s++;
		}
		
		char opr;
		if(*s=='*'||*s=='+'||*s=='/'||*s=='%'||*s=='-'||*s=='^')
		{
			if(top != -1)
			{
				opr = pop();
				while(priority(opr) >= priority(*s))
				{
					*t = opr;
					t++;
					opr = pop();
				}
				push(opr);
				push(*s);
			}
			else
				push(*s);
			s++;
		}
		if(*s == ')')
		{
			opr = pop();
			while(opr != '(')
			{
				*t = opr;
				t++;
				opr = pop();
			}
			s++;
		}
	}
	while(top != -1)
	{
		char opr = pop();
		*t = opr;
		t++;
	}
	*t = '\0';
}

int infix2postfix::priority(char c)
{
	if(c == '^')
		return 3;
	if(c == '*'||c == '/' || c == '%')
		return 2;
	else
	{
		if(c == '+' || c == '-')
			return 1;
		else
			return 0;
	}
}

void infix2postfix::show()
{
	cout<<"Postfix form is "<<target<<endl;	
}

int main()
{
	char expr[MAX];
	infix2postfix s;

	cout<<"Enter your infix expression\n";
	cin.getline(expr, MAX);
	
	s.myexpr(expr);
	s.convert();
	s.show();
}
