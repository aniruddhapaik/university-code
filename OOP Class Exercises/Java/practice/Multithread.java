class MyThread extends Thread {
  String threadname;
  int sleeptime;

  MyThread(String name, int timems) {
    threadname = name;
    sleeptime = timems;
  }

  @Override
  public void run() {
    try {
      for (int i = 1; i <= 5; i++) {
        System.out.println("Count: " + i + " | " + threadname + " will sleep for " + sleeptime + " ms");
        Thread.sleep(sleeptime);
        System.out.println("Count: " + i + " | -->" + threadname + " woke up from sleep | " + sleeptime * i + " ms done");
      }
    } catch (InterruptedException e) {}
  }
}

public class Multithread {
  public static void main(String[] args) {
    System.out.println("Two threads will be started off with different sleep-times");
    System.out.println("---------------------");

    MyThread thread1 = new MyThread("ONE", 200);
    MyThread thread2 = new MyThread("TWO", 500);

    thread1.start();
    thread2.start();
  }
}