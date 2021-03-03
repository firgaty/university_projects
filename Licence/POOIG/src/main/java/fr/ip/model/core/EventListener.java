package fr.ip.model.core;

import java.util.LinkedList;

/**
 * Interface of listeners
 * @param <T> Type of events to listen
 */
public interface EventListener<T extends Event> {

    /**
     * Trigger the given event
     * @param event
     */
    void trigger (T event);

    /**
     * Add a new action for the given event type
     * @param name
     * @param event
     */
    void add (String name, ActionEvent<T> event);

    /**
     * Run all actions from a list while the event doesn't stop the propagation
     * @param list
     * @param event
     */
    default void runAll (LinkedList<ActionEvent<T>> list, T event) {

        for (ActionEvent<T> e: list) {
            e.run(event);
            if (!event.isPropagate()) break;
        }
    }

}
