import java.io.FileWriter;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

public class FileProcessingExample {

  public static void main(String[] args) {
    String filePath = "example.txt";

    // Step 1: Write to the file
    writeFile(filePath, "Hello, this is a file processing example in Java!\n"+
    "Welcome to file handling.");

    // Step 2: Read from the file
    readFile(filePath);
  }

  // Method to write data to a file
  public static void writeFile(String filePath, String content) {
    try {
      // Create a FileWriter object to write to the file
      FileWriter writer = new FileWriter(filePath);
      writer.write(content); // Write content to file
      writer.close(); // Close the writer
      System.out.println("Data has been written to " + filePath);
    } catch (IOException e) {
      System.out.println("An error occurred while writing to the file.");
      e.printStackTrace();
    }
  }

  // Method to read data from a file
  public static void readFile(String filePath) {
    try {
      // Create a FileReader and wrap it in a BufferedReader for line-by-line reading
      BufferedReader reader = new BufferedReader(new FileReader(filePath));
      String line;

      System.out.println("Reading data from " + filePath + ":");
      while ((line = reader.readLine()) != null) {
        System.out.println(line); // Print each line to console
      }

      reader.close(); // Close the reader
    } catch (IOException e) {
      System.out.println("An error occurred while reading from the file.");
      e.printStackTrace();
    }
  }
}
