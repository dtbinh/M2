Binôme : NAIT ABDELAZIZ Yanis et MIRANDA Yoan

Pour cette dernière séance, nous avons choisi d'implémenter le jeu du duel.

Pour ce faire, nous avons :
	-Branché une led avec une résistance au port A5 ainsi qu'un bouton au port B7 pour le joueur 1
	-Branché une led avec une résistance au port B4 ainsi qu'un bouton au port C3 pour le joueur 2
	-Utilisé la led au port G13 pour la led centrale

Le déroulement séquentiel du code que nous avons écrit :
	-On connecte correctement les leds et les boutons
	-On fait un tour de boucle d'un certain nombre d'itérations pendant lequel la led centrale reste éteinte et on teste si un 
	 des deux joueurs appuie sur son bouton, ce qui engendre la perte de la partie du jeu du duel de ce dernier et on allume la 
	 led du joueur vainqueur
	-Si aucun joueur n'a appuyé sur son bouton, on allume donc la led centrale 
	-On fait une boucle infinie pendant laquelle on teste si un joueur appuie sur son bouton. Si un joueur a appuyé sur son bouton
	 alors il a gagné la partie , donc allumage de sa led
	
Pour tester si un bouton est appuyé , on teste juste s'il y a du courant qui passe par le pin auquel il est connecté
