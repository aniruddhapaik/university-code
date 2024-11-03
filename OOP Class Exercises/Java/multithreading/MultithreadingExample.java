// Class extending Thread
class MyThread extends Thread {
  private String threadName;
  private int sleeptime;

  public MyThread(String name, int timems) {
    this.threadName = name;
    this.sleeptime = timems;
  }

  // Override the run method to specify the task for this thread
  @Override
  public void run() {
    for (int i = 1; i <= 5; i++) {
      System.out.println(threadName + " - Count: " + i);
      try {
        Thread.sleep(this.sleeptime); // Pause the thread for some milliseconds
        System.out.println("\n ... " + threadName + " slept for " + 
                            this.sleeptime);
      } catch (InterruptedException e) {
        System.out.println(threadName + " interrupted.");
      }
    }
    System.out.println(threadName + " finished.");
  }
}

// Main class to test multithreading
public class MultithreadingExample {
  public static void main(String[] args) {
    // Create and start two threads
    MyThread thread1 = new MyThread("Thread 1", 500);
    MyThread thread2 = new MyThread("Thread 2", 250);

    thread1.start(); // Starts Thread 1, which calls run() in a new thread
    thread2.start(); // Starts Thread 2, which calls run() in a new thread
  }
}
