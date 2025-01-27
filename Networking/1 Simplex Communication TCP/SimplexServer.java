import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class SimplexServer { 
  public static void main(String[] args) { 
    final int PORT = 12345;
    try (ServerSocket serverSocket = new ServerSocket(PORT)) { 
      System.out.println("Server is running and waiting for a connection...");
      // Wait for a client connection 
      Socket socket = serverSocket.accept();
      System.out.println("Client connected!");
      // Send data to the client 
      OutputStream outputStream = socket.getOutputStream();
      PrintWriter writer = new PrintWriter(outputStream, true);
      writer.println("Hello, this is simplex communication from the server!");
      System.out.println("Message sent to the client.");
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
} 