import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FileTransferSingle {
  private static final int PORT = 5000;
  private static final String FILE_READ = "D:\\Games\\sample.txt";
  private static final String FILE_WRITE = "D:\\Games\\received.txt";

  public static void sender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("S: Waiting for client to connect...");
      Socket socket = serverSocket.accept();
      System.out.println("S: Client connected.");
      
      File file = new File(FILE_READ);
      FileInputStream fileInputStream = new FileInputStream(file);
      OutputStream outputStream = socket.getOutputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while((bytesRead = fileInputStream.read(buffer)) != -1) {
        outputStream.write(buffer, 0, bytesRead);
      }

      fileInputStream.close();
      outputStream.close();
      serverSocket.close();
      socket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void receiver() {
    try (Socket socket = new Socket("localhost", PORT)) {
      System.out.println("R: connected to the server.");

      FileOutputStream fileOutputStream = new FileOutputStream(FILE_WRITE);
      InputStream inputStream = socket.getInputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while((bytesRead = inputStream.read(buffer)) != -1) {
        fileOutputStream.write(buffer, 0, bytesRead);
      }

      fileOutputStream.close();
      inputStream.close();
      socket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Choose mode: \n1. Send\n2. Receive");
    int choice = scanner.nextInt();
    if (choice == 1) { sender(); }
    else if (choice == 2) { receiver(); }
    scanner.close();
  }
}