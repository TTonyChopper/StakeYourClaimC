#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
 printf("\n\n                             STAKE YOUR CLAIM\n\n");
//Boucle qui gère la fermeture de l'éxecutable
 do
  {
    printf("\n\nNOUVELLE PARTIE\n\n");
//Variable qui vaut 0 lorsque la partie est finie
    int jeu = 1;
//Variable représentant l'abscisse de la case en cours de jeu
    int m=0;
//Variable représentant l'ordonnée de la case en cours de jeu
    int n=0;
//Variable représentant le nombre de colonnes de la partie
    int a=0;
//Variable représentant le nombre de lignes de la partie
    int b=0;
//Tableau mémorisant l'état du jeu
    int t[552];
//Tableau donnant les indices dans le tableau t des cases utiles(non "invisibles"),afin d'y accéder simplement
    int vraisindices[552]={0};
//Variable contenant les points obtenus par le joueur de tour "impairs"
    int resultsi=0;
//Variable contenant les points obtenus par le joueur de tour "pairs"
    int resultsp=0;
//Variable comptabilisant le nombre de tours joués
    int nbtour = 0;
//Variable permettant d'accéder a la case d'abscisse m d'ordonnée n par t[pcasemn]
    int casemn=0;
    imprimertableau0(&a,&b,t);
    creerindices(a,b,vraisindices);
//Boucle qui gère les tours de jeu
    do
    {
        int parite=(nbtour)%2;
        (parite) ? tourordinateur(&nbtour,a,b,t,vraisindices,resultsi,resultsp),imprimertableaufinal(a,b,t,&casemn) : tourimpair(&nbtour,&m,&n,a,b,t,&casemn,vraisindices);
        jeu=testerfindejeu(a,b,t,&jeu,vraisindices,parite);
    }
    while (jeu);
//Imprime le tableau final si la partie se termine après le tour du joueur
    ((nbtour)%2) && (imprimertableaufinal(a,b,t,&casemn)) ;
//Donne les résultats de la partie en fin de jeu
    printf("                            GAME OVER                         \n");
    points(a,b,t,vraisindices,&resultsi,&resultsp);
    Gagnant(&resultsi,&resultsp,nbtour);
 }
 while (BOUCLEINFINIE()==2);
return 0;
}

//Permet de créer un nombre "aléatoire" en fonction du temps
int randomtime()
{
   static int first = 0;

   (first == 0) && (srand (time (NULL)),first = 1);
   return (rand ());
}

//imprime le tableau initial avec des cases vides ' 'pour chaque case du jeu
void imprimertableau0(int *pa,int *pb,int t[])
{
    int i;
    printf("Nombre de lignes(26max)?");
    scanf("\n%d",pb);
    printf("Nombre de colonnes(18max)?");
    scanf("\n%d",pa);
    imprimerligne0(*pa);
    inittableau(t);
    for(i=0; i < *pb; i++)
    {
        imprimerbord(*pa);
        imprimercases0(*pa,i);
    }
    imprimerbord(*pa);
}

//Imprime la toute première ligne du plateau de jeu
void imprimerligne0(int a)
{
    int i;int z;
    printf(" ");
    for(i=0,z='1'; i < a; i++,z++)
    {
        printf("   %c",z);
    }
    printf("\n");
}

//Initialise t a {0}
void inittableau(int t[])
{
    int i;
    for (i = 0 ; i < 552; i++)
    {
      t[i] =' ';
    }
}

//Imprime les bordures du plateau de jeu
void imprimerbord(int a)
{
    int i;
    printf("  ");
    for(i=0; i<a; i++)
    {
        printf("+---");
    }
    printf("+\n");
}

//Imprime les lignes contenant les cases du plateau de jeu(initialisées par ' ')
void imprimercases0(int a,int i)
{
    int j;
    int z='A'+i;
    printf("%c ",z);
    for(j=0; j<a; j++)
    {
        printf("|   ");
    }
    printf("|\n");
}

//Crée le tableau vraisindices[] permettant d'accéder facilement par une boucle à toutes les cases du plateau de jeu à travers t
void creerindices(int a,int b,int *vraisindices[])
{
 int i;
 for(i=0;i<a*b;i++)
 {
  int k=0;
  k=i/a;
  vraisindices[i]=a+2+i+k;
 }
}

//S'occupe des tours du joueur
void tourimpair(int *pnbtour,int *pm,int *pn,int a,int b,int *t[],int *pcasemn,int *vraisindices[])
{
    *pnbtour=(*pnbtour)+1;
//Boule vérifiant si le coup est valide
    do
    {
//Boucle vérifiant si le coup est dans le plateau de jeu
      do
      {
        printf("Tour No%d,Joueur 1(X) :\nChoisissez la case(LettreChiffre):",*pnbtour);
        scanf("\n%c",pm);
        scanf("\n%c",pn);
        *pcasemn=(*pm -'A'+1)*(a+1)+(*pn-'1'+2)-1;
        (coupimpossible(a,b,*pcasemn,vraisindices)) && printf("         Case INTROUVABLE!\n             Rejouez\n");
      }
      while (coupimpossible(a,b,*pcasemn,vraisindices));
      printf("VOUS AVEZ JOUE :%c%c\n",*pm,*pn);
    }
    while (!verificationimpair(t,pcasemn));
    t[*pcasemn]='X';
    adji(a,t,pcasemn);
}

//Teste si le coup est dans le plateau de jeu
int coupimpossible(int a,int b,int casemn,int vraisindices[])
 {
  int i;
  int couphorscases = 1;
  for(i=0;i<a*b;i++)
   {
    (casemn==vraisindices[i]) && (couphorscases=0);
   }
  return couphorscases;
 }

//Teste si le coup est dans les règles pour le joueur
int verificationimpair(int t[],int *pcasemn)
{
    int R = 1;
    if(t[*pcasemn]=='#'||t[*pcasemn]=='o'||t[*pcasemn]=='O'||t[*pcasemn]=='X')
     {
      printf("         Coup NON AUTORISE!\n             Rejouez\n");
      R = 0;
     }
    return R;
}

//Gère la modification des cases adjacentes pour le joueur
void adji(int a,int t[],int *pcasemn)
{
  int doubleif = 0;
  *pcasemn = (*pcasemn)-1;
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)-(a);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a+2);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
}

//Gère le tour de l'ordinateur
void tourordinateur(int *pnbtour,int a,int b,int *t[],int vraisindices[],int resultsi,int resultsp)
{
//Variable représentant la case k : le tableau étant parcouru dans le "sens de lecture"
    int k;
//Correspond a la plus grande difference de points pour le tour suivant qu'il est possible d'obtenir
//L'ordinateur pourra gagner s'il maintient ce nombre le plus grand possible
    int maxpointsagagner=-5;
//Correspond aux nombres de coups qui donne le meme "maxpointsagagner"
    int nbremax=0;
//Nombre aléatoire destiné à choisir un coup au hasard parmis les coups précédents
    int aleatoire=0;
//Tableau représentant la projection hypothétique duplateau au tour suivant après un coup donné de l'ordinateur
    int projectioncoupsuivant[552]={0};
//Tableau donnant la différence du score au tour suivant(score ordinateur -score joueur) pour chaque coup que l'ordinateur peut jouer
    int pointspossibles[552]={0};
//Boucle permettant d'initialiser pointspossibles[]
//Représente la plus petite différence de score que l'on peut avoir après un coup
    int r;
              for(r=0;r<552;r++)
                   {
                        pointspossibles[r]=-5;
                   }
    *pnbtour=(*pnbtour)+1;
    for (k=0;k<a*b;k=k+1)
      {
              int q;
              for(q=0;q<552;q++)
                   {
                        projectioncoupsuivant[q]=t[q];
                   }
              if (verificationpair(projectioncoupsuivant,vraisindices,k))
                   {
                    projectioncoupsuivant[vraisindices[k]]='O';
                    adjp(a,projectioncoupsuivant,vraisindices,k);
                    points(a,b,projectioncoupsuivant,vraisindices,&resultsi,&resultsp);
                    pointspossibles[k]=resultsp-resultsi;
                    ((resultsp-resultsi) > maxpointsagagner) && (maxpointsagagner=resultsp-resultsi) ;
                   }
      }
    for(k=0;k<a*b;k++)
      {
        (pointspossibles[k]==maxpointsagagner) && (nbremax+=1);
      }
    aleatoire=randomtime();
    //Meilleurs coups de l'ordinateur :  printf("maxpointsagagner=%d",maxpointsagagner);
    //k représente le numéro de la case du coup que l'ordinateur choisit finalement
    k=(aleatoire % nbremax);
    decisioncoup(pointspossibles,maxpointsagagner,&k) ;
    affichercoup(a,b,k);
    t[vraisindices[k]]='O';
    adjp(a,t,vraisindices,k);
}

//Teste si le coup envisagé par l'ordinateur est dans les règles
int verificationpair(int *projectioncoupsuivant[],int vraisindices[],int k)
{
    int R = 1;
    (projectioncoupsuivant[vraisindices[k]]=='#'||projectioncoupsuivant[vraisindices[k]]=='x'||projectioncoupsuivant[vraisindices[k]]=='X'||projectioncoupsuivant[vraisindices[k]]=='O') && (R = 0);
    return R;
}

//Gère la modification des cases adjacentes pour l'ordinateur
void adjp(int a,int projectioncoupsuivant[],int vraisindices[],int k)
{
  int doubleif = 0;
  vraisindices[k] = (vraisindices[k])-1;
     if (projectioncoupsuivant[vraisindices[k]] == 'x'||projectioncoupsuivant[vraisindices[k]] == '#')
      {
        projectioncoupsuivant[vraisindices[k]]='#';
        doubleif=1;
      }
     if (projectioncoupsuivant[vraisindices[k]] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        projectioncoupsuivant[vraisindices[k]]='o';
      }
  doubleif = 0;
     vraisindices[k] = vraisindices[k]-(a);
     if (projectioncoupsuivant[vraisindices[k]] == 'x'||projectioncoupsuivant[vraisindices[k]] == '#')
      {
        projectioncoupsuivant[vraisindices[k]]='#';
        doubleif=1;
      }
     if (projectioncoupsuivant[vraisindices[k]] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        projectioncoupsuivant[vraisindices[k]]='o';
      }
  doubleif = 0;
     vraisindices[k] = vraisindices[k]+(a+2);
     if (projectioncoupsuivant[vraisindices[k]] == 'x'||projectioncoupsuivant[vraisindices[k]] == '#')
      {
        projectioncoupsuivant[vraisindices[k]]='#';
        doubleif=1;
      }
     if (projectioncoupsuivant[vraisindices[k]] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        projectioncoupsuivant[vraisindices[k]]='o';
      }
  doubleif = 0;
     vraisindices[k] = vraisindices[k]+(a);
     if (projectioncoupsuivant[vraisindices[k]] == 'x'||projectioncoupsuivant[vraisindices[k]] == '#')
      {
        projectioncoupsuivant[vraisindices[k]]='#';
        doubleif=1;
      }
     if (projectioncoupsuivant[vraisindices[k]] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        projectioncoupsuivant[vraisindices[k]]='o';
      }
     vraisindices[k] = vraisindices[k]-(a+1);
}

//L'ordinateur choisit un coup parmis les meilleurs
void decisioncoup(int *pointspossibles[],int maxpointsagagner,int *k)
{
  int l;
  l=0;
  do
    {
      (pointspossibles[l]==maxpointsagagner) && (*k=(*k)-1);
      l=l+1;
    }
  while ((*k)>-1);
  *k=l-1;
}

//Affiche suivant le format(Lettre,Chiffre) le coup joué par l'ordinateur
void affichercoup(int a,int b,int k)
{
  int lettreordi=0;
  int chiffreordi=0;
  chiffreordi=(k%(a))+'1';
  lettreordi=(k/(a))+'A';
  printf("L'ORDINATEUR JOUE :%c%c\n",lettreordi,chiffreordi);
}

//Imprime le tableau pour la fin de tour
void imprimertableaufinal(int a,int b,int t[])
{
    int i;
    int z;
    int j;
    int casemnrecalcule=0;
    imprimerligne0(a);
    for(i=0,z='A'; i<b; i++,z++)
    {
        imprimerbord(a);
        printf("%c ",z);
        for(j=0; j<a; j++)
        {
            casemnrecalcule=(i+1)*(a+1)+(j+2)-1;
            printf("| %c ",t[casemnrecalcule]);
        }
        printf("|\n");
    }
    imprimerbord(a);
}

//Test s'il reste des coups a jouer
int testerfindejeu(int a,int b,int t[],int *jeu,int vraisindices[],int parite)
{
  *jeu=0;
  int k;
    for(k=0; k<a*b; k++)
     {
      ((t[vraisindices[k]] == 'o'+ parite*('o'-'x')) || (t[vraisindices[k]]==' ')) && (*jeu = 1);
     }
 return *jeu;
 }

//Compte les points de chaque joueur
int points(int a,int b,int t[],int vraisindices[],int *resultsi,int *resultsp)
  {
      int k;
      *resultsi=0;
      *resultsp=0;
      for(k=0; k<a*b; k++)
     {
      (t[vraisindices[k]] == 'x') && (*resultsi=(*resultsi)+1);
      (t[vraisindices[k]] == 'X') && (*resultsi=(*resultsi)+4);
      (t[vraisindices[k]] == 'o') && (*resultsp=(*resultsp)+1);
      (t[vraisindices[k]] == 'O') && (*resultsp=(*resultsp)+4);
     }
  }

//Détermine le vainqueur
void Gagnant(int *resultsi,int *resultsp,int nbtour)
 {
  (*resultsi>*resultsp) && printf("Le Joueur 1(X) gagne avec un score de %d a %d [%d tours]",*resultsi,*resultsp,nbtour);
  (*resultsi<*resultsp) && printf("Le Joueur 2(O) gagne avec un score de %d a %d [%d tours]",*resultsp,*resultsi,nbtour);
  (*resultsi==*resultsp) && printf("EGALITE : %d-%d [%d tours],vous pouvez rejouer.....",*resultsi,*resultsp,nbtour);
 }

//Gère la fermeture de l'éxecutable
int BOUCLEINFINIE()
{
  int i=0;
  printf("\n1 : Pour arreter taper 1\n2 : Pour rejouer taper 2\n");
  scanf("\n%d",&i);
 return i;
}
