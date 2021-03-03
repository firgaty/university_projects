package fr.ip.view.goose;

import fr.ip.model.core.Cell;
import fr.ip.model.core.Game;
import fr.ip.model.core.Player;
import fr.ip.model.core.Configuration;

import fr.ip.model.goose.GoosePlayer;
import fr.ip.model.goose.GooseGame;

import fr.ip.view.core.GameBoardPanel;
import fr.ip.view.core.MainFrame;
import fr.ip.view.core.SingleView;
import fr.ip.view.core.components.CellButton;
import fr.ip.view.goose.GooseModalBox;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;

public class GoosePanel extends GameBoardPanel {

    @Override
    public void onOpen (HashMap<String, Object> map) {
        super.onOpen(map);
        GooseModalBox modal = new GooseModalBox(MainFrame.instance, "Add players", true);
        GooseModalBox.Output out = modal.showGameModalBox();

        if (out.isCancel()) {
            MainFrame.set("menu");
            return;
        }
        removeAll();

        game = new GooseGame(Configuration.configuration.goose.numberOfCells);
        for(GoosePlayer player : out)
            game.addPlayer(player);

        game.setup();
        game.start();
        buttons = new ArrayList<CellButton>();

        setLayout(new BorderLayout());
        add(new GameControlPanel(), BorderLayout.EAST);
        add(new BoardPanel(Configuration.configuration.goose.cellOrder), BorderLayout.CENTER);

        for (Player player: game) {
            GoosePlayer p = (GoosePlayer)player;
            buttons.get(p.getPawn().getLocation().id - 1).add(p.getPawn());
        }

        playButton.addActionListener(e -> {
            game.playTurn();
            GoosePlayer p = (GoosePlayer)Game.getInstance().getCurrentPlayer();

            for (int i = 0; i < Cell.size(); i++) {
                CellButton btn = buttons.get(i);
                btn.remove(p.getPawn());
            }

            CellButton btn = buttons.get(p.getPawn().getLocation().id - 1);
            btn.add(p.getPawn());

            if (game.isEnd()) onEnd();
        });

        MainFrame.canRestart(true);
        revalidate();
    }

    private void onEnd() {
        playButton.setEnabled(false);
        HashMap<String, Object> map = new HashMap<>();
        map.put("target", "goose");
        map.put("win", Game.getInstance().getCurrentPlayer().toString());

        MainFrame.set("end", map);
    }
}
