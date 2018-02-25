/* SynchronizedBuffer.java
 * SynchronizedBuffer synchronizes access to a single shared integer.
 *
 * Created by David Haltinner
 * Implements a 3 buffer circular layout instead of a single buffer.
 */



public class SynchronizedBuffer implements Buffer {
    private int buffer[] = {-1,-1,-1}; // shared by producer and consumer threads
    private int occupiedBufferCount = 0; // count of occupied buffers
    private int nextToRead=0;
    private int nextToWrite=0;
    
    // place value into buffer
    public synchronized void set( int value ) {
        // for output purposes, get name of thread that called this method
        String name = Thread.currentThread().getName();
        
        // while there are no empty locations, place thread in waiting state
        while ( occupiedBufferCount == 3 ) {
            
            // output thread information and buffer information, then wait
            try {
                System.err.println( name + " tries to write." );
                displayState( "Buffer full. " + name + " waits.\n" );
                wait();
            }
            
            // if waiting thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }
            
        } // end while
        
        buffer[nextToWrite] = value;
        
        // indicate producer cannot store another value
        // until consumer retrieves current buffer value
        nextToWrite++;
        if (nextToWrite>2) nextToWrite=0;
        occupiedBufferCount++;
        displayState( "\n" + name + " writes " + value );
        
        notify(); // tell waiting thread to enter ready state
        
    } // end method set; releases lock on SynchronizedBuffer
    
    // return value from buffer
    public synchronized int get() {
        // for output purposes, get name of thread that called this method
        String name = Thread.currentThread().getName();
        
        // while no data to read, place thread in waiting state
        while ( occupiedBufferCount == 0 ) {
            
            // output thread information and buffer information, then wait
            try {
                System.err.println( name + " tries to read." );
                displayState( "Buffer empty. " + name + " waits.\n" );
                wait();
            }
            
            // if waiting thread interrupted, print stack trace
            catch ( InterruptedException exception ) {
                exception.printStackTrace();
            }
            
        } // end while
        
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
        
    } // end method get; releases lock on SynchronizedBuffer
    
    // display current operation and buffer state
    public void displayState( String operation ) {
        System.err.println(operation);
        System.err.println("(buffers occupied: "+occupiedBufferCount+")");
        System.err.print("buffers:  ");
        if (buffer[0]<10 && buffer[0]>-1) System.err.print(" ");
        System.err.print(buffer[0]);
        if (buffer[1]<10 && buffer[1]>-1) System.err.print(" ");
        System.err.print("   "+buffer[1]);
        if (buffer[2]<10 && buffer[2]>-1) System.err.print(" ");
        System.err.print("   "+buffer[2]+"\n");
        System.err.println("         ---- ---- ----");
        int spacing=10;
        if (nextToRead<nextToWrite) {
            spacing += nextToRead*5;
            for (int i=0; i<spacing; i++) System.err.print(" ");
            System.err.print("R");
            for (int i=0; i<(nextToWrite-nextToRead)*4; i++) System.err.print(" ");
            System.err.print("W");
        }
        else {
            spacing += nextToWrite*5;
            for (int i=0; i<spacing; i++) System.err.print(" ");
            System.err.print("W");
            for (int i=0; i<(nextToRead-nextToWrite)*4; i++) System.err.print(" ");
            System.err.print("R");
        }
        System.err.println("\n");
    }
    
} // end class SynchronizedBuffer


