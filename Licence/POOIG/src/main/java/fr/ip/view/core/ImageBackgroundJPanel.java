package fr.ip.view.core;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.lang.Thread;
import java.util.Random;
import java.util.ArrayList;
import java.lang.InterruptedException;
import java.util.HashMap;
import java.util.Arrays;
import java.util.List;

public class ImageBackgroundJPanel extends JPanel {

    protected BufferedImage image;
    public final static Color TRANSPARENT = new Color(0,0,0,0);
    private final static Random rand = new Random();

    public static class ImageBackgroundView extends ImageBackgroundJPanel implements SingleView {

        protected static int offset = 0;
        protected static List<Meteor> meteors;
        protected static ImageBackgroundView instance = null;

        protected static Thread manager = new Thread(() -> {
            while (true) {
                offset = (offset + 1) % instance.getWidth();

                for (Meteor meteor : meteors) {
                    meteor.x += meteor.speed;
                    meteor.y += meteor.speed;
                    if (meteor.x >= instance.getWidth() || meteor.y >= instance.getHeight())
                        meteor.initPosition();

                }

                try {
                    Thread.sleep(20);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                instance.repaint();
            }
      });


         private class Meteor {
             
             private BufferedImage image;
             private int x, y, speed;
             private final static int max = 350, maxSpeed = 4;

             public Meteor (String path) {
                 try {
                     image = ImageIO.read(new File(path));
                 } catch (IOException e) {
                     e.printStackTrace();
                 }

                x = rand.nextInt(250) + 100;
                y = - image.getHeight() - rand.nextInt(300);
                speed = rand.nextInt(Meteor.maxSpeed - 1) + 3;
             }

            public void initPosition () {
                x = rand.nextInt(getWidth() - 250);
                y = - image.getHeight() - rand.nextInt(300);
                speed = rand.nextInt(Meteor.maxSpeed - 1) + 3;
            }

             public void draw (Graphics graphics) {
                 graphics.drawImage(image, x, y, ImageBackgroundView.this);
             }

         }


         public ImageBackgroundView (LayoutManager layout) {
             super(layout);
            if (meteors == null) {
                meteors = Arrays.asList(
                  new Meteor("./assets/meteor_groupe.png"),
                  new Meteor("./assets/meteor_seul.png"),
                  new Meteor("./assets/meteor_seul.png"));
            }
        }

         public ImageBackgroundView () {
             this(new GridBagLayout());
         }

         @Override
         public void paintComponent(Graphics graphics) {
            super.paintComponent(graphics);
            if (image != null) {
                this.drawSafeResize(graphics, image, offset, 0);
                this.drawSafeResize(graphics, image, offset - getWidth(), 0);
            }
             for (Meteor cloud: meteors)
               cloud.draw(graphics);
         }

        protected void drawSafeResize(Graphics graphics, BufferedImage img, int x, int y) {
            graphics.drawImage(img, x, y, getWidth(), getHeight(), this);
        }
         
         public void onOpen (HashMap<String, Object> map) {
            instance = this;
             if (manager.getState() == Thread.State.NEW)
               manager.start();
         }

         public void onClose () {
         }

     }

    public ImageBackgroundJPanel(LayoutManager layout) {
        super(layout);
        setBackground(TRANSPARENT);
         
    }

    public ImageBackgroundJPanel() {
        this (new GridBagLayout());
    }

    public void setImage(String filepath) {
        try {
            image = ImageIO.read(new File(filepath));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        if (image != null) drawSafeResize(graphics, image, 0, 0);
    }

    protected void drawSafeResize(Graphics graphics, BufferedImage img, int x, int y) {
        int w = img.getWidth(), h = img.getHeight();
        if (getWidth() > w) {
            h *= getWidth() / w;
            w = getWidth();
        }

        if (getHeight() > h) {
            w *= getHeight() / h;
            h = getHeight();
        }

        graphics.drawImage(img, x, y, w, h, this);
    }
}
