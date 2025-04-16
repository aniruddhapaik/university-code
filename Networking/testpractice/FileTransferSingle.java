import java.io.*;
import java.net.*;
import java.util.Scanner;

class FileTransferSingle {
  static private final int PORT = 5000;
  static private String FILE_READ = "D:\\Games\\sample.txt";
  static private String FILE_WRITE = "D:\\Games\\samplereceived.txt";

  public static void Sender() {
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("waiting for client to connect...");
      Socket socket = serverSocket.accept();
      System.out.println("Client connected");

      File file = new File(FILE_READ);
      FileInputStream fileInputStream = new FileInputStream(file);
      OutputStream outputStream = socket.getOutputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;

      while ((bytesRead = fileInputStream.read(buffer)) != -1) {
        outputStream.write(buffer, 0, bytesRead);
      } 
      System.out.println("File sent successfully");
      fileInputStream.close();
      socket.close();
      serverSocket.close();
      outputStream.close();
    } catch (IOException e) { e.printStackTrace(); }
  }

  public static void Receiver() {
    try (Socket socket = new Socket("localhost", PORT)) {
      System.out.println("Connected to server");

      FileOutputStream fileOutputStream = new FileOutputStream(FILE_WRITE);
      InputStream inputStream = socket.getInputStream();
      byte[] buffer = new byte[4096];
      int bytesRead = 0;
      while ((bytesRead = inputStream.read(buffer)) != -1) {
        fileOutputStream.write(buffer, 0, bytesRead);
      }
      System.out.println("Successfully received file");
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