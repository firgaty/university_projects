# Projet de Language Objet Avancé 2019

## Instructions

- Lancer `make` pour compiler, `make run filename` pour lancer le jeu, `make run_crea` pour lancer l'éditeur de jeux.

- Pour générer un arbre de l'architecture de fichier : `make tree`.

- Pour nettoyer les objets compilé: `make clean`.

- Vous pouvez utiliser le fichier **test.game** pour votre premiere partie.

## Documentation et UML

Le projet dépassant les 10Mo avec la doc et le graph de dépéndances générés, nous n'avons pas pu les soumettre directement avec le projet. Ainsi nous avons décidé de le soumettre en précisant la procédure pour les générer.

- Pour générer la documentation Doxygen, à condition d'avoir installé `doxygen`, surtout utile pour observer le graphe de la hierarchie des héritages: `make doxygen`. Cela va générer la documentation dans `doc/html`, il faudra donc utiliser un navigateur pour ouvrir le fichier `doc/html/index.html`.

- Pour générer le graphe des dépendences, à condition d'avoir python 3 et `graphviz`: `make dependency`. Le graphe se trouvera à `doc/dependency_graph.png`
