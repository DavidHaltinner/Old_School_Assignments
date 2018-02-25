/* SynchronizedBuffer.java
 * SynchronizedBuffer synchronizes access to a single shared integer.
 *
 * Created by David Haltinner
 * Implements a 3 buffer circular layout instead of a single buffer.
 */
import javax.swing.*;

public class SynchronizedBuffer implements Buffer {
    private int buffer[] = {-1,-1,-1}; // shared by producer and consumer threads
    private int occupiedBufferCount = 0; // count of occupied buffers
    private int nextToRead=0;
    private int nextToWrite=0;
    private JTextArea text;
   
    public SynchronizedBuffer(JTextArea temp) {
        text=temp;
    }
    
    // place value into buffer
    public synchronized void set( int value ) {
        // for output purposes, get name of thread that called this method
        String name = Thread.currentThread().getName();        
        // while there are no empty locations, place thread in waiting state
        while ( occupiedBufferCount == 3 ) {            
            // output thread information and buffer information, then wait
            try {
                text.append( name + " tries to write." );
                displayState( "Buffer full. " + name + " waits.\n" );
                wait();
            }            
            // if waiting thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }            
        }         
        buffer[nextToWrite] = value;        
        // indicate producer cannot store another value
        // until consumer retrieves current buffer value
        nextToWrite++;
        if (nextToWrite>2) nextToWrite=0;
        occupiedBufferCount++;
        displayState( "\n" + name + " writes " + value );        
        notify(); // tell waiting thread to enter ready state        
    } 
    
    public synchronized int get() {
        // for output purposes, get name of thread that called this method
        String name = Thread.currentThread().getName();        
        // while no data to read, place thread in waiting state
        while ( occupiedBufferCount == 0 ) {            
            // output thread information and buffer information, then wait
            try {
                text.append( name + " tries to read." );
                displayState( "Buffer empty. " + name + " waits.\n" );
                wait();
            }            
            // if waiting thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }            
        }         
        // indicate that producer can store another value
        // because consumer just retrieved buffer value
        --occupiedBufferCount;
        int temp=buffer[nextToRead];
        if (nextToRead==nextToWrite-1) nextToWrite--;
        else if (nextToRead==2 && nextToWrite==0) nextToWrite=2;
        else {
            nextToRead++;
            if (nextToRead>2) nextToRead=0;
        }
        displayState( "\n" + name + " reads " + temp );        
        notify(); // tell waiting thread to become ready to execute       
        return temp;        
    }     
    // display current operation and buffer state
    public void displayState( String operation ) {
        text.append(operation+"\n");
        text.append("(buffers occupied: "+occupiedBufferCount+")\n");
        text.append("buffers:  ");
        if (buffer[0]<10 && buffer[0]>-1) text.append(" ");
        text.append(buffer[0]+"");
        if (buffer[1]<10 && buffer[1]>-1) text.append(" ");
        text.append("   "+buffer[1]);
        if (buffer[2]<10 && buffer[2]>-1) text.append(" ");
        text.append("   "+buffer[2]+"\n");
        text.append("          ---- ---- ----\n");
        int spacing=10;
        if (nextToRead<nextToWrite) {
            spacing += nextToRead*6+1;
            for (int i=0; i<spacing; i++) text.append(" ");
            text.append("R");
            for (int i=0; i<(nextToWrite-nextToRead)*4+1; i++) text.append(" ");
            text.append("W");
        }
        else {
            spacing += nextToWrite*6+1;
            for (int i=0; i<spacing; i++) text.append(" ");
            text.append("W");
            for (int i=0; i<(nextToRead-nextToWrite)*4+1; i++) text.append(" ");
            text.append("R");
        }
        text.append("\n");
    }
}
