package fr.ip.model.util;

import java.util.ArrayList;
import java.util.function.Predicate;

public class Question implements Predicate<String> {

    public final String question;
    public final String answer;

    @Override
    public boolean test(String s) {
        return answer.equals(s.toLowerCase().trim());
    }

    public Question(String question, String answer) {
        this.question = question;
        this.answer = answer.toLowerCase().trim();
    }
}
