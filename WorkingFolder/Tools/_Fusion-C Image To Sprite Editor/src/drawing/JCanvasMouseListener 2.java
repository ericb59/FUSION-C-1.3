
package drawing;

import java.awt.event.*;

import javax.swing.SwingUtilities;

/**
 * 
 * @author Sylvain
 * @version
 */
public class JCanvasMouseListener extends MouseAdapter 
		 {
	protected JCanvas canvas;

	public JCanvasMouseListener(JCanvas canvas) {
		super();
		this.canvas = canvas;
		canvas.addMouseListener(this);
	}
		
	public JCanvas getCanvas() {
		return canvas;
	}

	public void mouseClicked(MouseEvent e) {
		
		if (SwingUtilities.isLeftMouseButton(e)) {
			leftClickAction(e);

		} else {
			rightClickAction(e);
		}
	}

	

	

		

	/**
	 * @pre: @post:
	 */
	protected void rightClickAction(MouseEvent e) {

	}

	/**
	 * @pre: @post:
	 */
	protected void leftClickAction(MouseEvent e) {
		
	}



	

}