import java.io.*;
import java.net.*;
import java.util.Scanner;

public class SimplexConnectionOriented {
  static final int PORT = 12345;
  static final String HOST = "localhost";
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Choose mode:\n1. Send\n2. Receive\nEnter Choice: ");
    int choice = scanner.nextInt();
    if (choice == 1) { Sender(); }
    else if (choice == 2) { Receiver(); }
    scanner.close();
  }

  public static void Sender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("Waiting for receiver to connect...");
      Socket socket = serverSocket.accept();
      System.out.println("Receiver connected.");
      PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);
      writer.println("This is a message sent to the receiver");
      System.out.println("Message sent to receiver");
      serverSocket.close();
      socket.close();
    } catch (Exception e) { e.printStackTrace(); }
  }

  public static void Receiver() {
    try (Socket socket = new Socket(HOST, PORT)) {
      System.out.println("Connected to sender");
      BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
      String message = reader.readLine();
      System.out.println("Message from sender: " + message);
      socket.close();
    } catch (Exception e) { e.printStackTrace(); }
  }
}