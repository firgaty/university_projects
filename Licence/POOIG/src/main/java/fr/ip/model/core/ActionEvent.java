package fr.ip.model.core;

/**
 * Functional interface representing an action after an Event
 * @param <T>
 * @see Event
 */
@FunctionalInterface
public interface ActionEvent<T extends Event> {

    /**
     * Function to call when the event is trigger
     * @param event Triggered event
     */
    void run (T event);

}
