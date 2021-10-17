package drawing;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class ChoixCouleur extends JFrame {
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public ChoixCouleur() {
		this.setLayout(new BorderLayout());
		this.setSize(460,380);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setLocationRelativeTo(null); // centre la fenetre dans l'ecran

        JLabel banner = new JLabel("Hello!", JLabel.CENTER);
        banner.setForeground(Color.yellow);
        JColorChooser tcc = new JColorChooser(banner.getForeground());
        add(tcc, BorderLayout.PAGE_END);
        JButton setColor = new JButton("Set Color");
        add(setColor);
        this.setVisible(true);

        setColor.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
		        ImageToMSXSprite.couleurRect = tcc.getColor();
			}
		});

    }
}
