/*
 * HW04A.java
 *
 * This class contains the infomration to create the GUI for the synchronized
 * buffering program. It inherits from JFrame, and contains text labels, text
 * fields, scroll pane, and button.
 *
 * @author  David Haltinner
 */

import javax.swing.*;

public class Hw04Frame extends JFrame {
    
    /** Creates new form HW04A */
    public Hw04Frame() {
        initComponents();
        this.setSize(430, 370);
        
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        NumberLabel = new JLabel();
        NumberText = new JTextField();
        RunButton = new JButton();
        DataPane = new JScrollPane();
        DataTextArea = new JTextArea();
        ReadLabel = new JLabel();

        getContentPane().setLayout(null);

        setTitle("HW04 Part A");
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                exitForm(evt);
            }
        });

        NumberLabel.setText("How many objects do you want to read: ");
        getContentPane().add(NumberLabel);
        NumberLabel.setBounds(10, 10, 260, 15);

        getContentPane().add(NumberText);
        NumberText.setBounds(270, 10, 69, 19);

        RunButton.setText("Run!");
        RunButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                RunButtonMouseClicked(evt);
            }
        });

        getContentPane().add(RunButton);
        RunButton.setBounds(360, 10, 62, 25);

        DataPane.setViewportView(DataTextArea);

        getContentPane().add(DataPane);
        DataPane.setBounds(20, 40, 400, 260);

        ReadLabel.setText("Run app by filling in the above field and clicking Run!");
        getContentPane().add(ReadLabel);
        ReadLabel.setBounds(20, 310, 400, 15);

        pack();
    }
    
    /** This method is called when the button is pressed. It checks for a valid number,
     * and creates Consumer and Producer treads.
     */    
    private void RunButtonMouseClicked(java.awt.event.MouseEvent evt) {
        DataTextArea.setText(null);
        if (NumberText.getText().equals(""))
            ReadLabel.setText("Please provide a number above!");
        else {
            SynchronizedBuffer buffer = new SynchronizedBuffer(DataTextArea);
            
            // create producer and consumer objects
            int num = Integer.parseInt(NumberText.getText());
            
            Producer producer = new Producer( buffer, num, DataTextArea);
            Consumer consumer = new Consumer(buffer, num, DataTextArea);
            producer.start();  // start producer thread
            consumer.start();  // start consumer thread
            
            ReadLabel.setText("Thank you.");
        }
    }
    
    /** Exit the Application */
    private void exitForm(java.awt.event.WindowEvent evt) {
        System.exit(0);
    }
        
    /** The main method simply creates the GUI.
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        Hw04Frame frame = new Hw04Frame();
        frame.show();
        
    }
   
    private JScrollPane DataPane;
    private static JTextArea DataTextArea;
    private JLabel NumberLabel;
    private JTextField NumberText;
    private JLabel ReadLabel;
    private JButton RunButton;  
}
