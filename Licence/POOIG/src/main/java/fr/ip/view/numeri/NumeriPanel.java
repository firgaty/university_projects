package fr.ip.view.numeri;

import fr.ip.model.core.Game;
import fr.ip.model.core.Pawn;
import fr.ip.model.core.Player;
import fr.ip.model.core.Configuration;

import fr.ip.model.numeri.NumeriGame;
import fr.ip.model.numeri.NumeriCell;
import fr.ip.model.numeri.NumeriPlayer;

import fr.ip.view.core.GameBoardPanel;
import fr.ip.view.core.MainFrame;
import fr.ip.view.core.SingleView;
import fr.ip.view.core.components.CellButton;

import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;

public class NumeriPanel extends GameBoardPanel {

    public void onOpen (HashMap<String, Object> map) {
        super.onOpen(map);
        NumeriModalBox modal = new NumeriModalBox(MainFrame.instance, "Add players", true);
        NumeriModalBox.Output out = modal.showGameModalBox();

        if (out.isCancel()) {
            MainFrame.set("menu");
            return;
        }
        removeAll();

        game = new NumeriGame(Configuration.configuration.numeri.numberOfCells);
        for(NumeriPlayer player : out)
            game.addPlayer(player);

        game.setup();
        game.start();
        buttons = new ArrayList<>();

        setLayout(new BorderLayout());
        add(new GameControlPanel(), BorderLayout.EAST);
        add(new BoardPanel(Configuration.configuration.numeri.cellOrder), BorderLayout.CENTER);

        for (Player player: game)
            for (Pawn pawn: ((NumeriPlayer)player).pawns())
                buttons.get(pawn.getLocation().id - 1).add(pawn);

        playButton.addActionListener(e -> {
            game.playTurn();
            NumeriPlayer player = (NumeriPlayer) Game.getInstance().getCurrentPlayer();

            for (Pawn pawn : player.pawns()) {
                for (CellButton button : buttons) button.remove(pawn);
                buttons.get(pawn.getLocation().id - 1).add(pawn);
            }

            if (game.isEnd()) onEnd();
        });

        MainFrame.canRestart(true);
        revalidate();
    }

    private void onEnd () {
        playButton.setEnabled(false);
        HashMap<String, Object> map = new HashMap<>();
        map.put("target", "numeri");

        int max = 0;
        NumeriPlayer winner = null;
        for (Player p: game) {
            NumeriPlayer player = (NumeriPlayer)p;
            int score = 0;
            for (NumeriPlayer.NumeriPawn pawn: player.pawns())
                score += pawn.id * ((NumeriCell)pawn.getLocation()).value;
            if (score > max) {
                max = score;
                winner = player;
            }
        }

        map.put("win", winner.toString());

        MainFrame.set("end", map);
    }

}
