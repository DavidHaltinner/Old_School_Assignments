/**
 * This file contains the conversion app. It takes in a file name as a 
 * parameter, and usues it to read in infix expressions. It then sends that 
 * expression to a function that converts it to postfix using a stack. This 
 * function does error checking, and will bail out with an error message if 
 * there is one. 
 * @author David Haltinner
 * @date Oct 4 2002
 * */
#include <iostream.h>
#include <ctype.h>
#include <fstream.h>
#include "AStack.h"
/**
 * This function takes in a character and checks to see it's mathmetical 
 * prefrence, and returns that as an integer.
 * @params t; the operator to check
 * @return an integer value corresponding to its precedence
 * */
int ISP(char t)
{
   if (t == '(') return 1;
   else if (t == '#') return 0;
   else if (t == '+' || t == '-') return 2;
   else if (t == '*' || t == '/') return 3;
   else if (t == '^') return 4;
   return -1;
}
/**
 * This function takes in a character and checks to see it's mathmetical 
 * prefrence, and returns that as an integer.
 * @params t; the operator to check
 * @return an integer value corresponding to its precedence
 * */
int INP(char t)
{
   if (t == '(') return 5;
   else if (t == '+' || t == '-') return 2;
   else if (t == '*' || t == '/') return 3;
   else if (t == '^') return 4;
   return -1;
}
/**
 * This function gets handed information about an error (an integer 
 * corresponding to the type of error, and the slot where the error is), and 
 * then outputs the error with a ^ pointing to the slot where it occured.
 * @params type; which error. slot; where it occured in the expression
 **/
void Error(int type, int slot)
{
   for (int i = 0; i<slot; i++)
      cout<<" ";
   cout<<"^"<<endl<<"Error in Position "<<int(slot/2)+1<<": ";
   if (type == 1) 
      cout<<"First chracter is an operator"<<endl;
   else if (type == 2) 
      cout<<"Last character is an operator"<<endl;
   else if (type == 3) 
      cout<<"Identifier followed by an identifier or ("<<endl;
   else if (type == 4)
      cout<<") followed by an identifier"<<endl;
   else if (type == 5)
      cout<<"Operator followed by an operator or )"<<endl;
   else if (type == 6)
      cout<<"( followed by an operator"<<endl;
   else if (type == 7)
      cout<<"Unmatched ("<<endl;
   else if (type == 8)
      cout<<"Unmatched )"<<endl;
}
/**
 * This is the function that does the conversion. It takes an infix char array,
 * and reads through it. It places the operators in a stack, and the operands
 * in another char array. When needed, it will pull out an operator off the 
 * stack. This function also checks for error in the expression along the 
 * way, and calls the error method if needed.
 * @params E; the infix expression
 * */
void PostFix(char E[])
{
   if (isalpha(E[0])==0 && E[0]!='(')
   {
      Error(1, 0);
      return;
   }
   else if (E[0]=='(' && isalpha(E[2])==0 && E[2]!='(')
   {
      Error(1,2);
      return;
   }
   AStack<char> S(4);
   S.Push('#');
   char P[80];
   char t;
   int eslot = 0;
   int pslot = 0;   
   int numleft = 0;
   int numright = 0;
   int lastleft;
   while (true)
   {
      t = E[eslot];
      if (t == '$')
      {
         if (isalpha(E[eslot-2])==0 && E[eslot-2] != ')')
         {
            Error(2,eslot-2);
            return;
         }
         if (numright < numleft)
         {
            Error(7,lastleft);
            return;
         }
         while (S.Top() != '#')
         {
            P[pslot]=S.Pop();
            P[++pslot]=' ';
            ++pslot;
         }
         break;
      }
      else if (isalpha(t)!=0)
      {
         if (isalpha(E[eslot-2])!=0 || isalpha(E[eslot+2])!=0 
            || E[eslot+2] == '(')
         {
            Error(3,eslot);
            return;
         }
         P[pslot]=t;
         P[++pslot]=' ';
         ++pslot;
      }
      else if (t == ')')
      {
         numright++;
         if (numright > numleft)
         {
            Error(8,eslot);
            return;
         }
         if (isalpha(E[eslot+2]) != 0)
         {
            Error(4, eslot);
            return;
         }
         while (S.Top() != '(')
         {
            P[pslot]=S.Pop();
            P[++pslot]=' ';
            ++pslot;
         }
         S.Pop();
      }
      else
      {
         if (E[eslot] == '(') 
         {
            numleft++;
            lastleft=eslot;
         }
         if ((eslot>=2 && E[eslot+2]!='$' && E[eslot] != '(' && E[eslot] !=')')
		&&( (isalpha(E[eslot-2])==0 && E[eslot-2]!=')') 
		|| (isalpha(E[eslot+2])==0 && E[eslot+2]!='(')))
         {
            Error(5,eslot);
            return;
         }
         if (E[eslot-2]=='(' && isalpha(E[eslot])==0 && E[eslot]!='(')
         {
            Error(6,eslot);
            return;
         }
         while (ISP(S.Top()) >= INP(t))
         {
            P[pslot]=S.Pop();
            P[++pslot]=' ';
            ++pslot;
         }
         S.Push(t);
      }
      eslot+=2;
   }
   P[pslot]='\0';
   cout<<endl<<"Postfix: "<<P<<endl;   
}
/**
 * This is the main function. It takes in a file name as an argument, and opens
 * it up to read out the infix expressions held in it. It then sends them to 
 * the PostFix function to get worked on.
 * @params argc; number of arguments. argv; the filename and program's name
 * @return 0 if we worked correctly. 1 if we failed on the file.
 * */
int main (int argc, char * argv[])
{
   if (argc !=2)
   {
      cout<<"Please give one file as an argument"<<endl;
      return 0;
   }
   ifstream in;
   in.open(argv[1]);
   if (!in) 
   {
      cout<<"open failed on file one"<<endl;
      return 1;
   }
   cout<<"Infix to Postfix Expressions."<<endl;
   char infix[80];
   while (in.getline(infix,80))
   {
      cout<<endl<<infix<<endl;
      PostFix(infix);
   }
   in.close();   
   return 0;
}
