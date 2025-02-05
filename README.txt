Temps de travail (par personne) : environ 20h

Remarque Générale :

Projet long mais kiffant, quelque consigne n'ont pas été respecté a la lettre mais dans l'ensemble je pense que tout va bien, c'est un plaisir de voir un projet bien marché

Galère rencontré :

Affichage de la roue : La roue ne s'affichait pas bien, tourner dans le mauvais angle et ne tournais pas sur elle meme, car le point central n'était pas exacte
Encadrement des cases : mettre a la main chaque position de chaque case du plateau
Logique du jeu : faire la logique de gain, perte etc...

Partie Amayas : Gestion SDL et Interface Graphique

Gestion du temps et des phases de jeu :
	- TIME_BETTING et TIME_STOP : Durées des phases.
	- Gestion du timer (SDL_GetTicks() pour faire avancer le jeu).
	- Passage entre phase de mise et phase de tirage.
Gestion de l’historique des numéros gagnants :
	- initHistorique() : Initialise la mémoire des derniers numéros.
	- ajouterNumeroHistorique() : Enregistre un numéro après chaque tirage.
	- afficherHistorique() : Affiche l’historique sur l’écran.
Gestion du son et de la musique :
	- Mix_OpenAudio() : Initialise le système audio.
	- Mix_PlayMusic() : Joue la musique de fond en boucle.
	- Mix_PlayChannel() : Joue les effets sonores (clic, spin).
	- Gestion des erreurs en cas de fichiers audio manquants.

Partie Dan : Logique du Jeu et Gestion des mises

Gestion des mises des joueurs :
	- poserMise() : Enregistre une mise avec son montant et sa position.
	- initialiserMises() : Réinitialise les mises à chaque manche.
Détection des cases cliquées et conversion en mises :
	- detecterCaseCliquee() : Vérifie sur quelle case la souris a cliqué.
	- parseNumList() : Extrait les numéros couverts par une mise.
Calcul des gains après chaque tirage :
	- calculerGains() : Vérifie si une mise est gagnante et met à jour le solde.
	- estRouge() : Détermine la couleur d'un numéro tiré.

Partie Alexandre : Gestion de l'historique, du Timer et du Son

Initialisation et gestion de SDL :
	- initSDL() : Crée la fenêtre et le renderer.
	- loadTexture() : Charge et retourne une texture SDL.
	- renderText() : Affiche du texte sur l'écran avec SDL_ttf.
Affichage du jeu et de ses composants :
	- Chargement et rendu des textures (menu, plateau, roulette, jetons, etc.).
	- Gestion des rotations de la roue (rouletteAngle et SDL_RenderCopyEx()).
	- Affichage du solde et des mises avec SDL_ttf.
Gestion des événements souris pour l’interface :
	- Détection des clics pour les boutons (Play, Exit, Retour).
	- Sélection des jetons et placement des mises sur le tapis.

Si on avait plus de temps :

Ajout d'un onglet "Regle" : permettant d'afficher les regles du jeu
Ajout d'un onglet "Option" : permettant de regler le volume du son ou la taille de la fenetre
Ajout d'un système de payement sécurisé : la mise de depart est de 1000, mais si on ajoute ca, on mettra l'argent mis dans le jeu pour misé
