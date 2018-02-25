#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include "LList.h"
#include "BST4.h"
/**
 * This class cData holds information about a course. It has the course 
 * number, the title of the course, the department the course is in, and a 
 * Linked List holding the roster. It has a key function returning the course 
 * number for the BST to use. It also has << overloaded to easily output the 
 * course information
 * @author David Haltinner
 * @date Oct. 31, 2002
 * */
class cData {
   public:
      int courseNo;
      char * title;
      char * department;
      LList<int> roster;
      //Empty Constructor
      cData() {  };
      //Copy Constructor
      cData(const cData & temp)
      {
         courseNo=temp.courseNo;
         title=new char[strlen(temp.title)];
         strcpy(title, temp.title);
         department=new char[strlen(temp.department)];
         strcpy(department, temp.department);
         roster=temp.roster;
       }
      //Destructor which deletes the two char pointers
      ~cData() 
      {
         delete [] title; 
	 delete [] department; 
      }
      /**
       * This is the overloaded << operator function. It takes in the output 
       * stream, and a cData object. It then puts the number, name, and 
       * department of the course into the stream, and returns it. 
       * @param out, the stream to place it in; 
       * @param temp, which is the cData object to output
       * @return out, the stream with the new data in it
       * */
      friend std::ostream & operator <<(std::ostream & out, cData &temp)      
      { 
         out<<temp.courseNo<<" "<<temp.department<<" "<<temp.title;    
         return out; 
      }
      /**
      * Overloading the assignment operator to avoid segfaults when these are 
      * being copied around. Need to copy the actual char []s, not just the 
      * pointers.
      * @param temp, which is the object i want to copy from
      * @return a refrence to the new object
      * */
      cData& operator =(const cData & temp)
      {
         courseNo=temp.courseNo;
         title=new char[strlen(temp.title)];
         strcpy(title, temp.title);
         department=new char[strlen(temp.department)];
         strcpy(department, temp.department);
         roster=temp.roster;
	 return *this;
      }
      /**
       * This function returns the course number. It is used by the Binary 
       * Search Tree to do comparisons.
       * @return the course number
       * */
      int key () const { return courseNo; }
};
/**
 * This class sData holds information about a student. It has the students ID 
 * number, their first and last names, and a Linked List holding their list of
 * courses. It has a key function returning the student ID number for the BST 
 * to use in comparisons. It also has << overloaded to easily output the 
 * student information
 * @author David Haltinner
 * @date Oct. 31, 2002
 * */
class sData {
   public:
      int studentID;
      char * fname;
      char * lname;
      LList<int> myCourses;
      //Empty constructor
      sData() { };
      //Copy Constructor
      sData(const sData & temp)
      {
         studentID=temp.studentID;
         fname=new char[strlen(temp.fname)];
         strcpy(fname, temp.fname);
         lname=new char[strlen(temp.lname)];
         strcpy(lname, temp.lname);
         myCourses=temp.myCourses;
      }
      //Destructor, deletes the two char pointers
      ~sData() 
      { 
         delete [] fname; 
	 delete [] lname; 
      }
      /**
       * This is the overloaded << operator function. It takes in the output 
       * stream, and a sData object. It then puts the student id number, first
       * name, and last name into the stream, and returns it. 
       * @param out, the stream to place it in; 
       * @param temp, which is the sData object to output
       * @return out, the stream with the new data in it
       * */
      friend std::ostream & operator <<(std::ostream & out, sData &temp) 
      { 
         out<<temp.studentID<<" "<<temp.fname<<" "<<temp.lname;     
         return out; 
      }
      /**
       * Overloading the assignment operator to avoid segfaults when these are 
       * being copied around. Need to copy the actual char []s, not just the 
       * pointers.
       * @param temp, which is the object i want to copy from
       * @return a refrence to the new object
       * */
      sData& operator =(const sData & temp)
      {
          studentID=temp.studentID;
          fname=new char[strlen(temp.fname)];
          strcpy(fname, temp.fname);
          lname=new char[strlen(temp.lname)];
          strcpy(lname, temp.lname);
          myCourses=temp.myCourses;
	  return *this;
      }
      /**
       * This function returns the student ID number. It is used by the Binary 
       * Search Tree to do comparisons.
       * @return the course number
       * */
      int key () const { return studentID; }
};
/**
 * Almost every function uses these two trees, so instead of passing many 
 * reference parameters, I decided to put them out here for everyone to get 
 * access to.
 * */
BST<sData, int> studentTree;
BST<cData, int> courseTree;
/**
 * This function goes through the course Binary Search Tree and prints out all
 * of the courses in it
 * */
void allCourses()
{
   cout<<"All Courses"<<endl<<"-------------------------------------"<<endl;
   courseTree.aPrint();
}
/**
 * This function goes through the student Binary Search Tree and prints out all
 * of the students in it.
 * */
void allStudents() 
{
   cout<<"All Students"<<endl<<"-------------------------------------"<<endl;
   studentTree.aPrint();
}
/**
 * This function takes in an input stream holding a course number. It then
 * displays all of the students currently in the course's roster list.
 * @param in, the inout stream to get the course number from
 * */
void classRoster(ifstream &in) 
{
   cData temp;
   in>>temp.courseNo;
   if (!courseTree.search(temp.courseNo, temp))
   {
      cout<<"Class #"<<temp.courseNo<<" not found"<<endl;
      return;
   }
   cout<<"Class roster for "<<temp<<endl
       <<"----------------------------------------------"<<endl;
   temp.roster.first();
   sData tempstudent;
   while (!temp.roster.end())
   { 
      tempstudent.studentID=temp.roster.getData();
      if (studentTree.search(tempstudent.studentID, tempstudent))
         cout<<tempstudent<<endl;
      temp.roster.next();     
   }
}
/**
 * This function takes in an input stream holding a student's id number.
 * It then displays all of the courses he/she is currently enrolled in.
 * @param in, the input stream to grab the ID from
 * */
void courseList(ifstream &in) 
{
   sData temp;
   in>>temp.studentID;
   if (!studentTree.search(temp.studentID, temp))
   {
      cout<<"Student #"<<temp.studentID<<" could not be found"<<endl;
      return;
   }
   cout<<"Classes being taken by "<<temp<<endl
       <<"-----------------------------------------"<<endl;
   temp.myCourses.first();
   while (!temp.myCourses.end())
   {
      cData tempcourse;
      courseTree.search(temp.myCourses.getData(), tempcourse);
      cout<<tempcourse<<endl;
      temp.myCourses.next();
   }
}
/**
 * This function takes in the input stream for a file containing course 
 * information. It then places this information into a cData object, and adds 
 * it to the course tree.
 * @param in, the file's input stream
 * */
void createCourseRecords(ifstream &in)
{
   while (in)
   {
      cData temp;
      in>>temp.courseNo;
      if (!courseTree.search(temp.key(), temp))
      {
         char tempchar[50];
         in>>tempchar;
         temp.title=new char[strlen(tempchar)];
         strcpy(temp.title, tempchar);
         in>>tempchar;
         temp.department=new char[strlen(tempchar)];
         strcpy(temp.department, tempchar);
         courseTree=courseTree.insert(temp);
      }
   }
}
/**
 * This function takes in the input stream of a file holding student 
 * information. It then creats a sData object out of the inputted data, and 
 * inserts them into the classes' roster that the file specifies. It then 
 * adds them into the student tree.
 * @params in, the file's input stream
 * */
void createStudentRecords(ifstream &in)
{
   while (in)
   {
      sData temp;
      in>>temp.studentID;
      if (!studentTree.search(temp.key(), temp))
      {
         char tempname[50];
         in>>tempname;
         temp.lname=new char[strlen(tempname)];
         strcpy(temp.lname, tempname);
         in>>tempname;
         temp.fname=new char[strlen(tempname)];
         strcpy(temp.fname, tempname);
         int numcourses;
         in>>numcourses;
         cData tempcourse;
         for (int i=0; i<numcourses; i++)
         {
            in>>tempcourse.courseNo;       
            if (!courseTree.search(tempcourse.courseNo, tempcourse))
               cout<<"While adding student "<<temp<<", the course "
                   <<tempcourse.courseNo
                   <<" did not exist, skipping that course."<<endl<<endl;
            else {
               courseTree=courseTree.erase(tempcourse.courseNo, tempcourse);
               tempcourse.roster.append(temp.studentID);
               temp.myCourses.append(tempcourse.courseNo);
               courseTree=courseTree.insert(tempcourse);
            }      
         }
         studentTree=studentTree.insert(temp);
      }
   }      
}
/**
 * This function takes in an input stream to get the student id bumber and 
 * course number. It then removes that course from the student's course list, 
 * and removes the student from that class's roster.
 * @param in, the input stream holding the data we need
 * */
void dropStudent(ifstream &in)
{
   sData tempstudent;
   in>>tempstudent.studentID;
   if (!studentTree.search(tempstudent.studentID, tempstudent))
   {
      cout<<"Student # "<<tempstudent.studentID<<" not found"<<endl;
      return;
   }
   studentTree=studentTree.erase(tempstudent.studentID, tempstudent);
   cData tempcourse;
   in>>tempcourse.courseNo;
   if (tempstudent.myCourses.find(tempcourse.courseNo))
      tempstudent.myCourses.extractPosition();
   if (!courseTree.search(tempcourse.courseNo, tempcourse))
   {
      cout<<"Course # "<<tempcourse.courseNo
          <<" not found"<<endl;
      return;
   }
   courseTree=courseTree.erase(tempcourse.courseNo, tempcourse);
   if (tempcourse.roster.find(tempstudent.studentID))
      tempcourse.roster.extractPosition();
   cout<<tempstudent
       <<" has been successfully dropped from class "
       <<tempcourse<<endl;   
   studentTree=studentTree.insert(tempstudent);
   courseTree=courseTree.insert(tempcourse);
}
/**
 * This function takes in a file input stream from which it grabs a student id
 * number. It then removes this student from all class rosters he/she is in, 
 * and removes the student from the student tree.
 * @param in, the input stream to grab the ID from
 * */
void withdrawStudent(ifstream &in) 
{
   sData tempstudent;
   in>>tempstudent.studentID;
   if (!studentTree.search(tempstudent.studentID, tempstudent))
   {
      cout<<"Student #"<<tempstudent.studentID
          <<" not found"<<endl;
      return;
   }
   cData tempcourse;
   while (!tempstudent.myCourses.isEmpty())
   {
      tempstudent.myCourses.first();
      tempcourse.courseNo=tempstudent.myCourses.getData();
      if (courseTree.search(tempcourse.courseNo, tempcourse))
      {
         tempcourse.roster.find(tempstudent.studentID);
         tempcourse.roster.extractPosition();   
      }
      tempstudent.myCourses.extractPosition();   
   }   
   studentTree=studentTree.erase(tempstudent.studentID, tempstudent);
   cout<<tempstudent<<" has been withdrawn from the university"<<endl;
}
/**
 * This is the main function. It takes in 3 files as arguemnts in the order of
 * Student info, Course info, and then Transactions. It calls functions to 
 * creat the binary search trees for courses and students, and then starts 
 * using the Transactions file to call the appropriate functions above.
 * @param argc, number of arguments
 * @param argv, the 3 file names and the program name. Files must be in this 
 *      order: Courses, Students, Transactions
 * @return 0 if everything is done successfully, 1 if something failed
 * */
int main (int argc, char * argv[])
{   
   if (argc !=4){
      cout<<"Please give three files as an arguments"<<endl; 
      return 1; 
   }
   ifstream coursein(argv[1]), studin(argv[2]), transin(argv[3]);
   if (!studin || !coursein || !transin) { 
      cout<<"Open failed!"<<endl; 
      return 1; 
   }    
   createCourseRecords(coursein);
   coursein.close();
   createStudentRecords(studin);
   studin.close();
   char whattodo;
   while(transin>>whattodo)
   {
      if (whattodo == 'D') dropStudent(transin);
      else if (whattodo == 'W') withdrawStudent(transin);
      else if (whattodo == 'C') classRoster(transin);
      else if (whattodo == 'S') courseList(transin);
      else if (whattodo == 'A') allCourses();
      else if (whattodo == 'X') allStudents();
      cout<<endl;
   }
   transin.close();
}
