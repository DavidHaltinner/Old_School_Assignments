/*
 * HW05D.java
 *
 * @author  David Haltinner
 *
 * This program creates a jPanel inside of a JFrame that allows shapes to be
 * chosen and be drawn with mouse movements. A corner will be placed where the
 * mouse is clicked, and the other corner will be where the mouse button is
 * released.
 */
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import java.util.LinkedList;
import javax.swing.*;

public class HW05E extends JFrame {
    private int x;
    private int y;
    
    /**
     * This class has parellel shape and color lists to associate a color to a shape that is drawn.
     */
    private class ColorShapeList {
        LinkedList shapes=new LinkedList();
        LinkedList colors=new LinkedList();
        LinkedList fill=new LinkedList();
    }
    
    ColorShapeList rectangles=new ColorShapeList();
    ColorShapeList lines=new ColorShapeList();
    ColorShapeList ovals=new ColorShapeList();
    ColorShapeList rounded=new ColorShapeList();
    
    /** Creates new form HW05A */
    public HW05E() {
        initComponents();
        setSize(650,650);
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        drawingPanel = new JPanel();
        shapeComboBox = new JComboBox();
        colorChooser = new JColorChooser();
        fillBox = new JCheckBox();

        getContentPane().setLayout(null);

        setTitle("David Haltinner HW05");
        setResizable(false);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosing(java.awt.event.WindowEvent evt) {
                exitForm(evt);
            }
        });

        drawingPanel.setLayout(null);

        drawingPanel.setPreferredSize(new java.awt.Dimension(900, 900));
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

        shapeComboBox.setModel(new DefaultComboBoxModel(new String[] { "Line", "Oval", "Rectangle", "Rounded Rectangle" }));
        drawingPanel.add(shapeComboBox);
        shapeComboBox.setBounds(0, 0, 220, 24);

        drawingPanel.add(colorChooser);
        colorChooser.setBounds(220, 0, 429, 230);

        fillBox.setText("Fill with Color");
        drawingPanel.add(fillBox);
        fillBox.setBounds(0, 30, 220, 23);

        getContentPane().add(drawingPanel);
        drawingPanel.setBounds(0, 0, 670, 530);

        pack();
    }
    
    /**
     * This method gets the current mouse posistion, and creates a new shape and adds it to the list.
     */
    private void drawRect(MouseEvent evt) {
        Rectangle r=(Rectangle)rectangles.shapes.removeFirst();
        if (x<evt.getX() && y<evt.getY())
            r=new Rectangle(x,y+20,evt.getX()-x, evt.getY()-y);
        else if (x<evt.getX() && y>evt.getY())
            r=new Rectangle(x,evt.getY()+20,evt.getX()-x, y-evt.getY());
        else if (x>evt.getX() && y<evt.getY())
            r=new Rectangle(evt.getX(),y+20,x-evt.getX(), evt.getY()-y);
        else if (x>evt.getX() && y>evt.getY())
            r=new Rectangle(evt.getX(),evt.getY()+20,x-evt.getX(), y-evt.getY());
        else r=new Rectangle();
        rectangles.shapes.addFirst(r);
        repaint();
    }
    
    /**
     * This method gets the current mouse posistion, and creates a new shape and adds it to the list.
     */
    private void drawRoundRect(MouseEvent evt) {
        RoundRectangle2D.Double r=(RoundRectangle2D.Double)rounded.shapes.removeFirst();
        if (x<evt.getX() && y<evt.getY())
            r.setRoundRect(x,y+20,evt.getX()-x, evt.getY()-y, 10, 10);
        else if (x<evt.getX() && y>evt.getY())
            r.setRoundRect(x,evt.getY()+20,evt.getX()-x, y-evt.getY(), 10, 10);
        else if (x>evt.getX() && y<evt.getY())
            r.setRoundRect(evt.getX(),y+20,x-evt.getX(), evt.getY()-y, 10, 10);
        else if (x>evt.getX() && y>evt.getY())
            r.setRoundRect(evt.getX(),evt.getY()+20,x-evt.getX(), y-evt.getY(), 10, 10);
        rounded.shapes.addFirst(r);
        repaint();
    }
    
    /**
     * This method gets the current mouse posistion, and creates a new shape and adds it to the list.
     */
    private void drawOval(MouseEvent evt) {
        Ellipse2D.Double r=(Ellipse2D.Double)ovals.shapes.removeFirst();
        if (x<evt.getX() && y<evt.getY())
            r.setFrame(x,y+20,evt.getX()-x, evt.getY()-y);
        else if (x<evt.getX() && y>evt.getY())
            r.setFrame(x,evt.getY()+20,evt.getX()-x, y-evt.getY());
        else if (x>evt.getX() && y<evt.getY())
            r.setFrame(evt.getX(),y+20,x-evt.getX(), evt.getY()-y);
        else if (x>evt.getX() && y>evt.getY())
            r.setFrame(evt.getX(),evt.getY()+20,x-evt.getX(), y-evt.getY());
        ovals.shapes.addFirst(r);
        repaint();
    }
    
    /**
     * This method gets the current mouse posistion, and creates a new shape and adds it to the list.
     */
    private void drawLine(MouseEvent evt) {
        Line2D l = (Line2D)lines.shapes.removeFirst();
        l.setLine(x,y+20,evt.getX(), evt.getY()+20);
        lines.shapes.addFirst(l);
        repaint();
    }
    
    /**
     * This method gets the current mouse posistion, and calls the associated funtion to draw the desired shape.
     */
    private void drawingPanelMouseDragged(java.awt.event.MouseEvent evt) {
        if (shapeComboBox.getSelectedItem().equals("Rectangle")) drawRect(evt);
        else if (shapeComboBox.getSelectedItem().equals("Rounded Rectangle")) drawRoundRect(evt);
        else if (shapeComboBox.getSelectedItem().equals("Line")) drawLine(evt);
        else if (shapeComboBox.getSelectedItem().equals("Oval")) drawOval(evt);
    }
    
    /**
     * This method draws the shape from the previos clicked position to the current mouse position.
     */
    private void drawingPanelMouseReleased(java.awt.event.MouseEvent evt) {
        if (shapeComboBox.getSelectedItem().equals("Rectangle")) drawRect(evt);
        else if (shapeComboBox.getSelectedItem().equals("Rounded Rectangle")) drawRoundRect(evt);
        else if (shapeComboBox.getSelectedItem().equals("Line")) drawLine(evt);
        else if (shapeComboBox.getSelectedItem().equals("Oval")) drawOval(evt);
    }
    
    /**
     * The paint method draws out the shapes.
     */
    public void paint(Graphics g) {
        if (!drawingPanel.getSize().equals(myFrame.getSize())) drawingPanel.setSize(myFrame.getSize());
        g.setColor(colorChooser.getColor());
        super.paint(g);
        for (int i=0; i<rectangles.shapes.size(); i++) {
            g.setColor((Color)rectangles.colors.get(i));
            if (rectangles.fill.get(i).equals("fill")) g.fillRect((int)((Rectangle)rectangles.shapes.get(i)).getX(), (int)((Rectangle)rectangles.shapes.get(i)).getY(), (int)((Rectangle)rectangles.shapes.get(i)).getWidth(), (int)((Rectangle)rectangles.shapes.get(i)).getHeight());
            else g.drawRect((int)((Rectangle)rectangles.shapes.get(i)).getX(), (int)((Rectangle)rectangles.shapes.get(i)).getY(), (int)((Rectangle)rectangles.shapes.get(i)).getWidth(), (int)((Rectangle)rectangles.shapes.get(i)).getHeight());
        }
        for (int i=0; i<lines.shapes.size(); i++) {
            g.setColor((Color)lines.colors.get(i));
            g.drawLine((int)((Line2D)lines.shapes.get(i)).getX1(), (int)((Line2D)lines.shapes.get(i)).getY1(), (int)((Line2D)lines.shapes.get(i)).getX2(), (int)((Line2D)lines.shapes.get(i)).getY2());
        }
        for (int i=0; i<rounded.shapes.size(); i++) {
            g.setColor((Color)rounded.colors.get(i));
            if (rounded.fill.get(i).equals("fill")) g.fillRoundRect((int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getX(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getY(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getWidth(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getHeight(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getArcWidth(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getArcHeight());
            else g.drawRoundRect((int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getX(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getY(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getWidth(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getHeight(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getArcWidth(), (int)((RoundRectangle2D.Double)rounded.shapes.get(i)).getArcHeight());
        }
        for (int i=0; i<ovals.shapes.size(); i++) {
            g.setColor((Color)ovals.colors.get(i));
            if (ovals.fill.get(i).equals("fill")) g.fillOval((int)((Ellipse2D.Double)ovals.shapes.get(i)).getX(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getY(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getWidth(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getHeight());
            else g.drawOval((int)((Ellipse2D.Double)ovals.shapes.get(i)).getX(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getY(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getWidth(), (int)((Ellipse2D.Double)ovals.shapes.get(i)).getHeight());
        }
    }
    
    /**
     * This methid records the current mouse position in order to draw it when the mouse is released.
     */
    private void drawingPanelMousePressed(java.awt.event.MouseEvent evt) {
        x=evt.getX();
        y=evt.getY();
        if (shapeComboBox.getSelectedItem().equals("Rectangle")) {
            if (fillBox.getSelectedObjects()==null) rectangles.fill.addFirst("no");
            else rectangles.fill.addFirst("fill");
            rectangles.colors.addFirst(colorChooser.getColor());
            rectangles.shapes.addFirst(new Rectangle());
        }
        else if (shapeComboBox.getSelectedItem().equals("Rounded Rectangle")) {
            if (fillBox.getSelectedObjects()==null) rounded.fill.addFirst("no");
            else rounded.fill.addFirst("fill");
            rounded.colors.addFirst(colorChooser.getColor());
            rounded.shapes.addFirst(new RoundRectangle2D.Double());
        }
        else if (shapeComboBox.getSelectedItem().equals("Line")) {
            lines.colors.addFirst(colorChooser.getColor());
            lines.shapes.addFirst(new Line2D.Double());
        }
        else if (shapeComboBox.getSelectedItem().equals("Oval")) {
            if (fillBox.getSelectedObjects()==null) ovals.fill.addFirst("no");
            else ovals.fill.addFirst("fill");
            ovals.colors.addFirst(colorChooser.getColor());
            ovals.shapes.addFirst(new Ellipse2D.Double());
        }
    }
    
    /** Exit the Application */
    private void exitForm(java.awt.event.WindowEvent evt) {
        System.exit(0);
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        myFrame = new HW05E();
        myFrame.show();
    }
    
    private static JFrame myFrame;
    private JColorChooser colorChooser;
    private JPanel drawingPanel;
    private JCheckBox fillBox;
    private JComboBox shapeComboBox;
}
