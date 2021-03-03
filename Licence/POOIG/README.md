# POOIG

## Installation
Pour installer le projet, il suffit de cloner le dépôt
```
$ git clone https://github.com/Peaupote/POOIG.git
```

## Compiler
Afin de compiler, sans avoir à se prendre la tête avec des IDE, sans modifier le CLASSHPATH nous utilisons Maven.

Il suffit donc d'installer maven, puis à la racine du projet
```
$ mvn package # compile dans target
$ java -jar target/project-1.0-SNAPSHOT.jar # execute le programme
```

On peut toujours compiler soit même le projet. Il faut cependant noter que le package de base est fr.ip et pas main.java.fr.ip.

## Architecture du dépot
```
.
├── assets       Ressources pour le projet (images, audio...)
├── pom.xml      Fichier de configuration pour compiler avec Maven
├── README.md
└── src
    └── main
        └── java
            └── fr
                └── ip
                    ├── App.java                                Classe principale du projet
                    ├── model                                   Package contenant les classes servant à modéliser le jeu
                    │   ├── core                                  - Package pour les classes communes au deux jeux
                    │   │   ├── ActionEvent.java
                    │   │   ├── Board.java
                    │   │   ├── Cell.java
                    │   │   ├── Event.java
                    │   │   ├── EventListener.java
                    │   │   ├── Game.java
                    │   │   ├── Pawn.java
                    │   │   └── Player.java
                    │   ├── goose                                 - Package pour le jeu de l'oie
                    │   │   ├── GooseCell.java
                    │   │   ├── GooseGame.java
                    │   │   └── GoosePlayer.java
                    │   ├── numeri                                - Package pour le numeri
                    │   │   ├── NumeriCell.java
                    │   │   ├── NumeriGame.java
                    │   │   └── NumeriPlayer.java
                    │   └── util                                  - Classes utilitaires
                    │       ├── Facade.java
                    │       ├── Level.java
                    │       ├── Message.java
                    │       ├── Question.java
                    │       ├── Settings.java
                    │       ├── StringUtil.java
                    │       └── Tuple.java
                    └── view                                    Package contenant les classes servant à l'interface graphique
                        ├── core                                Package contenant les classes communes et les pages principales
                        │   ├── components
                        │   │   ├── CellButton.java
                        │   │   ├── Configuration.java
                        │   │   ├── PrimaryButton.java
                        │   │   └── SettingPanel.java
                        │   ├── EndPanel.java
                        │   ├── GameBoardPanel.java
                        │   ├── GameModalBox.java
                        │   ├── ImageBackgroundJPanel.java
                        │   ├── MainFrame.java
                        │   ├── Menu.java
                        │   └── SingleView.java
                        ├── goose                             Jeu de l'oie
                        │   ├── GooseModalBox.java
                        │   └── GoosePanel.java
                        └── numeri                            Numeri
                            ├── NumeriModalBox.java
                            └── NumeriPanel.java
```

