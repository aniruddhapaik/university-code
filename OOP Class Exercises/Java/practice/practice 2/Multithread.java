class MyThread extends Thread {
  private String threadname;
  private int sleeptime;

  MyThread(String name, int timems) {
    this.threadname = name;
    this.sleeptime = timems;
  }

  @Override
  public void run() {
    try {
      for (int i = 1; i <= 5; i++) {
        System.out.println(i + ". Thread " + this.threadname + " sleeping for " + this.sleeptime);
        Thread.sleep(this.sleeptime);
      }
      System.out.println("Thread " + this.threadname + " finished");
    } catch (InterruptedException e) {}
  }
}

public class Multithread {
  public static void main(String[] args) {
    MyThread thread1 = new MyThread("ONE", 200);
    MyThread thread2 = new MyThread("TWO", 500);

    thread1.start();
    thread2.start();
  }
}
