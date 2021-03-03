package fr.ip.model.core;

public class Configuration {

    /**
     * Configuration instance for the current game
     */
		public static final Configuration configuration = new Configuration ();

    /**
     * Global configuration
     */
    public static class Global {}

    /**
     * Configuration for either Numeri or Goose game
     */
    public static class Game {

        /**
         * Enum the way to display cells in the frame
         */
				public static class CellOrder {

            /**
             * Options' name
             */
						public final static String[] options = {"Column", "Rectangle", "Zigzag", "Spiral"};

            /**
             * Options' symbolic variables
             */
						public static final int COLUMN    = 0,
									 									RECTANGLE = 1,
																		ZIGZAG    = 2,
																		SPIRAL    = 3;

				}

        public int numberOfPlayers, numberOfCells, cellOrder;

        public Game (int numberOfCells, int numberOfPlayers, int cellOrder) {
            this.numberOfCells = numberOfCells;
            this.numberOfPlayers = numberOfPlayers;
            this.cellOrder = cellOrder;
        }
    }

    /**
     * Configuration for goose game
     */
    public static class Goose extends Game {

        /**
         * Way to end the game
         */
        public static class EndMode {
            
            /**
             *  Options' name
             */
            public static final String[] modes = {
                "Terminer quand sur la dernière case",
                "Terminer quand dépasse la dernière case"
            };

            /**
             * Options' symbolic variable
             */
            public static final int 
              ON_LAST   = 0,
              OVER_LAST = 1;

        }

        public int endMode;

        /**
         * cohabits: Can two or more pawn be on the same cell
         * questions: ask questions and can replay if correct answer
         */
        public boolean cohabits, questions;
        
        public Goose (int nC, int nP, int cO, int endMode, boolean cohabits, boolean questions) {
            super (nC, nP, cO);
            this.endMode   = endMode;
            this.cohabits  = cohabits;
            this.questions = questions;
        }

    }

    /**
     * Option for the numeri
     */
    public static class Numeri extends Game {
        
        /**
         * align: replay if 3 pawns are align
         * replay: additional face on the dice
         */
        public boolean align, replay;

        public Numeri (int nC, int nP, int cO, boolean align, boolean replay) {
            super(nC, nP, cO);
            this.align  = align;
            this.replay = replay;
        }

    }

    /**
     * Specific configuration instances
     */
    public final Goose goose;
    public final Numeri numeri;

    public Configuration () {
        this.goose  = new Goose(15, 5, 3, 0, false, true);
        this.numeri = new Numeri(40, 5, 3, false, false);
    }

}
