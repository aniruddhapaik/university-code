import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class SimplexUDPServer {
  public static void main(String[] args) {
    final int PORT = 12345;
    try(DatagramSocket socket = new DatagramSocket(PORT)) {
      System.out.println("Waiting for message from client...");
      byte[] buffer = new byte[1024];
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
      socket.receive(packet);
      String message = new String(packet.getData(), 0, packet.getLength());
      System.out.println("Client: " + message);
    } catch(Exception e) {
      e.printStackTrace();
    }
  }
}