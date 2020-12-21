#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <time.h>
// les fonctions de la stratégie
void affiche_dec(int val)
{
    
	printf("Vous avez lu une valeur entiere egale a %d en decimal", val);
}
void affiche_oct(int val)
{
   
	printf("Vous avez lu une valeur entiere egale a  %o en octal", val);
}
void affiche_hex(int val)
{
    printf("Vous avez lu une valeur entiere egale a %x en hexadecimal", val);
}
// fontion qui définit le contexte de la stratégie
void affiche(int a, int (*pf)(int))
{
    return ((*pf)(a));
}

//La fonction du thread
void* lire_entier(void *arg) {
  int un_entier;
  int val_arg = (int) arg;
  printf("Bienvenue chez le thread ayant comme argument %d\n", val_arg);
  printf("Priere de saisir un entier:");
  scanf("%d", &un_entier);
  pthread_exit((void *) un_entier); 
}//fin lire_entier



int main(void) {
  clock_t temps_initial, temps_final;
  float temps_cpu;
  int i, val_retour,choix;
  pthread_t thread1;
  pthread_t thread2;
  srand(time(NULL));
  i = 1 + rand() % 100;
  temps_initial=clock();
  int succes = pthread_create(&thread1, NULL, lire_entier, (void *) i);
  if (succes != 0) {
    fprintf(stderr, "Erreur de creation du thread ...");
    exit(0);
  }//fin if (succes != 0)
  
  //Attente du thread de lecture
  pthread_join(thread1, (void *)&val_retour);
  temps_final=clock();
  temps_cpu=(temps_final-temps_initial)*1e-6;
  printf(" le temps d'execution de la lecture en s %f\n",temps_cpu);
  
  temps_initial=clock();
  printf("1 pour decimal, 2 pour octal et 3 pour hexadecimal :");
  scanf("%d", &choix);
  
  
  switch  (choix){
  	case 1:
  		affiche(val_retour, &affiche_dec);
  		break;
  	case 2:
  		affiche(val_retour, &affiche_oct);
  		break;
  	case 3:
  		affiche(val_retour, &affiche_hex);
  		break;
  	default:
  		affiche(val_retour, &affiche_dec);
  		break;
  }
  temps_final=clock();
  temps_cpu=(temps_final-temps_initial)*1e-6;
  printf(" le temps d'execution de l'ecriture en s %f\n",temps_cpu);
  return 0;
}//fin main()






