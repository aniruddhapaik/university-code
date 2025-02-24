import java.util.Random;
import java.util.Scanner;

class Frame { 
  int seqNum;
  boolean received;

  Frame(int seqNum) { 
    this.seqNum = seqNum;
    this.received = false;
  } 
} 

class Sender { 
  private int windowSize;
  private int totalFrames;
  private Frame[] frames;
  private Receiver receiver;
  private Random random = new Random();
  Sender(int totalFrames, int windowSize, Receiver receiver) { 
  this.totalFrames = totalFrames;
  this.windowSize = windowSize;
  this.receiver = receiver;
  this.frames = new Frame[totalFrames];
  
  // Initialize frames with sequence numbers 
  for (int i = 0; i < totalFrames; i++) {
    frames[i] = new Frame(i);
  } 
} 

  public void sendFrames() { 
    int base = 0;
    
    while (base < totalFrames) { 
      System.out.println("\n--- Sending Frames in Window ---");
      
      for (int i = base; i < Math.min(base + windowSize, totalFrames); i++) {
        // Simulating a 20% probability of frame loss 
        boolean isLost = random.nextInt(5) == 0;
        if (isLost) { 
          System.out.println("Sender: Frame " + i + " lost in transmission.");
        } else { 
          receiver.receiveFrame(frames[i]);
        } 
      } 

      // Wait for acknowledgments and retransmit lost frames 
      for (int i = base; i < Math.min(base + windowSize, totalFrames); i++) {
        if (!frames[i].received) {
          System.out.println("Sender: Retransmitting frame " + i);
          receiver.receiveFrame(frames[i]); // Retransmit the lost frame
        } 
      } 

      // Move window forward after all frames in the window are acknowledged 
      while (base < totalFrames && frames[base].received) { 
        base++;
      } 

      try { 
        Thread.sleep(1000); // Simulate delay
      } catch (InterruptedException e) {
        e.printStackTrace();
      } 
    } 
    System.out.println("Sender: All frames successfully transmitted!");
  } 
} 

class Receiver { 
  private Random random = new Random();
  public void receiveFrame(Frame frame) { 
  
  // Simulating 20% probability of frame corruption 
  boolean isCorrupt = random.nextInt(5) == 1;
  if (isCorrupt) { 
    System.out.println("Receiver: Frame " + frame.seqNum + " received corrupted. Requesting retransmission.");
    return;
  } 

  // Acknowledge the received frame 
  frame.received = true;
  System.out.println("Receiver: Frame " + frame.seqNum + " received successfully. Sending ACK.");
  } 
} 

public class SelectiveRepeatProtocol {
  public static void main(String[] args) { 
    Scanner scanner = new Scanner(System.in);

    System.out.print("Enter total number of frames to send: ");
    int totalFrames = scanner.nextInt();

    System.out.print("Enter window size: ");
    int windowSize = scanner.nextInt();

    Receiver receiver = new Receiver();
    Sender sender = new Sender(totalFrames, windowSize, receiver);
    sender.sendFrames();

    scanner.close();
  } 
} 