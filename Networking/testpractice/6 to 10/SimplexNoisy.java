import java.util.Random;

class Sender { 
  private static final int MAX_FRAME = 5; // Maximum number of frames
  private int frameNumber = 0;
  private Random random = new Random();

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

class Receiver {
  private static final int MAX_FRAME = 5;
  public void receiveFrame(int frameNumber, boolean isCorrupted) { 
    if (!isCorrupted) { 
      System.out.println("[Receiver] Frame " + frameNumber + " received successfully.");
      sendAcknowledgment(frameNumber);
    } else { 
      System.out.println("[Receiver][x] Frame " + frameNumber + " is corrupted, sending NACK.");
      sendNegativeAcknowledgment(frameNumber);
    } 
  }

  private void sendAcknowledgment(int frameNumber) { 
    System.out.println("[Receiver][A] Sending ACK for Frame " + frameNumber);
  } 

  private void sendNegativeAcknowledgment(int frameNumber) { 
    System.out.println("[Receiver][N] Sending NACK for Frame " + frameNumber);
  } 
} 

public class SimplexNoisy { 
  public static void main(String[] args) { 
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    sender.sendFrame(receiver);
  } 
} 
