/******************************************************************************
 ** Program 3 Client.java  
 ** by David Haltinner  
 ** May 7th, 2003
 ** This program sends a request to a Server application, that will respond by
 ** either sending the textual contents of the file, or by saying that the file
 ** does not exist. 
 *****************************************************************************/
import java.net.*;
import java.io.*;

public class Client {
    public static void main(String args[]) {
        DatagramSocket s = null;
        String server;
        int port = 5678;
        String lineToBeSent;
        BufferedReader input;
        InetAddress IP=null;
        if (args.length != 3) {
            System.out.println("Usage: client host remotefile localfile");
            System.exit(1);
        }
        server=args[0];
        try {
            IP = InetAddress.getByName(server);
            s=new DatagramSocket(port);
        }
        catch (UnknownHostException e) {
            System.out.println(e);
            System.exit(1);
        }
        catch (IOException e) {
            System.out.println(e);
            System.exit(1);
        }
        byte[] sendData = new byte[1024];
        byte[] receiveData = new byte[1024];
        try {
            lineToBeSent=args[1].concat("#");   // File name
            for (int i=1; i<lineToBeSent.length(); i++) // make it a byte array
                sendData[i]=lineToBeSent.getBytes()[i-1];
            sendData[0]=new Integer(0).byteValue(); // Request open file
            DatagramPacket packet = new DatagramPacket(sendData,sendData.length, IP, port);
            s.send(packet); //Send it!
            BufferedWriter output=new BufferedWriter(new FileWriter(args[2]));
            Byte type;  // Header information
            do {
                packet=new DatagramPacket(receiveData, receiveData.length,IP, port);
                s.receive(packet);      // Get a packet
                type=new Byte(receiveData[0]);  // The header byte
                if (type.intValue()==1) {   // Get text line
                    for (int i=0; i!=receiveData.length-1; i++)
                        receiveData[i]=receiveData[i+1];    // Remove the 1 byte header
                    String message=new String(receiveData);     // Make it a string
                    output.write(message);  //Write to a file
                    System.out.println(message); // Write to the console
                    sendData[0]=new Integer(1).byteValue();     // Make an ACK packet
                    packet = new DatagramPacket(sendData,sendData.length, IP, port);
                    s.send(packet);     // Send ACK packet
                }
            } while (type.intValue()==1);   // Not EOF of File Not Found
            output.close();     //Close file
            s.close();      //Close socket
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
