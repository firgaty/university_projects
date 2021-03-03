package fr.ip.view.core.components;

import javax.swing.*;
import java.awt.*;
import javax.swing.border.EmptyBorder;
import javax.swing.AbstractButton;
import javax.swing.JComponent;
import javax.swing.plaf.basic.BasicButtonUI;

public class PrimaryButton extends JButton {

		private static final Font font = new Font ("Helvetica", Font.PLAIN, 14);

		private class Style extends BasicButtonUI {

				@Override
				public void installUI (JComponent component) {
						super.installUI(component);
						AbstractButton button = (AbstractButton) component;
						button.setOpaque(false);
						button.setBorder(new EmptyBorder(5, 15, 5, 15));
				}

				@Override
				public void paint (Graphics graphics, JComponent component) {
						Dimension size = component.getSize();
						Graphics2D g2 = (Graphics2D) graphics;
						g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
						graphics.setColor(((AbstractButton)component).getModel().isPressed() ? component.getBackground() : component.getBackground().darker());
						graphics.fillRoundRect(0, 0, size.width, size.height, 10, 10);

						super.paint(graphics, component);
				}

		}

    public PrimaryButton(String name) {
        super (name);
				setBackground (new Color(0x2dce98));
				setForeground (Color.white);
				setFont(font);
				setUI(new Style());
    }

}
