import java.io.*;
import java.net.*;
public class FullDuplexServer { 
  public static void main(String[] args) { 
    try { 
      // Create a server socket on port 12345 
      ServerSocket serverSocket = new ServerSocket(12345);
      System.out.println("Server is waiting for a client...");
      // Accept an incoming client connection 
      Socket clientSocket = serverSocket.accept();
      System.out.println("Client connected!");
      // Streams for communication 
      BufferedReader inputFromClient = new BufferedReader(new 
      InputStreamReader(clientSocket.getInputStream()));
      PrintWriter outputToClient = new PrintWriter(clientSocket.getOutputStream(), true);
      BufferedReader inputFromServer = new BufferedReader(new 
      InputStreamReader(System.in));
      String clientMessage, serverMessage;

      while (true) { 
        // Receive message from client 
        clientMessage = inputFromClient.readLine();
        if (clientMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Client disconnected.");
          break;
        } 
        System.out.println("Client: " + clientMessage);
        
        // Send message to client 
        System.out.print("Server: ");
        serverMessage = inputFromServer.readLine();
        outputToClient.println(serverMessage);
        if (serverMessage.equalsIgnoreCase("exit")) { 
          System.out.println("Server disconnected.");
          break;
        } 
      } 
      // Close connections 
      clientSocket.close();
      serverSocket.close();
    } catch (IOException e) { 
      e.printStackTrace();
    } 
  } 
} 