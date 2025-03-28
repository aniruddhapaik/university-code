import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

public class SimplexClient {
  public static void main(String[] args) {
    final String HOST = "localhost";
    final int PORT = 12345;
    try(Socket socket = new Socket(HOST, PORT)) {
      System.out.println("Connected to server");
      BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      String message = reader.readLine();
      System.out.println("Server: " + message);
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}