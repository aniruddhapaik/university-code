import java.util.Random;

class Frame {
  int seqNum;
  boolean received = false;
  boolean retransmit = false;
  Frame (int seqNum) { this.seqNum = seqNum; }
}

class Sender {
  private int base = 0;
  private int windowSize = 3;
  private Frame[] frames;
  private Random random = new Random();

  public void sendFrame(Receiver receiver, int totalFrames) {
    this.frames = new Frame[totalFrames];
    for (int j = 0; j < totalFrames; j++) { this.frames[j] = new Frame(j); }

    while(base < totalFrames) {
      System.out.println();
      for (int i = base; i < Math.min(base + windowSize, totalFrames); i++) {
        if (this.frames[i].retransmit) { System.out.println("S: going to retransmit frame " + this.frames[i].seqNum); }
        else if (this.frames[i].received) { continue; }
        System.out.println("S: sending frame " + i);
        boolean frameLost = random.nextInt(5) == 0;
        if (frameLost) { 
          System.out.println("S: frame lost..."); 
          this.frames[i].retransmit = true;  
        }
        else { receiver.receiveFrame(this.frames[i]); }
      }

      while(base < totalFrames && this.frames[base].received) { base++; }
      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("All frames sent successfully.");
  }
}

class Receiver {
  private Random random = new Random();

  public void receiveFrame(Frame frame) {
    boolean frameCorrupted = random.nextInt(5) == 1;
    if (frameCorrupted) {
      System.out.println("R: frame corrupted. discarding...");
      frame.retransmit = true;
    } else {
      System.out.println("R: frame received successfully. send ACK");
      frame.received = true;
      frame.retransmit = false;
    }
  }
}

public class SelectiveRepeatProtocol {
  public static void main(String[] args) {
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    sender.sendFrame(receiver, 8);
  }
}