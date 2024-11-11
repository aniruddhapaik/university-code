import java.io.FileWriter;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileProcess {
  public static void WriteFile(String filepath, String message) {
    try {
      FileWriter writer = new FileWriter(filepath);
      writer.write(message);
      writer.close();
      System.out.println("Message was written to file");
    } catch(IOException e) {}
  }

  public static void ReadFile(String filepath) {
    try {
      BufferedReader reader = new BufferedReader(new FileReader(filepath));
      String line;
      int linecount = 0;
      System.out.println("----\nData being read from " + filepath);
      while((line = reader.readLine()) != null) {
        linecount++;
        System.out.println("LINE " + linecount + " | " + line);
      }
      reader.close();
    } catch(IOException e) {}
  }
 public static void main(String[] args) {
  String filepath = "example.txt";
  String message = "Hello World!\nWriting to a file is fun\nWhat is up?";
  WriteFile(filepath, message);
  ReadFile(filepath);
 } 
}
