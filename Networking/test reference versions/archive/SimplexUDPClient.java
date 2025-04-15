import java.net.DatagramSocket;
import java.net.DatagramPacket;
import java.net.InetAddress;

public class SimplexUDPClient {
  public static void main(String[] args) {
    final String HOST = "localhost";
    final int PORT = 12345;
    try(DatagramSocket socket = new DatagramSocket()) {
      String message = "hello server";
      byte[] buffer = message.getBytes();
      InetAddress serverAddress = InetAddress.getByName(HOST);
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length, serverAddress, PORT);
      socket.send(packet);
      System.out.println("Message sent to server");
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}