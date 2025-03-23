import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
public class SimplexUDPServer { 
  public static void main(String[] args) { 
    final int PORT = 12345;
    try (DatagramSocket socket = new DatagramSocket()) { 
      String message = "Hello, this is simplex communication using UDP!";
      // Convert the message to bytes 
      byte[] buffer = message.getBytes();
      // Specify the recipient (localhost and the specified port) 
      InetAddress clientAddress = InetAddress.getByName("localhost");
      // Create a DatagramPacket to send the data 
      DatagramPacket packet = new DatagramPacket(buffer, buffer.length, clientAddress, PORT);
      // Send the packet 
      socket.send(packet);
      System.out.println("Message sent to the client.");
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
} 