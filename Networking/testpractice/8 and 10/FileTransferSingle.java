import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FileTransferSingle {
  private static final int PORT = 5000;
  private static final String FILE_TO_SEND = "D:\\Games\\sample.txt";
  private static final String FILE_TO_RECEIVE = "D:\\Games\\received.txt";

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.println("Choose mode: \n1. Sender \n2. Receiver");
    int choice = scanner.nextInt();
    
    if (choice == 1) {
      startSender();
    } else if (choice == 2) {
      startReceiver();
    } else {
      System.out.println("Invalid choice. Exiting...");
    }

    scanner.close();
  }
  
  public static void startSender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("Waiting for receiver...");
      Socket socket = serverSocket.accept();
      System.out.println("Receiver connected!");

      File file = new File(FILE_TO_SEND);
      FileInputStream fileInputStream = new FileInputStream(file);
      OutputStream outputStream = socket.getOutputStream();
      byte[] buffer = new byte[4096];
      int bytesRead;

      while ((bytesRead = fileInputStream.read(buffer)) != -1) {
        outputStream.write(buffer, 0, bytesRead);
      }

      System.out.println("File sent successfully!");
      fileInputStream.close();
      outputStream.close();
      socket.close();
      serverSocket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
  
  public static void startReceiver() {
    try (Socket socket = new Socket("localhost", PORT)) {
      System.out.println("Connected to sender!");

      InputStream inputStream = socket.getInputStream();
      FileOutputStream fileOutputStream = new FileOutputStream(FILE_TO_RECEIVE);
      byte[] buffer = new byte[4096];
      int bytesRead;

      while ((bytesRead = inputStream.read(buffer)) != -1) {
        fileOutputStream.write(buffer, 0, bytesRead);
      }

      System.out.println("File received successfully!");
      fileOutputStream.close();
      inputStream.close();
      socket.close();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}