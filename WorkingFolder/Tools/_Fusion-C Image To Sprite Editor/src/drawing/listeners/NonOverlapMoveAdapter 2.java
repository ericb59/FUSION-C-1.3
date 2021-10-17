/*
 * Created on Aug 19, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package drawing.listeners;

import java.awt.Point;
import java.awt.event.MouseEvent;

import drawing.JCanvas;
import drawing.MoveDrawableMouseListener;

/**
 * @author Sylvain
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class NonOverlapMoveAdapter extends MoveDrawableMouseListener{
	
	private Point initialLocation;

	/**
	 * @param canvas
	 */
	public NonOverlapMoveAdapter(JCanvas canvas) {
		super(canvas);
		
	}

	
	public void mouseReleased(MouseEvent e) {
		if(drawable== null) return ;
		if( !canvas.isAlone(drawable)){
			drawable.setPosition(initialLocation);

		}
		initialLocation =null;
		drawable=null;
		canvas.repaint();
	}

	/* (non-Javadoc)
	 * @see java.awt.event.MouseListener#mousePressed(java.awt.event.MouseEvent)
	 */
	public void mousePressed(MouseEvent e) {
		super.mousePressed(e);
		if(drawable!=null) {
			initialLocation=drawable.getPosition();
		}
	}

}
