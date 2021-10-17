package drawing;

import java.awt.Component;
import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JComponent;
import javax.swing.JFrame;

/**
 * @author Sylvain
 *
 * 
 */
public class GUIHelper {
	static JFrame frame;
	public static void showOnFrame(JComponent component, String frameName) {
		frame = new JFrame(frameName);
		WindowAdapter wa = new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		};
		//        frame.setSize(dim);
		frame.addWindowListener(wa);
		frame.getContentPane().add(component);
		frame.pack();

		frame.setVisible(true);
//		frame.setResizable(false);
		frame.setLocationRelativeTo(null);

	}
/*	
	public static void showOnFrame(Component component, String frameName) {
		frame = new Frame(frameName);
		WindowAdapter wa = new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		};
		//        frame.setSize(dim);
		frame.addWindowListener(wa);
		frame.add(component);
		frame.pack();

		frame.setVisible(true);
//		frame.setResizable(false);

	}
*/
}
