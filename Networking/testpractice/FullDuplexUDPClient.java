import java.io.*;
import java.net.*;

public class FullDuplexUDPClient {
  public static void main(String[] args) {
    try{
      DatagramSocket clientSocket = new DatagramSocket();
      byte[] sendBuffer;
      byte[] receiveBuffer = new byte[1024];
      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(System.in));

      int serverPort = 12345;
      InetAddress serverAddress = InetAddress.getByName("localhost");

      while(true) {
        System.out.print("Client: ");
        String clientMessage = inputFromClient.readLine();
        sendBuffer = clientMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, serverPort);
        clientSocket.send(sendPacket);
        if(clientMessage.equalsIgnoreCase("exit")) {
          System.out.println("Client disconnected!");
          break;
        }

        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        clientSocket.receive(receivePacket);
        String serverMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        System.out.println("Server: " + serverMessage);
        if(serverMessage.equalsIgnoreCase("exit")) {
          System.out.println("Server disconnected!");
          break;
        }
      }
      clientSocket.close();
    } catch(IOException e) {
      e.printStackTrace();
    }
  }
}