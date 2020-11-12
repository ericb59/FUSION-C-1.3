package SpritePath;

import java.awt.BorderLayout;
import java.awt.Font;
import java.util.Locale;
import java.util.ResourceBundle;

//import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextArea;

public class APropos extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public APropos(){
		// fenetre A propos
		Locale locale=Locale.getDefault();
		ResourceBundle res = ResourceBundle.getBundle("SpritePath.messages", locale);
		
		String NL=System.getProperty("line.separator");
		
		this.setLayout(new BorderLayout());
		this.setSize(460,340);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        this.setLocationRelativeTo(null); // centre la fenetre dans l'ecran

        JTextArea textArea = new JTextArea( NL +
        		(String)res.getObject("text_apropos1") + NL + NL +
        		(String)res.getObject("text_apropos2") + NL + NL +
        		(String)res.getObject("text_apropos3") + NL + NL +
        		(String)res.getObject("text_apropos4") + NL + NL +
        		(String)res.getObject("text_apropos5") + NL + NL +
        		(String)res.getObject("text_apropos6")
        	);
        textArea.setFont(new Font("Serif", Font.PLAIN, 14));
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        textArea.setEditable(false);
        textArea.setVisible(true);

        this.add(textArea);
/*        
        JButton buttonLoad = new JButton((String)res.getObject("text_fermer"));
        buttonLoad.setBounds(40, 170, 120, 30);
        this.add(buttonLoad);
*/
//        pack(); //permet de mettre une bonne dimension a la fenetre  
        
		}
}
