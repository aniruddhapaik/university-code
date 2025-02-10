import java.util.Random;
import java.util.Scanner;

class Sender { 
  private int windowSize;
  private int base;
  private int nextSeqNum;
  private Random random;

  public Sender(int windowSize) { 
    this.windowSize = windowSize;
    this.base = 0;
    this.nextSeqNum = 0;
    this.random = new Random();
  } 
  
  public void sendFrames(Receiver receiver, int totalFrames) { 
    while (base < totalFrames) { 
      // Send frames within the window 
      while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames) { 
        System.out.println("Sender: Sending frame " + nextSeqNum);

        boolean isLost = random.nextInt(5) == 0; // 20% chance of loss
        if (isLost) { 
          System.out.println("Sender: Frame " + nextSeqNum + " lost!");
        } else { 
          receiver.receiveFrame(nextSeqNum);
        } 
        nextSeqNum++;
      } 

      // Wait for acknowledgment 
      int ack = receiver.getAcknowledgment();

      if (ack >= base) { 
        System.out.println("Sender: ACK received for frame " + ack);
        base = ack + 1; // Slide the window
      } else { 
        System.out.println("Sender: ACK not received, resending frames from " + base);
        nextSeqNum = base; // Reset nextSeqNum to base for retransmission
      } 
      
      try { 
        Thread.sleep(1000); // Simulate delay
      } catch (InterruptedException e) {
        e.printStackTrace();
      } 
    } 
    System.out.println("Sender: All frames sent successfully!");
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
      System.out.println("Receiver: Frame " + frameNumber + " corrupted! Discarding...");
      return;
    } 

    if (frameNumber == expectedFrame) { 
      System.out.println("Receiver: Frame " + frameNumber + " received successfully!");
      expectedFrame++; // Expect the next frame
    } else { 
      System.out.println("Receiver: Out-of-order frame received! Discarding...");
    } 
  } 

  public int getAcknowledgment() {
    boolean ackLost = random.nextInt(5) == 2; // 20% chance of ACK loss
    
    if (ackLost) { 
      System.out.println("Receiver: ACK lost!");
      return expectedFrame - 1; // Simulate ACK loss
    } 
    
    System.out.println("Receiver: Sending ACK for frame " + (expectedFrame - 1));
    return expectedFrame - 1;
  } 
} 

public class GoBackNProtocol { 
  public static void main(String[] args) { 
    Scanner scanner = new Scanner(System.in);
    
    System.out.print("Enter the window size: ");
    int windowSize = scanner.nextInt();

    System.out.print("Enter the total number of frames: ");
    int totalFrames = scanner.nextInt();
    
    Sender sender = new Sender(windowSize);
    Receiver receiver = new Receiver();
    
    sender.sendFrames(receiver, totalFrames);
    scanner.close();
  } 
} 