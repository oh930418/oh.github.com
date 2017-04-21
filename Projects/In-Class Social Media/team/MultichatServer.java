package team;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map; 

public class MultichatServer {
 
    //creat map to save user_name, client's outputstream
     Map<String, DataOutputStream> clients; 
     Data data[] = new Data[10];
     
     int data_num = 0;
     int q_num = 0;

    MultichatServer() { 
        clients = Collections.synchronizedMap( //
                 new HashMap<String, DataOutputStream>());
     } 

    public void start() {
         ServerSocket serverSocket = null; 
        Socket socket = null; 

        try { 
            serverSocket = new ServerSocket(7779);
 
            while (true) { 
                // Waiting for client access. accept() 
                socket = serverSocket.accept(); 

                // creat Thread  (server -> client)
                 ServerReceiver thread = new ServerReceiver(socket);
                 thread.start(); 

            }// while 

        } catch (Exception e) { 
            e.printStackTrace(); 
        } finally { 
            SocketUtil.close(serverSocket); 
        } 
    } 
    // Send a message to all users  
    void sendToAll(String msg) { 
        // Extract list of connected users
        Iterator<String> it = clients.keySet().iterator(); 

        while (it.hasNext()) { 
            try { 
            	

                String name = it.next(); 
                DataOutputStream out = clients.get(name); 
                out.writeUTF(msg); 
            } catch (IOException e) { 
            } 
        } 
    } 

    public static void main(String[] args) {
         new MultichatServer().start(); 
    } 

 
     // Thread (server -> client)
    class ServerReceiver extends Thread {
         Socket socket; 
        DataInputStream in; 
        DataOutputStream out; 

        ServerReceiver(Socket socket) { 
            this.socket = socket; 
            try { 
                // creat InputStream to receive
                 in = new DataInputStream(socket.getInputStream());
                  
                // creat OutputStream to send
                 out = new DataOutputStream(socket.getOutputStream());
             } catch (IOException e) { 
            } 
        } 

        public void run() {
             String name = ""; 
            try { 
                // The server first receive a name from the client.
                 name = in.readUTF(); 
                 
                 // store client information on Map  
                clients.put(name, out); 
               // Send the received message to all clients
                 while (in != null) { 

                     sendToAll(in.readUTF()); 
                }//while  
                 
            } catch (IOException e) { 
                // ignore 
            } finally { 
 e
                  
                // remove client object
                clients.remove(name); 
                System.out.println("[" + socket.getInetAddress() //
                         + ":" + socket.getPort() + "]" + "에서 접속을 종료하였습니다.");
             } 
        } 
    } 
}
