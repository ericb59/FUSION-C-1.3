package SpritePath;

import java.awt.Color;
import java.awt.Cursor;
import java.awt.FileDialog;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.Locale;
import java.util.ResourceBundle;

import javax.imageio.ImageIO;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;

enum Codes_Retour
{ INCONNU, KO, OK };

public class SpritePath extends JPanel implements MouseListener, MouseMotionListener{

	/**
	 * This tool allows you to create sprite path for MSX system (256 x 212 px), in absolute or relative coordinates.
	 * The result is in the form of a text file containing a table in C language format.
	 */
	private static final long serialVersionUID = 1L;

	static Locale locale=Locale.getDefault();
	//	static Locale locale = new Locale("en", "EN");

	static ResourceBundle res = ResourceBundle.getBundle("SpritePath.messages", locale);
	static ResourceBundle cfg = ResourceBundle.getBundle("SpritePath.param", locale);

	JFrame window = new JFrame("MSX Sprite Path");
	private static JLabel label0 = new JLabel("Image");

	static BufferedImage bufImg = null;
	Image imageScaled = null;
	JLabel img=new JLabel();

	/* caractere(s) "nouvelle ligne" en fonction du systeme */
	String NL=System.getProperty("line.separator");

	private int posx, posy, imgw, imgh;
	File imageFile = null;
	File outFile = null;
	String ofile="path.txt";
	String odir=".";

	private int buttonClicked;
	
	/* curseur fleche */
	Cursor curseurDefaut = new Cursor(Cursor.DEFAULT_CURSOR);
	/* curseur fleche */
	Cursor curseurCroix = new Cursor(Cursor.CROSSHAIR_CURSOR);
	/* rectangle correspondant au menu pour affichier le curseur fleche */
	Rectangle cellBounds = new Rectangle(0,31,0,0);
	/* couleur de fond ; par defaut : noir */
	private int couleurFond=0xff000000;
	/* couleur du point ; par defaut : bleue */
	static Color couleurPoint=Color.BLUE;
	/* coefficient d'agrandissement de l'image ; par defaut : x2 */
	int coef = Integer.valueOf((String)cfg.getObject("conf_magnify_default"));
	/* coordonnees absolues : A ou relatives : R */
	char format=((String)cfg.getObject("conf_format_default")).charAt(0);

	int maxpt= 54272;
	int crdx[] = new int[maxpt];
	int crdy[] = new int[maxpt];
	int nbpt=0;
	int mdx=1,mdy=37;
	public SpritePath(String filename) throws Exception {
		crdx[0]=0;
		crdy[0]=0;

		// Ajout d'une barre de menu a la fenetre
		JMenuBar barreMenu = new JMenuBar();
		setJMenuBar(barreMenu);    	
		// Creation des options du menu
		JMenu menu1 = new JMenu((String)res.getObject("text_fichier"));
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
		JRadioButtonMenuItem rbMenuItemFormatAbs = new JRadioButtonMenuItem((String)res.getObject("text_abs_format"));
		JRadioButtonMenuItem rbMenuItemFormatRel = new JRadioButtonMenuItem((String)res.getObject("text_rel_format"));
		JRadioButtonMenuItem rbMenuItemFormatCmp = new JRadioButtonMenuItem((String)res.getObject("text_cmp_format"));
		rbMenuItemFormatAbs.setSelected(true);
		group2.add(rbMenuItemFormatAbs);
		menu1.add(rbMenuItemFormatAbs);
		rbMenuItemFormatRel.setSelected(false);
		group2.add(rbMenuItemFormatRel);
		menu1.add(rbMenuItemFormatRel);
		rbMenuItemFormatCmp.setSelected(false);
		group2.add(rbMenuItemFormatCmp);
		menu1.add(rbMenuItemFormatCmp);

		// changer de langue pour les messages
		//		locale = new Locale("fr", "FR");
		//		locale = new Locale("en", "EN");

		// choix de la couleur du point		
		menu1.addSeparator();
		ButtonGroup group3 = new ButtonGroup();
		JRadioButtonMenuItem rbMenuItemWht = new JRadioButtonMenuItem((String)res.getObject("text_white"));
		JRadioButtonMenuItem rbMenuItemBlk = new JRadioButtonMenuItem((String)res.getObject("text_black"));
		JRadioButtonMenuItem rbMenuItemRed = new JRadioButtonMenuItem((String)res.getObject("text_red"));
		JRadioButtonMenuItem rbMenuItemBlu = new JRadioButtonMenuItem((String)res.getObject("text_blue"));
		JRadioButtonMenuItem rbMenuItemGre = new JRadioButtonMenuItem((String)res.getObject("text_green"));
		JRadioButtonMenuItem rbMenuItemYel = new JRadioButtonMenuItem((String)res.getObject("text_yellow"));
		rbMenuItemWht.setSelected(false);
		rbMenuItemWht.setMnemonic(KeyEvent.VK_W);
		group3.add(rbMenuItemWht);
		menu1.add(rbMenuItemWht);
		rbMenuItemBlk.setSelected(false);
		rbMenuItemBlk.setMnemonic(KeyEvent.VK_D);
		group3.add(rbMenuItemBlk);
		menu1.add(rbMenuItemBlk);
		rbMenuItemRed.setSelected(false);
		rbMenuItemRed.setMnemonic(KeyEvent.VK_R);
		group3.add(rbMenuItemRed);
		menu1.add(rbMenuItemRed);
		rbMenuItemBlu.setSelected(true);
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

		JButton sauve=new JButton((String)res.getObject("text_sauve"));
		JButton vide=new JButton((String)res.getObject("text_vide"));

		this.add(barreMenu);
		this.add(sauve);
		this.add(vide);

		this.add(img);

		imageFile = new File(filename);
		outFile = new File(ofile);

		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});

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
					window.setVisible(false);
					chargeImage(imageFile);
					//					curseurCadre = curseurCadre_x1;
					window.setVisible(true);

				}
			}
		});
		rbMenuItemx2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (coef!=2) {
					coef = 2;
					window.setVisible(false);
					chargeImage(imageFile);
					//					curseurCadre = curseurCadre_x2;
					window.setVisible(true);
				}
			}
		});
		rbMenuItemx4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (coef!=4) {
					coef = 4;
					window.setVisible(false);
					chargeImage(imageFile);
					//					curseurCadre = curseurCadre_x4;
					window.setVisible(true);
				}
			}
		});

		rbMenuItemFormatAbs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (format!='A') {
					format='A';
				}
			}
		});
		rbMenuItemFormatRel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (format!='R') {
					format='R';
				}
			}
		});
		rbMenuItemFormatCmp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (format!='C') {
					format='C';
				}
			}
		});

		rbMenuItemWht.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.WHITE;
			}
		});
		rbMenuItemBlk.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.BLACK;
			}
		});
		rbMenuItemRed.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.RED;
			}
		});
		rbMenuItemBlu.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.BLUE;
			}
		});
		rbMenuItemGre.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.GREEN;
			}
		});
		rbMenuItemYel.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				couleurPoint=Color.YELLOW;
			}
		});

		openFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				FileDialog filedialog = new FileDialog(window, (String)res.getObject("text_choix_fichier_image"), FileDialog.LOAD);
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

				window.setVisible(false);

				try {
					loadimage(imageFile);
				} catch (Exception ex) {
					error(ex.getMessage(),ex);
				}
				window.setVisible(true);

				chargeImage(imageFile);
			}
		});

		spriteFile.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {

				FileDialog filedialog = new FileDialog(window, (String)res.getObject("text_choix_fichier_sortie"), FileDialog.SAVE);
				filedialog.setDirectory(".");
				filedialog.setVisible(true);

				ofile = filedialog.getFile();
				odir = filedialog.getDirectory();
				if (ofile==null||odir==null) return;

				outFile=new File(odir+File.separator+ofile);
			}
		});

		sauve.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				//				System.out.println("Sauve dans "+odir+File.separator+ofile);
				String restxt="";
				if (nbpt>0) {
					restxt+=NL+"{";
					// format absolu
					if (format=='A') {
						for (int i=1; i<=nbpt; i++ ) {
							restxt+=Integer.toString(crdx[i])+","+Integer.toString(crdy[i]);
							if (i<(nbpt)) restxt+=",";
						}
					}
					// format relatif
					if (format=='R'||format=='C') {
						int dx=0,dy=0;
						char ad;
						restxt+=Integer.toString(crdx[1])+","+Integer.toString(crdy[1])+"}"+NL;
						//						restxt+="{0,0,";
						restxt+="{";
						for (int i=2; i<=nbpt; i++ ) {
							dx=crdx[i]-crdx[i-1];
							dy=crdy[i]-crdy[i-1];
							ad=0;
							if (dx>-8 && dx<8) {if(dx<0) ad=(char)((-dx*2)+1); else ad=(char)(dx*2);}
							if (dy>-8 && dy<8) {if(dy<0) ad=(char) (ad+((-dy*2)+1)*16); else ad=(char) (ad+((dy)*32));}
							if(format=='R') restxt+=Integer.toString(dx)+","+Integer.toString(dy);
							if(format=='C') restxt+=String.format("0x%02X", (int)ad);
							if (i<(nbpt)) restxt+=",";
						}
					}
					restxt+="}"+NL;
					restxt+=Integer.toString(nbpt)+NL;
					try {
						FileWriter fse=new FileWriter(outFile,true);
						fse.write(restxt);
						fse.close();
					} catch (Exception we) {}
				}
			}  
		});  		
		//		System.out.println(locale.getDisplayLanguage());

		vide.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				nbpt=0;
			}
		});

		window.setResizable(false);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// charge l'image par defaut
		chargeImage(imageFile);

		window.setContentPane(this);
		window.setVisible(true);

		/*
        try { window.setCursor(curseurCadre); }
        catch(Exception e){}
		 */	
		this.addMouseListener(this);
		this.addMouseMotionListener(this);        

	}

	public void printPixelARGB(int pixel, int px, int py) {
		int alpha = (pixel >> 24) & 0xff;
		int red = (pixel >> 16) & 0xff;
		int green = (pixel >> 8) & 0xff;
		int blue = (pixel) & 0xff;
		System.out.println("argb: " + alpha + ", " + red + ", " + green + ", " + blue + " pt: " + px + " " + py);
	}

	// Dessine chemin
	final Runnable dessineChemin = new Runnable() {
		@Override
		public void run() {
			int tpx, tpy;

			// recalage des coordonnees du point traite par rapport au curseur
			tpx=(posx-mdx)/coef;
			tpy=(posy-mdy)/coef;

			if (tpx>=0 && tpx<=255 && tpy>=0 && tpy<=212) {
				// enregistrement dans le tableau
				if (!(crdx[nbpt]==tpx && crdy[nbpt]==tpy) && nbpt<maxpt) {
					//					System.out.println("coords: " + tpx + "," + tpy);
					bufImg.setRGB(tpx, tpy, couleurPoint.getRGB());
					imageScaled.flush();
					window.repaint();
					nbpt++;
					crdx[nbpt]=tpx;
					crdy[nbpt]=tpy;
				}
			}
		}
	};

	// choix de la couleur du fond
	final Runnable suppressionPoint = new Runnable() {
		@Override
		public void run() {
			int tpx, tpy;
			tpx=(posx-mdx)/coef;
			tpy=(posy-mdy)/coef;
			if (nbpt>0) {
				tpx=crdx[nbpt];
				tpy=crdy[nbpt];
				crdx[nbpt]=0;
				crdy[nbpt]=0;
				nbpt--;
				bufImg.setRGB(tpx, tpy, 0);
				imageScaled.flush();
				window.repaint();
//				System.out.println("coords: " + tpx + "," + tpy);
			}
		}
	};

	public static void main(String args[]) throws Exception{
		String imgPath = (String)cfg.getObject("conf_image_sprite_default");
		new SpritePath(imgPath);
	}

	private static void setJMenuBar(JMenuBar barreMenu) {
		// TODO Auto-generated method stub

	}

	private static void loadimage(File file) throws IOException {
		label0.setIcon( null );
		bufImg = ImageIO.read( file );
		if (bufImg!=null) label0.setIcon( new ImageIcon(bufImg) );
	}

	private static void error(String text, Exception ex) {
		if (ex!=null) {
			StringWriter sw = new StringWriter();
			PrintWriter pw = new PrintWriter(sw);
			ex.printStackTrace(pw);
			String s = sw.toString();
			s = s.substring(0,Math.min(512,s.length()));
			text = text + "\n\n" + s +" (...)";
		}
		JOptionPane.showMessageDialog(null,
				text,
				(String)res.getObject("text_erreur"),
				JOptionPane.ERROR_MESSAGE
				);
	}

	@Override
	public void mouseClicked(MouseEvent me) {
		posx=me.getX();
		posy=me.getY();

		buttonClicked = me.getButton();

		if (buttonClicked == MouseEvent.BUTTON1) {
			// Bouton GAUCHE
			if (cellBounds != null && cellBounds.contains(posx, posy-5)) {
				new Thread(dessineChemin).start();
			}
		} else if(buttonClicked == MouseEvent.BUTTON2) {
			// Bouton du MILIEU
		} else if(buttonClicked == MouseEvent.BUTTON3) {
			// Bouton DROIT
			if (posy>6) {
				new Thread(suppressionPoint).start();
			}
		}		

	}

	@Override
	public void mouseDragged(MouseEvent me) {
		posx=me.getX();
		posy=me.getY();

		int tpx=(posx-mdx)/coef;
		int tpy=(posy-mdy)/coef;

		if (buttonClicked == MouseEvent.BUTTON1) {
			if (cellBounds != null && cellBounds.contains(posx, posy-5)) {
				if (!(crdx[nbpt]==tpx && crdy[nbpt]==tpy) && nbpt<maxpt) {
					//				System.out.println("coords: " + tpx + "," + tpy);
					bufImg.setRGB(tpx, tpy, couleurPoint.getRGB());
					imageScaled.flush();
					window.repaint();
					nbpt++;
					crdx[nbpt]=tpx;
					crdy[nbpt]=tpy;
				}
			}
		}
		/*		
		if (cellBounds != null && cellBounds.contains(posx, posy)) {
			window.setCursor(curseurCroix);
		} else {
			window.setCursor(curseurDefaut);
		}		
		 */
		//		System.out.println("mouseDragged: " + posx + "," + posy);
	}

	@Override
	public void mouseMoved(MouseEvent me) {
		final int x = me.getX();
		final int y = me.getY();
		/* modifie la forme du curseur en fonction de la zone survolee */
		if (cellBounds != null && cellBounds.contains(x, y-5)) {
			window.setCursor(curseurCroix);
		} else {
			window.setCursor(curseurDefaut);
		}		
	}

	@Override
	public void mousePressed(MouseEvent me) {
		buttonClicked = me.getButton();
	}

	@Override
	public void mouseReleased(MouseEvent me) {
	}

	@Override
	public void mouseEntered(MouseEvent me) {
	}

	@Override
	public void mouseExited(MouseEvent me) {
	}

	public void chargeImage(File imageFile) {
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

		// Affichage de la fenetre
		//        window.setSize(imgw+2, imgh+20);
		window.setSize(imgw+6, imgh+63); // determine la taille de la fenetre
		//		window.setResizable(false); // pas de redimensionnement possible
		//		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		window.setLocationRelativeTo(null); // centre la fenetre dans l'ecran

		cellBounds.height=imgh;
		cellBounds.width=imgw;

		this.remove(img);
		//transformation de l'image
		img = new JLabel(new ImageIcon(imageScaled));
		this.add(img);
		//		window.repaint();
		//		window.setContentPane(this);
		window.setVisible(true);		
	}

}