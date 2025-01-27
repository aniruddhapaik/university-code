import java.util.Random;

class Sender { 
  private int frameNumber = 0;
  public void sendFrame(Receiver receiver) { 
    System.out.println("[Sender] Sending Frame " + frameNumber);
    receiver.receiveFrame(frameNumber, this);
  } 

  public void receiveAcknowledgment(int ack) { 
    if (ack == frameNumber) { 
      System.out.println("[Sender] Acknowledgment received for Frame " + ack);
      frameNumber++;
    } else { 
      System.out.println("[Sender] Incorrect acknowledgment received. Resending Frame " + frameNumber);
    } 
  } 
} 
  
class Receiver { 
  private int expectedFrame = 0;
  public void receiveFrame(int frame, Sender sender) { 
    if (frame == expectedFrame) { 
      System.out.println("[Receiver] Frame " + frame + " received successfully.");
      sendAcknowledgment(frame, sender);
      expectedFrame++;
    } else { 
      System.out.println("[Receiver] Unexpected frame received. Expected: " + expectedFrame + ", Received: " + frame);
    } 
  } 

  public void sendAcknowledgment(int frame, Sender sender) { 
    System.out.println("[Receiver] Sending acknowledgment for Frame " + frame);
    sender.receiveAcknowledgment(frame);
  } 
}
 
public class StopAndWaitProtocol { 
  public static void main(String[] args) { 
    Sender sender = new Sender();
    Receiver receiver = new Receiver();
    Random random = new Random();
    int totalFrames = 5;
    System.out.println("Starting Stop-and-Wait Protocol Simulation...");
    
    for (int i = 1; i <= totalFrames; i++) {
      System.out.println("\n--- Transmission " + (i) + " ---");

      sender.sendFrame(receiver);
      // Simulate a delay to make the output more readable 
      try { 
        Thread.sleep(random.nextInt(500) + 500);
      } catch (InterruptedException e) { 
        e.printStackTrace();
      } 
    } 
    System.out.println("\nSimulation Complete!");
  } 
}
