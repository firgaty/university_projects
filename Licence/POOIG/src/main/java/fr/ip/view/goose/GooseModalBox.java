package fr.ip.view.goose;

import fr.ip.model.core.Configuration;
import fr.ip.model.goose.GoosePlayer;
import fr.ip.view.core.GameModalBox;

import java.awt.*;
import java.awt.event.ActionListener;

public class GooseModalBox extends GameModalBox<GoosePlayer> {

    public GooseModalBox(Frame frame, String title, boolean modal) {
        super (frame, title, modal);

        ActionListener max = getMax(Configuration.configuration.goose);
        form.add.addActionListener (max);
        form.name.addActionListener (max);
    }

    @Override
    protected GoosePlayer construct(String name) {
        return new GoosePlayer(name);
    }
}
