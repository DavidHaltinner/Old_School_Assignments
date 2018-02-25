// Producer.java with synchronized
// Producer's run method controls a thread that
// stores values in sharedLocation.

import javax.swing.*;
public class Producer extends Thread {
    private Buffer sharedLocation; // reference to shared object
    private int numWrites;
    private JTextArea text;
    // constructor
    public Producer( Buffer shared, int num, JTextArea texttemp) {
        super( "Producer" );
        sharedLocation = shared;
        numWrites=num;
        text=texttemp;
    }
    // store values from 1 to 4 in sharedLocation
    public void run() {
        for ( int count = 1; count <= numWrites; count++ ) {
            
            // sleep 0 to 3 seconds, then place value in Buffer
            try {
                Thread.sleep( ( int ) ( Math.random() * 3001 ) );
                sharedLocation.set( count );
            }
            
            // if sleeping thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }            
        }
        text.append("\n"+getName()+" done producing."+"\nTerminating "+getName()+".\n");        
    }    
} 
