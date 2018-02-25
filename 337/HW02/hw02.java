/****************************************************
 *
 * HW02 - compute employee salary
 *
 * Author: David Haltinner
 * Date:  02/24/2004
 * Description: compute employee salary
 *
 * inputfile1: employee.txt
 *
 *   employeeName SS# position supervisorSS# baseSalary [overtimePay]
 *
 *      [overtimePay] for programmer only
 *
 * inputfile2: workhour.txt
 *
 *   timeLog employeeSS# workhours overtimeHours
 *
 * usage: java hw02 <profit>
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
import java.io.*;
import java.util.*;

public class hw02 {
    
    public static void main(String[] args) throws IOException {
        // profit comes from command line: java hw02 <profit>
        if (args.length != 1) {
            System.out.println("Please pass the profit as a command line argument");
            System.exit(1);
        }
        float profit=Float.parseFloat(args[0]);
        
        // Create an array of employees, staff[]; the length of staff is MAXSTAFF
        Employee [ ] staff = new Employee[Employee.MAXSTAFF];
        
        // Choose a line-oriented class e.g. LineNumberReader and FileReader
        // to read from the two data files
        BufferedReader infile = new BufferedReader(new FileReader("employee.txt"));
        
        // Fill the records of employees in staff[]
        String temp;
        StringTokenizer st;
        Employee.noStaff=0;
        String name, ssn, position;
        
        while (infile.ready()) {
            temp = infile.readLine();
            st = new StringTokenizer(temp);
            name=st.nextToken();
            ssn=st.nextToken();
            position=st.nextToken();
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
            else {
                System.out.println("Invalid job: "+position);
                System.exit(1);
            }
            Employee.noStaff++;
        }
        
        // set the number of employee records
        infile.close();
        System.out.println("The number of employees is "+Employee.noStaff);
        
        // Determine the number of direct reports of each manager
        for (int i=0; i<Employee.noStaff; i++) {
            if (!staff[i].getSupervisor().equals(" "))
                for (int j=0; j<Employee.noStaff; j++)
                    if (staff[j].match(staff[i].getSupervisor()))
                        staff[j].countDirectReport();
        }
        
        // Collect and accumulate workhours and overtime hours of all employees
        infile = new BufferedReader(new FileReader("workhour.txt"));
        while (infile.ready()) {
            temp=infile.readLine();
            st=new StringTokenizer(temp);
            st.nextToken();
            ssn=st.nextToken();
            float workHours=Float.parseFloat(st.nextToken());
            float overTime=Float.parseFloat(st.nextToken());
            for (int j=0; j<Employee.noStaff; j++)
                if (staff[j].match(ssn))
                    staff[j].computeHours(workHours, overTime);
        }
        infile.close();
        
        // Compute salary of each employee and Print results
        for (int j=0; j<Employee.noStaff; j++) {
            staff[j].computeSalary();
            staff[j].printData();
        }
        
    } // end of main
    
} // end of class



