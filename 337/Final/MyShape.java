/*
 * MyShape.java
 *
 * This is a class that holds the data needed to draw a rectangle, line, oval,
 * or rounded rectangle. It has methods that are used to set the color, fill,
 * and the end points of the shape.
 *
 * @author  David Haltinner
 */

import java.awt.*;

public class MyShape {
    private String type;
    private int x;
    private int y;
    private int x2;
    private int y2;
    private Color color;
    private boolean fill;
    
    /** Creates a new instance of MyShape */
    public MyShape() {
    }
    
    /** Create a new MyShape with a specific type defined */
    public MyShape(String temp) {
        type=temp;
    }
    
    /** Set the type of shape **/
    public void setType(String temp) {
        type=temp;
    }
    
    /** This method draws the shape according to the specified options */
    public void draw(Graphics g) {
        g.setColor(color);
        if (type.equals("Line")) g.drawLine(x,y+15,x2,y2+15);
        else {
            int a,b,c,d;
            if (x<x2) {
                a=x;
                c=x2-x;
            }
            else {
                a=x2;
                c=x-x2;
            }
            if (y<y2) {
                b=y;
                d=y2-y;
            }
            else {
                b=y2;
                d=y-y2;
            }
            b+=30;  
            if (type.equals("Rectangle") && !fill) g.drawRect(a,b,c,d);
            else if (type.equals("Rounded Rectangle") && !fill) g.drawRoundRect(a,b,c,d, 10, 10);
            else if (type.equals("Oval") && !fill) g.drawOval(a,b,c,d);
            else if (type.equals("Rectangle") && fill) g.fillRect(a,b,c,d);
            else if (type.equals("Rounded Rectangle") && fill) g.fillRoundRect(a,b,c,d, 10, 10);
            else if (type.equals("Oval") && fill) g.fillOval(a,b,c,d);
        }
    }
    
    /** This method is used to set the color of the shape. */
    public void setColor(Color c) {
        color=c;
    }
    
    /** This method sets the fill state of the shape */
    public void setFill(boolean f) {
        fill=f;
    }
    
    /** This method sets the endpoints of the shape */
    public void setPoints(int a, int b, int c, int d) {
        x=a;
        y=b;
        x2=c;
        y2=d;
    }
}
