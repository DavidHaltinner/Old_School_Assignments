/*
 * Exam2.java
 *
 * This class inherits from JFrame and will create a calculator that can do
 * basic mathmatical functions using double numbers.
 * After receiving the answer you want, close and reopen the application to
 * start a new operation.
 *
 * Created on April 13, 2004
 * @author  David Haltinner
 */

import javax.swing.*;

public class Exam2 extends JFrame {
    private boolean dotAlreadyClicked=false;    //Make sure only one dot
    private boolean firstClick=true;            //First number inputted?
    private boolean canReplace=false;           //See if the displayed number can be replaced
    private double tempResult=0.0;              //Results so far
    private String operation=".";               //Next operation to perform
    
    /** Creates new form Exam2 */
    public Exam2() {
        initComponents();
        setSize(205,170);
    }
    
    /** This method will check to see if enough data has been entered to perform an
     * operation, and then perform the appropriate one. It will also then display the
     * current results, and set the number as replacable.
     */
    private void setupResult() {
        if (!firstClick) {
            if (operation.equals("/")) tempResult=tempResult/Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("+")) tempResult=tempResult+Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("-")) tempResult=tempResult-Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("*")) tempResult=tempResult*Double.parseDouble(resultsLabel.getText());
            resultsLabel.setText(Double.toString(tempResult));
        }
        else {
            if (!dotAlreadyClicked) resultsLabel.setText(resultsLabel.getText()+".0");
            tempResult=Double.parseDouble(resultsLabel.getText());
            firstClick=false;
        }
        canReplace=true;
        dotAlreadyClicked=false;
    }
    
    /** This method will set the displayed number to the inputted number if it is
     * starting at 0, otherwise it will append the given number to the displayed
     * number.
     */
    private void setNumber(String num) {
        if (resultsLabel.getText().equals("0") || canReplace) resultsLabel.setText(num);
        else resultsLabel.setText(resultsLabel.getText()+num);
        canReplace=false;
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        resultsLabel = new JLabel();
        sevenButton = new JButton();
        eightButton = new JButton();
        nineButton = new JButton();
        divideButton = new JButton();
        fourButton = new JButton();
        fiveButton = new JButton();
        sixButton = new JButton();
        oneButton = new JButton();
        twoButton = new JButton();
        threeButton = new JButton();
        multiplyButton = new JButton();
        dotButton = new JButton();
        zeroButton = new JButton();
        minusButton = new JButton();
        equalsButton = new JButton();
        addButton = new JButton();

        getContentPane().setLayout(null);

        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                exitForm(evt);
            }
        });

        resultsLabel.setFont(new java.awt.Font("Dialog", 1, 14));
        resultsLabel.setText("0");
        getContentPane().add(resultsLabel);
        resultsLabel.setBounds(0, 0, 190, 17);

        sevenButton.setText("7");
        sevenButton.setMaximumSize(new java.awt.Dimension(50, 25));
        sevenButton.setMinimumSize(new java.awt.Dimension(50, 25));
        sevenButton.setPreferredSize(new java.awt.Dimension(50, 25));
        sevenButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sevenButtonActionPerformed(evt);
            }
        });

        getContentPane().add(sevenButton);
        sevenButton.setBounds(0, 20, 50, 25);

        eightButton.setText("8");
        eightButton.setMaximumSize(new java.awt.Dimension(50, 25));
        eightButton.setMinimumSize(new java.awt.Dimension(50, 25));
        eightButton.setPreferredSize(new java.awt.Dimension(50, 25));
        eightButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                eightButtonActionPerformed(evt);
            }
        });

        getContentPane().add(eightButton);
        eightButton.setBounds(50, 20, 50, 25);

        nineButton.setText("9");
        nineButton.setMaximumSize(new java.awt.Dimension(50, 25));
        nineButton.setMinimumSize(new java.awt.Dimension(50, 25));
        nineButton.setPreferredSize(new java.awt.Dimension(50, 25));
        nineButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                nineButtonActionPerformed(evt);
            }
        });

        getContentPane().add(nineButton);
        nineButton.setBounds(100, 20, 50, 25);

        divideButton.setText("/");
        divideButton.setMaximumSize(new java.awt.Dimension(50, 25));
        divideButton.setMinimumSize(new java.awt.Dimension(50, 25));
        divideButton.setPreferredSize(new java.awt.Dimension(50, 25));
        divideButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                divideButtonActionPerformed(evt);
            }
        });

        getContentPane().add(divideButton);
        divideButton.setBounds(150, 20, 50, 25);

        fourButton.setText("4");
        fourButton.setMaximumSize(new java.awt.Dimension(50, 25));
        fourButton.setMinimumSize(new java.awt.Dimension(50, 25));
        fourButton.setPreferredSize(new java.awt.Dimension(50, 25));
        fourButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                fourButtonActionPerformed(evt);
            }
        });

        getContentPane().add(fourButton);
        fourButton.setBounds(0, 50, 50, 25);

        fiveButton.setText("5");
        fiveButton.setMaximumSize(new java.awt.Dimension(50, 25));
        fiveButton.setMinimumSize(new java.awt.Dimension(50, 25));
        fiveButton.setPreferredSize(new java.awt.Dimension(50, 25));
        fiveButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                fiveButtonActionPerformed(evt);
            }
        });

        getContentPane().add(fiveButton);
        fiveButton.setBounds(50, 50, 50, 25);

        sixButton.setText("6");
        sixButton.setMaximumSize(new java.awt.Dimension(50, 25));
        sixButton.setMinimumSize(new java.awt.Dimension(50, 25));
        sixButton.setPreferredSize(new java.awt.Dimension(50, 25));
        sixButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sixButtonActionPerformed(evt);
            }
        });

        getContentPane().add(sixButton);
        sixButton.setBounds(100, 50, 50, 25);

        oneButton.setText("1");
        oneButton.setMaximumSize(new java.awt.Dimension(50, 25));
        oneButton.setMinimumSize(new java.awt.Dimension(50, 25));
        oneButton.setPreferredSize(new java.awt.Dimension(50, 25));
        oneButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                oneButtonActionPerformed(evt);
            }
        });

        getContentPane().add(oneButton);
        oneButton.setBounds(0, 80, 50, 25);

        twoButton.setText("2");
        twoButton.setMaximumSize(new java.awt.Dimension(50, 25));
        twoButton.setMinimumSize(new java.awt.Dimension(50, 25));
        twoButton.setPreferredSize(new java.awt.Dimension(50, 25));
        twoButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                twoButtonActionPerformed(evt);
            }
        });

        getContentPane().add(twoButton);
        twoButton.setBounds(50, 80, 50, 25);

        threeButton.setText("3");
        threeButton.setMaximumSize(new java.awt.Dimension(50, 25));
        threeButton.setMinimumSize(new java.awt.Dimension(50, 25));
        threeButton.setPreferredSize(new java.awt.Dimension(50, 25));
        threeButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                threeButtonActionPerformed(evt);
            }
        });

        getContentPane().add(threeButton);
        threeButton.setBounds(100, 80, 50, 25);

        multiplyButton.setText("*");
        multiplyButton.setMaximumSize(new java.awt.Dimension(50, 25));
        multiplyButton.setMinimumSize(new java.awt.Dimension(50, 25));
        multiplyButton.setPreferredSize(new java.awt.Dimension(50, 25));
        multiplyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                multiplyButtonActionPerformed(evt);
            }
        });

        getContentPane().add(multiplyButton);
        multiplyButton.setBounds(150, 50, 50, 25);

        dotButton.setText(".");
        dotButton.setMaximumSize(new java.awt.Dimension(50, 25));
        dotButton.setMinimumSize(new java.awt.Dimension(50, 25));
        dotButton.setPreferredSize(new java.awt.Dimension(50, 25));
        dotButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                dotButtonActionPerformed(evt);
            }
        });

        getContentPane().add(dotButton);
        dotButton.setBounds(50, 110, 50, 25);

        zeroButton.setText("0");
        zeroButton.setMaximumSize(new java.awt.Dimension(50, 25));
        zeroButton.setMinimumSize(new java.awt.Dimension(50, 25));
        zeroButton.setPreferredSize(new java.awt.Dimension(50, 25));
        zeroButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                zeroButtonActionPerformed(evt);
            }
        });

        getContentPane().add(zeroButton);
        zeroButton.setBounds(0, 110, 50, 25);

        minusButton.setText("-");
        minusButton.setMaximumSize(new java.awt.Dimension(50, 25));
        minusButton.setMinimumSize(new java.awt.Dimension(50, 25));
        minusButton.setPreferredSize(new java.awt.Dimension(50, 25));
        minusButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                minusButtonActionPerformed(evt);
            }
        });

        getContentPane().add(minusButton);
        minusButton.setBounds(150, 80, 50, 25);

        equalsButton.setText("=");
        equalsButton.setMaximumSize(new java.awt.Dimension(50, 25));
        equalsButton.setMinimumSize(new java.awt.Dimension(50, 25));
        equalsButton.setPreferredSize(new java.awt.Dimension(50, 25));
        equalsButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                equalsButtonActionPerformed(evt);
            }
        });

        getContentPane().add(equalsButton);
        equalsButton.setBounds(100, 110, 50, 25);

        addButton.setText("+");
        addButton.setMaximumSize(new java.awt.Dimension(50, 25));
        addButton.setMinimumSize(new java.awt.Dimension(50, 25));
        addButton.setPreferredSize(new java.awt.Dimension(50, 25));
        addButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                addButtonActionPerformed(evt);
            }
        });

        getContentPane().add(addButton);
        addButton.setBounds(150, 110, 50, 25);

        pack();
    }
    
    private void multiplyButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setupResult();
        operation="*";
    }
    
    private void minusButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setupResult();
        operation="-";
    }
    
    private void addButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setupResult();
        operation="+";
    }
    
    private void equalsButtonActionPerformed(java.awt.event.ActionEvent evt) {
        if (!firstClick) {
            if (operation.equals("/")) tempResult=tempResult/Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("+")) tempResult=tempResult+Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("-")) tempResult=tempResult-Double.parseDouble(resultsLabel.getText());
            else if (operation.equals("*")) tempResult=tempResult*Double.parseDouble(resultsLabel.getText());
        }
        else
            tempResult=Double.parseDouble(resultsLabel.getText());
        resultsLabel.setText(Double.toString(tempResult));
        operation=".";
        canReplace=true;
        dotAlreadyClicked=true;
    }
    
    private void divideButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setupResult();
        operation="/";
    }
    
    private void dotButtonActionPerformed(java.awt.event.ActionEvent evt) {
        if (canReplace) {
            resultsLabel.setText("0");
            canReplace=false;
        }
        if (!dotAlreadyClicked) resultsLabel.setText(resultsLabel.getText()+".");
        dotAlreadyClicked=true;
    }
    
    private void zeroButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("0");
    }
    
    private void threeButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("3");
    }
    
    private void twoButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("2");
    }
    
    private void oneButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("1");
    }
    
    private void sixButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("6");
    }
    
    private void fiveButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("5");
    }
    
    private void fourButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("4");
    }
    
    private void nineButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("9");
    }
    
    private void sevenButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("7");
    }
    
    private void eightButtonActionPerformed(java.awt.event.ActionEvent evt) {
        setNumber("8");
    }
   
    /** Exit the Application */
    private void exitForm(java.awt.event.WindowEvent evt) {
        System.exit(0);
    }
    
    /**
     * Simply create the form, and wait for user input.
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        new Exam2().show();
    }
    
    // Components
    private JButton addButton;
    private JButton divideButton;
    private JButton dotButton;
    private JButton eightButton;
    private JButton equalsButton;
    private JButton fiveButton;
    private JButton fourButton;
    private JButton minusButton;
    private JButton multiplyButton;
    private JButton nineButton;
    private JButton oneButton;
    private JLabel resultsLabel;
    private JButton sevenButton;
    private JButton sixButton;
    private JButton threeButton;
    private JButton twoButton;
    private JButton zeroButton;
}
ÿÿ