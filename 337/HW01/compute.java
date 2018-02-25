/**
 * compute.java
 * This program takes in input from a file in the form of a mathmetical 
 * operation followed by 2 integers. It will output the first number, the 
 * operation, the second number, and equals sign, and the naswer to a another 
 * file given as the second argumanet.
 *
 * Due on February 12, 2004
 * @author  David Haltinner
 */
import java.io.*;
import java.util.*;
public class compute {
    
    /** Creates a new instance of compute */
    public compute() {
    }
    
    /**
     * The main method which does the input, arithmetic, and output.
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        if (args.length!=2) {
            System.out.println("Wrong number of arguments.\nUSAGE: java compute infile outfile\n");
            System.exit(1);
        }
        try {
            BufferedReader infile = new BufferedReader(new FileReader(args[0]));
            FileWriter outfile = new FileWriter(args[1]);
            while (infile.ready()) {
                StringTokenizer input=new StringTokenizer(infile.readLine());
                String operation=input.nextToken();
                int num1=Integer.parseInt(input.nextToken());
                int num2=Integer.parseInt(input.nextToken());
                int answer=0;
                if (operation.equals("+")) answer=num1+num2;
                else if (operation.equals("-")) answer=num1-num2;
                else if (operation.equals("*")) answer=num1*num2;
                else if (operation.equals("/")) answer=num1/num2;
                outfile.write(num1 + " " + operation + " " + num2 + " = " + answer + "\n");
            }
            infile.close();
            outfile.close();
        }
        catch (Exception e) {
            System.out.println(e);
            System.exit(1);
        }   
    }
}
