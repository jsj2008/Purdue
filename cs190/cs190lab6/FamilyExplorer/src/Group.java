/** Copyright 2014 -- Levi Starrett
    For educational purposes only

    The Group class describes a group of Person objects, implemented using
    Java ArrayList

    **/

import java.util.*;

public class Group implements Iterable<Person> {

    // INSTANCE VARIABLES
    private ArrayList<Person> group;

    // INNER CLASS
    private class GroupIterator implements Iterator<Person> {
        private int counter = 0;

        public boolean hasNext() {
            return (counter < group.size());
        }

        public Person next() {
            return get(counter++);
        }

        public void remove() {}
    }

    // CONSTRUCTORS
    public Group() {
        group = new ArrayList<Person>();
    }

    // INSTANCE METHODS

    /** Add a person to the group */
    public void add(Person p) {
        group.add(p);
    }

    /** Get a person by index */
    public Person get(int i) {
        return group.get(i);
    }

    /** Get a person by name */
    public Person get(String name) {
        for (Person p : group) {
            if (p.getName().equals(name))
                return p;
        }
        return null;
    }

    /** Get size of the group */
    public int size() {
        return group.size();
    }

    // ITERABLE METHODS
    /** Return an Iterator to satisfy implemented interface */
    @Override
    public GroupIterator iterator() {
        return new GroupIterator();
    }

    // OUTPUT

    /** Override of toString() from superclass */
    @Override
    public String toString() {
        StringBuilder output = new StringBuilder();
        Formatter f = new Formatter(output);

        f.format("|-GROUP-----------------------------------------|\n");
        f.format("|-ID---------------------------------------NAME-|\n");

        for (Person p : group) {
            f.format("| %2d %42s |\n", group.indexOf(p), p.getName());
        }

        f.format("|-----------------------------------------------|");

        return output.toString();
    }

}
