/*
 * Hw04B.java
 *
 * This applet is a multiplication test system. It asks a series of questions and
 * determines the correct results, displaying a score and time to the user.
 * @author  David Haltinner
 */
import java.util.*;
import javax.swing.*;

public class Hw04B extends JApplet {
    private int x;
    private int y;
    private int totalQuestions=0;
    private int totalCorrect=0;
    private Random r;
    private long startTime;
    
    /** Initializes the applet Hw04B */
    public void init() {
        initComponents();
        r = new Random();
        x=r.nextInt(100);
        y=r.nextInt(100);
        ProblemLabel.setText(x+" * "+y+" = ");
        TotalLabel.setText("You have not answered any questions yet.");
        startTime=System.currentTimeMillis();
        TimeSpentLabel.setText("Starting clock. Please begin answering questions.");
    }
    
    /** This method is called from within the init() method to
     * initialize the form.
     */
    private void initComponents() {
        java.awt.GridBagConstraints gridBagConstraints;
        
        ProblemLabel = new JLabel();
        AnswerField = new JTextField();
        MultiplyButton = new JButton();
        TotalLabel = new JLabel();
        InstructionsLabel = new JLabel();
        TimeSpentLabel = new JLabel();
        AnswersScrollPane = new JScrollPane();
        AnswersTextArea = new JTextArea();
        
	ProblemLabel.setMinimumSize(new java.awt.Dimension(65,19));

        getContentPane().setLayout(new java.awt.GridBagLayout());
        
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 60, 4, 34);
        getContentPane().add(ProblemLabel, gridBagConstraints);
        
        AnswerField.setMinimumSize(new java.awt.Dimension(35, 19));
        AnswerField.setPreferredSize(new java.awt.Dimension(25, 19));
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.insets = new java.awt.Insets(10, 110, 0, 0);
        getContentPane().add(AnswerField, gridBagConstraints);
        try {
            MultiplyButton.setIcon(new ImageIcon("mulbutton.jpg"));
        } catch (Exception e) {
            MultiplyButton.setText("Multiply");
            AnswersTextArea.append("There was an access error to the icon file.\n");
        }
        MultiplyButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                MultiplyButtonMouseClicked(evt);
            }
        });
        
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 1;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.insets = new java.awt.Insets(0, 12, 20, 0);
        getContentPane().add(MultiplyButton, gridBagConstraints);
        
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 2;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.insets = new java.awt.Insets(20, 16, 35, 171);
        getContentPane().add(TotalLabel, gridBagConstraints);
        
        InstructionsLabel.setText("Enter your guess into the field below. Click Multiply to check your answer. ");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.gridheight = 2;
        gridBagConstraints.anchor = java.awt.GridBagConstraints.NORTH;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 0, 9);
        getContentPane().add(InstructionsLabel, gridBagConstraints);
        
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 4;
        gridBagConstraints.gridwidth = 3;
        gridBagConstraints.insets = new java.awt.Insets(10, 10, 0, 343);
        getContentPane().add(TimeSpentLabel, gridBagConstraints);
        
        AnswersScrollPane.setMinimumSize(new java.awt.Dimension(500, 100));
        AnswersScrollPane.setPreferredSize(new java.awt.Dimension(450, 450));
        AnswersScrollPane.setViewportView(AnswersTextArea);
        
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 5;
        gridBagConstraints.gridwidth = 3;
        getContentPane().add(AnswersScrollPane, gridBagConstraints);
        
    }
    
    /** This method is ran when the button is clicked. It checks to see if they gave the
     * correct answer, determines a new score, sets up the next question, and displays
     * the time.
     */
    private void MultiplyButtonMouseClicked(java.awt.event.MouseEvent evt) {
        if (!AnswerField.getText().equals("")) {
            totalQuestions++;
            String rw;
            if ((x*y)==(Integer.parseInt(AnswerField.getText()))) {
                totalCorrect++;
                rw="right. Good job!\n";
            }
            else rw="wrong.\n";
            AnswersTextArea.append(ProblemLabel.getText()+(x*y)+", you guessed "+AnswerField.getText()+" which is "+rw);
            x=r.nextInt(100);
            y=r.nextInt(100);
            ProblemLabel.setText(x+" * "+y+" = ");
            TotalLabel.setText("You have "+totalCorrect+" correct out of "+totalQuestions+". Which is "+(int)(((double)totalCorrect/(double)totalQuestions)*100)+"%");
            AnswerField.setText("");
        }
        else AnswersTextArea.append("Please give your answer first.\n");
        TimeSpentLabel.setText("You have spent "+(System.currentTimeMillis()-startTime)/1000+" seconds on this test.");
    }
    
    private JTextField AnswerField;
    private JScrollPane AnswersScrollPane;
    private JTextArea AnswersTextArea;
    private JLabel InstructionsLabel;
    private JButton MultiplyButton;
    private JLabel ProblemLabel;
    private JLabel TimeSpentLabel;
    private JLabel TotalLabel;
}
