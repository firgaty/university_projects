package fr.ip.model.numeri;

import fr.ip.model.core.*;
import fr.ip.model.util.Facade;
import fr.ip.model.util.Message;
import fr.ip.model.core.Configuration;

import javax.swing.*;
import java.util.*;
import java.awt.Graphics;

public class NumeriPlayer extends Player {

    private NumeriPawn[] pawns;
    private static final Random rand = new Random();

    public class NumeriPawn extends Pawn {

        public final int id;

        public NumeriPawn(Player p, int id) {
            super(p);
            this.id = id;
        }

        @Override
        public String toString() {
            return NumeriPlayer.this.toString() + "(" + id + ")";
        }

        
        public void draw(Graphics graphics, int x, int y) {
            super.draw(graphics, x, y);
            graphics.drawString(id + "", x + 25, y + 60);
        }
    }

    public NumeriPlayer (String name) {
        super (name);

        pawns = new NumeriPawn[6];
        for (int i = 0; i < 6; i++)
            pawns[i] = new NumeriPawn(this, i + 1);

        listener().add("play", (Event event) -> {
            int offset = Configuration.configuration.numeri.replay ? 0 : 1;
            int number = rand.nextInt(6 - offset) + offset;
            int[] ids;

            if (number == 0) {
                String[] back = Facade.read("You made 0, you can move a pawn backward").split(",");
                NumeriPlayer target = (NumeriPlayer)Game.getInstance().getPlayerByName(back[0]);
                Pawn pawn = target.pawns()[Integer.parseInt(back[1]) - 1];
                pawn.goToCell(pawn.getLocation().next(1, false));
                number = rand.nextInt(5) + 1;
            }

            while (true) {
                String ans = Facade.read(this + "\nYou made " + number + "\nSelect your pawns: ");
                if (ans != null) {
                    ids = Arrays.stream(ans.split(","))
                            .map(Integer::parseInt)
                            .mapToInt(Integer::intValue)
                            .distinct()
                            .toArray();
                    if (Arrays.stream(ids).sum() == number) break;
                }
                Facade.show(new Message("Wrong combinaison", JOptionPane.ERROR_MESSAGE));
            }

            for (int id: ids)
                pawns[id - 1].goToCell(pawns[id - 1].getLocation().next(1));

            String show = "";
            for (Pawn pawn: pawns)
                show += pawn.getLocation() + "\n";
            Facade.show(new Message(show, JOptionPane.INFORMATION_MESSAGE));

            if (Configuration.configuration.numeri.align && isAlignement()) {
                Facade.show(new Message("3 of your pawns are aligns. You can replay"));
                Game.getInstance().playAgain();
            }
        });

    }

    private boolean isAlignement() {
        for (Pawn p1: pawns)
          if (p1.getLocation().id != 1)
            for (Pawn p2: pawns)
              if (p2.getLocation().id == p1.getLocation().id + 1)
                for (Pawn p3: pawns)
                  if (p3.getLocation().id == p2.getLocation().id + 1) return true;
        return false;
    }

    public NumeriPawn[] pawns () {
        return pawns;
    }

}
