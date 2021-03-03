package fr.ip.model.numeri;

import fr.ip.model.core.Cell;

public class NumeriCell extends Cell {

    public final int value;

    public NumeriCell () {
        super();
        if (id != 1 && id != NumeriGame.getSize())
            new SinglePawnCell(true);

        if (id <= 3) value = -3;
        else if (id == 4 || id == 5) value = -2;
        else if (id == 6 || id == 7) value = -1;
        else if (id == 10) value = 1;
        else if (id == 13) value = 2;
        else if (id == 15) value = 3;
        else if (id == 17) value = 4;
        else if (id == 19) value = 5;
        else if (id == 20) value = 6;
        else if (id == 23) value = 7;
        else if (id == 25) value = 8;
        else if (id == 27) value = 9;
        else if (id == 28) value = 10;
        else if (id == 31) value = 11;
        else if (id == 32) value = 12;
        else if (id == 34) value = 13;
        else if (id == 35) value = 15;
        else if (id == 38) value = 20;
        else if (id == 39) value = 25;
        else if (id == 40) value = 30;
        else value = 0;

    }

}
