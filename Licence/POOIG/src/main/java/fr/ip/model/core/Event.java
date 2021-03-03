package fr.ip.model.core;

/**
 * Class representing an event in-game
 */
public class Event {

    /**
     * Name of the event
     * For example: enter, stay, play, endTurn
     */
    public final String name;

    /**
     * Does the event stop the run loop
     */
    private boolean propagate;

    public Event(String name) {
        propagate = true;
        this.name = name;
    }

    /**
     * Special kind of event for Cells
     * @see Cell
     */
    public static class CellEvent extends Event {

        /**
         * Moving pawn
         */
        private final Pawn pawn;

        public CellEvent(String name, Cell target, Pawn pawn) {
            super(name);
            this.pawn = pawn;
        }

        public Pawn getPawn() {
            return pawn;
        }

    }

    /**
     * Event for a parametric type
     * (we never know)
     * @param <T>
     */
    public static class EventType<T> extends Event {

        /**
         * Element to consider for the event
         */
        private final T element;

        public EventType (String name, T element) {
            super(name);
            this.element = element;
        }

        public T getElement() {
            return element;
        }
    }

    public String getName() { return name; }

    public boolean isPropagate() {
        return propagate;
    }

    public void stopPropagation () {
        propagate = false;
    }

}
