import java.net.*;
import java.io.*;

public class FullDuplexUDPClient { 
  public static void main(String[] args) { 
    try { 
      // Create a DatagramSocket 
      DatagramSocket clientSocket = new DatagramSocket();
      InetAddress serverAddress = InetAddress.getByName("localhost");
      byte[] sendBuffer;
      byte[] receiveBuffer = new byte[1024];
      BufferedReader inputFromClient = new BufferedReader(new 
      InputStreamReader(System.in));
      
      while (true) { 
        // Send a message to the server 
        System.out.print("Client: ");
        String clientMessage = inputFromClient.readLine();
        sendBuffer = clientMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, 12345);
        clientSocket.send(sendPacket);
        if (clientMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Client disconnected.");
          break;
        } 

        // Receive a response from the server 
        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        clientSocket.receive(receivePacket);
        String serverMessage = new String(receivePacket.getData(), 0, 
        receivePacket.getLength());
        System.out.println("Server: " + serverMessage);

        if (serverMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Server disconnected.");
          break;
        } 
      } 
      // Close the socket 
      clientSocket.close();
    } catch (IOException e) { 
      e.printStackTrace();
    } 
  } 
} 