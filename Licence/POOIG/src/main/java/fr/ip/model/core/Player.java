package fr.ip.model.core;

import java.util.LinkedList;
import java.util.Random;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.io.IOException;
import java.io.File;

/**
 * Class representing a player
 */
public abstract class Player {

    /**
     * Name of the player
     */
    public final String name;

    /**
     * Listener
     * @see Listener
     */
    private Listener listener;

    /**
     * Action event to run on a pawn
     * And game if on last cell
     */
    public static abstract class PawnAction implements ActionEvent {

        protected Pawn pawn;

        public PawnAction(Pawn pawn) {
            this.pawn = pawn;
            pawn.getPlayer().listener.add("end", (Event event) -> {
                if (pawn.getLocation().id == Cell.size())
                    Game.getInstance().removePlayer();
            });
        }

        public abstract void run(Event event);

    }

    /**
     * End the game if over last cell
     */
    public static class EndIfOverLastCell extends PawnAction {

        public EndIfOverLastCell(Pawn pawn) {
            super(pawn);
        }

        public void run (Event event) {
            Cell locate = pawn.getLocation();
            int target = locate.id + (new Random()).nextInt(5) + 1;
            // System.out.println("--> target: " + target);
            if (target < Cell.size()) pawn.goToCell(Cell.get(target));
        }

    }

    /**
     * If over last cell, go backward
     */
    public static class EndIfOnLastCell extends PawnAction {

        public EndIfOnLastCell(Pawn pawn) {
            super(pawn);
        }

        @Override
        public void run(Event event) {
            Cell locate = pawn.getLocation();
            int target = locate.id + (new Random()).nextInt(5) + 1;
            // System.out.println("--> target: " + target);
            if (target <= Cell.size()) pawn.goToCell(Cell.get(target));
            else if (target > Cell.size()) pawn.goToCell(Cell.get(2 * Cell.size() - target));
        }
    }

    /**
     * Player events listener
     */
    public class Listener implements EventListener<Event> {

        /**
         * List of events for:
         *   - pass turn
         *   - start turn
         *   - end turn
         */
        private LinkedList<ActionEvent<Event>> passEvent, startEvent, endEvent;

        public Listener() {
            passEvent  = new LinkedList<ActionEvent<Event>>();
            startEvent = new LinkedList<ActionEvent<Event>>();
            endEvent = new LinkedList<ActionEvent<Event>>();
        }

        /**
         * Run action for the triggered event
         * @param event
         */
        @Override
        public void trigger(Event event) {
            LinkedList<ActionEvent<Event>> list;
            switch (event.getName()) {
                case "pass": list = passEvent;break;
                case "play": list = startEvent;break;
                case "end" : list = endEvent; break;
                default: return;
            }

            runAll(list, event);
        }

        /**
         * Add the given action for the given event
         * @param name
         * @param event
         */
        @Override
        public void add(String name, ActionEvent event) {
            switch (name) {
                case "pass": passEvent.add(event);break;
                case "play": startEvent.add(event);break;
                case "end": endEvent.add(event);break;
            }
        }
    }

    private BufferedImage  icon;

    public Player (String name) {
        this.name = name;
        listener = new Listener();
    }

    public Listener listener () {
        return listener;
    }

    @Override
    public String toString() {
        return name;
    }

    public void setIcon (String path) {
        try {
            icon = ImageIO.read(new File(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void draw(Graphics graphics, int x, int y) {
       if (icon != null)
          graphics.drawImage (icon, x, y, icon.getWidth() / 2, icon.getHeight() / 2, null);
    }
}
