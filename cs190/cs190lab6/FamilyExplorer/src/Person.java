/** Copyright 2014 -- Levi Starrett
    For educational purposes only

    The Person class describes one single person in a family tree

    A person can have up to two parents, any number of siblings, one spouse,
    and any number of children

    A person has a name, an age, a gender, and a description (optional).

    **/

import java.util.*;

public class Person {

    // CONSTANTS
    public static final int MALE = 0;
    public static final int FEMALE = 1;

    // INSTANCE VARIABLES
    private String name;                    // instance attribute for the person's name
    private int age;                        // instance attribute for the person's age
    private int gender;                     // instance attribute for the person's gender, possible values: Person.MALE, Person.FEMALE

    private Person mom;                     // instance attribute reference to mom instance
    private Person dad;                     // instance attribute reference to dad instance
    private Person spouse;                  // instance attribute reference to spouse instance
    private Group siblings;                 // instance attribute reference to siblings list
    private Group children;                 // instance attribute reference to children list

    // CONSTRUCTORS
    public Person(String name, int age, int gender) {
        if (name != null)
            this.name = name;

        if (age >= 0)
            this.age = age;

        if (gender == Person.MALE || gender == Person.FEMALE)
            this.gender = gender;
    }

    // GETTERS
    public String getName() {
        return name;
    }

    public int getAge() {
        return age;
    }

    public int getGender() {
        return gender;
    }

    public Person getMom() {
        return mom;
    }

    public Person getDad() {
        return dad;
    }

    public Person getSpouse() {
        return spouse;
    }

    public Group getSiblings() {
        return siblings;
    }

    public Group getChildren() {
        return children;
    }

    public int getNumSiblings() {
        if (siblings != null)
            return siblings.size();
        else
            return 0;
    }

    public int getNumChildren() {
        if (children != null)
            return children.size();
        else
            return 0;
    }

    // SETTERS
    public void setName(String name) {
        if (name != null)
            this.name = name;
    }

    public void setAge(int age) {
        if (age >= 0)
            this.age = age;
    }

    public void setGender(int gender) {
        if (gender == Person.MALE || gender == Person.FEMALE)
            this.gender = gender;
    }

    public void setMom(Person mom) {
        this.mom = mom;
    }

    public void setDad(Person dad) {
        this.dad = dad;
    }

    public void setSpouse(Person spouse) {
        this.spouse = spouse;
    }

    public void setSiblings(Group siblings) {
        this.siblings = siblings;
    }

    public void setChildren(Group children) {
        this.children = children;
    }

    // OUTPUT

    /** Override of toString() from superclass */
    @Override
    public String toString() {
        StringBuilder output = new StringBuilder();
        Formatter f = new Formatter(output);
        f.format("|-PERSON-PROFILE--------------------------------|\n");
        f.format("| Name: %39s |\n", getName());
        f.format("| Age: %40d |\n", getAge());
        String gender = getGender() == Person.MALE ? "MALE" : "FEMALE";
        f.format("| Gender: %37s |\n", gender);
        f.format("| Number of Siblings: %25d |\n", getNumSiblings());
        f.format("| Number of Children: %25d |\n", getNumChildren());
        f.format("|-----------------------------------------------|");

        return output.toString();
    }

}
