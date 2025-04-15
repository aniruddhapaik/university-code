import java.io.*;
import java.net.*;

public class FullDuplexClient {
  public static void main(String[] args) {
    final String HOST = "localhost";
    final int PORT = 12345;
    try{
      Socket clientSocket = new Socket(HOST, PORT);
      System.out.println("Connected to the server");

      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
      PrintWriter outputToServer = new PrintWriter(clientSocket.getOutputStream(), true);
      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(System.in));

      String clientMessage, serverMessage;

      while(true) {
        System.out.print("Client: ");
        clientMessage = inputFromClient.readLine();
        outputToServer.println(clientMessage);
        if(clientMessage.equalsIgnoreCase("exit")) {
          System.out.println("Client disconnected");
          break;
        }

        serverMessage = inputFromServer.readLine();
        if(serverMessage.equalsIgnoreCase("exit")) {
          System.out.println("Server disconnected");
          break;
        }
        System.out.println(serverMessage);
      }
      clientSocket.close();
    } catch(IOException e) {
      e.printStackTrace();
    }
  }
}