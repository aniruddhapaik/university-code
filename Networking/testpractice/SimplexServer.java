import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class SimplexServer {
  public static void main(String[] args) {
    final int PORT = 12345;
    try(ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("Waiting for client...");
      Socket socket = serverSocket.accept();
      System.out.println("Client connected.");
      OutputStream outputStream = socket.getOutputStream();
      PrintWriter writer = new PrintWriter(outputStream, true);
      writer.println("This message is sent through output stream");
      System.out.println("Message sent to client");
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}