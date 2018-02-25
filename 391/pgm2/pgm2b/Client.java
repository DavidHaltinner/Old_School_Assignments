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
        if (args.length != 1) {
            System.out.println("Usage: client host");
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
            input=new BufferedReader(new InputStreamReader(System.in));
            while(true) {
                lineToBeSent=input.readLine();
                lineToBeSent=lineToBeSent.concat("#");
		// I need to find the size of the actual string, since the
		// length of it is the size of the byte array. So I used a 
		// marker to determine the real size.

                sendData=lineToBeSent.getBytes();
                if (lineToBeSent.equals(".")) break;
                DatagramPacket packet = new DatagramPacket(sendData, 
			lineToBeSent.length(), IP, port);
                packet.setLength(lineToBeSent.length());
                s.send(packet);
                packet=new DatagramPacket(receiveData, receiveData.length, 
			IP, port);
                s.receive(packet);
                ByteArrayInputStream bos = new ByteArrayInputStream(
			packet.getData());
                DataInputStream dos = new DataInputStream(bos);
                int size=dos.readInt();
                System.out.println(size);
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
        s.close();
    }
}
