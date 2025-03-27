import java.io.*;
import java.net.*;

public class FullDuplexServer {
  public static void main(String[] args) {
    final int PORT = 12345;
    try{
      ServerSocket serverSocket = new ServerSocket(PORT);
      System.out.println("Waiting for client...");
      Socket clientSocket = serverSocket.accept();
      System.out.println("Client connected!");

      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      PrintWriter outputToClient = new PrintWriter(clientSocket.getOutputStream(), true);
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(System.in));

      String clientMessage, serverMessage;

      while(true) {
        clientMessage = inputFromClient.readLine();
        if (clientMessage.equalsIgnoreCase("exit")) {
          System.out.println("Client disconnected.");
          break;
        }
        System.out.println("Client: " + clientMessage);

        System.out.print("Server: ");
        serverMessage = inputFromServer.readLine();
        outputToClient.println(serverMessage);
        if (serverMessage.equalsIgnoreCase("exit")) {
          System.out.println("Disconnected!");
          break;
        }
      }
      serverSocket.close();
      clientSocket.close();
    } catch(IOException e) {
      e.printStackTrace();
    }
  }
}