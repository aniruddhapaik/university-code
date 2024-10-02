import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class BasicGUIExample {
    public static void main(String[] args) {
        // Create the frame (window)
        JFrame frame = new JFrame("Basic GUI Example");
        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // Create a panel to hold components
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(6, 2, 10, 10));  // 6 rows, 2 columns, with spacing

        // Create components
        JLabel label1 = new JLabel("Enter your name:");
        JTextField textField1 = new JTextField(15);

        JLabel label2 = new JLabel("Enter your age:");
        JTextField textField2 = new JTextField(15);

        JLabel label3 = new JLabel("Gender:");
        String[] genders = {"Male", "Female", "Other"};
        JComboBox<String> comboBox = new JComboBox<>(genders);

        JCheckBox checkBox = new JCheckBox("Subscribe to newsletter");

        JButton button = new JButton("Submit");

        // Create an area for output
        JTextArea outputArea = new JTextArea(5, 20);
        outputArea.setEditable(false);

        // Add components to panel
        panel.add(label1);
        panel.add(textField1);

        panel.add(label2);
        panel.add(textField2);

        panel.add(label3);
        panel.add(comboBox);

        panel.add(checkBox);

        panel.add(button);

        // Scrollable text area
        JScrollPane scrollPane = new JScrollPane(outputArea);
        panel.add(scrollPane);

        // Add action listener to button
        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String name = textField1.getText();
                String age = textField2.getText();
                String gender = (String) comboBox.getSelectedItem();
                boolean subscribed = checkBox.isSelected();

                outputArea.setText("Name: " + name + "\n");
                outputArea.append("Age: " + age + "\n");
                outputArea.append("Gender: " + gender + "\n");
                outputArea.append("Subscribed to newsletter: " + subscribed + "\n");
            }
        });

        // Add panel to frame
        frame.add(panel);

        // Make the frame visible
        frame.setVisible(true);
    }
}
