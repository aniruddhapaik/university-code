class Vehicle {
  Vehicle() {}

  public void Honk() {
    System.out.println("HONK HONK");
  }
}

class Ferrari extends Vehicle {
  @Override
  public void Honk() {
    System.out.println("Sweet HONK");
  }
}

public class PracticeJava {
  public static void main(String[] args) {
    Vehicle v = new Vehicle();
    Vehicle f = new Ferrari();
    v.Honk();
    f.Honk();
  }
}