package fr.ip.model.core;

import java.awt.Graphics;

/**
 * Class Representing a pawn
 */
public class Pawn {

    /**
     * The location of the pawn
     */
    private Cell cell;

    /**
     * The player that own the pawn
     */
    private Player player;

    public Pawn(Player player) {
        this.player = player;
    }

    /**
     * Set pawn to a new location and trigger corresponding events
     * @param c target location
     */
    public void goToCell (Cell c) {
        if (cell != null)
            cell.listener().trigger(new Event.CellEvent("leave", cell, this));
        setCell(c);
        if (cell != null)
            cell.listener().trigger(new Event.CellEvent("enter", cell, this));
    }

    public void setCell (Cell c) {
        cell = c;
    }

    public Player getPlayer() {
        return player;
    }

    public Cell getLocation () {
        return cell;
    }

    public String toString () {
        return player.toString();
    }

    public void draw(Graphics graphics, int x, int y) {
        player.draw(graphics, x, y);
    }

}
