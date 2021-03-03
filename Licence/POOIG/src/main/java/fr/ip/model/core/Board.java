package fr.ip.model.core;

import fr.ip.model.util.Tuple;

/**
 * Class managing the cycle of players:
 *   - next player
 *   - play again
 *   - don't play
 * A kind of Iterable<Player>
 */
public class Board {

    /**
     * A kind of Players' Iterator
     * Represent an infinite loop of players
     */
    public static class Cycle {

        /**
         * List of all players with their ability to play
         */
        private Tuple<Player, Boolean>[] ps;

        /**
         * Number of the player whose turn it is
         */
        private int index;

        /**
         * Count number of players that can not play
         */
        private int removed;

        public Cycle (Player[] ps) {
            index = ps.length - 1;
            this.ps = new Tuple[ps.length];

            for(int i = 0; i < ps.length; i++)
                this.ps[i] = new Tuple<>(ps[i], true);

            this.removed = 0;
        }

        /**
         * Can an other player play
         * @return true if a player can play, false otherwise
         */
        public boolean hasNext() {
            return ps.length != 0 && removed != ps.length;
        }

        /**
         * @return Next player to play
         */
        public Player next () {
            index = (index + 1) % ps.length;
            while (!ps[index].y) {
                ps[index].x.listener().trigger(new Event("pass"));
                index = (index + 1) % ps.length;
            }
            return ps[index].x;
        }

        /**
         * The current player can not play anymore
         */
        public void remove () {
            if(!ps[index].y)
                return;
            ps[index].y = false;
            removed ++;
        }

        /**
         * The current player can now play
         */
        public void add () {
            if(ps[index].y)
                return;
            ps[index].y = true;
            removed --;
        }

        /**
         * The player can now play
         * @param player
         */
        public void add (Player player) {
            int i;
            for (i = 0; i < ps.length; i++)
                if (player == ps[i].x){
                    if(ps[i].y)
                        return;
                    ps[i].y = true;
                    removed --;
                }
        }

        /**
         * Set index to the previous player
         */
        public void previous () {
            index = (index - 1) % ps.length;
            if (index < 0) index += ps.length;
        }

    }

    /**
     * Kind of Iterator<Player>
     */
    private Cycle players;

    public Board(Player[] ps) {
        players = new Cycle(ps);
    }

    public Cycle iterator() {
        return players;
    }
}
