import java.util.Random;

class Sender {
  private int seqNum = 0;
  private int transmissionCount = 0;
  private Random random = new Random();
  public void sendFrame(Receiver receiver, int totalFrames) {
    int framesSent = 0;
    while (framesSent < totalFrames) {
      System.out.println("TRANSMISSION " + transmissionCount);
      System.out.println("S: sending frame " + seqNum);
      boolean frameLost = random.nextInt(5) == 0;
      boolean frameCorrupted = random.nextInt(5) == 1;

      if (frameLost) { System.out.println("S: frame lost..."); }
      else { receiver.receiveFrame(seqNum, frameCorrupted); }

      if (frameLost || frameCorrupted) { seqNum = 1 - seqNum; }

      boolean ackReceived = receiver.getAck(seqNum);
      if (ackReceived) {
        System.out.println("S: ACK received for frame " + seqNum);
        if (!frameLost && !frameCorrupted) { framesSent++; }
      } else { System.out.println("S: ACK not received. resending frame " + seqNum); }
      if (frameLost || frameCorrupted || ackReceived) { seqNum = 1 - seqNum; }
      transmissionCount++;
      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("All frames sent successfully.");
  }
}

class Receiver {
  private int expectedSeqNum = 0;
  private Random random = new Random();

  public void receiveFrame(int seqNum, boolean frameCorrupted) {
    if (frameCorrupted) { System.out.println("R: frame corrupted. discarding frame..."); }
    else {
      if (expectedSeqNum == seqNum) {
        System.out.println("R: frame " + expectedSeqNum + " received successfully.");
        expectedSeqNum = 1 - expectedSeqNum;
      } else { System.out.println("R: received duplicate frame. discarding..."); }
    }
  }

  boolean getAck(int seqNum) {
    boolean ackLost = random.nextInt(5) == 2;
    if (ackLost) {
      System.out.println("R: ACK lost...");
      return false;
    }
    System.out.println("R: sending ACK for frame " + seqNum);
    return true;
  }
}

public class OneBitSlidingWindowProtocol {
  public static void main(String[] args) {
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    sender.sendFrame(receiver, 5);
  }
}