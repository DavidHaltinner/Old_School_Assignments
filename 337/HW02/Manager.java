public class Manager extends Employee {
    private static final float RATE = 0.02F;
    private float baseSalary;
    private int directReport; // number of people report to the manager
    
     // Constructor
    public Manager(String s1, String s2, float x) {
    	super(s1, s2, " ");  // empty string for supervisor
    	position = "manager";
      	baseSalary = x;
    }
    
    public void countDirectReport() {
    	directReport++;
    }
    
    public void computeSalary() {
       	salary = baseSalary * (1 + RATE * directReport );
 	}
}

