import java.net.*;
import java.io.*;
public class FullDuplexUDPServer { 
  public static void main(String[] args) { 
    try { 
      // Create a DatagramSocket on port 12345 
      DatagramSocket serverSocket = new DatagramSocket(12345);
      System.out.println("Server is waiting for messages...");
      byte[] receiveBuffer = new byte[1024];
      byte[] sendBuffer;
      
      InetAddress clientAddress = null;
      int clientPort = 0;
      
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(System.in));
      
      while (true) { 
        // Receive a message from the client 
        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        serverSocket.receive(receivePacket);
        String clientMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        
        clientAddress = receivePacket.getAddress();
        clientPort = receivePacket.getPort();
        
        System.out.println("Client: " + clientMessage);
        
        if (clientMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Client disconnected.");
          break;
        } 

        // Send a response to the client 
        System.out.print("Server: ");
        String serverMessage = inputFromServer.readLine();
        sendBuffer = serverMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, clientAddress, clientPort);
        serverSocket.send(sendPacket);
        
        if (serverMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Server disconnected.");
          break;
        } 
      } 
      // Close the socket 
      serverSocket.close();
    } catch (IOException e) { 
      e.printStackTrace();
    } 
  } 
} 