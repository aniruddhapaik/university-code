import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FullDuplexConnectionOriented {
  static final int PORT = 12345;
  static final String HOST = "localhost";
  public static void main(String[] args) {
    System.out.println("Chose mode:\n1. Server\n2. Client\nEnter choice: ");
    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();
    if (choice == 1) { Server(); }
    else if (choice == 2) { Client(); }
    scanner.close();
  }

  public static void Server() {
    try {
      ServerSocket serverSocket = new ServerSocket(PORT);
      System.out.println("waiting for client");
      Socket socket = serverSocket.accept();
      System.out.println("client connected");

      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(System.in));
      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter outputToClient = new PrintWriter(socket.getOutputStream(), true);
      String clientMessage, serverMessage;
      while(true) {
        clientMessage = inputFromClient.readLine();
        if (clientMessage.equalsIgnoreCase("exit")) { break; }
        System.out.println("client: " + clientMessage);

        serverMessage = inputFromServer.readLine();
        outputToClient.println(serverMessage);
        if (serverMessage.equalsIgnoreCase("exit")) { break; }
      }
    } catch (Exception e) { e.printStackTrace(); }
  }

  public static void Client() {
    try (Socket socket = new Socket(HOST, PORT)) {
      System.out.println("Connected to the server");

      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(System.in));
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter outputToServer = new PrintWriter(socket.getOutputStream(), true);
      String clientMessage, serverMessage;
      while (true) {
        clientMessage = inputFromClient.readLine();
        outputToServer.println(clientMessage);
        if (clientMessage.equalsIgnoreCase("exit")) { break; }

        serverMessage = inputFromServer.readLine();
        if (serverMessage.equalsIgnoreCase("exit")) { break; }
        System.out.println("Server: " + serverMessage);
      }
    } catch (Exception e) { e.printStackTrace(); }
  }
}