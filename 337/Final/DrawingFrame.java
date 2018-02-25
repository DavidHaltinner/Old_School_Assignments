/*
 * DrawingFrame.java
 *
 * This class is the internal frames that can be drawn on. It contains methods
 * that return the color, fill state, and type of shape so that they can be
 * drawn correctly.
 *
 * @author  David Haltinner
 */

import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class DrawingFrame extends JInternalFrame {
    
    private int x;
    private int y;
    LinkedList shapes=new LinkedList();
    private JPanel drawingPanel;

    /** Creates new form DrawingFrame */
    public DrawingFrame() {
        initComponents();
        setSize(300,300);
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        drawingPanel = new JPanel();

        setClosable(true);
        try {
            setSelected(true);
        } catch (java.beans.PropertyVetoException e1) {
            e1.printStackTrace();
        }
        setVisible(true);
        drawingPanel.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                drawingPanelMousePressed(evt);
            }
            public void mouseReleased(java.awt.event.MouseEvent evt) {
                drawingPanelMouseReleased(evt);
            }
        });
        drawingPanel.addMouseMotionListener(new java.awt.event.MouseMotionAdapter() {
            public void mouseDragged(java.awt.event.MouseEvent evt) {
                drawingPanelMouseDragged(evt);
            }
        });

        getContentPane().add(drawingPanel, java.awt.BorderLayout.CENTER);

        pack();
    }
    
    /**
     * This mthod is called when the mouse is dragged over the panel. It redraws the current shape.
     */    
    private void drawingPanelMouseDragged(java.awt.event.MouseEvent evt) {
        draw(evt);
    }
    
    /**
     * This method draws the final shape and stores it in the list of shapes.
     */    
    private void drawingPanelMouseReleased(java.awt.event.MouseEvent evt) {
        draw(evt);
    }
    
    /**
     * This method creates a new shape, and stores the fill state and color for it.
     */    
    private void drawingPanelMousePressed(java.awt.event.MouseEvent evt) {
        x=evt.getX();
        y=evt.getY();
        MyShape m=new MyShape(FinalProject.getType());
        m.setColor(FinalProject.getColor());
        m.setFill(FinalProject.getFill());
        shapes.addFirst(m);
    }
    
    /**
     * This method is called in order to draw out the frame and panel. It calls the draw method of the shapes.
     */    
    private void draw(MouseEvent evt) {
        MyShape r=(MyShape)shapes.removeFirst();
        r.setPoints(x,y,evt.getX(), evt.getY());
        shapes.addFirst(r);
        repaint();
    }
    
    
    /**
     * This is the overridden paint methond that is automatically called to repaint the panel and frame.
     */    
    public void paint(Graphics g) {
        super.paint(g);
        for (int i=0; i<shapes.size(); i++)
            ((MyShape)shapes.get(i)).draw(g);
    }
}
