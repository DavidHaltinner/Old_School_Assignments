import java.net.*;
import java.io.*;

public class Server {
    public static void main(String args[]) {
        int port=5678;
        DatagramSocket s=null;
        InetAddress IPAddress=null;
        try {
            s=new DatagramSocket(port);
            
            while(true) {
                try {
                    while(true) {
                        byte[] receiveData = new byte[1024];
                        byte[] sendData = new byte[1024];
                        
                        DatagramPacket packet = new DatagramPacket(
				receiveData, receiveData.length);
                        s.receive(packet);
                        
                        String message=new String(packet.getData());
                // I need to find the size of the actual string, since the
		// length of it is the size of the byte array. So I used a 
		// marker to determine the real size.
                        int i;
                        for (i=0; i<message.length(); i++)
                            if (message.charAt(i)=='#') break;
                        message=message.substring(0,i);
                        System.out.println(message);
                        IPAddress = packet.getAddress();
                        ByteArrayOutputStream bos = 
				new ByteArrayOutputStream();
                        DataOutputStream dos = new DataOutputStream(bos);
                        dos.writeInt(message.length());
                        sendData=bos.toByteArray();
                        packet = new DatagramPacket(sendData, 
				sendData.length, IPAddress, port);
                        s.send(packet);
                    }
                }
                catch (IOException e) {
                    System.out.println(e);
                }
                
                s.close();
                System.out.println("Connection closed by client");
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
