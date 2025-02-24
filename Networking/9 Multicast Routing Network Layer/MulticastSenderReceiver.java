import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;

public class MulticastSenderReceiver { 
  private static final String MULTICAST_GROUP = "230.0.0.1"; // Multicast IP 
  private static final int PORT = 5000; // Multicast Port 

  public static void main(String[] args) { 
    // Start the sender in one thread 
    new Thread(MulticastSenderReceiver::startSender).start();

    // Start multiple receivers dynamically 
    for (int i = 1; i <= 3; i++) { // Create 3 receivers 
      final int receiverID = i;
      new Thread(() -> startReceiver(receiverID)).start();
    } 
  } 

  // Sender thread 
  public static void startSender() { 
    try { 
      DatagramSocket socket = new DatagramSocket();
      InetAddress group = InetAddress.getByName(MULTICAST_GROUP);
      int messageCount = 1;

      while (messageCount <= 5) { // Send 5 messages 
        String message = "Hello Receivers! Message " + messageCount;
        byte[] buffer = message.getBytes();
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length, group, PORT);
        socket.send(packet);
        System.out.println("[Sender] Sent: " + message);
        Thread.sleep(2000); // Delay between messages 
        messageCount++;
      } 
      socket.close();
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 

  // Receiver thread 
  public static void startReceiver(int receiverID) { 
    try { 
      MulticastSocket socket = new MulticastSocket(PORT);
      InetAddress group = InetAddress.getByName(MULTICAST_GROUP);
      socket.joinGroup(group);

      while (true) { 
        byte[] buffer = new byte[256];
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        socket.receive(packet);
        
        String receivedMessage = new String(packet.getData(), 0, packet.getLength());
        System.out.println("[Receiver " + receiverID + "] Received: " + receivedMessage);
        
        if (receivedMessage.contains("Message 5")) { 
        System.out.println("[Receiver " + receiverID + "] Last message received. Exiting...");
        break;
        } 
      } 
      socket.leaveGroup(group);
      socket.close();
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
} 