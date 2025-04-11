import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FileTransferSingle {
  private static final int PORT = 5000;
  private static final String READ_PATH = "D:\\Games\\sample.txt";
  private static final String RECEIVE_PATH = "D:\\Games\\received.txt";

  public static void main(String[] args) {
    System.out.println("Choose mode: \n1. Send \n2. Receive");
    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();
    if (choice == 1) { sender(); }
    else { receiver(); }
    scanner.close();
  }

  public static void sender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("S: waiting for receiver to connect...");
      Socket socket = serverSocket.accept();
      System.out.println("S: receiver connected.");

      File file = new File(READ_PATH);
      FileInputStream fileInputStream = new FileInputStream(file);
      OutputStream outputStream = socket.getOutputStream();
      byte[] buffer = new byte[4096];
      int bytesRead;

      while((bytesRead = fileInputStream.read(buffer)) != -1) {
        outputStream.write(buffer, 0, bytesRead);
      }

      System.out.println("S: File sent successfully.");
      fileInputStream.close();
      outputStream.close();
      socket.close();
      serverSocket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void receiver() {
    try (Socket socket = new Socket("localhost", PORT)) {
      System.out.println("R: Connected to the sender server.");

      InputStream inputStream = socket.getInputStream();
      FileOutputStream fileOutputStream = new FileOutputStream(RECEIVE_PATH);
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while((bytesRead = inputStream.read(buffer)) != -1) {
        fileOutputStream.write(buffer, 0, bytesRead);
      }

      System.out.println("R: file received and written successfully");
      socket.close();
      fileOutputStream.close();
      inputStream.close();
    } catch (IOException e) { e.printStackTrace(); }
  }
}