package myutilities;

/*
 * MyException.java
 *
 * Created on March 2, 2004, 11:43 AM
 * @author  David Haltinner
 */
public class MyException extends java.lang.Exception {
    
    /**
     * Creates a new instance of <code>MyException</code> without detail message.
     */
    public MyException() {
    }
    
    
    /**
     * Constructs an instance of <code>MyException</code> with the specified detail message.
     * @param msg the detail message.
     */
    public MyException(String msg) {
        super(msg);
    }
}
