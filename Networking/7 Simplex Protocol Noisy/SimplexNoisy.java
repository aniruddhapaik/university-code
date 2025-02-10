import java.util.Random;
// Sender class that sends frames 
class Sender { 
  private static final int MAX_FRAME = 2; // Maximum number of frames
  private int frameNumber = 0;
  private Random random = new Random();

  // Method to simulate sending a frame 
  public void sendFrame(Receiver receiver) { 
    while (frameNumber < MAX_FRAME) { 
      System.out.println("[Sender] Sending Frame " + frameNumber);
      boolean isFrameCorrupted = random.nextInt(10) < 2; // 20% chance of noise
      receiver.receiveFrame(frameNumber, isFrameCorrupted);

      if (!isFrameCorrupted) { 
        System.out.println("[Sender] Frame " + frameNumber + " sent successfully!\n---------------------\n");
        frameNumber++;
      } else { 
        System.out.println("[Sender][x] Frame " + frameNumber + " corrupted, retransmitting.\n");
      } 
      
      try { 
        Thread.sleep(1000); // Delay for simulating real-world transmission time 
      } catch (InterruptedException e) { 
        e.printStackTrace();
      } 
    } 
    System.out.println("[Sender] All frames transmitted.");
  } 
} 

// Receiver class that receives frames 
class Receiver {
  private static final int MAX_FRAME = 5;
  // Method to simulate receiving a frame 
  public void receiveFrame(int frameNumber, boolean isCorrupted) { 
    if (!isCorrupted) { 
      System.out.println("[Receiver] Frame " + frameNumber + " received successfully.");
      sendAcknowledgment(frameNumber);
    } else { 
      System.out.println("[Receiver][x] Frame " + frameNumber + " is corrupted, sending NACK.");
      sendNegativeAcknowledgment(frameNumber);
    } 
  }

  // Method to send acknowledgment for a successfully received frame 
  private void sendAcknowledgment(int frameNumber) { 
    System.out.println("[Receiver][A] Sending ACK for Frame " + frameNumber);
  } 

  // Method to send a negative acknowledgment for a corrupted frame 
  private void sendNegativeAcknowledgment(int frameNumber) { 
    System.out.println("[Receiver][N] Sending NACK for Frame " + frameNumber);
  } 
} 

// Main class to run the protocol 
public class SimplexNoisy { 
  public static void main(String[] args) { 
    Sender sender = new Sender();
    Receiver receiver = new Receiver();

    // Start the transmission process 
    sender.sendFrame(receiver);
  } 
} 
