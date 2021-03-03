package fr.ip.model.goose;

import fr.ip.model.core.Cell;
import fr.ip.model.core.Event;
import fr.ip.model.core.Pawn;
import fr.ip.model.core.Player;
import fr.ip.model.util.Facade;
import fr.ip.model.util.Message;

import fr.ip.model.core.Configuration;

import javax.swing.*;

public class GoosePlayer extends Player {

    private Pawn pawn;

    public GoosePlayer (String name) {
        super(name);

        pawn = new Pawn(this);

        if (Configuration.configuration.goose.endMode == Configuration.Goose.EndMode.ON_LAST)
            listener().add("play", new EndIfOnLastCell(pawn));
        else if (Configuration.configuration.goose.endMode == Configuration.Goose.EndMode.OVER_LAST)
            listener().add("play", new EndIfOverLastCell(pawn));

        listener().add("pass", (Event event) -> {
            Cell c = pawn.getLocation();
            c.listener().trigger(new Event.CellEvent("stay", c, pawn));
        });

        listener().add("play", (Event event) -> {
            Facade.show(new Message(name + " playing\n" + pawn.getLocation(), JOptionPane.INFORMATION_MESSAGE));
        });
    }

    public Pawn getPawn() {
        return pawn;
    }
}
