
package drawing;
import java.awt.*;

public abstract class FormDrawable implements IMovableDrawable {
	
	protected Rectangle rect ;
	protected Color color;
	protected float trsp;
	protected String fileName;
	
	/**
	 * @param color the color of this form
	 * @param pos the coordinate of the center this form
	 * @param dim the dimension of this form
	 */
	public FormDrawable(Color color, Point pos, Dimension dim, float transparency, String fileName){
		this.color=color;
		this.rect = new Rectangle(dim);
		this.trsp = transparency;
		this.fileName = fileName;
		setPosition(pos);
	}
	
	public abstract void draw(Graphics g) ;
	
	public Rectangle getRectangle(){
		return (Rectangle) rect.clone();
	}

	public Point getPosition() {
		Point p = rect.getLocation();
		p.x = (p.x+rect.width/2);
		p.y = (p.y+rect.height/2);
		return p;
	}
	
	public void setPosition(Point p) {
		rect.x = (p.x-rect.width/2);
		rect.y = (p.y-rect.height/2);
	}

}
