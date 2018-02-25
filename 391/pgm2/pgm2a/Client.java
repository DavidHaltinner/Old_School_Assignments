import java.net.*;
import java.io.*;

public class Client {
    public static void main(String args[]) {
        Socket s = null;
        String server;
        int port = 5678;
        String lineToBeSent;
        BufferedReader input;
        PrintWriter output;
        if (args.length != 1) {
            System.out.println("Usage: client host");
            System.exit(1);
        }
        server=args[0];
        try {
            s=new Socket(server, port);
        }
        catch (UnknownHostException e) {
            System.out.println(e);
            System.exit(1);
        }
        catch (IOException e) {
            System.out.println(e);
            System.exit(1);
        }
        try {
            InputStream getack=s.getInputStream();
            input=new BufferedReader(new InputStreamReader(System.in));
            output=new PrintWriter(s.getOutputStream(), true);
            while(true) {
                lineToBeSent=input.readLine();
                if (lineToBeSent.equals(".")) break;
                output.println(lineToBeSent);
                System.out.println(getack.read());
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
        try {
            s.close();
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
