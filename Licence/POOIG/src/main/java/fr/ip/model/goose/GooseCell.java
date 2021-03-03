package fr.ip.model.goose;

import fr.ip.model.core.Cell;
import fr.ip.model.core.Event;
import fr.ip.model.core.Game;
import fr.ip.model.util.Facade;
import fr.ip.model.util.Message;
import fr.ip.model.core.Configuration;

import javax.swing.*;

public class GooseCell extends Cell {

    public GooseCell () {
        super();
        if (id != 1 && id != GooseGame.getSize() && id != 4)
            if (!Configuration.configuration.goose.cohabits)
                new SinglePawnCell(false);

        if (id == 4) new TrapCell();
        if (id == 6 || id == 9) new CounterCell(2);
        if (id % 5 == 0 && id != GooseGame.getSize()) new JumpCell(1);
        if (id == 8) listener().add("enter", (Event.CellEvent e) -> {
            Facade.show(new Message("Play again"));
            Game.getInstance().playAgain();
            e.stopPropagation();
        });
        if (Configuration.configuration.goose.questions && id % 5 == 0)
            new QuestionCell(
                    (Event.CellEvent event) -> {
                        Facade.show(new Message("Correct answer"));
                        Game.getInstance().playAgain();
                    },
                    (Event.CellEvent event) -> Facade.show(new Message("It's a fail loser !")));
    }
}
