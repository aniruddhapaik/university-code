import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class AWTPractice extends Frame implements ActionListener {
  private Label label;
  private Button button;
  private int counter;
  private Random random = new Random();

  AWTPractice() {
    setTitle("AWT Example Practice");
    setSize(500, 500);
    setLayout(null);

    label = new Label("Hello World Label, try clicking the button");
    label.setBounds(50, 30, 300, 50);
    add(label);

    button = new Button("Click me!");
    button.setBounds(100, 200, 80, 30);
    add(button);

    // label = new Label("Click the button to see the message!");
    // label.setBounds(20, 20, 200, 50);
    // add(label);

    // // Create a button and add it to the frame
    // button = new Button("Click Me");
    // button.setBounds(30, 100, 80, 30);
    // add(button);    

    button.addActionListener(this);

    setVisible(true);

    addWindowListener(new WindowAdapter() {
      public void windowClosing(WindowEvent we) {
        System.exit(0);
      }
    });
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    counter++;
    button.setBounds(random.nextInt(getWidth()-80), 50 + random.nextInt(getHeight()-80), 80, 30);
    label.setText("Button has been clicked " + counter + " times");
  }

  public static void main(String[] args) {
    new AWTPractice();
  }
}
