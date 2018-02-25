/*
 * HW05A.java
 *
 * @author  David Haltinner
 *
 * This program creates a jPanel inside of a JFrame that allows rectangles to
 * be drawn with mouse movements. A corner will be placed where the mouse is
 * clicked, and the other corner will be where the mouse button is released.
 */
import java.awt.*;
import java.util.LinkedList;
import javax.swing.*;
public class HW05A extends JFrame {
    private int x;
    private int y;
    LinkedList rectangles=new LinkedList();
    
    /** Creates new form HW05A */
    public HW05A() {
        initComponents();
        setSize(300,300);
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     */
    private void initComponents() {
        drawingPanel = new JPanel();

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

        getContentPane().add(drawingPanel);
        drawingPanel.setBounds(0, 0, 400, 300);

        pack();
    }
    
    /**
     * This method draws the rectangle from the previos clicked position to the current mouse position.
     */
    private void drawingPanelMouseReleased(java.awt.event.MouseEvent evt) {
        Rectangle r;
        if (x<evt.getX() && y<evt.getY())
            r=new Rectangle(x,y+20,evt.getX()-x, evt.getY()-y);
        else if (x<evt.getX() && y>evt.getY())
            r=new Rectangle(x,evt.getY()+20,evt.getX()-x, y-evt.getY());
        else if (x>evt.getX() && y<evt.getY())
            r=new Rectangle(evt.getX(),y+20,x-evt.getX(), evt.getY()-y);
        else if (x>evt.getX() && y>evt.getY())
            r=new Rectangle(evt.getX(),evt.getY()+20,x-evt.getX(), y-evt.getY());
        else r=new Rectangle();
        rectangles.add(r);
        repaint();
    }

    /**
     * The paint method draws out the rectangles.
     */    
    public void paint(Graphics g) {
        if (!drawingPanel.getSize().equals(myFrame.getSize())) drawingPanel.setSize(myFrame.getSize());
        super.paint(g);
        for (int i=0; i<rectangles.size(); i++)
            g.drawRect((int)((Rectangle)rectangles.get(i)).getX(), (int)((Rectangle)rectangles.get(i)).getY(), (int)((Rectangle)rectangles.get(i)).getWidth(), (int)((Rectangle)rectangles.get(i)).getHeight());
    }

    /**
     * This methid records the current mouse position in order to draw it when the mouse is released.
     */
    private void drawingPanelMousePressed(java.awt.event.MouseEvent evt) {
        x=evt.getX();
        y=evt.getY();
    }
    
    /** Exit the Application */
    private void exitForm(java.awt.event.WindowEvent evt) {
        System.exit(0);
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        myFrame = new HW05A();
        myFrame.show();
    }
    private static JFrame myFrame;
    private JPanel drawingPanel;
}
