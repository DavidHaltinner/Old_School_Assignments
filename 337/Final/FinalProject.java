/*
 * FinalProject.java
 *
 * This class holds all the pieces for the application together. It inherits
 * from JFrame, and creates a desktop pane in which internal frames are housed
 * that allow the user to draw on, and one internal frame that keeps the
 * settings for color, fill state, and shape of what should be drawn.
 *
 * @author  David Haltinner
 */

import java.awt.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;

public class FinalProject extends javax.swing.JFrame {
    
    /** Creates new form FinalProject */
    public FinalProject() {
        initComponents();
        setSize(800,600);
        DrawingFrame drawme = new DrawingFrame();
        desktopPane.add(drawme);
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        desktopPane = new javax.swing.JDesktopPane();
        OptionsFrame = new javax.swing.JInternalFrame();
        shapeComboBox = new javax.swing.JComboBox();
        fillBox = new javax.swing.JCheckBox();
        colorChooser = new javax.swing.JColorChooser();
        newButton = new javax.swing.JButton();
        menuBar = new javax.swing.JMenuBar();
        fileMenu = new javax.swing.JMenu();
        newMenuItem = new javax.swing.JMenuItem();
        exitMenuItem = new javax.swing.JMenuItem();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        OptionsFrame.getContentPane().setLayout(null);

        OptionsFrame.setMinimumSize(new java.awt.Dimension(475, 350));
        OptionsFrame.setPreferredSize(new java.awt.Dimension(475, 350));
        OptionsFrame.setVisible(true);
        shapeComboBox.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Line", "Oval", "Rectangle", "Rounded Rectangle" }));
        OptionsFrame.getContentPane().add(shapeComboBox);
        shapeComboBox.setBounds(20, 10, 220, 24);

        fillBox.setText("Fill with Color");
        OptionsFrame.getContentPane().add(fillBox);
        fillBox.setBounds(20, 40, 220, 23);

        OptionsFrame.getContentPane().add(colorChooser);
        colorChooser.setBounds(20, 70, 429, 230);

        newButton.setLabel("New Drawing");
        newButton.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                newButtonMouseClicked(evt);
            }
        });

        OptionsFrame.getContentPane().add(newButton);
        newButton.setBounds(290, 10, 120, 25);

        OptionsFrame.setBounds(200, 120, 470, 340);
        desktopPane.add(OptionsFrame, javax.swing.JLayeredPane.DEFAULT_LAYER);

        getContentPane().add(desktopPane, java.awt.BorderLayout.CENTER);

        fileMenu.setText("File");
        newMenuItem.setLabel("New Drawing");
        newMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                newMenuItemActionPerformed(evt);
            }
        });

        fileMenu.add(newMenuItem);

        exitMenuItem.setLabel("Exit Program");
        exitMenuItem.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                exitMenuItemActionPerformed(evt);
            }
        });

        fileMenu.add(exitMenuItem);

        menuBar.add(fileMenu);

        setJMenuBar(menuBar);

        pack();
    }
    
    private void newButtonMouseClicked(java.awt.event.MouseEvent evt) {
        DrawingFrame drawme = new DrawingFrame();
        desktopPane.add(drawme);
        drawme.toFront();
    }
    
    /**
     * This method is called when the File\New menu item is clicked. It creates a new drawing frame.
     */
    private void newMenuItemActionPerformed(java.awt.event.ActionEvent evt) {
        DrawingFrame drawme = new DrawingFrame();
        desktopPane.add(drawme);
        drawme.toFront();
    }
    
    /**
     * This method is called when the File/Exit option is chosen. It closes the application.
     */
    private void exitMenuItemActionPerformed(java.awt.event.ActionEvent evt) {
        System.exit(0);
    }
    
    /**
     * This methds returns the type of shape to be drawn.
     */
    public static String getType() {
        return (String) shapeComboBox.getSelectedItem();
    }
    
    /**
     * This method returns the fill state of the shape to be drawn.
     */
    public static boolean getFill() {
        if (fillBox.getSelectedObjects()==null) return false;
        else return true;
    }
    
    /**
     * This method returns the color of the type to be drawn.
     */
    public static Color getColor() {
        return colorChooser.getColor();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        new FinalProject().show();
    }
    
    private static javax.swing.JInternalFrame OptionsFrame;
    private static javax.swing.JColorChooser colorChooser;
    private javax.swing.JDesktopPane desktopPane;
    private javax.swing.JMenuItem exitMenuItem;
    private javax.swing.JMenu fileMenu;
    private static javax.swing.JCheckBox fillBox;
    private javax.swing.JMenuBar menuBar;
    private javax.swing.JButton newButton;
    private javax.swing.JMenuItem newMenuItem;
    private static javax.swing.JComboBox shapeComboBox;
}
