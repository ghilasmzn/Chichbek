#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "graphics.h"

//Typedef
typedef enum { ROUGE,VERT,JAUNE,BLEU } couleur;
typedef struct cheval {
  int avancement;
  int x; //position
  int y;
}cheval;

typedef struct joueur {
  couleur couleur;
  cheval cj1;
  cheval cj2;
  int ecurie;
  int pg;
}joueur;

//Fonctions

void initialiser_ecurie(joueur* j){ 
  switch ((*j).couleur)
    {case JAUNE: (*j).cj1.x=5; (*j).cj1.y=5; (*j).cj2.x=2; (*j).cj2.y=2;break;
    case BLEU: (*j).cj1.x=14; (*j).cj1.y=5; (*j).cj2.x=11; (*j).cj2.y=2; break;
    case ROUGE: (*j).cj1.x=14; (*j).cj1.y=14; (*j).cj2.x=11; (*j).cj2.y=11; break;
    case VERT: (*j).cj1.x=5; (*j).cj1.y=14; (*j).cj2.x=2; (*j).cj2.y=11; break;
    }
  }

int est_dans_ecurie(cheval* c){ // elle renvoie 0 si un cheval est dans son écurie, 1 sinon.
  if( ((*c).x==5 && (*c).y==5) || ((*c).x==2 && (*c).y==2) ){
	return 0;
  }
  else if( ((*c).x==14 && (*c).y==5) || ((*c).x==11 && (*c).y==2) ){
	return 0;
  }
  else if( ((*c).x==14 && (*c).y==14) || ((*c).x==11 && (*c).y==11) ){
	return 0;
      }
  else if( ((*c).x==5 && (*c).y==14) || ((*c).x==2 && (*c).y==11) ){
	  return 0;
  }
  else{
	return 1;
      }
     
}

  
void retour_ecurie(cheval* c,joueur* j){ //cette fonction remets un cheval dans son écurie.
  if ((*j).ecurie==1){
    switch ((*j).couleur)
      {case JAUNE: (*c).x=5; (*c).y=5; break;
      case BLEU: (*c).x=14; (*c).y=5; break;
      case ROUGE: (*c).x=14; (*c).y=14; break;
      case VERT: (*c).x=5; (*c).y=14; break;
      }
    (*j).ecurie++;
    (*c).avancement=0;
  }
  else if ((*j).ecurie==0){
    switch ((*j).couleur)
      {case JAUNE:(*c).x=2; (*c).y=2; break;
      case BLEU: (*c).x=11; (*c).y=2; break;
      case ROUGE: (*c).x=11; (*c).y=11; break;
      case VERT: (*c).x=2; (*c).y=11; break;
      }
    (*j).ecurie++;
    (*c).avancement=0;
  }
} 

void avancer_cheval(cheval* c, int nb_cases){
  //cette fonction fait avancer un cheval case par case en prenant en compte tous les cas possibles sur notre plateau.
  int i=0;
 if((*c).avancement+nb_cases <= 62)
   for (i=0;i<nb_cases;i++){
	
	// déplacement du cheval  dans le sens des aiguilles d'une montre.
	if((*c).avancement <55){ //56 est le nombre de case dans le tableau.
	  (*c).avancement++;
	  if(((*c).y==7) &&((*c).x<7))
	    {(*c).x++;}
	  else if(((*c).y<=7) && ((*c).y>1) && ((*c).x==7))
	    {(*c).y--;}
	  else if(((*c).y==1) && ((*c).x>=7) && ((*c).x<9))
	    {(*c).x++;}	
	  else if(((*c).y<7) && ((*c).x==9))
	    {(*c).y++;}
	  else if(((*c).y==7)&&((*c).x>=9)&&((*c).x<15))
	{(*c).x++;}
      else if(((*c).y>=7)&&((*c).y<9) &&((*c).x==15))
	{(*c).y++;}
      else if(((*c).y==9) &&((*c).x>9) && ((*c).x<=15))
	{(*c).x--;}
      else if(((*c).y>=9) &&((*c).y<15) && ((*c).x==9))
	{(*c).y++;}
      else if(((*c).y==15) &&((*c).x<=9)&&((*c).x>7))
	{(*c).x--;}
      else if(((*c).y>9) &&((*c).y<=15)&&((*c).x==7))
	{(*c).y--;}
      else if(((*c).y==9) && ((*c).x<=7) && ((*c).x>1))
	{(*c).x--;}
      else if(((*c).y>7) &&((*c).y<=9)&&((*c).x==1))
	{(*c).y--;}
    
	}
  
	else{
    (*c).avancement++;
    // dans ce cas le cheval a fait un tour complet et il peut donc commencer à grimper l'échelle.
    if(((*c).x>=1)&&((*c).x<=7)&&((*c).y==8))
	{(*c).x++;}
    else if (((*c).x==8)&& ((*c).y>=1) && ((*c).y<=7))
      {(*c).y++;}	
    else if (((*c).x<=15) && ((*c).x>=9) && ((*c).y==8))
      {(*c).x--;}
    else if (((*c).x==8)&& ((*c).y<=15) && ((*c).y>=9))
      {(*c).y--;}
	}}
}


int cheval_est_sur_depart(joueur* j){ // cette fonction renvoie 0 si un cheval vient tout juste de sortir, 1 sinon.

  if (((*j).couleur==JAUNE) && ((*j).cj1.x==1 && (*j).cj1.y==7)){
      return 1;
    }
  else if (((*j).couleur==BLEU) && ((*j).cj1.x==9 && (*j).cj1.y==1)){
      return 1;
    }
  else if( ((*j).couleur==ROUGE) && ((*j).cj1.x==15 && (*j).cj1.y==9)){
    return 1;
    }
  else if (((*j).couleur==VERT) && ((*j).cj1.x==7 && (*j).cj1.y==15) ){
      return 1;
    }
  
  else if (((*j).couleur==JAUNE) && ((*j).cj2.x==1 && (*j).cj2.y==7)){
      return 2;
    }
  else if (((*j).couleur==BLEU) && ((*j).cj2.x==9 && (*j).cj2.y==1)){
      return 2;
    }
  else if( ((*j).couleur==ROUGE) && ((*j).cj2.x==15 && (*j).cj2.y==9)){
      return 2;
    }
  else if (((*j).couleur==VERT) && ((*j).cj2.x==7 && (*j).cj2.y==15) ){
      return 2;
    }
  return 0;
}


void sortir_cheval(cheval* c,joueur* j){ // cette fonction place un cheval sur la case de départ qui lui correspond
  if ((*j).couleur==JAUNE){
    (*c).x=1;
    (*c).y=7;}
  else if ((*j).couleur==BLEU){
    (*c).x=9;
    (*c).y=1;}
  else if ((*j).couleur==ROUGE){
    (*c).x=15;
    (*c).y=9;}
  else if ((*j).couleur==VERT){
    (*c).x=7;
    (*c).y=15;}
  (*j).ecurie--;
}

int choix_user2(joueur* j){
  // on appelle cette fonction lorsque le joueur obtient un 6 au lancer , a un cheval sur le plateau et un autre dans son écurie.
  int x1=0,y1=0,t=0;
  while(!((x1>=765 && x1<=894 && y1>=550 && y1<=589) || (x1>=765 && x1<=894 && y1>=620 && y1<=659))){
    MLV_wait_mouse(&x1, &y1);
  }
  if(x1>=765 && x1<=894 && y1>=550 && y1<=589 ){ //si l'utilisateur appuie sur avancer cheval.
    t=est_dans_ecurie(&j->cj1);
   
    if(t==0){ // si le cheval 1 est encore dans l'écurie :
      avancer_cheval(&j->cj2,6);
      return 0;} // alors on avance le cheval 2.
    
    t=est_dans_ecurie(&j->cj2);
    if (t==0){ // si le cheval 2 est encore dans l'écurie :
      avancer_cheval(&j->cj1,6);
      return 0;} // alors on avance le cheval 1.
  }
  else if(x1>=765 && x1<=894 && y1>=620 && y1<=659 ){ //si l'utilisateur appuie sur sortir cheval:
    t=est_dans_ecurie(&j->cj1); //si le cheval 1 est dans l'écurie:
    if(t==0){
      if ((*j).couleur==JAUNE){ // alors on sort le cheval 1 ( tout dépend de la couleur du joueur ).
       (*j).cj1.x=1;
       (*j).cj1.y=7;
      }
     else if ((*j).couleur==BLEU){
       (*j).cj1.x=9;
       (*j).cj1.y=1;
     }
     else if ((*j).couleur==ROUGE){
       (*j).cj1.x=15;
       (*j).cj1.y=9;
     }
     else if ((*j).couleur==VERT){
       (*j).cj1.x=7;
       (*j).cj1.y=15;
       }
     (*j).ecurie--;
    }
    t=est_dans_ecurie(&j->cj2); // si le cheval 2 est dans l'écurie
      if (t==0){
	if ((*j).couleur==JAUNE){ // alors on sort le cheval 2 ( tout dépend de la couleur du joueur )
	(*j).cj2.x=1;
	(*j).cj2.y=7;
	}
     else if ((*j).couleur==BLEU){
       (*j).cj2.x=9;
       (*j).cj2.y=1;
        }
     else if ((*j).couleur==ROUGE){
       (*j).cj2.x=15;
       (*j).cj2.y=9;
        }
     else if ((*j).couleur==VERT){
       (*j).cj2.x=7;
       (*j).cj2.y=15;
   }
	(*j).ecurie--;
	return 0;
      
    }
  }
  return (-1);
}

int choix_user3(joueur* j,int l){
  // quand les deux chevaux sont sur le plateau ( écurie =0) , on laisse le choix à l'utilisateur de désigner le cheval qu'il veut avancer.
  int x1=0,y1=0;
  double c1x=0,c1y=0,c2x=0,c2y=0;
  cheval horse1,horse2;
  // on récupère les coordonnées de nos deux chevaux.
  c1x=(j->cj1.x)*42.3; 
  c1y=(j->cj1.y)*42.3;
  c2x=(j->cj2.x)*42.3;
  c2y=(j->cj2.y)*42.3;

  horse1.x=(j->cj1.x);
  horse1.y=(j->cj1.y);
  horse2.x=(j->cj2.x);
  horse2.y=(j->cj2.y);
  horse1.avancement=j->cj1.avancement;
  horse2.avancement=j->cj2.avancement;
  // pour vérifier que 2 chevaux d'un seul et même joueur  ne s'empileront pas sur la même case après le lancer du dé.
  if(horse1.avancement<horse2.avancement){
    avancer_cheval(&horse1,l);
    if(horse1.x==horse2.x && horse1.y==horse2.y){
    avancer_cheval(&j->cj2,l);
    return 0;
    }}
  else if (horse1.avancement>horse2.avancement){
    avancer_cheval(&horse2,l);
    if(horse1.x==horse2.x && horse1.y==horse2.y){
    avancer_cheval(&j->cj1,l);
    return 0;
    }}

  while(!((x1>=c1x && x1<=(c1x+42.3) && y1>=c1y && y1<=(c1y+42.3)) || (x1>=c2x && x1<=(c2x+42.3) && y1>=c2y && y1<=(c2y+42.3)))){
    MLV_wait_mouse(&x1, &y1); // on attends le clic de l'utilisateur sur un des deux chevaux
  }
  if(x1>=c1x && x1<=(c1x+42.3) && y1>=c1y && y1<=(c1y+42.3) ){ //si l'utilisateur clique sur le cheval 1:
    avancer_cheval(&j->cj1,l);
    return 0; } //alors on avance le cheval 1 
  else if(x1>=c2x && x1<=(c2x+42.3) && y1>=c2y && y1<=(c2y+42.3) ){ //si l'utilisateur clique sur le cheval 2:
    avancer_cheval(&j->cj2,l);
    return 0;} //alors on avance le cheval 2
  return (-1);
}



int est_six(joueur* j){
  int k;
  // cette fonction prends en compte les cas possibles si un joueur obtient 6 au lancer de dé.
  if ((*j).ecurie==2){ // si les deux chevaux du joueur sont dans son écurie, son cheval 1 sort automatiquement
     if ((*j).couleur==JAUNE){
       (*j).cj1.x=1;
       (*j).cj1.y=7;}
     else if ((*j).couleur==BLEU){
       (*j).cj1.x=9;
       (*j).cj1.y=1;}
     else if ((*j).couleur==ROUGE){
       (*j).cj1.x=15;
       (*j).cj1.y=9;}
     else if ((*j).couleur==VERT){
       (*j).cj1.x=7;
       (*j).cj1.y=15;}
     (*j).ecurie--;
     return 5;
  }
  
  else if ( (*j).ecurie==1 ) {
    k=cheval_est_sur_depart(j);
    switch (k){
    case 0:
      return 2;
      break;
    case 1:
      avancer_cheval(&j->cj1,6);
      break;
    case 2:
      avancer_cheval(&j->cj2,6);
      break;
    }
  }
		
  else if ((*j).ecurie==0) {
    //si le joueur possède ses deux chevaux sur le plateau
    return 3;
    // on s'en servira pour le renvoyer vers la fonction choix_user3
  }
  return (-1);
}
    
   
  

int lancer_de(){
  return ((rand() %6)+1);
}


int main (){
  int i=0,j=0,l=0,t=0,n=0,gagnant=0,vainqueur=0,x,y,a,largeur=1000,longueur=700,nb_joueurs=0;

  //Declaration de nos images
  MLV_Image *plateau,*fond,*de[6],*pion[4],*boutonlancer,*bouton_nb_joueurs[3],*bouton_sortircheval,*bouton_avancercheval;

  a=menu();
  if (a==1){
    fond=MLV_load_image("fond.jpg");
    bouton_nb_joueurs[0]=MLV_load_image("two.png");
    bouton_nb_joueurs[1]=MLV_load_image("three.png");
    bouton_nb_joueurs[2]=MLV_load_image("four.png");
    bouton_sortircheval=MLV_load_image("button_sortir-cheval.png");
    bouton_avancercheval=MLV_load_image("button_avancer-cheval.png");
    MLV_draw_image( fond, 0, 0);
    MLV_draw_text( 150, 40, "Choissisez le nombre de joueurs : ", MLV_COLOR_WHITE );
    MLV_draw_image( bouton_nb_joueurs[0] , 200, 200);
    MLV_draw_image( bouton_nb_joueurs[1] , 400, 200);
    MLV_draw_image( bouton_nb_joueurs[2] , 300, 400);
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
    while(nb_joueurs==0){
      if(x>=200 && x<=264 && y>=200 && y<=264){
	nb_joueurs=2;
      }
      else if (x>=400 && x<=464 && y>=200 && y<=264){
	nb_joueurs=3;

      }
      else if (x>=300 && x<=364 && y>=400 && y<=464){
	nb_joueurs=4;
      }
      else {
	MLV_wait_mouse(&x, &y);
      }
    }
      joueur tab[4];
  if(nb_joueurs==4){
    tab[0].couleur=JAUNE;
    tab[1].couleur=BLEU;
    tab[2].couleur=ROUGE;
    tab[3].couleur=VERT;
    pion[0]=MLV_load_image("pion_jaune.png");
    pion[1]=MLV_load_image("pion_bleu.png");
    pion[2]=MLV_load_image("pion_rouge.png");
    pion[3]=MLV_load_image("pion_vert.png");
     
    }
  else if (nb_joueurs==3){
    tab[0].couleur=JAUNE;
    tab[1].couleur=BLEU;
    tab[2].couleur=ROUGE;
    pion[0]=MLV_load_image("pion_jaune.png");
    pion[1]=MLV_load_image("pion_bleu.png");
    pion[2]=MLV_load_image("pion_rouge.png");
  }
  else if (nb_joueurs==2){
    tab[0].couleur=JAUNE;
    tab[1].couleur=ROUGE;
    pion[0]=MLV_load_image("pion_jaune.png");
    pion[1]=MLV_load_image("pion_rouge.png"); 
  }

  for(i=0;i<nb_joueurs;i++){
    tab[i].ecurie=2;
    initialiser_ecurie(&tab[i]);
    tab[i].cj1.avancement=0;
    tab[i].cj2.avancement=0;
  }
  srand(time(NULL));
  // Chargements de nos images
  plateau= MLV_load_image( "plateau.png" );
  de[0]=MLV_load_image("de_1.png");
  de[1]=MLV_load_image("de_2.png");
  de[2]=MLV_load_image("de_3.png");
  de[3]=MLV_load_image("de_4.png");
  de[4]=MLV_load_image("de_5.png");
  de[5]=MLV_load_image("de_6.png");

  boutonlancer=MLV_load_image("boutonlancer.jpg");
  MLV_resize_image_with_proportions( plateau, largeur, longueur);
  MLV_draw_image( fond, 0, 0);
  MLV_draw_image( plateau, 0, 0);
  MLV_draw_image( boutonlancer, 765, 300 );

  
  switch (nb_joueurs){
  case 4:
    MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
    MLV_draw_text( 550,10, "joueur 2", MLV_COLOR_WHITE );
    MLV_draw_text( 50,675 , "joueur 4", MLV_COLOR_WHITE );
    MLV_draw_text( 550,675, "joueur 3", MLV_COLOR_WHITE );
    break;
  case 3:
    MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
    MLV_draw_text( 550,10, "joueur 2", MLV_COLOR_WHITE );
    MLV_draw_text( 550,675, "joueur 3", MLV_COLOR_WHITE );
    break;
  case 2:
    MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
    MLV_draw_text( 550,675, "joueur 2", MLV_COLOR_WHITE );
    break;
  }

 
  MLV_actualise_window();
  while (gagnant==0){
	  
    for(i=0;i<nb_joueurs;i++){
    
      //création de la fenetre.
      MLV_draw_adapted_text_box(
				  760, 400,
				  "  tour du joueur: %d  ",
				  1,
				  MLV_COLOR_BLUE, MLV_COLOR_YELLOW, MLV_COLOR_BLUE,
				  MLV_TEXT_CENTER,
				  i+1
				  );
	MLV_actualise_window();
	MLV_wait_mouse(&x, &y);
	while(!((x>=765 && x<=885)&&(y>=300 && y<=330))){
	  MLV_wait_mouse(&x, &y);
	}
	
	l=lancer_de();
	MLV_draw_image( de[l-1], 785, 194 );
	if (l!=6){ // si le résultat du dé est différent de 6
	  if(tab[i].ecurie==1){ // si le joueur possède un cheval sur le plateau
	    if(est_dans_ecurie(&tab[i].cj1)==1)    
	      { 
		avancer_cheval(&tab[i].cj1,l);
		   
	      }
	    else if(est_dans_ecurie(&tab[i].cj2)==1)  //pour savoir si c'est le cheval 2 qui est en jeu
	      {
		avancer_cheval(&tab[i].cj2,l);
	      }
	  }
	  if((tab[i].ecurie==0)){
	    MLV_draw_text( 700, 450, "Cliquez sur le cheval à déplacer", MLV_COLOR_WHITE );
	    MLV_actualise_window();
	    if(tab[i].pg==0){
	      if((tab[i].cj1.avancement+l)<=62 && (tab[i].cj2.avancement+l)<=62 ){
		choix_user3(&tab[i],l);
	      }
	      else{
		if((tab[i].cj1.avancement+l)>62){
		  avancer_cheval(&tab[i].cj2,l);}
		if((tab[i].cj2.avancement+l)>62){
		  avancer_cheval(&tab[i].cj1,l);}
	      }
	    }
	    
	    
	    else if(tab[i].pg==1){
		  if(tab[i].cj1.x==200+4*i){
		    avancer_cheval(&tab[i].cj2,l);
		  }
		  else if(tab[i].cj2.x==201+4*i){
		    avancer_cheval(&tab[i].cj1,l);
		  }}
	  }
	}
	else { // résultat du dé égal à 6
	      t=est_six(&tab[i]); 
	      //printf("t=%d\ncheval sur départ %d \n\n",t,cheval_est_sur_depart(&tab[i]));
	      if(t==2){
		MLV_draw_image(bouton_avancercheval,765,550);
		MLV_draw_image(bouton_sortircheval,765,620);
		MLV_actualise_window();
		choix_user2(&tab[i]);
		//	printf("c1x=%d,c1y=%d,c2x=%d,c2y=%d,ecurie=%d \n",tab[i].cj1.x,tab[i].cj1.y,tab[i].cj2.x,tab[i].cj2.y,tab[i].ecurie);
	      }
	      else if (t==3){
		MLV_draw_text( 700, 450, "Cliquez sur le cheval à déplacer", MLV_COLOR_WHITE );
		MLV_actualise_window();
	        if(tab[i].pg==0){
		  if((tab[i].cj1.avancement+l)<=62 && (tab[i].cj2.avancement+l)<=62 ){
		    choix_user3(&tab[i],l);
		  }
		  else{
		    if((tab[i].cj1.avancement+l)>62){
		      avancer_cheval(&tab[i].cj2,l);}
		    if((tab[i].cj2.avancement+l)>62){
		      avancer_cheval(&tab[i].cj1,l);}
		  }
		}
	    
		
		else if(tab[i].pg==1){
		  if(tab[i].cj1.x==200+4*i){
		    avancer_cheval(&tab[i].cj2,l);
		  }
		  else if(tab[i].cj2.x==201+4*i){
		    avancer_cheval(&tab[i].cj1,l);
		  }}
		    
	      }	
	      i--;
	      t=0;
	}
	
	    for (n=0;n<nb_joueurs;n++){
	      if(n!=i){
		      if (tab[i].cj1.x==tab[n].cj1.x && tab[i].cj1.y==tab[n].cj1.y){
			retour_ecurie(&tab[n].cj1,&tab[n]);
		      }
		      else if (tab[i].cj1.x==tab[n].cj2.x && tab[i].cj1.y==tab[n].cj2.y) {
			retour_ecurie(&tab[n].cj2,&tab[n]);
		      }
		      else if (tab[i].cj2.x==tab[n].cj1.x && tab[i].cj2.y==tab[n].cj1.y){
			retour_ecurie(&tab[n].cj1,&tab[n]);
		      }
		      else if (tab[i].cj2.x==tab[n].cj2.x && tab[i].cj2.y==tab[n].cj2.y) {
			retour_ecurie(&tab[n].cj2,&tab[n]);
		      }
	         }
	      if(tab[i].cj1.x==8 && tab[i].cj1.y==8){
		tab[i].pg++;
		tab[i].cj1.x=200+4*i;
		tab[i].cj1.y=200+4*i;
		printf("pg = %d \n",tab[i].pg);
	      }
	      if(tab[i].cj2.x==8 && tab[i].cj2.y==8){
		tab[i].pg++;
		tab[i].cj2.x=201+4*i;
		tab[i].cj2.y=201+4*i;
		printf("pg = %d \n",tab[i].pg);
	      }
	       if (tab[i].pg==2){
		 gagnant=1;
		 vainqueur=i+1;
		 i=nb_joueurs;
	      }
	    }
	   
  
	    MLV_draw_image( fond, 0, 0);
	    MLV_draw_image( de[l-1], 785, 194 );
	    MLV_draw_image( boutonlancer, 765, 300 );
	    MLV_draw_image(plateau,0,0);
	     switch (nb_joueurs){
	     case 4:
	       MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
	       MLV_draw_text( 550,10, "joueur 2", MLV_COLOR_WHITE );
	       MLV_draw_text( 50,675 , "joueur 4", MLV_COLOR_WHITE );
	       MLV_draw_text( 550,675, "joueur 3", MLV_COLOR_WHITE );
	       break;
	     case 3:
	       MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
	       MLV_draw_text( 550,10, "joueur 2", MLV_COLOR_WHITE );
	       MLV_draw_text( 550,675, "joueur 3", MLV_COLOR_WHITE );
	       break;
	     case 2:
	       MLV_draw_text( 50, 10, "joueur 1", MLV_COLOR_WHITE );
	       MLV_draw_text( 550,675, "joueur 2", MLV_COLOR_WHITE );
	       break;
	     }
	     
	    MLV_actualise_window();
	    for(j=0;j<nb_joueurs;j++){
	      if(tab[j].ecurie==2){initialiser_ecurie(&tab[j]);}
	      MLV_draw_image( pion[j], ((tab[j].cj1.x)*42.3),((tab[j].cj1.y)*42.3));
	      MLV_draw_image( pion[j], ((tab[j].cj2.x)*42.3),((tab[j].cj2.y)*42.3));
	      MLV_actualise_window();
	    }}
   
  }

  MLV_draw_image( fond, 0, 0);
  MLV_draw_text( 100, 200, "le joueur %d a gagné", MLV_COLOR_WHITE,vainqueur );
 
 
  }
   
  
	MLV_actualise_window();
	MLV_wait_seconds(150);
  
  return 0;
}
