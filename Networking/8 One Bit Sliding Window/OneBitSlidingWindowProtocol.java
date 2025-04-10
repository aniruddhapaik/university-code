import java.util.Random;

class Sender {
  private int sequenceNumber = 0; // One-bit sequence number (0 or 1)
  private Random random = new Random();
  int transmissionCount = 0;

  public void sendFrame(Receiver receiver, int totalFrames) {
    int framesSent = 0;
    while (framesSent < totalFrames) {
      System.out.println("TRANSMISSION " + transmissionCount);
      System.out.println("[i] Sender: Sending frame with sequence number " + sequenceNumber);
      boolean frameCorrupted = random.nextInt(5) == 0; // 1 in 5 chance of corruption
      boolean frameLost = random.nextInt(5) == 1; // 1 in 5 chance of loss
      if (frameLost) {
        System.out.println("[x] Sender: Frame lost in transmission...");
      } else {
        receiver.receiveFrame(sequenceNumber, frameCorrupted);
      }

      if (frameCorrupted || frameLost) {
        sequenceNumber = 1 - sequenceNumber; // Toggle sequence number (0 → 1 or 1 → 0)
      }

      boolean ackReceived = receiver.getAcknowledgment(sequenceNumber);
      if (ackReceived) {
        System.out.println("[i] Sender: ACK received for sequence number " + sequenceNumber + "\n");
        sequenceNumber = 1 - sequenceNumber; // Toggle sequence number (0 → 1 or 1 → 0)
        if (!frameCorrupted && !frameLost) {
          framesSent++; // Increase frame count
        }
      } else {
        System.out.println("[x] Sender: ACK not received. Resending frame...\n");
        if (frameCorrupted || frameLost) {
          sequenceNumber = 1 - sequenceNumber; // Toggle sequence number (0 → 1 or 1 → 0)
        }
      }
      transmissionCount++;

      try {
        Thread.sleep(1000); // Simulating delay
      } catch (InterruptedException e) {
        e.printStackTrace();
      }
    }
    System.out.println("Sender: Transmission completed. All " + totalFrames + " frames sent successfully.");
  }
}

class Receiver {
  private int expectedSequenceNumber = 0;
  private Random random = new Random();

  public void receiveFrame(int sequenceNumber, boolean frameCorrupted) {
    if (frameCorrupted) {
      System.out.println("[x] Receiver: Frame received is corrupted. Discarding...");
      return;
    }
    if (sequenceNumber == expectedSequenceNumber) {
      System.out.println("[i] Receiver: Frame received successfully with sequence number " + sequenceNumber);
      expectedSequenceNumber = 1 - expectedSequenceNumber; // Toggle sequence number
    } else {
      System.out.println("[D] Receiver: Duplicate frame received. Discarding...");
    }
  }

  public boolean getAcknowledgment(int sequenceNumber) {
    boolean ackLost = random.nextInt(5) == 2; // 1 in 5 chance of ACK loss
    if (ackLost) {
      System.out.println("[x] Receiver: ACK lost...");
      return false;
    }
    System.out.println("[i] Receiver: Sending ACK for sequence number " + sequenceNumber);
    return true;
  }
}

public class OneBitSlidingWindowProtocol {
  public static void main(String[] args) {
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    int totalFrames = 5; // Set the total number of frames to send
    sender.sendFrame(receiver, totalFrames);
  }
}