#include <iostream.h>

#define by_macro(a,b) \
	{ (a)=(a)+(b); (b)=(a)-(b); (a)=(a)-(b); }

void by_value(int a, int b)
{
	a=a+b;
	b=a-b;
	a=a-b;
}

void by_reference(int &a, int &b)
{
	a=a+b;
	b=a-b;
	a=a-b;
}

void by_copy_restore(int &a, int &b)
{
	int copya=a;
	int copyb=b;

	a=a+b;
	b=a-b;
	a=a-b;
					
	a=copya;
	b=copyb;
}

void main()
{
	int x;
	int y[10];
	
	for (int i=0; i<10; i++)
		y[i]=i*123;
	x=4;
	by_macro(x,(y[x]));
	cout<<"macro: "<<x<<" "<<y[x]<<endl;

	
	x=4;
	for (int i=0; i<10; i++)
		y[i]=i*123;
	
	by_value(x,y[x]);
	cout<<"by value: "<<x<<" "<<y[x]<<endl;

	
	x=4;
	for (int i=0; i<10; i++)
		y[i]=i*123;
	by_reference(x,y[x]);
	cout<<"by reference: "<<x<<" "<<y[x]<<endl;

	
	x=4;
	for (int i=0; i<10; i++)
		y[i]=i*123;
	by_copy_restore(x,y[x]);
	cout<<"by copy restore: "<<x<<" "<<y[x]<<endl;
}
