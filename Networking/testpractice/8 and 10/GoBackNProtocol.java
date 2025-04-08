import java.util.Random;
import java.util.Scanner;

class Sender { 
  private int windowSize;
  private int base;
  private int seqNum;
  private Random random;

  public Sender(int windowSize) { 
    this.windowSize = windowSize;
    this.base = 0;
    this.seqNum = 0;
    this.random = new Random();
  } 
  
  public void sendFrames(Receiver receiver, int totalFrames) { 
    while (base < totalFrames) { 
      while (seqNum < Math.min(base + windowSize, totalFrames)) { 
        System.out.println("[i] Sender: Sending frame " + seqNum);

        boolean isLost = random.nextInt(5) == 0; // 20% chance of loss
        if (isLost) { 
          System.out.println("[x] Sender: Frame " + seqNum + " lost!");
        } else { 
          receiver.receiveFrame(seqNum);
        } 
        seqNum++;
      } 
      System.out.println("");

      int ack = receiver.getAcknowledgment();

      if (ack < 0) { 
        System.out.println("[i] Sender: ACK not received, resending frames from " + base);
        seqNum = base; // Reset seqNum to base for retransmission
      } else { 
        if (ack > 0) { System.out.println("[i] Sender: ACK received for frame " + (ack - 1)); }
        else { System.out.println("[i] Sender: Retransmitting from frame 0"); }
        seqNum = base = ack;
      }
      System.out.println("");
      
      try { Thread.sleep(1000); } 
      catch (InterruptedException e) { e.printStackTrace(); } 
    } 
    System.out.println("[i] Sender: All frames sent successfully!");
  } 
} 

class Receiver { 
  private int expectedFrame;
  private Random random;
  
  public Receiver() { 
    this.expectedFrame = 0;
    this.random = new Random();
  } 

  public void receiveFrame(int frameNumber) { 
    boolean isCorrupted = random.nextInt(5) == 1; // 20% chance of corruption
    
    if (isCorrupted) { 
      System.out.println("[x] Receiver: Frame " + frameNumber + " corrupted! Discarding...");
      return;
    } 

    if (frameNumber == expectedFrame) { 
      System.out.println("[i] Receiver: Frame " + frameNumber + " received successfully!");
      expectedFrame++; // Expect the next frame
    } else { 
      System.out.println("[x] Receiver: Out-of-order frame received! Discarding...");
    } 
  } 

  public int getAcknowledgment() {
    boolean ackLost = random.nextInt(5) == 2; // 20% chance of ACK loss
    
    if (ackLost) { 
      System.out.println("[x] Receiver: ACK lost!");
      return -1;
    } 
    
    if (expectedFrame - 1 < 0) { 
      System.out.println("[i] Receiver: Requesting retransmission from frame 0");
    } else { System.out.println("[i] Receiver: Sending ACK for frame " + (expectedFrame - 1)); }
    return expectedFrame;
  } 
} 

public class GoBackNProtocol { 
  public static void main(String[] args) { 
    Scanner scanner = new Scanner(System.in);
    
    System.out.print("Enter the total number of frames: ");
    int totalFrames = scanner.nextInt();

    System.out.print("Enter the window size: ");
    int windowSize = scanner.nextInt();
    
    Sender sender = new Sender(windowSize);
    Receiver receiver = new Receiver();
    
    sender.sendFrames(receiver, totalFrames);
    scanner.close();
  } 
} 