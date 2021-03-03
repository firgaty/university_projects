package fr.ip.model.goose;

import fr.ip.model.core.Game;
import fr.ip.model.core.Player;

public class GooseGame extends Game {

    private GooseCell first;
		private static int length;

    public GooseGame(int length) {
        super(length);
				GooseGame.length = length;
    }

    public void setup () {
        // setup cells
        first = new GooseCell();
        for (int i = 0; i < length - 1; i++)
            new GooseCell();

        for (Player p: players)
            ((GoosePlayer)p).getPawn().goToCell(first);
    }

    public boolean isEnd () {
        for (Player player : this)
            if (((GoosePlayer)player).getPawn().getLocation().id == length)
                return true;
        return false;
    }

		public static int getSize() {
				return length;
		}

}
