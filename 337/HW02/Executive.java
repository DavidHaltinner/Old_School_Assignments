public class Executive extends Manager {
    private static final float RATE = 0.025F;
    private float baseSalary;
    private float profit;
        
     // Constructor
    public Executive(String s1, String s2, float x, float y) {
    	super(s1, s2, x);
    	position = "executive";
     	baseSalary = x;
     	profit = y;
    }
    
    public void computeSalary() {
    	salary = baseSalary + profit * RATE;
	}
}

