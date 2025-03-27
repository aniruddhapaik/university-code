import java.io.*;
import java.net.*;

public class FullDuplexClient { 
  public static void main(String[] args) { 
    try { 
      // Connect to the server on localhost and port 12345 
      Socket socket = new Socket("localhost", 12345);
      System.out.println("Connected to the server!");
      // Streams for communication 
      BufferedReader inputFromServer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      PrintWriter outputToServer = new PrintWriter(socket.getOutputStream(), true);
      BufferedReader inputFromClient = new BufferedReader(new InputStreamReader(System.in));
      
      String serverMessage, clientMessage;
      
      while (true) { 
        // Send message to server
        System.out.print("Client: ");
        clientMessage = inputFromClient.readLine();
        outputToServer.println(clientMessage);
        if (clientMessage.equalsIgnoreCase("exit")) { 
        System.out.println("Client disconnected.");
        break;
        } 

        // Receive message from server 
        serverMessage = inputFromServer.readLine();
        if (serverMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Server disconnected.");
          break;
        } 
        System.out.println("Server: " + serverMessage);
      } 
      
      // Close connections 
      socket.close();
    } catch (IOException e) { 
      e.printStackTrace();
    } 
  } 
}