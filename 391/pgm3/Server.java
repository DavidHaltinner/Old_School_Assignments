/******************************************************************************
 ** Program 3 Server.java  
 ** by David Haltinner  
 ** May 7th, 2003
 ** This program responds to a request, and sends either the textual contents of
 ** the requested file, or by saying that the file does not exist. 
 *****************************************************************************/
import java.net.*;
import java.io.*;

public class Server {
    public static void main(String args[]) {
        int port=5678;
        DatagramSocket s=null;
        InetAddress IPAddress=null;
        try {
            s=new DatagramSocket(port);
            
            byte[] receiveData = new byte[1024];
            byte[] sendData = new byte[1024];
            BufferedReader input=null;
startover:  // If there is no file start over and wait for new request
            while(true) {   //Server needs to keep going
                DatagramPacket packet = new DatagramPacket(receiveData, receiveData.length);
                s.receive(packet);  // Get a packet
                Byte type = new Byte(receiveData[0]);
                if (type.intValue()==0) {   //Open File Request
                    for (int i=0; i<receiveData.length-1; i++)
                        receiveData[i]=receiveData[i+1];    // Take of the 1 byte header
                    String file=new String(receiveData);    // Filename
                    try {
                        input = new BufferedReader(new FileReader(file));   // open the file
                    }
                    catch (IOException e) {
                        sendData[0]=new Integer(0).byteValue();     //File not found message
                        IPAddress=packet.getAddress();      // Get their address
                        packet = new DatagramPacket(sendData, sendData.length, IPAddress, port);
                        s.send(packet);     // Tell them I can't find the file
                        continue startover;     // Let's start over
                    }
                }
                type=new Byte(new Integer(1).byteValue());  // Tell them I'm sending a line of text
                while (input.ready()) {
                    if (type.intValue()!=0) {     // Not an open request
                        String message=input.readLine();    // Get line of file
                        IPAddress = packet.getAddress();    // Get their address
                        for (int i=1; i<message.length(); i++)
                            sendData[i]=message.getBytes()[i-1];    // Change from string to byte[]
                        sendData[0]=new Integer(1).byteValue(); //File Line header
                        packet = new DatagramPacket(sendData, sendData.length, IPAddress, port);
                        s.send(packet); // Send the file line
                    }
                    s.receive(packet);  // Get an ACK (we hope!)
                    type = new Byte(receiveData[0]);    // Is it an ACK?
                }
                sendData[0]=new Integer(2).byteValue();     //We are done, End of File
                packet = new DatagramPacket(sendData, sendData.length, IPAddress, port);
                s.send(packet);     // Tell them
                input.close();      // Close File
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}


