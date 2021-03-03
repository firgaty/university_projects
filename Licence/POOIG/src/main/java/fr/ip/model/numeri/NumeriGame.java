package fr.ip.model.numeri;

import fr.ip.model.core.Game;
import fr.ip.model.core.Pawn;
import fr.ip.model.core.Player;

public class NumeriGame extends Game {

		private static int length;

    public NumeriGame (int length) {
        super(length);
				NumeriGame.length = length;
    }

    @Override
    public void setup() {
        NumeriCell first = new NumeriCell();
        for (int i = 1; i < length; i++)
            new NumeriCell();

        for (Player p: players)
            for(Pawn pawn: ((NumeriPlayer)p).pawns())
                pawn.goToCell(first);
    }

    @Override
    public boolean isEnd() {
        // bad implementation, to rework
        int c = 0;
        for (Player player : this)
            for (Pawn p : ((NumeriPlayer)player).pawns())
                if (p.getLocation().id > length - 3) {
                    c++;
                    if (c == 3) return true;
                }
        return false;
    }

		public static int getSize() {
				return length;
		}
}
