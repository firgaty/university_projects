package fr.ip.model.core;

import java.util.Iterator;
import java.util.LinkedList;

/**
 * Abstract class representing the game
 */
public abstract class Game implements Iterable<Player> {

    /**
     * List of all registered players
     */
    protected LinkedList<Player> players;

    /**
     * Cycle of player in-game
     */
    protected Board board;

    /**
     * Static instance representing the game state
     */
    private static State instance;

    /**
     * Number of cell in game
     */
    public final int length;

    /**
     * Represent game state
     * Allow you to act on the game state from anywhere "safely"
     */
    public class State {

        /**
         * The last player to play
         */
        private Player currentPlayer;

        /**
         * The current player can not play anymore
         */
        public void removePlayer () {
            board.iterator().remove();
        }

        /**
         * The current play can now play
         */
        public void add () {
            board.iterator().add();
        }

        /**
         * The given player can now play
         * @param player
         */
        public void add(Player player) {
            board.iterator().add(player);
        }

        /**
         * The current player play again
         */
        public void playAgain () {
            board.iterator().previous();
        }

        public Player getCurrentPlayer () {
            return currentPlayer;
        }

        public Player getPlayerByName (String name) {
            for (Player p: Game.this)
                if (p.name.equals(name)) return p;
            return null;
        }

    }

    /**
     * Create a game, with no cells and no players
     */
    public Game (int length) {
        players = new LinkedList<>();
        Cell.flush();
				this.length = length;
    }

    /**
     * Register the given player
     * @param p player to add
     */
    public void addPlayer (Player p) {
        players.add(p);
    }

    /**
     * Create game state and board.iterator() instances
     */
    public void start () {
        board = new Board(players.toArray(new Player[0]));
        instance = new State();
    }

    /**
     * Trigger play and end on the current player
     */
    public void playTurn () {
        Player player = board.iterator().next();
        instance.currentPlayer = player;
        player.listener().trigger(new Event("play"));
        player.listener().trigger(new Event("end"));
    }

    /**
     * Function calling all needed functions to play
     */
    public void play () {
        setup();
        start();
        while(!isEnd() && board.iterator().hasNext())
            playTurn();
    }

    /**
     * Define the board state (cells)
     */
    public abstract void setup ();

    /**
     * Define either if the game is end or not
     * @return true if the game has end
     */
    public abstract boolean isEnd ();

    @Override
    public Iterator<Player> iterator() {
        return players.iterator();
    }

    public int size() {
        return players.size();
    }

    public static State getInstance() {
        return instance;
    }

}
