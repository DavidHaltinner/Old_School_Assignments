import java.net.*;
import java.io.*;

public class Server {
    public static void main(String args[]) {
        int port=5678;
        ServerSocket s;
        BufferedReader input;
        try {
            s=new ServerSocket(port);
            while(true) {
                Socket new_s = s.accept();
                input=new BufferedReader(new InputStreamReader(new_s.getInputStream()));
                try {
                    while(true) {
                        String message=input.readLine();
                        if (message==null) break;
                        System.out.println(message);
                    }
                }
                catch (IOException e) {
                    System.out.println(e);
                }
                try {
                    new_s.close();
                    System.out.println("Connectio closed by client");
                }
                catch (IOException e) {
                    System.out.println(e);
                }
            }
        }
        catch (IOException e) {
            System.out.println(e);
        }
    }
}
