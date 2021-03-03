package fr.ip.view.core;

import fr.ip.model.core.Player;
import fr.ip.model.core.Configuration;

import fr.ip.view.core.components.PrimaryButton;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.util.ArrayList;
import java.util.Iterator;

public abstract class GameModalBox<T extends Player> extends JDialog{

    public class Output implements Iterable<T> {
        private final ArrayList<T> players;
        private boolean cancel;

        public Output () {
            players = new ArrayList<>();
            cancel = true;
        }

        public int size () {
            return players.size();
        }

        @Override
        public Iterator<T> iterator() {
            return players.iterator();
        }

        public boolean isCancel() {
            return cancel;
        }
    }

    protected class Form extends JPanel {

        public DefaultListModel<Player> listModel;
        public JTextField name;
        public PrimaryButton add, rm;
        public JList list;

        public Form() {
            name = new JTextField(10);
            add = new PrimaryButton("+");
            rm = new PrimaryButton("-");
            rm.setEnabled(false);

            JPanel in = new JPanel();
            in.add(name);
            in.add(add);
            in.add(rm);

            listModel = new DefaultListModel<>();

            list = new JList(listModel);
            list.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
            list.setLayoutOrientation(JList.HORIZONTAL_WRAP);
            list.setVisibleRowCount(-1);

            JScrollPane scrollPane = new JScrollPane(list);
            scrollPane.setPreferredSize(new Dimension(230, 300));

            setLayout(new BorderLayout());
            add(in, BorderLayout.NORTH);
            add(list, BorderLayout.CENTER);
        }

    }

    protected class Control extends JPanel {

        public PrimaryButton done, cancel;

        public Control () {
            done = new PrimaryButton("Done");
            cancel = new PrimaryButton("Cancel");
            done.setEnabled(false);
            add(done);
            add(cancel);
        }
    }

    protected Output out;
    protected Form form;
    protected Control control;

    public GameModalBox (Frame parent, String title, boolean modal) {
        super(parent, title, modal);
        out = new Output();

        setSize(new Dimension(250, 400));
        initComponents();
    }

    private void initComponents() {
        JPanel head = new JPanel();
        head.add(new JLabel("Add players"));

        form = new Form();
        control = new Control();

        ActionListener add = e -> {
            String name = form.name.getText().trim();
            if (!name.isEmpty()) {
                for (Player p : out.players)
                    if (p.name.equals(name)) {
                        JOptionPane.showMessageDialog(GameModalBox.this,
                                name + " is taken",
                                "Invalid username",
                                JOptionPane.ERROR_MESSAGE);
                        return;
                    }

                T p = construct(name);
                out.players.add(p);
                form.listModel.addElement(p);
                form.name.setText("");
                form.rm.setEnabled(true);
                control.done.setEnabled(true);
            } else if (!out.players.isEmpty())
                control.done.doClick();
        };

        form.add.addActionListener(add);
        form.name.addActionListener(add);
        form.rm.addActionListener(e -> {
            int index = form.list.getSelectedIndex();
            if (index != -1) {
                form.listModel.remove(index);
                out.players.remove(index);

                if (form.listModel.getSize() == 0) {
                    form.rm.setEnabled(false);
                    control.done.setEnabled(false);
                } else if (index == form.listModel.getSize()) {
                    index--;
                    form.list.setSelectedIndex(index);
                    form.list.ensureIndexIsVisible(index);
                }

                form.add.setEnabled(true);
                form.name.setEnabled(true);
            }
        });

        control.done.addActionListener(e -> {
            setVisible(false);
            out.cancel = false;
        });
        control.cancel.addActionListener(e -> setVisible(false));

        setLayout(new BorderLayout());
        add(head, BorderLayout.CENTER);
        add(form, BorderLayout.CENTER);
        add(control, BorderLayout.SOUTH);
    }

    public Output showGameModalBox () {
        setVisible(true);
        return out;
    }

    protected abstract T construct (String name);

    protected ActionListener getMax (Configuration.Game game) {
        return e -> {
            if (out.size() + 1 == game.numberOfPlayers) {
                form.add.setEnabled(false);
                form.name.setEnabled(false);
            }
        };
    }

}
