import java.io.*;
import java.net.*;

public class Sender { 
  public static void main(String[] args) { 
    try { 
      // Create a socket for communication 
      DatagramSocket socket = new DatagramSocket();
      InetAddress receiverAddress = InetAddress.getByName("localhost");
      int port = 12345;
      
      // Simulated data to send 
      String[] messages = { 
      "Frame 1: Hello Receiver!", 
      "Frame 2: This is a simplex protocol.", 
      "Frame 3: Data flows one way only.", 
      "Frame 4: End of transmission." 
      };
      
      // Send frames (messages) one by one 
      for (String message : messages) { 
        byte[] data = message.getBytes();
        DatagramPacket packet = new DatagramPacket(data, data.length, receiverAddress, port);
        socket.send(packet);
        System.out.println("Sent: " + message);
        Thread.sleep(1000); // Simulate a delay between frames
      } 
      
      // Send an "END" signal to indicate the end of transmission 
      byte[] endSignal = "END".getBytes();
      DatagramPacket endPacket = new DatagramPacket(endSignal, endSignal.length, receiverAddress, port);
      socket.send(endPacket);
      System.out.println("Transmission complete. Sent END signal.");
      
      // Close the socket 
      socket.close();
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
} 
