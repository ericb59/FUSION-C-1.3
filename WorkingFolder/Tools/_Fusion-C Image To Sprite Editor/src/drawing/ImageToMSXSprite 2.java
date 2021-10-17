package drawing;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FileDialog;
import java.awt.Image;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.Locale;
import java.util.ResourceBundle;

import javax.imageio.ImageIO;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;

/**
 * @author Sylvain
 *
 */
public class ImageToMSXSprite {
	public static float transparency = 0.6f;
	static BufferedImage bufImg = null;
	static Image imageScaled = null;
	static File imageFile = null;
	static File outFile = null;

	static Locale locale=Locale.getDefault();
	//	static Locale locale = new Locale("en", "EN");
	static ResourceBundle res = ResourceBundle.getBundle("drawing.messages", locale);
	static ResourceBundle cfg = ResourceBundle.getBundle("drawing.param", locale);

	/* caractere(s) "nouvelle ligne" en fonction du systeme */
	static String NL=System.getProperty("line.separator");

	static int posx, posy, imgw, imgh;
	/* couleur de fond ; par defaut : noir */
	static int couleurFond=0xff000000;
	static Color couleurRect=Color.RED;
	
	/* coefficient d'agrandissement de l'image ; par defaut : x2 */
	static int coef = Integer.valueOf((String)cfg.getObject("conf_magnify_default"));
	/* format des donnees de sortie ; A=assembleur, C=C */
	static char format=((String)cfg.getObject("conf_format_default")).charAt(0);

	static Point a;

	static Point positionActuelleRectangle = new Point(6+(16*coef),32+(16*coef));
	static IDrawable rect = new RectangleDrawable(couleurRect,positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
	
	static JCanvas jc = new JCanvas();
	static JLabel img=new JLabel();

	public static void main(String[] args) {

		jc.setBackground(Color.WHITE);
		jc.setPreferredSize(new Dimension(800,600));

		// Ajout gestion saisie clavier
		jc.addKeyListener(new KeyListener() {

            @Override
            public void keyTyped(KeyEvent e) {}

            @Override
            public void keyReleased(KeyEvent e) {}

            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyChar() == ' ') {
                	new DetectSpriteForm();
                }
            }
        });
		jc.setFocusable(true);
		jc.requestFocusInWindow();

		// Ajout d'une barre de menu a la fenetre
		JMenuBar barreMenu = new JMenuBar();
		setJMenuBar(barreMenu);    	
		// Creation des options du menu
		JMenu menu1 = new JMenu((String)res.getObject("text_fichier")); // bouton Fichier

		// 
		JMenuItem openFile = new JMenuItem((String)res.getObject("text_ouvrir_image")); // choix de l'image a charger    	
		menu1.add(openFile);

		JMenuItem spriteFile = new JMenuItem((String)res.getObject("text_fichier_sortie")); // choix du fichier de sortie    	
		menu1.add(spriteFile);

		// boutons de choix du grossissement de l'image
		menu1.addSeparator();
		ButtonGroup group1 = new ButtonGroup();
		JRadioButtonMenuItem rbMenuItemx1 = new JRadioButtonMenuItem("x1");
		JRadioButtonMenuItem rbMenuItemx2 = new JRadioButtonMenuItem("x2");
		JRadioButtonMenuItem rbMenuItemx4 = new JRadioButtonMenuItem("x4");
		rbMenuItemx1.setSelected(false);
		rbMenuItemx1.setMnemonic(KeyEvent.VK_1);
		group1.add(rbMenuItemx1);
		menu1.add(rbMenuItemx1);
		rbMenuItemx2.setSelected(true);
		rbMenuItemx2.setMnemonic(KeyEvent.VK_2);
		group1.add(rbMenuItemx2);
		menu1.add(rbMenuItemx2);
		rbMenuItemx4.setSelected(false);
		rbMenuItemx4.setMnemonic(KeyEvent.VK_4);
		group1.add(rbMenuItemx4);
		menu1.add(rbMenuItemx4);

		// boutons de choix du format de sortie		
		menu1.addSeparator();
		ButtonGroup group2 = new ButtonGroup();
		JRadioButtonMenuItem rbMenuItemFormatAsm = new JRadioButtonMenuItem((String)res.getObject("text_asm_format"));
		JRadioButtonMenuItem rbMenuItemFormatC = new JRadioButtonMenuItem((String)res.getObject("text_c_format"));
		rbMenuItemFormatAsm.setSelected(true);
		group2.add(rbMenuItemFormatAsm);
		menu1.add(rbMenuItemFormatAsm);
		rbMenuItemFormatC.setSelected(false);
		group2.add(rbMenuItemFormatC);
		menu1.add(rbMenuItemFormatC);

		// changer de langue pour les messages
		//		locale = new Locale("fr", "FR");
		//		locale = new Locale("en", "EN");

		// choix de la couleur du rectangle		
		menu1.addSeparator();
//		JMenuItem fChoixCouleur = new JMenuItem("couleur"); // fenetre choix couleur    	
//		menu1.add(fChoixCouleur);
		ButtonGroup group3 = new ButtonGroup();
		JRadioButtonMenuItem rbMenuItemRed = new JRadioButtonMenuItem("Red");
		JRadioButtonMenuItem rbMenuItemBlu = new JRadioButtonMenuItem("Blue");
		JRadioButtonMenuItem rbMenuItemGre = new JRadioButtonMenuItem("Green");
		JRadioButtonMenuItem rbMenuItemYel = new JRadioButtonMenuItem("Yellow");
		rbMenuItemRed.setSelected(true);
		rbMenuItemRed.setMnemonic(KeyEvent.VK_R);
		group3.add(rbMenuItemRed);
		menu1.add(rbMenuItemRed);
		rbMenuItemBlu.setSelected(false);
		rbMenuItemBlu.setMnemonic(KeyEvent.VK_B);
		group3.add(rbMenuItemBlu);
		menu1.add(rbMenuItemBlu);
		rbMenuItemGre.setSelected(false);
		rbMenuItemGre.setMnemonic(KeyEvent.VK_G);
		group3.add(rbMenuItemGre);
		menu1.add(rbMenuItemGre);
		rbMenuItemYel.setSelected(false);
		rbMenuItemYel.setMnemonic(KeyEvent.VK_Y);
		group3.add(rbMenuItemYel);
		menu1.add(rbMenuItemYel);
		
		menu1.addSeparator();
		JMenuItem aPropos = new JMenuItem((String)res.getObject("text_a_propos")); // fenetre a propos    	
		menu1.add(aPropos);

		// Quitter le programme
		JMenuItem exit = new JMenuItem((String)res.getObject("text_quitter"));
		menu1.add(exit);

		barreMenu.add(menu1);
		jc.add(barreMenu);

		jc.add(img);

		//		imageFile = new File(filename);
		outFile = new File("sprite.txt");

		//		JButton buttonLoad = new JButton("Charger image");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
/*
		fChoixCouleur.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// choix couleur
				ChoixCouleur fchoix=new ChoixCouleur();
				fchoix.setVisible(true);
				Point positionActuelleRectangle = rect.getRectangle().getLocation();
				jc.removeDrawable(rect);
				rect = new RectangleDrawable(couleurRect, positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
				jc.addDrawable(rect);

			}
		});
*/
		aPropos.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// fenetre A propos
				APropos apropos=new APropos();
				apropos.setTitle((String)res.getObject("text_a_propos"));
				apropos.setVisible(true);
			}
		});


		rbMenuItemx1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (coef!=1) {
					coef = 1;
					chargeImage(imageFile);
				}
			}
		});
		rbMenuItemx2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (coef!=2) {
					coef = 2;
					chargeImage(imageFile);
				}
			}
		});
		rbMenuItemx4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (coef!=4) {
					coef = 4;
					chargeImage(imageFile);
				}
			}
		});
		rbMenuItemFormatAsm.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (format!='A') {
					format='A';
				}
			}
		});
		rbMenuItemFormatC.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (format!='C') {
					format='C';
				}
			}
		});
		rbMenuItemRed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (couleurRect!=Color.RED) {
					couleurRect=Color.RED;
					Point positionActuelleRectangle = rect.getRectangle().getLocation();
					positionActuelleRectangle.x+=16;
					positionActuelleRectangle.y+=16;
					jc.removeDrawable(rect);
					rect = new RectangleDrawable(couleurRect, positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
					jc.addDrawable(rect);					
				}
			}
		});
		rbMenuItemBlu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (couleurRect!=Color.BLUE) {
					couleurRect=Color.BLUE;
					Point positionActuelleRectangle = rect.getRectangle().getLocation();
					positionActuelleRectangle.x+=16;
					positionActuelleRectangle.y+=16;
					jc.removeDrawable(rect);
					rect = new RectangleDrawable(couleurRect, positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
					jc.addDrawable(rect);					
				}
			}
		});
		rbMenuItemGre.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (couleurRect!=Color.GREEN) {
					couleurRect=Color.GREEN;
					Point positionActuelleRectangle = rect.getRectangle().getLocation();
					positionActuelleRectangle.x+=16;
					positionActuelleRectangle.y+=16;
					jc.removeDrawable(rect);
					rect = new RectangleDrawable(couleurRect, positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
					jc.addDrawable(rect);					
				}
			}
		});
		rbMenuItemYel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (couleurRect!=Color.YELLOW) {
					couleurRect=Color.YELLOW;
					Point positionActuelleRectangle = rect.getRectangle().getLocation();
					positionActuelleRectangle.x+=16;
					positionActuelleRectangle.y+=16;
					jc.removeDrawable(rect);
					rect = new RectangleDrawable(couleurRect, positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
					jc.addDrawable(rect);					
				}
			}
		});

		openFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				FileDialog filedialog = new FileDialog(GUIHelper.frame, (String)res.getObject("text_choix_fichier_image"), FileDialog.LOAD);
				filedialog.setDirectory("."+File.separator+"images");
				filedialog.setFilenameFilter(new FilenameFilter() {
					public boolean accept(File dir, String name) {
						if (name.startsWith(".")) return false;
						String lower = name.toLowerCase();
						return  lower.endsWith(".png") || 
								lower.endsWith(".gif");
					}
				});
				filedialog.setVisible(true);

				String filename = filedialog.getFile();
				String directory = filedialog.getDirectory();
				if (filename==null||directory==null) return;

				imageFile=new File(directory+File.separator+filename);

				chargeImage(imageFile);

			}
		});

		spriteFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				FileDialog filedialog = new FileDialog(GUIHelper.frame, (String)res.getObject("text_choix_fichier_sortie"), FileDialog.SAVE);
				filedialog.setDirectory(".");
				filedialog.setVisible(true);

				String filename = filedialog.getFile();
				String directory = filedialog.getDirectory();
				if (filename==null||directory==null) return;

				outFile=new File(directory+File.separator+filename);
			}
		});

		new MoveDrawableMouseListener(jc);
		GUIHelper.showOnFrame(jc,"MSX Image To Sprite data");
		imageFile = new File("images/spr1.png");
		chargeImage(imageFile);
	}

	public static void chargeImage(File imageFile) {
		jc.setVisible(false);
		try
		{
			// lecture du fichier image
			bufImg = ImageIO.read(imageFile);
			// ajouter le travail sur l'image ici
		} 
		catch (IOException el)
		{
			System.out.println((String)res.getObject("text_erreur") + el.getMessage());
		}	

		imgh=bufImg.getHeight()*coef;
		imgw=bufImg.getWidth()*coef;

		imageScaled = bufImg.getScaledInstance(imgw, imgh, Image.SCALE_REPLICATE);

		GUIHelper.frame.setSize(imgw+6, imgh+63);
		jc.setLocation(0, 0);
		jc.remove(img);
		Point positionActuelleRectangle = rect.getRectangle().getLocation();
		positionActuelleRectangle.x+=16;
		positionActuelleRectangle.y+=16;
		jc.removeDrawable(rect);
		//transformation de l'image
		img = new JLabel(new ImageIcon(imageScaled));
		jc.add(img);
		rect = new RectangleDrawable(couleurRect,positionActuelleRectangle, new Dimension(16*coef,16*coef), transparency);
		jc.addDrawable(rect);
		jc.setPreferredSize(new Dimension(imgw+6, imgh+63));
		jc.repaint();
		jc.setVisible(true);
		jc.setFocusable(true);
		jc.requestFocusInWindow();		
	}
	
	private static void setJMenuBar(JMenuBar barreMenu) {
		// TODO Auto-generated method stub

	}


}

