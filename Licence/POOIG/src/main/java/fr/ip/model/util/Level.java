package fr.ip.model.util;

import javax.swing.*;

public enum Level {
    BEGINNER("Débutant"),
    INTERMEDIATE("Intermédiaire"),
    EXPERIENCED("Confirmé"),
    EXPERT("Expert"),
    ANY("Mixte");

    private String name;

    Level(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    public static Level levelFromString(String level) {
        switch (level.toLowerCase()) {
            case "débutant":
                return Level.BEGINNER;
            case "debutant":
                return Level.BEGINNER;
            case "intermédiaire":
                return Level.INTERMEDIATE;
            case "intermediaire":
                return Level.INTERMEDIATE;
            case "confirmé":
                return Level.EXPERIENCED;
            case "confirme":
                return Level.EXPERIENCED;
            case "expert":
                return Level.EXPERT;
            case "mixte":
                return Level.ANY;
            default:
                Facade.show(new Message("Niveau de question non spécifié ou incorrect.", JOptionPane.WARNING_MESSAGE));
                return null;
        }
    }

    public static boolean isLevel(String level) {
        switch (level.toLowerCase()) {
            case "débutant":
                return true;
            case "debutant":
                return true;
            case "intermédiaire":
                return true;
            case "intermediaire":
                return true;
            case "confirmé":
                return true;
            case "confirme":
                return true;
            case "expert":
                return true;
            case "mixte":
                return true;
            default:
                return false;
        }
    }
}