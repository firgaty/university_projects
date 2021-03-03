package fr.ip.model.util;

import fr.ip.view.core.MainFrame;

import javax.swing.*;
import java.util.Scanner;

public abstract class Facade {

    private static Facade instance = null;

    public static class CommandLine extends Facade {

        private static Scanner scanner = new Scanner(System.in);

        public CommandLine () {
            super();
        }

        @Override
        protected void showEntry(Message message) {
            System.out.println(message);
        }

        @Override
        protected String readEntry(String head) {
            System.out.println(head);
            return scanner.nextLine();
        }
    }

    public static class Gui extends Facade {

        @Override
        protected void showEntry(Message message) {
            String[] options = {"OK"};
            JOptionPane.showOptionDialog(MainFrame.instance,
                    message.toString(), "Title", JOptionPane.DEFAULT_OPTION,
                    message.type, null, options, options[0]);
        }

        @Override
        protected String readEntry(String head) {
            return JOptionPane.showInputDialog(MainFrame.instance, head, "Title", JOptionPane.QUESTION_MESSAGE);
        }
    }

    public Facade () {
        if (instance == null)
            instance = this;
    }

    protected abstract void showEntry (Message message);

    protected abstract String readEntry (String head);

    public static void show (Message message) {
        instance.showEntry(message);
    }

    public static String read (String head) {
        return instance.readEntry(head);
    }

    public static String read () {
        return instance.readEntry("");
    }

}
