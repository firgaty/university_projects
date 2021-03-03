package fr.ip.view.core;

import fr.ip.view.core.components.PrimaryButton;

import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.util.HashMap;

public class Menu extends ImageBackgroundJPanel.ImageBackgroundView {

    JButton numeri, goose;

    public Menu () {
        setImage("./assets/bkg.png");

        numeri = new PrimaryButton("Play Numeri");
        goose = new PrimaryButton("Play Goose");

        goose.addActionListener(e -> MainFrame.set("goose"));
        numeri.addActionListener(e -> MainFrame.set("numeri"));

        setLayout(new BorderLayout(50, 50));
        JPanel labelPanel = new JPanel();
        labelPanel.setBackground(new Color(0,0,0,0));
        JLabel title = new JLabel();
        title.setIcon(new ImageIcon("./assets/Goose--Numeri.png"));
        labelPanel.add(title);
        labelPanel.setBorder(new EmptyBorder(150, 0, 0, 0));
        add(labelPanel, BorderLayout.CENTER);

        JPanel buttons = new JPanel(new GridLayout(1,2, 50, 0)),
                left = new JPanel(), right = new JPanel();
        left.setBackground(new Color(0,0,0,0));
        right.setBackground(new Color(0,0,0,0));
        buttons.setBackground(new Color(0,0,0,0));
        left.add(goose);
        right.add(numeri);
        buttons.add(left);
        buttons.add(right);
        buttons.setBorder(new EmptyBorder(0, 0, 100, 0));
        add(buttons, BorderLayout.SOUTH);

    }

    @Override
    public void onOpen(HashMap<String, Object> map) {
        super.onOpen(map);
        MainFrame.canRestart(false);
    }

}
