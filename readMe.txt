

                                                                   LE LANGAGE TURTLE : 
                                                                  --------------------



GROUPE :      WALID LAMKOUTAR / TOUFIK KHARIJ / ZAID LAMRANI / OUSSAMA TARMOUNE  ---> GL2 ENSIAS
--------        


N.B :
----
 Ce projet s'inscrit dans le cadre du développement d'un compilateur turtle qui va selon une grammaire bien définie dans le dossier courant faire en sorte qu'une tortue se mouvoit dans son espace
avec des fonctionnalités diverses et en deux dimensions.

-----------------------------------------------------------------------


Spécificités : 
--------------

- Le compilateur de notre langage d'extension .trtl est écrit en langage C et compile vers le langage javascript (JS), plus précisément ce langage généré va interagir avec la balise <canvas> prédéfinie dans le langage HTML5

et les méthodes associés à son contexte et ainsi matérialiser notre code graphiquement sur la page Web.

- Parmi les fonctionnalités offertes : 

---> La possibilité de translater la tortue dans le canvas dans une direction verticale avec un nombre de pixels donné en paramétre.

---> La possibilité de faire tourner la tortue dans les deux sens suivant un angle en degrés passé en parametres.

---> La possibilité de changer le style, la largeur et la couleur du tracé qui accompagne la trajectoire de la tortue.

---> La possibilité de faire déplacer la tortue vers un point de coordonnées (x,y) suivant les axes du canvas .

- On présente une interface Web qui demande à l'utilisateur de saisir un code propre au langage turtle, celui ci sera transféré à un serveur intermédiaire qui s'occupera de la compilation et la géneration du code javascript nécessaire pour 
 
tracer le comportement induit de l'entrée de l'utilisateur.

- Tout est hébergé en local .


-------------------------------------------------------------------

Description : 
-------------

1) Fonction moveTo(x:entier, y:entier)          --------------------------------------------------->axe x
                                                |
                                                |
                                                |
   Déplace la tortue au point.                  |
                                                |
                                                |
                                                |
                                                |                     point de coordonnées (x,y)
                                                |
                                                |
                                                |
                                                |
                                                v
                                              axe y
               


2) moveForward(entier) : déplace la tortue verticalement dans le sens direct d'entier pixels.

3) moveBackward(entier) : déplace la tortue verticalement dans le sens indirect d'entier pixels. (la tortue change de direction)

4) turnLeft(nb degrés) : La tortue tourne à gauche d'un angle donné en paramétre et en degré.

5) turnRIght(nb degrés) : la tortue tourne à droite d'un angle donné en paramètre et en degré.

6) penStyle(dashed | dotted | solid) : change le style du tracé suivant l'espacement désiré.

7) penColor(x:entier<255,y:entier<255,z:entier<255) --> suivant le standard rgb(x,y,z) pour le choix des palettes de couleurs.

8) penWidth(entier) : change la largeur du tracé (ne prenez pas une valeur au dessus de 10 ca risque de dégénerer !!!!)



N.B :  si vous commettez une erreur quelque part, notre compilateur est en mesure de vous aider à vous repérer pour la corriger aussitot !!!!!
-----



                                 