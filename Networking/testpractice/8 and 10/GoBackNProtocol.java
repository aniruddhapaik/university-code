import java.util.Random;

class Sender {
  private int seqNum = 0;
  private int windowSize = 3;
  private int base = 0;
  private Random random = new Random();

  public void sendFrame(Receiver receiver, int totalFrames) {
    while (base < totalFrames) {
      while (seqNum < Math.min(base + windowSize, totalFrames)) {
        System.out.println("S: sending frame " + seqNum);
        boolean frameLost = random.nextInt(5) == 0;
        if (frameLost) { System.out.println("S: frame lost..."); }
        else { receiver.receiveFrame(seqNum); }
        seqNum++;
      } System.out.println("");
      int ack = receiver.getAck();
      if (ack < 0) { 
        System.out.println("S: ACK not received. retransmitting from frame " + base); 
        seqNum = base;
      } else {
        System.out.println("S: ACK received for frame " + (ack-1));
        base = seqNum = ack;
      } System.out.println("");

      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("All frames sent successfully.");
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
        System.out.println("R: frame " + expectedSeqNum + " received successfully.");
        expectedSeqNum++;
      } else { System.out.println("R: out of order frame received. discarding..."); }
    }
  }

  public int getAck() {
    boolean ackLost = random.nextInt(5) == 2;
    if (ackLost) {
      System.out.println("R: ACK lost...");
      return -1;
    }
    System.out.println("R: ACK sent for frame " + (expectedSeqNum-1));
    return expectedSeqNum;
  }
}

public class GoBackNProtocol {
  public static void main(String[] args) {
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    sender.sendFrame(receiver, 8);
  }
}