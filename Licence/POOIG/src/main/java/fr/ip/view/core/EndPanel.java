package fr.ip.view.core;

import fr.ip.view.core.components.PrimaryButton;

import javax.swing.*;
import java.awt.*;
import java.util.HashMap;

public class EndPanel extends ImageBackgroundJPanel.ImageBackgroundView {

    private String target = "goose";
    private JLabel win;

    public EndPanel() {
        super(new BorderLayout(30, 30));
        setImage("./assets/bkg.png");

        win = new JLabel("J1 won !");
        win.setFont(new Font("Helvetica", Font.BOLD, 30));
        win.setForeground(Color.WHITE);
        add(win, BorderLayout.NORTH);

        Icon gif = new ImageIcon("./assets/winner.gif");
        add(new JLabel(gif), BorderLayout.CENTER);

        JPanel footer = new JPanel();
        PrimaryButton menuButton = new PrimaryButton("Menu"),
                again      = new PrimaryButton("Play again");
        footer.add(menuButton);
        footer.add(again);
        add(footer, BorderLayout.SOUTH);

        menuButton.addActionListener(e -> MainFrame.set("menu"));
        again.addActionListener(e -> MainFrame.set(target));
    }

    @Override
    public void onOpen(HashMap<String, Object> map) {
        super.onOpen(map);
        target = map.get("target").toString();
        win.setText(map.get("win").toString() + " won !");

        MainFrame.canRestart(false);
    }

}
