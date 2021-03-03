package fr.ip.view.core.components;

import fr.ip.model.core.Pawn;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.LinkedList;
import java.io.IOException;
import java.io.File;
import javax.imageio.ImageIO;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.lang.InterruptedException;
import java.lang.Thread;
import java.util.Random;

public class CellButton extends JButton {

    private LinkedList<Pawn> pawns;

    private BufferedImage image;

    private final static String[] paths = {
        "./assets/terre.png",
        "./assets/jupiter.png",
        "./assets/mars.png",
        "./assets/mercure.png",
        "./assets/neptune.png",
        "./assets/moon.png",
        "./assets/saturne.png",
        "./assets/venus.png",
        "./assets/death-star.png",
        "./assets/uranus.png"
    };

    private static final Random rand = new Random();
    private static final Font font = new Font ("Helvetica", Font.BOLD, 20);
    private int rotation, direction; 

    public CellButton (String name) {
        super(name);
        pawns = new LinkedList<>();

        try {
            image = ImageIO.read(new File(paths[rand.nextInt(paths.length)]));
        } catch (IOException e) {
            e.printStackTrace();
        }

        rotation = rand.nextInt(360);
        direction = rand.nextInt(2);

        new Thread(() -> {
            try {
                Thread.sleep(rand.nextInt(500));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            while (true) {
                rotation += direction == 1 ? 1 : -1;
                repaint();

                try {
                    Thread.sleep(20);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();

        setBorderPainted(false);
        setBorder(null);
        setContentAreaFilled(false);
    }

    @Override
    protected void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);

        double rotationRequired = Math.toRadians (rotation);
        double locationX = image.getWidth() / 2;
        double locationY = image.getHeight() / 2;
        AffineTransform tx = AffineTransform.getRotateInstance(rotationRequired, locationX, locationY);
        AffineTransformOp op = new AffineTransformOp(tx, AffineTransformOp.TYPE_BILINEAR);

        // Drawing the rotated image at the required drawing locations
        int x = (int)(getWidth() / 2 - locationX), y = (int)(getHeight() / 2 - locationY);
        ((Graphics2D)graphics).drawImage(op.filter(image, null), x, y, null);

        graphics.setColor(Color.white);
        graphics.setFont(font);
        graphics.drawString(getText(), getWidth() / 2, getHeight());
        String s = "";
        for (int i = 0; i < pawns.size(); i++)
            pawns.get(i).draw(graphics, 0, 0 + (i + 1) * 10);
    }

    public void add (Pawn pawn) {
        pawns.add(pawn);
        setEnabled(false);
    }

    public void remove (Pawn pawn) {
        pawns.remove(pawn);
        if (pawns.size() == 0)
            setEnabled(true);
    }

}
