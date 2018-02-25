// SharedBufferTest2.java
// SharedBufferTest2creates producer and consumer threads.

public class SharedBufferTest {

   public static void main( String [] args )
   {
      // create shared object used by threads; we use a SynchronizedBuffer
      // reference rather than a Buffer reference so we can invoke
      // SynchronizedBuffer method displayState from main
      SynchronizedBuffer sharedLocation = new SynchronizedBuffer();

      // create producer and consumer objects
      Producer producer = new Producer( sharedLocation );
      Consumer consumer = new Consumer( sharedLocation );

      producer.start();  // start producer thread
      consumer.start();  // start consumer thread

   } // end main

} // end class SharedBufferTest2


