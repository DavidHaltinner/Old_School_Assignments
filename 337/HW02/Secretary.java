public class Secretary extends Employee {
    private float hourlyPay;
    private int   supervisor;
     
    // Constructor
    public Secretary(String s1, String s2, String s3, float x) {
    	super(s1, s2, s3);
    	position = "secretary";
    	hourlyPay = x;
    	salary = 0;
 	}

    public void computeSalary() {
       	salary = hourlyPay * (workHours + 1.5F * overtimeHours);
 	}
}

