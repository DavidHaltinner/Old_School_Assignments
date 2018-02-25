public class Programmer extends Employee {
    private float baseSalary;
    private float overtimePay;
     
    // Constructor
    public Programmer(String s1, String s2, String s3, float x, float y) {
    	super(s1, s2, s3);
    	position = "programmer";
     	baseSalary = x;
    	overtimePay = y;
    	salary = 0;
	}
        
    public void computeSalary() {
       	salary = baseSalary + overtimePay * overtimeHours;
    }
}

