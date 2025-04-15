import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.util.Scanner;

public class SimplexConnectioLess {
  static final int PORT = 12345;
  static final String HOST = "localhost";
  public static void main(String[] args) {
    System.out.println("Chose mode:\n1. Receive\n2. Send\nEnter choice: ");
    Scanner scanner = new Scanner(System.in);
    int choice = scanner.nextInt();
    if (choice == 1) { Receiver(); }
    else if (choice == 2) { Sender(); }
    scanner.close();
  }

  public static void Receiver() {
    try(DatagramSocket socket = new DatagramSocket(PORT)) {
      System.out.println("Waiting for sender to send...");
      byte[] buffer = new byte[1024];
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
      socket.receive(packet);
      String message = new String(packet.getData(), 0, packet.getLength());
      System.out.println("Message from sender: " + message);
      socket.close();
    } catch (Exception e) { e.printStackTrace(); }
  }

  public static void Sender() {
    try (DatagramSocket socket = new DatagramSocket()) {
      System.out.println("Sending message to receiver.");
      InetAddress receiverAddress = InetAddress.getByName(HOST);
      String message = "This is a message for the receiver.";
      byte[] buffer = message.getBytes();
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length, receiverAddress, PORT);
      socket.send(packet);
      System.out.println("Message sent to receiver");
      socket.close();
    } catch (Exception e) { e.printStackTrace(); }
  }
}