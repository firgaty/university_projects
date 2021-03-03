package fr.ip.model.util;

import javax.swing.*;
import java.io.IOException;
import java.util.ArrayList;
import java.io.File;
import java.util.Random;
import java.util.Scanner;

public class QuestionBank {

    private ArrayList<Question> questions;
    private ArrayList<Question> inUseQuestions;
    private File folder;

    public QuestionBank() {
        try {
            this.folder = new File("./assets/questions");
        } catch (NullPointerException e) {
            Facade.show(new Message("Le dossier des questions est introuvable, existe-t-il ?", JOptionPane.ERROR_MESSAGE));
            System.exit(2);
        }
        File[] fileList = folder.listFiles();
        if (fileList == null) {
            Facade.show(new Message("Aucun fichier dans le dossier questions.", JOptionPane.ERROR_MESSAGE));
            System.exit(3);
        }

        this.questions = parse(fileList);
        this.inUseQuestions = questions;
    }

    private ArrayList<Question> parse(File[] fs) {
        ArrayList<Question> list = new ArrayList<>();
        ArrayList<Question> parsed;

        for (File f : fs) {
            parsed = parse(f);
            if (parsed != null) {
                list.addAll(parsed);
                parsed = null;
            }
        }

        return list;
    }

    private ArrayList<Question> parse(File f) {
        Scanner sc;
        String canonicalPath;

        try {
            canonicalPath = f.getCanonicalPath();
            Facade.show(new Message("Opening" + canonicalPath, JOptionPane.INFORMATION_MESSAGE));
            sc = new Scanner(f);
        } catch (IOException e) {
            Facade.show(new Message("Wrong file path", JOptionPane.ERROR_MESSAGE));
            return null;
        }

        ArrayList<Question> qs = new ArrayList<>();
        String question;

        while (sc.hasNextLine()) {
            question = sc.nextLine();
            if (!sc.hasNextLine())
                break;
            qs.add(new Question(question.trim(), sc.nextLine().trim()));
        }

        return qs;
    }

    public boolean isQuestionsLeft() {
        return this.inUseQuestions.size() > 0;
    }

    public Question getRandomQuestion() {
        if (!isQuestionsLeft()) {
            Facade.show(new Message("Aucune question ne reste à être posée.", JOptionPane.ERROR_MESSAGE));
            return null;
        }

        int index = new Random().nextInt(this.inUseQuestions.size());
        Question out = this.inUseQuestions.get(index);
        this.inUseQuestions.remove(index);
        return out;
    }

    public ArrayList<Question> getInUseQuestions() {
        return inUseQuestions;
    }

    public ArrayList<Question> getQuestions() {
        return questions;
    }

    public File getFolder() {
        return folder;
    }

    public void reset() {
        this.inUseQuestions = this.questions;
        Facade.show(new Message("Les questions ont été réinitialisées.", JOptionPane.INFORMATION_MESSAGE));
    }
}