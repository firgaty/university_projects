package fr.ip.view.core;
import fr.ip.view.core.components.SettingPanel;
import fr.ip.view.goose.GoosePanel;
import fr.ip.view.numeri.NumeriPanel;

import javax.swing.*;
import java.awt.*;
import java.util.HashMap;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.io.File;

public class MainFrame extends JFrame {

    private HashMap<String, SingleView> map;
    private CardLayout cl;
    public static MainFrame instance = null;
    private String current;
    private final JMenuItem restart;

    public MainFrame() {
        super();
        if (instance == null) instance = this;
        map = new HashMap<>();
        cl = new CardLayout();

        setTitle("Game");
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(750, 750));
        getContentPane().setLayout(cl);
        
        addView("menu", new Menu());
        addView("numeri", new NumeriPanel());
        addView("goose", new GoosePanel());
        addView("settings", new SettingPanel());
        addView("end", new EndPanel());

        JMenuBar bar = new JMenuBar();
        JMenu game = new JMenu("Game");
        restart = new JMenuItem("Restart");
        JMenuItem menu = new JMenuItem("Menu"),
                  goose = new JMenuItem("Goose game"),
                  numeri = new JMenuItem("Numeri game"),
                  setting = new JMenuItem("Settings");

        game.add(restart);
        game.add(menu);
        game.add(goose);
        game.add(numeri);
        bar.add(game);
        bar.add(setting);
        setJMenuBar(bar);

        restart.setEnabled(false);
        restart.addActionListener(e -> {
            String tmp = current;
            set("menu");
            set(tmp);
        });
        menu.addActionListener(e -> set("menu"));
        goose.addActionListener(e -> set("goose"));
        numeri.addActionListener(e -> set("numeri"));
        setting.addActionListener(e -> set("settings"));


        setVisible(true);

        try {
            AudioInputStream audioIn = AudioSystem.getAudioInputStream(new File("./assets/theme.wav"));
            Clip clip = AudioSystem.getClip();
            clip.open(audioIn);
            clip.start();
            clip.loop(Clip.LOOP_CONTINUOUSLY);
        } catch (Exception e) {
            //e.printStackTrace();
            System.err.println("Can play music: ./assets/theme.wav");
        }
    }

    public static void canRestart (boolean can) {
        instance.restart.setEnabled(can);
    }

    public static <T extends Component & SingleView> void addView (String name, T c) {
        instance.getContentPane().add(name, c);
        instance.map.put(name, c);
    }

    public static void set (String name, HashMap<String, Object> map) {
        if (instance.map.get(instance.current) != null)
            instance.map.get(instance.current).onClose();

        instance.current = name;
        instance.setTitle("Game - " + name);
        instance.map.get(name).onOpen(map);
        instance.cl.show(instance.getContentPane(), name);
    }

    public static void set(String name) {
        set(name, null);
    }
}
