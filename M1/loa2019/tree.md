```
.
├── BINOME.txt
├── Doxyfile
├── README.md
├── TODO.md
├── clang-format-all
├── demo.game
├── dependency_graph.py
├── include
│   ├── AppBase.hpp
│   ├── AppCreator.hpp
│   ├── AppGame.hpp
│   ├── Controller
│   │   ├── ControllerBase.hpp
│   │   ├── ControllerKeyboard.hpp
│   │   ├── Input.hpp
│   │   └── KeyboardLayout.hpp
│   ├── Model
│   │   ├── AI
│   │   │   ├── AI.hpp
│   │   │   ├── Algorithms
│   │   │   │   ├── AStar.hpp
│   │   │   │   └── PriorityQueue.hpp
│   │   │   └── DefaultAI.hpp
│   │   ├── Actionable.hpp
│   │   ├── Board
│   │   │   ├── Board.hpp
│   │   │   ├── BoardContainer.hpp
│   │   │   ├── Door.hpp
│   │   │   └── Square.hpp
│   │   ├── ChoiceSelect.hpp
│   │   ├── Color.hpp
│   │   ├── Colored.hpp
│   │   ├── Creator
│   │   │   ├── BoardCreator.hpp
│   │   │   ├── GameCreator.hpp
│   │   │   ├── LevelCreator.hpp
│   │   │   ├── LevelEditor.hpp
│   │   │   ├── LevelLinkEditor.hpp
│   │   │   ├── LinkEditor.hpp
│   │   │   └── OptionsArguments.hpp
│   │   ├── Event
│   │   │   └── Event.hpp
│   │   ├── FileController
│   │   │   ├── FileController.hpp
│   │   │   ├── FileReader.hpp
│   │   │   └── FileWriter.hpp
│   │   ├── Game.hpp
│   │   ├── GameObject
│   │   │   ├── Charger.hpp
│   │   │   ├── ChargerType.hpp
│   │   │   ├── Diamond.hpp
│   │   │   ├── GameObject.hpp
│   │   │   ├── GameObjectState.hpp
│   │   │   ├── Monster
│   │   │   │   ├── Monster.hpp
│   │   │   │   └── MonsterTypes.hpp
│   │   │   ├── Moveable.hpp
│   │   │   └── Player.hpp
│   │   ├── Level.hpp
│   │   ├── LevelLinks.hpp
│   │   ├── Links.hpp
│   │   ├── MoveSet
│   │   │   ├── CrossMoveSet.hpp
│   │   │   ├── DiagonalCrossMoveSet.hpp
│   │   │   ├── MoveSet.hpp
│   │   │   ├── MoveSetIDs.hpp
│   │   │   └── SquareMoveSet.hpp
│   │   ├── NumberSelector.hpp
│   │   └── Statistics
│   │       ├── GameStats.hpp
│   │       └── PlayerStats.hpp
│   ├── Util
│   │   ├── Convert.hpp
│   │   ├── Dimensional.hpp
│   │   ├── Math.hpp
│   │   ├── Point2D.hpp
│   │   └── TupleIteration.hpp
│   └── View
│       ├── CLI
│       │   ├── DisplayBlankCLI.hpp
│       │   ├── DisplayBoardCLI.hpp
│       │   ├── DisplayBoardCreatorCLI.hpp
│       │   ├── DisplayBoxCLI.hpp
│       │   ├── DisplayCLI.hpp
│       │   ├── DisplayChoiceSelectCLI.hpp
│       │   ├── DisplayContainerCLI.hpp
│       │   ├── DisplayGameCLI.hpp
│       │   ├── DisplayGameCreator.hpp
│       │   ├── DisplayGroupCLI.hpp
│       │   ├── DisplayLabelCLI.hpp
│       │   ├── DisplayLevelCLI.hpp
│       │   ├── DisplayLevelEditor.hpp
│       │   ├── DisplayLevelLinkEditor.hpp
│       │   ├── DisplayLinkEditor.hpp
│       │   ├── DisplayNumberSelectorCLI.hpp
│       │   ├── DisplayNumerBoxCLI.hpp
│       │   ├── DisplayPlayerStatsCLI.hpp
│       │   ├── DisplaySeperatorCLI.hpp
│       │   └── Layout
│       │       ├── HLayout.hpp
│       │       ├── Layout.hpp
│       │       └── VLayout.hpp
│       └── Display.hpp
├── log
├── makefile
├── manuel.pdf
├── src
│   ├── AppBase.cpp
│   ├── AppCreator.cpp
│   ├── AppGame.cpp
│   ├── Controller
│   │   ├── ControllerBase.cpp
│   │   ├── ControllerKeyboard.cpp
│   │   └── KeyboardLayout.cpp
│   ├── Model
│   │   ├── AI
│   │   │   ├── AI.cpp
│   │   │   ├── Algorithms
│   │   │   │   └── AStar.cpp
│   │   │   └── DefaultAI.cpp
│   │   ├── Board
│   │   │   ├── Board.cpp
│   │   │   └── Square.cpp
│   │   ├── Creator
│   │   │   └── LevelCreator.cpp
│   │   ├── Event
│   │   │   └── Event.cpp
│   │   ├── FileController
│   │   │   ├── FileController.cpp
│   │   │   ├── FileReader.cpp
│   │   │   └── FileWriter.cpp
│   │   ├── Game.cpp
│   │   ├── Level.cpp
│   │   ├── LevelLinks.cpp
│   │   ├── Links.cpp
│   │   └── MoveSet
│   │       └── MoveSet.cpp
│   ├── View
│   │   └── CLI
│   │       ├── DisplayBoardCLI.cpp
│   │       ├── DisplayCLI.cpp
│   │       ├── DisplayGameCLI.cpp
│   │       ├── DisplayLevelCLI.cpp
│   │       └── DisplayPlayerStatsCLI.cpp
│   ├── creator.cpp
│   └── game.cpp
├── test.game
└── tree.md

29 directories, 119 files
```
