import java.io.*;
import java.net.*;

public class FullDuplexUDPServer {
  public static void main(String[] args) {
    final int serverPort = 12345;
    try{
      byte[] sendBuffer;
      byte[] receiveBuffer = new byte[1024];
      InetAddress clientAddress = null;
      int clientPort = 0;
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(System.in));

      DatagramSocket serverSocket = new DatagramSocket(serverPort);
      System.out.println("Waiting for message from client");

      while(true) {
        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        serverSocket.receive(receivePacket);
        clientAddress = receivePacket.getAddress();
        clientPort = receivePacket.getPort();
        String clientMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        if(clientMessage.equalsIgnoreCase("exit")) {
          System.out.println("Client disconnected.");
          break;
        }
        System.out.println("Client: " + clientMessage);

        System.out.print("Server: ");
        String serverMessage = inputFromServer.readLine();
        sendBuffer = serverMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, clientAddress, clientPort);
        serverSocket.send(sendPacket);
        if(serverMessage.equalsIgnoreCase("exit")) {
          System.out.println("Server disconnected");
          break;
        }
      }
      serverSocket.close();
    } catch(IOException e) {
      e.printStackTrace();
    }
  }
}