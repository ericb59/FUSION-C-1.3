package drawing;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;

/**
 * @author Sylvain
 *
 * 
 */
public class CircleDrawable extends FormDrawable{

	/**
	 * @param color
	 * @param pos
	 * @param dim
	 */
	public CircleDrawable(Color color, Point pos, Dimension dim, float trsp) {
		super(color, pos, dim, trsp, "");
		
	}

	/* (non-Javadoc)
	 * @see draw.Drawable#draw(java.awt.Graphics)
	 */
	public void draw(Graphics g) {
        Graphics2D g2d = (Graphics2D) g.create();
		Color c = g2d.getColor();
		g2d.setColor(color);
        g2d.setComposite(java.awt.AlphaComposite.getInstance(java.awt.AlphaComposite.SRC_OVER,Math.min(trsp,1.0f)));
		g2d.fillOval(rect.x,rect.y,rect.width,rect.height);
		g2d.setColor(c);
	}

}
