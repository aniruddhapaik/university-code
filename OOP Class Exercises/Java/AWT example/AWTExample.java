import java.awt.*; // AWT components and containers
import java.awt.event.*; // AWT event handling
import java.util.Random;

// Main class to demonstrate AWT concepts
public class AWTExample extends Frame implements ActionListener {

  private Label label; // Label to display message
  private Button button; // Button to trigger action
  private int counter;
  private Random random = new Random();

  // Constructor to set up the GUI components
  public AWTExample() {
    // Set up the frame properties
    setTitle("AWT Example");
    setSize(500, 400);
    setLayout(null); // Use FlowLayout for arranging components

    // Create a label and add it to the frame
    label = new Label("Click the button to see the message!");
    label.setBounds(20, 20, 200, 50);
    add(label);

    // Create a button and add it to the frame
    button = new Button("Click Me");
    button.setBounds(30, 100, 80, 30);
    add(button);

    // Register the current instance as an action listener for the button
    button.addActionListener(this);

    // Make the frame visible
    setVisible(true);

    // Close the application when the window is closed
    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent windowEvent) {
        System.exit(0);
      }
    });
  }

  // Handle button click events
  @Override
  public void actionPerformed(ActionEvent e) {
    this.counter++;
    label.setText("Button clicked counter: " + this.counter);
    button.setBounds(random.nextInt(getWidth()-80), 50 + random.nextInt(getHeight()-80), 80, 30);
  }

  // Main method to launch the application
  public static void main(String[] args) {
    new AWTExample(); // Create an instance of the AWTExample class
  }
}
