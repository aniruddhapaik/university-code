import java.util.Random;

class Sender {
  private int seqNum = 0;
  private Random random = new Random();
  private int transmissionCount = 0;

  public void sendFrame(Receiver receiver, int totalFrames) {
    int framesSent = 0;
    while (framesSent < totalFrames) {
      System.out.println("\nTRANSMISSION: " + transmissionCount);
      System.out.println("[i] Sender: sending frame " + seqNum);
      boolean frameCorrupted = random.nextInt(5) == 0;
      boolean frameLost = random.nextInt(5) == 1;

      if (frameLost) { System.out.println("[x] Sender: frame lost in transmission"); } 
      else { receiver.receiveFrame(seqNum, frameCorrupted); }
      
      if (frameLost || frameCorrupted) { seqNum = 1 - seqNum; }

      boolean ackReceived = receiver.getAcknowledgement(seqNum);
      if (ackReceived) {
        System.out.println("[i] Sender: ACK received for frame sequence number " + seqNum);
        if (!frameLost && !frameCorrupted) { framesSent++; }
      } else { System.out.println("[x] Sender: ACK not received. resending frame..."); }

      if (frameLost || frameCorrupted || ackReceived) { seqNum = 1 - seqNum; }
      transmissionCount++;
      System.out.println("Progress: ( " + framesSent + "/" + totalFrames + " )");

      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("All " + framesSent + "/" + totalFrames + " frames sent successfully");
  }
}

class Receiver {
  private int expectedSeqNum = 0;
  private Random random = new Random();

  public void receiveFrame(int seqNum, boolean frameCorrupted) {
    if (frameCorrupted) { System.out.println("[x] Receiver: frame is corrupted. discarding..."); }
    else {
      if (seqNum == expectedSeqNum) {
        System.out.println("[i] Receiver: received frame with sequence number " + expectedSeqNum);
        expectedSeqNum = 1 - expectedSeqNum;
      } else { System.out.println("[D] Receiver: received duplicate frame. discarding..."); }
    }
  }

  public boolean getAcknowledgement(int seqNum) {
    boolean ackLost = random.nextInt(5) == 2;
    if (ackLost) {
      System.out.println("[x] Receiver: ACK lost...");
      return false;
    } 
    System.out.println("[i] Receiver: Sending ACK for frame sequence number " + seqNum);
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