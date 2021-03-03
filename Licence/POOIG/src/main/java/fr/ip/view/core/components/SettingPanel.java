package fr.ip.view.core.components;

import fr.ip.view.core.ImageBackgroundJPanel;
import fr.ip.view.core.GameBoardPanel;
import fr.ip.view.core.SingleView;
import fr.ip.view.core.components.PrimaryButton;
import fr.ip.model.core.Configuration;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.HashMap;

public class SettingPanel extends ImageBackgroundJPanel implements SingleView {

    private class GlobalPane extends JPanel {
        GlobalPane () {
            add(new JLabel("Jeu de l'Oie et du Numéri réalisé par Maxime FLIN et Félix DESMARETZ."));
        }
    }

    private class BoardSettingPane extends JPanel {

        SpinnerNumberModel playerCount, cellCount;
        JComboBox cellOrder;

        BoardSettingPane (Configuration.Game game) {
            this (new GridLayout(5,1), game);
        }

        BoardSettingPane (LayoutManager layout, Configuration.Game game) {
            super (layout);
            playerCount = new SpinnerNumberModel(game.numberOfPlayers,1,GameBoardPanel.icons.length - 1,1);
            cellCount = new SpinnerNumberModel(game.numberOfCells,2,100,1);
            JSpinner maxPlayer = new JSpinner(playerCount),
                    cellNumber = new JSpinner(cellCount);

            JPanel playerPane = new JPanel();
            playerPane.add(new JLabel("Maximum number of players"));
            playerPane.add(maxPlayer);
            add(playerPane);

            JPanel comboPanel = new JPanel();
            comboPanel.add(new JLabel("Cell order"));
            cellOrder = new JComboBox(Configuration.Game.CellOrder.options);
            cellOrder.setSelectedIndex(game.cellOrder);
            comboPanel.add(cellOrder);
            add(comboPanel);

            JPanel cellPane = new JPanel();
            cellPane.add(new JLabel("Number of cells"));
            cellPane.add(cellNumber);
            add(cellPane);


            playerCount.addChangeListener(e -> game.numberOfPlayers = playerCount.getNumber().intValue());
            cellOrder.addActionListener(e -> game.cellOrder = cellOrder.getSelectedIndex());
            cellCount.addChangeListener(e -> game.numberOfCells = cellCount.getNumber().intValue());
        }

    }

    private class GooseSettingPanel extends BoardSettingPane {

        public GooseSettingPanel (Configuration.Game game) {
            this ((Configuration.Goose)game);   
        }

        public GooseSettingPanel (Configuration.Goose game) {
            super(new GridLayout(8,1), game);

            JPanel endMode = new JPanel();
            endMode.add(new JLabel("Choose end mode"));
            JComboBox mode = new JComboBox(Configuration.Goose.EndMode.modes);
            mode.setSelectedIndex(game.endMode);
            endMode.add(mode);
            add(endMode);

            JPanel canCohabits = new JPanel();
            JCheckBox cohabits = new JCheckBox("Can cohabits");
            cohabits.setSelected(game.cohabits);
            canCohabits.add(cohabits);
            add(canCohabits);

            JPanel askQuestions = new JPanel();
            JCheckBox questions = new JCheckBox("Ask questions");
            questions.setSelected(game.questions);
            askQuestions.add(questions);
            add(askQuestions);

            cohabits.addActionListener(e -> game.cohabits = cohabits.isSelected());
            questions.addActionListener(e -> game.questions = questions.isSelected());
            mode.addActionListener(e -> game.endMode = mode.getSelectedIndex());
        }

    }

    private class NumeriSettingPanel extends BoardSettingPane {

        public NumeriSettingPanel (Configuration.Game game) {
            this((Configuration.Numeri)game);
        }

        public NumeriSettingPanel (Configuration.Numeri game) {
            super(new GridLayout(7, 1), game);
            
            JPanel alignPanel = new JPanel();
            JCheckBox align = new JCheckBox("Replay if 3 pawns are aligns");
            align.setSelected(false);
            alignPanel.add(align);
            add(alignPanel);

            JPanel replayPanel = new JPanel();
            JCheckBox replay = new JCheckBox("One more face on the pawn");
            replay.setSelected(false);
            replayPanel.add(replay);
            add(replayPanel);

            align.addActionListener(e -> game.align = align.isSelected());
            replay.addActionListener(e -> game.replay = replay.isSelected());
        }

    }

    private BoardSettingPane goose, numeri;

    public SettingPanel() {
        super(new GridLayout(1,1));
        setImage("./assets/bkg.png");

        goose = new GooseSettingPanel(Configuration.configuration.goose);
        numeri = new NumeriSettingPanel(Configuration.configuration.numeri);

        GlobalPane globalPane = new GlobalPane();

        JTabbedPane pane = new JTabbedPane();
        pane.addTab("Global settings", null, globalPane, "General settings");
        pane.addTab("Goose settings", null, goose, "Set cells for goose game");
        pane.addTab("Numeri settings", null, numeri, "Set cells for numeri game");

        pane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
        add(pane);
    }

    @Override
    public void onOpen(HashMap<String, Object> map) {
    }

    @Override
    public void onClose () {}
}
