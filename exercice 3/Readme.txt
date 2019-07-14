1- Enoncez les problèmes que vous serez emmenés à résoudre.
	-Obtenir la taille du travail que chaque processus devra effectuer.
	-Afficher la matrix
	-Calculer les décalages pour la matrice de résultats
	-Créer une Boucle sur le fragment de matrice pour ce processus


2- Montrez comment vous les résolvez.
	* ÉTAPE 1: créer le segment partagé
	* ÉTAPE 2: bifurquer les processus enfants
	* ÉTAPE 3: chaque processus enfant attache le segment
	* ÉTAPE 4: utilisez le segment partagé
	* ÉTAPE 5: chaque processus enfant détache le segment
	* ÉTAPE 6: chaque processus enfant se termine et le parent se joint
	* ÉTAPE 7: le processus de base supprime le segment
	
