class Animal {
  void makeNoise() {
    System.out.println("Generic animal sound..");
  }
}

class Lion extends Animal {
  @Override
  void makeNoise() {
    System.out.println("Rooaarr..");
  }
}

class Cow extends Animal {
  @Override
  void makeNoise() {
    System.out.println("Moooh..");
  }
}

public class PracticeClass {
  public static void main(String[] args) {
    Animal animal = new Animal();
    animal.makeNoise();

    animal = new Lion();
    animal.makeNoise();

    animal = new Cow();
    animal.makeNoise();
  }
}
