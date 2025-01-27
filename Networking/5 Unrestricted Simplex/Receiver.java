import java.io.*;
import java.net.*;

public class Receiver { 
  public static void main(String[] args) { 
    try { 
      // Create a socket to receive data 
      DatagramSocket socket = new DatagramSocket(12345);
      System.out.println("Receiver is waiting for frames...");
      byte[] buffer = new byte[1024];
      boolean transmissionEnded = false;
      
      while (!transmissionEnded) { 
        // Receive a frame (message) 
        DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
        socket.receive(packet);
        
        // Convert the received bytes to a string 
        String message = new String(packet.getData(), 0, packet.getLength());
        
        // Check for the "END" signal 
        if (message.equals("END")) { 
          transmissionEnded = true;
          System.out.println("Transmission complete. Received END signal.");
        } else { 
          System.out.println("Received: " + message);
        } 
      } 

      // Close the socket 
      socket.close();
    } catch (Exception e) { 
      e.printStackTrace();
    } 
  } 
} 
