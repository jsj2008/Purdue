/** Copyright 2014 -- Levi Starrett
    For educational purposes only

    TheJohnsons creates a particular family tree and family
    explorer to explore it.

    */

public class TheJohnsons {

    public static void main(String[] args) {
        Person p01 = new Person("Marty", 70, Person.MALE);
        Person p02 = new Person("Becky", 69, Person.FEMALE);

        Person p03 = new Person("Marty Jr.", 49, Person.MALE);
        Person p04 = new Person("Jenny", 47, Person.FEMALE);
        Person p05 = new Person("Marty III", 27, Person.MALE);
        Person p06 = new Person("Emily", 25, Person.FEMALE);
        Person p07 = new Person("Kim", 22, Person.FEMALE);

        Person p08 = new Person("Keith", 49, Person.MALE);
        Person p09 = new Person("Sarah", 49, Person.FEMALE);
        Person p10 = new Person("Tim", 24, Person.MALE);
        Person p11 = new Person("Annie", 24, Person.FEMALE);
        Person p12 = new Person("Richard", 2, Person.MALE);
        Person p13 = new Person("Hank", 26, Person.MALE);
        Person p14 = new Person("Brittany", 22, Person.FEMALE);
        Person p15 = new Person("Ben", 20, Person.MALE);
        Person p16 = new Person("Sydney", 16, Person.FEMALE);

        Person p17 = new Person("Jake", 48, Person.MALE);
        Person p18 = new Person("Natalie", 42, Person.FEMALE);
        Person p19 = new Person("Zack", 13, Person.MALE);

        Person p20 = new Person("John", 74, Person.MALE);
        Person p21 = new Person("Barb", 72, Person.FEMALE);

        Person p22 = new Person("Joe", 53, Person.MALE);
        Person p23 = new Person("Rachel", 47, Person.FEMALE);
        Person p24 = new Person("Anna", 19, Person.FEMALE);
        Person p25 = new Person("Heather", 17, Person.FEMALE);
        Person p26 = new Person("Kaitlin", 15, Person.FEMALE);
        Person p27 = new Person("Mikey", 5, Person.MALE);

        Person p28 = new Person("Bob", 47, Person.MALE);
        Person p29 = new Person("Tiffany", 45, Person.FEMALE);
        Person p30 = new Person("Cooper", 6, Person.MALE);

        Person p31 = new Person("Jim", 47, Person.MALE);
        Person p32 = new Person("Max", 5, Person.MALE);

        p01.setSpouse(p02);
        p02.setSpouse(p01);
        Group g01 = new Group();
        g01.add(p03);
        g01.add(p08);
        g01.add(p18);
        p01.setChildren(g01);
        p02.setChildren(g01);

        p20.setSpouse(p21);
        p21.setSpouse(p20);
        Group g02 = new Group();
        g02.add(p09);
        g02.add(p23);
        g02.add(p29);
        g02.add(p31);
        p20.setChildren(g02);
        p21.setChildren(g02);

        p08.setSpouse(p09);
        p09.setSpouse(p08);
        p08.setDad(p01);
        p08.setMom(p02);
        p09.setDad(p20);
        p09.setMom(p21);
        Group g03 = new Group();
        g03.add(p10);
        g03.add(p14);
        g03.add(p15);
        g03.add(p16);
        p08.setChildren(g03);
        p09.setChildren(g03);
        p08.setSiblings(g01);
        p09.setSiblings(g02);

        p03.setSpouse(p04);
        p04.setSpouse(p03);
        p03.setDad(p01);
        p03.setMom(p02);
        Group g04 = new Group();
        g04.add(p05);
        g04.add(p06);
        g04.add(p07);
        p03.setChildren(g04);
        p04.setChildren(g04);
        p03.setSiblings(g01);

        p17.setSpouse(p18);
        p18.setSpouse(p17);
        p18.setDad(p01);
        p18.setMom(p02);
        Group g05 = new Group();
        g05.add(p19);
        p17.setChildren(g05);
        p18.setChildren(g05);
        p18.setSiblings(g01);

        p22.setSpouse(p23);
        p23.setSpouse(p22);
        p23.setDad(p20);
        p23.setMom(p21);
        Group g06 = new Group();
        g06.add(p24);
        g06.add(p25);
        g06.add(p26);
        g06.add(p27);
        p22.setChildren(g06);
        p23.setChildren(g06);
        p23.setSiblings(g02);

        p28.setSpouse(p29);
        p29.setSpouse(p28);
        p29.setDad(p20);
        p29.setMom(p21);
        Group g07 = new Group();
        g07.add(p30);
        p28.setChildren(g07);
        p29.setChildren(g07);
        p29.setSiblings(g02);

        p31.setDad(p20);
        p31.setMom(p21);
        Group g08 = new Group();
        g08.add(p32);
        p31.setChildren(g08);
        p31.setSiblings(g02);

        for (Person p : g04) {
            p.setDad(p03);
            p.setMom(p04);
            p.setSiblings(g04);
        }

        for (Person p : g03) {
            p.setDad(p08);
            p.setMom(p09);
            p.setSiblings(g03);
        }
        p10.setSpouse(p11);
        p11.setSpouse(p10);
        Group g09 = new Group();
        g09.add(p12);
        p10.setChildren(g09);
        p11.setChildren(g09);
        p12.setDad(p10);
        p12.setMom(p11);

        p19.setDad(p17);
        p19.setMom(p18);

        for (Person p : g06) {
            p.setDad(p22);
            p.setMom(p23);
            p.setSiblings(g06);
        }

        p30.setDad(p28);
        p30.setMom(p29);

        p32.setDad(p31);

        FamilyExplorer f = new FamilyExplorer(p01);
        f.explore();
    }

}
