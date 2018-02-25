public class Employee {
    public static final int MAXSTAFF = 100;  // why static and final?
    public static int noStaff;	// class variable to be shared by all objects

    private String name;		// why private?  Would public be ok?
    private String ssn;
    private String supervisor;   // ssn of supervisor

    protected String position;	// why protected?  Would private work?
    protected float workHours;
    protected float overtimeHours;
    protected float salary;

	//private String position;
    //private float workHours;
    //private float overtimeHours;
    //private float salary;

     // Constructor
    public Employee(String s1, String s2, String s3) {
    	name = s1;				// Can I have: String name = s1; here?
    	ssn  = s2;
    	supervisor = s3;
    	workHours = 0;
    	overtimeHours = 0;
    	salary = 0;
    }
    /***********************************************
     *  Record regular and overtime work hours
     *  even if we may not use it to compute salary
     ***********************************************/
    public void computeHours(float x, float y) {  // accumulates workHours and
    	workHours += x;							  // overtimeHours for an employee
    	overtimeHours += y;
	}

    public boolean match(String x) {		// to be used for comparing ssn
    	if( ssn.compareTo(x) == 0 ) {
    		return true;
    	} else {
    		return false;
    	}
	}


	public float getSalary() {
		return( salary );
	}

	public String getSupervisor() {
		return( supervisor );
	}

	public String getPosition() {
		return( position );
	}


	public void printData() {
		System.out.println( "Name = " + name );
		System.out.println( "\tssn = " + ssn);
		System.out.println( "\tposition = " + position);
		System.out.println( "\tsalary = " + salary);
	}

	public void computeSalary() {
    	//  null - to be defined in the subclass
	}

	public void countDirectReport() {
		// null - to be defined in the subclass
	}
}


