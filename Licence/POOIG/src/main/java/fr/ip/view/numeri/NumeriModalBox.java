package fr.ip.view.numeri;

import fr.ip.model.numeri.NumeriPlayer;
import fr.ip.view.core.GameModalBox;
import fr.ip.model.core.Configuration;

import java.awt.*;
import java.awt.event.ActionListener;

public class NumeriModalBox extends GameModalBox<NumeriPlayer> {

    public NumeriModalBox(Frame frame, String title, boolean modal) {
        super (frame, title, modal);

        ActionListener max = getMax (Configuration.configuration.numeri);
        form.add.addActionListener (max);
        form.name.addActionListener (max);
    }

    @Override
    protected NumeriPlayer construct(String name) {
        return new NumeriPlayer(name);
    }
}
