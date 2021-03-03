package fr.ip.model.core;

import fr.ip.model.util.Facade;
import fr.ip.model.util.Message;
import fr.ip.model.util.Question;
import fr.ip.model.util.QuestionBank;

import javax.swing.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.function.Predicate;

/**
 * Abstract class representing a cell/square
 */
public abstract class Cell {
    private static final QuestionBank BANK = new QuestionBank();

    /**
     * Represent the position of the cell on the board
     */
    public final int id;

    /**
     * List of all cells created for the game
     */
    private static ArrayList<Cell> cells = new ArrayList<Cell>();

    /**
     * Event listener of cells
     * @see EventListener
     */
    private Listener listener;

    /**
     *  Intern class setting up a cell to allow only one pawn at the time
     */
    public class SinglePawnCell {

        /**
         * Pawn on the cell
         */
        private Pawn pawn;

        /**
         * Constructor.
         * @param forward if the cell is already took send the pawn forward or backward
         */
        public SinglePawnCell(boolean forward) {
            pawn = null;
            listener.add("enter", (Event.CellEvent event) -> {
                if (pawn != null) {
                    event.getPawn().goToCell(next(1, forward));
                    event.stopPropagation();
                } else pawn = event.getPawn();
            });

            listener.add("leave", (Event.CellEvent event) -> {
                if (pawn == event.getPawn()) pawn = null;
            });
        }

    }

    /**
     * Intern class setting up a cell to trap players on this cell while no other player come to take their place
     */
    protected class TrapCell {

        /**
         * Trapped player
         */
        private Player player;

        public TrapCell() {
            player = null;
            Cell.this.listener.add("enter", (Event.CellEvent event) -> {
                if (player != null)
                    Game.getInstance().add(player);
                Facade.show(new Message("You are trapped"));                  
                player = event.getPawn().getPlayer();
                Game.getInstance().removePlayer();
            });
        }
    }

    /**
     * When a pawn enter this cell, he jump to a new location
     */
    public class JumpCell {

        /**
         * Constructor.
         * @param target id of the new cell
         */
        public JumpCell (int target) {
            Cell.this.listener.add("enter", (Event.CellEvent event) -> {
                Facade.show(new Message("Jump to cell " + target, JOptionPane.INFORMATION_MESSAGE));
                event.getPawn().goToCell(Cell.get(target));
                event.stopPropagation();
            });
        }

    }

    /**
     * When a player enter this cell, he must stay for a define number of turns
     */
    protected class CounterCell {

        /**
         * List of players and the count of their remaining turn
         */
        private HashMap<Player, Integer> map;

        /**
         * Constructor.
         * @param i Number of turn a player must wait
         */
        public CounterCell (int i) {
            map = new HashMap<>();
            Cell.this.listener.add("enter", (Event.CellEvent event) -> {
                map.put(event.getPawn().getPlayer(), i);
                Game.getInstance().removePlayer();
                Facade.show(new Message("You must wait " + i + " turns"));
            });

            Cell.this.listener.add("stay", (Event.CellEvent event) -> {
                Player player = event.getPawn().getPlayer();
                map.compute(player, (p, j) -> j - 1);
                if (map.get(player) == 0) {
                    map.remove(player);
                    Game.getInstance().add(player);
                }
            });
        }

    }

    /**
     * When a player enter the cell, he must answer a question
     */
    protected class QuestionCell {

        /**
         * Constructor.
         * @param success Event to run if the answer is correct
         * @param fail Event ti run if the answer is wrong
         */
        public QuestionCell (ActionEvent<Event.CellEvent> success, ActionEvent<Event.CellEvent> fail) {
            Cell.this.listener().add("enter", (Event.CellEvent event) -> {
                Question q = BANK.getRandomQuestion();
                String answer = Facade.read("Question cell\n"+q.question);
                if (q.test(answer)) success.run(event);
                else fail.run(event);
            });
        }

    }

    /**
     * Event Listener for cells
     * @see fr.ip.model.core.Event.CellEvent
     * @see EventListener
     */
    public class Listener implements EventListener<Event.CellEvent> {

        /**
         * List of events to run on a cell when a pawn
         *   - enter
         *   - stay
         *   - leave
         */
        private LinkedList<ActionEvent<Event.CellEvent>> enter, stay, leave;

        public Listener() {
            enter = new LinkedList<>();
            stay  = new LinkedList<>();
            leave = new LinkedList<>();
        }

        /**
         * Trigger events on the cell
         * @param event Triggered event
         */
        @Override
        public void trigger(Event.CellEvent event) {
            LinkedList<ActionEvent<Event.CellEvent>> list;
            switch (event.getName()) {
                case "enter": list = enter;break;
                case "stay": list = stay;break;
                case "leave": list = leave;break;
                default: return;
            }

            runAll(list, event);
        }

        /**
         * Add a new event to the cell
         * @param name name of the event
         * @param event Action to run when the corresponding event is call
         */
        @Override
        public void add(String name, ActionEvent<Event.CellEvent> event) {
            switch (name) {
                case "enter": enter.add(event);break;
                case "stay": stay.add(event);break;
                case "leave": leave.add(event);break;
            }
        }

    }

    protected Cell() {
        cells.add(this);
        id = cells.size();

        listener = new Listener();
    }

    /**
     * Clear all cells
     */
    public static void flush () {
        cells = new ArrayList<>();
    }

    /**
     * @param incr incrementation on the board
     * @return The incr-th cell after the current cell
     */
    public Cell next (int incr) {
        return next(incr, true);
    }

    /**
     * @param incr incrementation on the board
     * @param forward does the incrementation go forward or backward
     * @return The incr-th cell after or before the current cell
     */
    public Cell next (int incr, boolean forward) {
        return get(id + (forward ? incr : -incr));
    }

    /**
     * @param index id of the cell
     * @return cell for the given id
     */
    static Cell get (int index) {
        return cells.get(Math.max(0, Math.min(index - 1, cells.size())));
    }

    /**
     * Size of the board
     * @return number of cells
     */
    public static int size() {
        return cells.size();
    }

    /**
     * @return Listener to add or trigger event
     */
    public Listener listener() {
        return listener;
    }

    @Override
    public String toString() {
        return "case: " + id;
    }
}
