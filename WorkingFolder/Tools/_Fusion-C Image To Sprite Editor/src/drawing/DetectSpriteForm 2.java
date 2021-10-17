package drawing;

import java.io.FileWriter;

public class DetectSpriteForm {
	public DetectSpriteForm() {
		int tpx, tpy, tpxd, tpyd, pixel, i, j, jj, k;
		String[] ligne = new String[16];
		int[] sprite1 = new int[8]; 
		int[] sprite2 = new int[8]; 
		int[] sprite3 = new int[8]; 
		int[] sprite4 = new int[8]; 
//		int coef=2;
		// recalage des coordonnées du point traité par rapport au curseur
		tpx=(ImageToMSXSprite.a.x-16)/ImageToMSXSprite.coef;
		tpy=(ImageToMSXSprite.a.y-46)/ImageToMSXSprite.coef;

		// RAZ tableau de lignes
		for (i=0;i<16;i++) { ligne[i]=""; }
		tpxd=tpx;
		tpyd=tpy;

		i=0; // indice ligne (0 à 15)
		j=0; // indice colonne (0 à 15)
		jj=7; // poids du bit correspondant au point en cours (7 à 0)
		k=0; // valeur calculée d'une ligne de sprite
		// déplacement à droite jusqu'à 16 points
		// et vers le bas 16 points
		ImageToMSXSprite.bufImg.setRGB(tpx-1, tpy-1, 0xffff0000);
		do {
			pixel = ImageToMSXSprite.bufImg.getRGB(tpx, tpy);
			tpx++;
			//				if (pixel == 0xffffffff) {
			if (pixel != ImageToMSXSprite.couleurFond) {
				ligne[i]+="x";
				k+=Math.pow(2, jj);
			} else {
				ligne[i]+=" ";
			}
			//				if ((tpx-tpxd)==(8*coef)) ligne[i]+=",";
			if (jj--==0) {
				if (j<8) {
					if (i<8) { sprite1[i]=k; } else { sprite4[i-8]=k; }
				} else {
					if (i<8) { sprite3[i]=k; } else { sprite2[i-8]=k; }
				}
				jj=7;k=0;
			}
			if (tpx > tpxd + (15)) { tpx=tpxd; tpy++; i++; }
			if (j++>15) j=0;
		} while ( (tpy < tpyd+(16)) && (tpx+1 < ImageToMSXSprite.imgw) && (tpy+1 < ImageToMSXSprite.imgh) );

		if (tpx+1 >= ImageToMSXSprite.imgw ) {
			System.out.println((String)ImageToMSXSprite.res.getObject("text_bord_atteint"));
			return;
		}

		//			bufImg.setRGB(tpx, tpy, (pixel & 0xff000000) | 0x00ff0000);

		String restxt=ImageToMSXSprite.NL;

		try {
			// fichier de sortie
			//				File fs=new File("."+File.separator+"sprite.txt");
			if(ImageToMSXSprite.outFile.exists() && !ImageToMSXSprite.outFile.isDirectory()) { 
				// append
			} else {
				ImageToMSXSprite.outFile.createNewFile();
			}
			FileWriter fse=new FileWriter(ImageToMSXSprite.outFile,true);

			/* affiche les donnees sous forme de croix pour verification */
			//				System.out.println("donnees zone=>");
			for (i=0;i<16;i++) {
				if (ImageToMSXSprite.format=='A') restxt+=";";
				if (ImageToMSXSprite.format=='C') restxt+="/*";
				restxt+=ligne[i];
				if (ImageToMSXSprite.format=='A') restxt+=";";
				if (ImageToMSXSprite.format=='C') restxt+="*/";
				restxt+=ImageToMSXSprite.NL;
				//					System.out.println("; "+ligne[i]);
			}
			/* version sortie binaire */
		System.out.println("Sprite 1");
		for (i=0;i<8;i++) {
			System.out.println(String.format("%08d", Integer.parseInt(Integer.toBinaryString(sprite1[i]))));
		}
		System.out.println("Sprite 2");
		for (i=0;i<8;i++) {
			System.out.println(String.format("%08d", Integer.parseInt(Integer.toBinaryString(sprite2[i]))));
		}
		System.out.println("Sprite 3");
		for (i=0;i<8;i++) {
			System.out.println(String.format("%08d", Integer.parseInt(Integer.toBinaryString(sprite3[i]))));
		}
		System.out.println("Sprite 4");
		for (i=0;i<8;i++) {
			System.out.println(String.format("%08d", Integer.parseInt(Integer.toBinaryString(sprite4[i]))));
		}
		System.out.println("");
			/* version sortie en hexadecimal */
			if (ImageToMSXSprite.format=='A') restxt+=";";
			if (ImageToMSXSprite.format=='C') restxt+="/*";
			restxt+=(String)ImageToMSXSprite.res.getObject("text_definition");
			if (ImageToMSXSprite.format=='A') restxt+=ImageToMSXSprite.NL+".db ";
			if (ImageToMSXSprite.format=='C') restxt+="*/"+ImageToMSXSprite.NL+"   {"; 
			for (i=0;i<8;i++) {
				restxt+=String.format("0x%02X", sprite1[i]);
				//					fse.write(String.format("0x%02X", sprite1[i]));
				if (i<7) restxt+=", ";
			}
			restxt+=","+ImageToMSXSprite.NL;
			restxt+="    ";
			for (i=0;i<8;i++) {
				restxt+=String.format("0x%02X", sprite2[i]);
				if (i<7) restxt+=", ";
			}
			restxt+=","+ImageToMSXSprite.NL;
			restxt+="    ";
			for (i=0;i<8;i++) {
				restxt+=String.format("0x%02X", sprite3[i]);
				if (i<7) restxt+=", ";
			}
			restxt+=","+ImageToMSXSprite.NL;
			restxt+="    ";
			for (i=0;i<8;i++) {
				restxt+=String.format("0x%02X", sprite4[i]);
				if (i<7) restxt+=", ";
			}
			if (ImageToMSXSprite.format=='C') restxt+="}"; 
			restxt+=ImageToMSXSprite.NL;

			/* pour les tests : affiche le resultat vers la sortie standard */
			//				System.out.print(restxt);

			try {
				fse.write(restxt);
			} catch (Exception we) {}

			fse.close(); // fermer le fichier

		} catch (Exception e) {}

		ImageToMSXSprite.imageScaled.flush();

//		window.repaint();
	}
}
