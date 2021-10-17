
package drawing;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageDrawable extends FormDrawable{

	/**
	 * @param fileName
	 * @param pos
	 * @param dim
	 * @param transparence
	 */
	public ImageDrawable(Color color, Point pos, Dimension dim, float trsp, String fileName) {
		super(color, pos, dim, trsp, fileName);
		
	}

	/* (non-Javadoc)
	 * @see draw.Drawable#draw(java.awt.Graphics)
	 */
	public void draw(Graphics g) {
//        Graphics2D g2d = (Graphics2D) g.create();
		Graphics2D g2d = (Graphics2D) g;
//		Color c = g2d.getColor();
//		g2d.setColor(color);
        g2d.setComposite(java.awt.AlphaComposite.getInstance(java.awt.AlphaComposite.SRC_OVER,Math.min(trsp,1.0f)));
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        BufferedImage img = null;
        try {
            img = ImageIO.read(new File(fileName));
        } catch (IOException e) {
        }
        
        g2d.scale(2, 2);
        
        g2d.drawImage(img, rect.x, rect.y, null);
        
//        g2d.fillRect(rect.x,rect.y,rect.width,rect.height);
//		g2d.setColor(c);
	}

}
