import java.awt.*;
import java.awt.event.*;
import java.util.Random;

class Frame1 extends Frame implements ActionListener {
  Frame1() {
    setSize(400, 400);
    setLayout(null);

    Button button = new Button("Another button");
    button.setBounds(20, 50, 80, 30);
    add(button);

    Button button2 = new Button("Button 2");
    button2.setBounds(50, 100, 80, 30);
    add(button2);

    button.addActionListener(this);

    button2.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
        System.out.println("Button 2 clicked");
      }
    });

    setVisible(true);

    addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent we) {
        Frame frame = (Frame) we.getSource();
        frame.dispose();
      }
    });
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    System.out.println("Button 1 clicked");
  }
}

public class AWTExample extends Frame implements ActionListener {
  private int counter = 0;
  private Button button;
  private Label label;
  private Label counterlabel;
  private Random random = new Random();
  private TextField text;

  AWTExample() {
    setTitle("AWT Example for the nth time");
    setSize(800, 500);
    setLayout(null);

    button = new Button("Click here!");
    button.setBounds(30, 80, 80, 30);
    add(button);

    label = new Label("Hey, try clicking the button");
    label.setBounds(10, 20, getWidth() / 2, 50);
    add(label);

    counterlabel = new Label("Button Click Counter: 0");
    counterlabel.setBounds(getWidth() / 2, 20, getWidth() / 2, 50);
    add(counterlabel);

    text = new TextField("This is a textfield, edit text");
    text.setBounds(10, 120, 200, 30);
    text.setBackground(Color.CYAN);
    add(text);

    button.addActionListener(this);

    setVisible(true);

    addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent we) {
        Frame frame = (Frame) we.getSource();
        frame.dispose();
      }
    });
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    this.counter++;
    this.counterlabel.setText("Button Click Counter: " + this.counter);
    button.setBounds(10 + random.nextInt(getWidth() - 80), 80, 80, 30);
  }

  public static void main(String[] args) {
    new AWTExample();
    new Frame1();
  }
}
