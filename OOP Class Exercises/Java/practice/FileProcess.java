import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

public class FileProcess {
  public static void writeFile(String filePath, String message) {
    try {
      FileWriter writer = new FileWriter(filePath);
      writer.write(message);
      writer.close();
      System.out.println("data has been written\n");
    } catch (IOException e) {
    }
  }

  public static void readFile(String filePath) {
    try {
      BufferedReader reader = new BufferedReader(new FileReader(filePath));
      System.out.println("reading from file: \n");

      String line;
      while((line = reader.readLine()) != null) {
        System.out.println(line);
      }

      reader.close();
    } catch (IOException e) {
    }
  }

  public static void main(String[] args) {
    String filePath = "file.txt";
    String message = "Hello World\nNew Line\nthis file has been written to";

    writeFile(filePath, message);
    readFile(filePath);
  }
}
