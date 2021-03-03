package fr.ip.model.util;

import javax.swing.*;

public class Message {
    public final int type;
    public final String content;

    public Message (String content) {
        this(content, JOptionPane.INFORMATION_MESSAGE);
    }

    public Message(String content, int type) {
        this.type = type;
        this.content = content;
    }

    @Override
    public String toString() {
        return content;
    }

}