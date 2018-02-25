// Consumer.java
// Consumer's run method controls a thread that loops
// and reads a value from sharedLocation each time.

import javax.swing.*;
public class Consumer extends Thread {
    private Buffer sharedLocation; // reference to shared object
    private int numReads;
    private JTextArea text;
    // constructor
    public Consumer( Buffer shared, int num, JTextArea texttemp ) {
        super( "Consumer" );
        sharedLocation = shared;
        numReads=num;
        text=texttemp;
    }
    
    // read sharedLocation's value four times and sum the values
    public void run() {
        int sum=0;
        for ( int count = 1; count <= numReads; count++ ) {
            
            // sleep 0 to 3 seconds, read value from Buffer and add to sum
            try {
                Thread.sleep( ( int ) ( Math.random() * 3001 ) );
                sum += sharedLocation.get();
            }         
            // if sleeping thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }
        }
        text.append("\n"+getName()+" read values totaling: "+sum+".\nTerminating "+getName()+".\n");
    }
}
