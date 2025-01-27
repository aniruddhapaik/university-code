import java.net.DatagramPacket;
import java.net.DatagramSocket;
public class SimplexUDPClient { 
  public static void main(String[] args) { 
    final int PORT = 12345;
    try (DatagramSocket socket = new DatagramSocket(PORT)) { 
      System.out.println("Client is waiting for a message...");
      // Buffer to store the incoming message 
      byte[] buffer = new byte[1024];
      // Create a DatagramPacket to receive data 
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
      // Receive the packet 
      socket.receive(packet);
      // Convert the received bytes to a string 
      String message = new String(packet.getData(), 0, packet.getLength());
      System.out.println("Message from server: " + message);
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
}