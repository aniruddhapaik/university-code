import java.io.*;
import java.net.*;
import java.util.Scanner;

public class FileTransferSingle {
  static private final int PORT = 5000;
  static private final String FILE_READ = "D:\\Games\\sample.txt";
  static private final String FILE_WRITE = "D:\\Games\\received.txt";

  public static void Sender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("S: waiting for client to connect...");
      Socket socket = serverSocket.accept();
      System.out.println("S: client connected.");

      File file = new File(FILE_READ);
      FileInputStream fileInputStream = new FileInputStream(file);
      OutputStream outputStream = socket.getOutputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while((bytesRead = fileInputStream.read(buffer)) != -1) {
        outputStream.write(buffer, 0, bytesRead);
      }
      System.out.println("S: Sent file succesffully.");
      fileInputStream.close();
      outputStream.close();
      serverSocket.close();
      socket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void Receiver() {
    try (Socket socket = new Socket("localhost", PORT)) {
      System.out.println("R: Connected to server.");

      FileOutputStream fileOutputStream = new FileOutputStream(FILE_WRITE);
      InputStream inputStream = socket.getInputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while((bytesRead = inputStream.read(buffer)) != -1) {
        fileOutputStream.write(buffer, 0, bytesRead);
      }
      System.out.println("R: file received successfully.");
      inputStream.close();
      fileOutputStream.close();
      socket.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void main(String[] args) {
    System.out.println("choose mode: \n1. Send\n2. Receive\nchoice: ");
    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();
    if (choice == 1) { Sender(); }
    else if (choice == 2) { Receiver(); }
  }
}