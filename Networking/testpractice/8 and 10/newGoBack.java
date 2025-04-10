import java.util.Random;

class Sender {
  private int windowSize;
  private int base = 0;
  private int seqNum = 0;
  private Random random = new Random();

  Sender(int windowSize) { this.windowSize = windowSize; }

  public void sendFrame(Receiver receiver, int totalFrames) {
    while (base < totalFrames) {
      while (seqNum < Math.min(base + windowSize, totalFrames)) {
        System.out.println("S: sending frame with sequence number " + seqNum);
        boolean frameLost = random.nextInt(5) == 0;
        if (frameLost) { System.out.println("S: frame " + seqNum + " lost in transmission..."); }
        else { receiver.receiveFrame(seqNum); }
        seqNum++;
      } System.out.println("");

      int ack = receiver.getAck();
      if (ack < 0) {
        System.out.println("S: ACK not received. resending frames from " + base); 
        seqNum = base;
      } else {
        System.out.println("S: received ack for sequence number " + (ack-1));
        base = seqNum = ack;
      } System.out.println("");

      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("Sent all frames successfully");
  }
}

class Receiver {
  private int expectedSeqNum = 0;
  private Random random = new Random();

  public void receiveFrame(int seqNum) {
    boolean frameCorrupted = random.nextInt(5) == 1;
    if (frameCorrupted) { System.out.println("R: frame " + seqNum + " corrupted. discarding..."); }
    else {
      if (expectedSeqNum == seqNum) {
        System.out.println("R: received frame " + seqNum + " successfully.");
        expectedSeqNum++;
      } else { System.out.println("R: received out of order frame. discarding..."); }
    }
  }

  public int getAck() {
    boolean ackLost = random.nextInt(5) == 2;
    if (ackLost) {
      System.out.println("R: ACK lost...");
      return -1;
    } else {
      System.out.println("Sending ACK for " + (expectedSeqNum-1));
      return expectedSeqNum;
    }
  }
}

public class GoBackNProtocol {
  public static void main(String[] args) {
    int totalFrames = 8;
    int windowSize = 3;
    Sender sender = new Sender(windowSize);
    Receiver receiver = new Receiver();
    sender.sendFrame(receiver, totalFrames);
  }
}