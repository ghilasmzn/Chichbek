#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <MLV/MLV_all.h>


int menu(){
  int largeur = 1000, longueur = 700 ;
 
  MLV_Image *menufond,*nouvelle,*reprendre,*scores,*nouvelle_enf,*reprendre_enf,*scores_enf;
  MLV_create_window( "CHICHBEK", "image", largeur, longueur );
  menufond=MLV_load_image("menu_fond.jpg");
  nouvelle=MLV_load_image("nouvelle_partie.jpg");
  reprendre=MLV_load_image("reprendre_partie.jpg");
  scores=MLV_load_image("meilleurs_scores.jpg");
  nouvelle_enf=MLV_load_image("nouvelle_partie_enfonce.jpg");
  reprendre_enf=MLV_load_image("reprendre_partie_enfonce.jpg");
  scores_enf=MLV_load_image("meilleurs_scores_enfonce.jpg");
  MLV_draw_image( menufond, 0, 0);
  MLV_draw_image( nouvelle, 415, 250);
  MLV_draw_image( reprendre, 415, 350);
  MLV_draw_image( scores, 415, 450);
 
  MLV_actualise_window();
  while( 1 ){
                int x,y;
                MLV_get_mouse_position( &x, &y );
                if((x>=415 && x<=585) && (y>=250 && y<=290)){
		  MLV_draw_image( nouvelle_enf, 415, 250);
		}
	        if(!((x>=415 && x<=585) && (y>=250 && y<=290))){
		  MLV_draw_image( nouvelle, 415, 250);
		}
		if((x>=415 && x<=585) && (y>=350 && y<=390)){
		  MLV_draw_image( reprendre_enf, 415, 350);
		}
	        if(!((x>=415 && x<=585) && (y>=350 && y<=390))){
		  MLV_draw_image( reprendre, 415, 350);
		}
		if((x>=415 && x<=585) && (y>=450 && y<=490)){
		  MLV_draw_image( scores_enf, 415, 450);
		}
	        if(!((x>=415 && x<=585) && (y>=450 && y<=490))){
		  MLV_draw_image( scores, 415, 450);
		}


		if( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED ){
		  MLV_get_mouse_position( &x, &y );
                if((x>=415 && x<=585) && (y>=250 && y<=290)){
		  return 1;
		}
	        
		
		if((x>=415 && x<=585) && (y>=350 && y<=390)){
		  return 2;
		}
	        
		if((x>=415 && x<=585) && (y>=450 && y<=490)){
		  return 3;
		}
	        
		}
                                        //
                // On récupère puis affiche l'état du bouton gauche de la souris.
                //
                
                //
                // On met à jour l'affichage.
                //
                MLV_actualise_window();
        }
  return 0;

}

  
  
  
  
