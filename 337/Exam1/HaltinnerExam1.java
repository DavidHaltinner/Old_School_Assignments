/****************************************************
 *
 * Exam1 - compute employee salary
 *
 * Author: David Haltinner
 * Date:  03/02/2004
 * Description: compute employee salary
 *
 * inputfile1: <employeefile>
 *
 *   employeeName SS# position supervisorSS# baseSalary [overtimePay]
 *
 *      [overtimePay] for programmer only
 *
 * inputfile2: <workhourfile>
 *
 *   timeLog employeeSS# workhours overtimeHours
 *
 * usage: java HaltinnerExam1 <profit> <employeefile> <workhourfile>
 *
 * external classes:
 *	Employee  ------- Secretary
 *		        |
 *				----- Programmer
 *				|
 *				----- Manager
 *					      |
 *						  ----- Executive
 *
 ****************************************************/
import company.*;
import myutilities.*;
import java.io.*;
import java.util.*;

public class HaltinnerExam1 {
    
    public static void main(String[] args) throws MyException {
        // profit comes from command line: java hw02 <profit>
        if (args.length != 3)
            throw new MyException("Inavlid number of arguments.");
        float profit=Float.parseFloat(args[0]);
        
        // Create an array of employees, staff[]; the length of staff is MAXSTAFF
        Employee [] staff = new Employee[Employee.MAXSTAFF];
        
        // Choose a line-oriented class e.g. LineNumberReader and FileReader
        // to read from the two data files
        BufferedReader infile;
        String temp;
        StringTokenizer st;
        Employee.noStaff=0;
        String name, ssn, position;
        
        try {
            infile = new BufferedReader(new FileReader(args[1]));
            
            // Fill the records of employees in staff[]
            if (!infile.ready()) throw new MyException("There are no employees in the input file.");
            while (infile.ready()) {
                temp = infile.readLine();
                st = new StringTokenizer(temp);
                name=st.nextToken();
                ssn=st.nextToken();
                position=st.nextToken();
                try {
                    if (position.equals("executive"))
                        staff[Employee.noStaff]=new Executive(name, ssn, Float.parseFloat(st.nextToken()), profit);
                    else if (position.equals("manager")) {
                        String supervisor=st.nextToken();
                        staff[Employee.noStaff]=new Manager(name, ssn, Float.parseFloat(st.nextToken()));
                    }
                    else if (position.equals("programmer"))
                        staff[Employee.noStaff]=new Programmer(name, ssn, st.nextToken(), Float.parseFloat(st.nextToken()), Float.parseFloat(st.nextToken()));
                    else if (position.equals("secretary"))
                        staff[Employee.noStaff]=new Secretary(name, ssn, st.nextToken(), Float.parseFloat(st.nextToken()));
                    else
                        throw new MyException("Invalid job title.");
                } catch (Exception e) {
                    throw new MyException("Invalid data format in employee file.");
                }
                
                if (Employee.noStaff>Employee.MAXSTAFF) throw new MyException("There are more employees then space allocated for.");
                Employee.noStaff++;
            }
            
            // set the number of employee records
            infile.close();
        } catch (IOException e) {
            throw new MyException("Errors accessing file "+args[1]);
        }
        System.out.println("The number of employees is "+Employee.noStaff);
        
        // Determine the number of direct reports of each manager
        boolean foundSup=false;
        int i;
        for (i=0; i<Employee.noStaff; i++) {
            if (!staff[i].getSupervisor().equals(" ")) {
                for (int j=0; j<Employee.noStaff; j++)
                    if (staff[j].match(staff[i].getSupervisor())) {
                        staff[j].countDirectReport();
                        foundSup=true;
                        break;
                    }
                break;
            }
        }
        if (!foundSup) throw new MyException("Supervisor "+staff[i].getSupervisor()+" does not exist.");
        // Collect and accumulate workhours and overtime hours of all employees
        try {
            infile = new BufferedReader(new FileReader(args[2]));
            if (!infile.ready()) throw new MyException("There are no work entries in the input file.");
            while (infile.ready()) {
                try {
                    temp=infile.readLine();
                    st=new StringTokenizer(temp);
                    st.nextToken();
                    ssn=st.nextToken();
                    float workHours=Float.parseFloat(st.nextToken());
                    float overTime=Float.parseFloat(st.nextToken());
                    for (int j=0; j<Employee.noStaff; j++)
                        if (staff[j].match(ssn)) {
                            staff[j].computeHours(workHours, overTime);
                            break;
                        }
                } catch (Exception e) {
                    throw new MyException("Invalid data in the workhour file.");
                }
            }
            infile.close();
        } catch (IOException e) {
            throw new MyException("Errors accessing file "+args[2]);
        }
        // Compute salary of each employee and Print results
        for (int j=0; j<Employee.noStaff; j++) 
            staff[j].computeSalary();
        
        Employee.setSortFlag(1);        //Sort by name
        Sort.shellSort((Sortable[])staff, Employee.noStaff);
        System.out.println("\nEmployees sorted by name:");
        for (int j=0; j<Employee.noStaff; j++) 
            staff[j].printData();
        
        
        Employee.setSortFlag(2);        //Sort by salary
        Sort.shellSort((Sortable[])staff, Employee.noStaff);
        System.out.println("\nEmployees sorted by salary");
        for (int j=0; j<Employee.noStaff; j++) 
            staff[j].printData();
        
        
    } // end of main
    
} // end of class



