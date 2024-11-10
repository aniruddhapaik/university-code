import java.io.FileWriter;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class ProcessFile {
  public static void main(String[] args) {
    String filepath = "newfile.txt";
    String message = "This message will be written to a file";

    WriteFile(filepath, message);
    ReadFile(filepath);
  }

  public static void WriteFile(String filepath, String message) {
    try {
      FileWriter writer = new FileWriter(filepath);
      writer.write(message);
      writer.close();
      System.out.println("Data was just written to file: " + filepath);
      System.out.println("-----------------------");
    } catch (IOException e) {}
  }

  public static void ReadFile(String filepath) {
    try {
      System.out.println("Data is going to be read from path: " + filepath);
      System.out.print("MESSAGE: ");
      BufferedReader reader = new BufferedReader(new FileReader(filepath));
      String line;
      while ((line = reader.readLine()) != null) {
        System.out.println(line);
      }
      reader.close();
    } catch (IOException e) {}
  }
}
