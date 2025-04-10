import java.util.Random;

class Sender {
  private int sequenceNumber = 0;
  private Random random = new Random();
  private int transmissionCount = 0;

  public void sendFrame(Receiver receiver, int totalFrames) {
    int framesSent = 0;
    while (framesSent < totalFrames) {
      System.out.println("\nTRANSMISSION " + transmissionCount);
      System.out.println("S: sending frame with sequence number " + sequenceNumber);
      boolean frameLost = random.nextInt(5) == 0;
      boolean frameCorrupted = random.nextInt(5) == 1;

      if (frameLost) { System.out.println("S: frame lost in transmission..."); }
      else { receiver.receiveFrame(sequenceNumber, frameCorrupted); }

      if (frameLost || frameCorrupted) { sequenceNumber = 1 - sequenceNumber; }

      boolean ackReceived = receiver.getAcknowledgement(sequenceNumber);
      if (ackReceived) { 
        System.out.println("S: ACK received for sequence number " + sequenceNumber);
        if (!frameLost && !frameCorrupted) { framesSent++; }
      } else { System.out.println("S: ACK not received. resending frame..."); }

      if (frameLost || frameCorrupted || ackReceived) { sequenceNumber = 1 - sequenceNumber; }
      transmissionCount++;
      try { Thread.sleep(1000); }
      catch (InterruptedException e) { e.printStackTrace(); }
    }
    System.out.println("Sent all frames successfully.");
  }
}

class Receiver {
  private int expectedSequenceNumber = 0;
  private Random random = new Random();

  public void receiveFrame(int sequenceNumber, boolean frameCorrupted) {
    if (frameCorrupted) {
      System.out.println("R: Frame is corrupted. discarding...");
    } else {
      if (expectedSequenceNumber == sequenceNumber) { 
        System.out.println("R: received frame with sequence number " + expectedSequenceNumber); 
        expectedSequenceNumber = 1 - expectedSequenceNumber;
      } else {
        System.out.println("R: received duplicate frame. discarding...");
      }
    }
  }

  public boolean getAcknowledgement(int sequenceNumber) {
    boolean ackLost = random.nextInt(5) == 2;
    if (ackLost) { 
      System.out.println("R: ACK lost..."); 
      return false;
    }
    System.out.println("R: ACK sent for sequence number " + sequenceNumber);
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