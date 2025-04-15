import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FullDuplexConnectionLess {
  static final int PORT = 12345;
  static final String HOST = "localhost";
  public static void main(String[] args) {
    System.out.println("Choose mode:\n1. Server\n2. Client\nEnter choice: ");
    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();
    if (choice == 1) { Server(); }
    else if (choice == 2) { Client(); }
    scanner.close();
  }

  public static void Server() {
    try {
      DatagramSocket serverSocket = new DatagramSocket(PORT);
      System.out.println("Waiting for messages from client...");

      byte[] receiveBuffer = new byte[1024];
      byte[] sendBuffer;
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(System.in));

      InetAddress clientAddress = null;
      int clientPort;
      String clientMessage, serverMessage;
      while(true) {
        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        serverSocket.receive(receivePacket);
        clientAddress = receivePacket.getAddress();
        clientPort = receivePacket.getPort();
        clientMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        if (clientMessage.equalsIgnoreCase("exit")) { System.out.println("client exit"); break; }
        System.out.println("Client: " + clientMessage);

        serverMessage = inputFromServer.readLine();
        sendBuffer = serverMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, clientAddress, clientPort);
        serverSocket.send(sendPacket);
        if (serverMessage.equalsIgnoreCase("exit")) { System.out.println("server exit"); break; }
      }
      serverSocket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void Client() {
    try {
      DatagramSocket clientSocket = new DatagramSocket();
      InetAddress serverAddress = InetAddress.getByName(HOST);

      byte[] receiveBuffer = new byte[1024];
      byte[] sendBuffer;
      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(System.in));
      String clientMessage, serverMessage;
      while (true) {
        clientMessage = inputFromClient.readLine();
        sendBuffer = clientMessage.getBytes();
        DatagramPacket sendPacket = new DatagramPacket(sendBuffer, sendBuffer.length, serverAddress, PORT);
        clientSocket.send(sendPacket);
        if (clientMessage.equalsIgnoreCase("exit")) { System.out.println("client exit"); break; }

        DatagramPacket receivePacket = new DatagramPacket(receiveBuffer, receiveBuffer.length);
        clientSocket.receive(receivePacket);
        serverMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        if (serverMessage.equalsIgnoreCase("exit")) { System.out.println("server exit"); break; }
        System.out.println("Server: " + serverMessage);
      }
      clientSocket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }
}