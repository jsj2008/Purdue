/** Copyright 2014 -- Levi Starrett
  For educational purposes only
  
  The FamilyExplorer class is an interface by which a user can explore
  a family tree
  
  It has a head attribute, corresponding to the entry point to the tree
  It is assumed that every member of the family is connected to the head
  
  The FamilyExplorer class has several commands:
  
  help
  - Prints command help
  
  quit
  - Exits the FamilyExplorer
  
  print
  - Prints summary for the current Person
  
  print [relationship] [identifier]
  - Prints summary for the specified Person
  - Identifier may be name or Group index
  - No identifier necessary for unambiguous relationships (eg spouse)
  - If no identifier provided for ambiguous relationship (eg siblings),
  the entier Group will be printed
  - No relatiohsip will throw an error
  - Valid relationships:
  + head
  + mom
  + dad
  + spouse
  + siblings
  + children
  
  goto [relationship] [identifier]
  - Behaves much like the 'print' command however changes the current Person
  to the identified Person
  - Identifier may be name or Group index
  - No identifier necessary for unambiguous relationships (eg spouse)
  - No identifier for ambiguous relationship (eg siblings) will throw
  an error
  - No relatiohsip will throw an error
  
  **/

import java.util.*;

public class FamilyExplorer {
    
    // INSTANCE VARIABLES
    private Person head;                    // instance variable reference to the head of household
    private Person current;                 // instance variable reference to the current selected Person
    private boolean running;                // instance variable status of loop
    
    // CONSTRUCTORS
    public FamilyExplorer(Person head) {
        this.head = head;
        current = this.head;
    }
    
    // INSTANCE METHODS
    /** Get cousins */
    private Group getCousins() {
        if (current == null) return null;
        Group cousins = new Group();
        Person dad = current.getDad();
        if (dad != null) {
            Group sibs = dad.getSiblings();
            if (sibs != null) {
                for (Person sib : sibs) {
                    if (sib != null && !sib.equals(dad)) {
                        Group children = sib.getChildren();
                        for (Person child : children) {
                            cousins.add(child);
                        }
                    }
                }
            }
        }
        Person mom = current.getMom();
        if (mom != null) {
            Group sibs = mom.getSiblings();
            if (sibs != null) {
                for (Person sib : sibs) {
                    if (sib != null && !sib.equals(mom)) {
                        Group children = sib.getChildren();
                        for (Person child : children) {
                            cousins.add(child);
                        }
                    }
                }
            }
        }
        return cousins;
    }
    /** Print current person */
    private void print() {
        System.out.println(current);
    }
    
    /** Print specified person */
    private void print(Person p) {
        System.out.println(p);
    }
    
    /** Print specified group */
    private void print(Group g) {
        System.out.println(g);
    }
    
    /** Switch to new current person */
    private void goTo(Person p) {
        current = p;
        print();
    }
    
    /** Parse input */
    private void parseCommand(String line) {
        // split arguments delimited by white space
        String[] args = line.split("\\s+");
        
        // check the number of aguments
        if (args.length <= 0 || args.length > 3) {
            System.out.println("Invalid number of agruments");
            return;
        }
        
        // get specified Person or Group
        Person person = null;
        Group group = null;
        
        if (args.length >= 2) {
            switch(args[1]) {
                case "head":
                    person = head;
                    break;
                case "mom":
                    person = current.getMom();
                    break;
                case "dad":
                    person = current.getDad();
                    break;
                case "spouse":
                    person = current.getSpouse();
                    break;
                case "siblings":
                    group = current.getSiblings();
                    break;
                case "children":
                    group = current.getChildren();
                    break;
                case "cousins":
                    group = getCousins();
                    break;
                default:
                    System.out.println("Invalid relationship");
                    return;
            }
        }
        if (args.length == 3) {
            try {
                int index = Integer.parseInt(args[2]);
                if (group != null && index >= 0 && index < group.size())
                    person = group.get(index);
                else {
                    System.out.println("Invalid index");
                    return;
                }
            }
            catch (NumberFormatException e) {
                if (group != null && group.get(args[2]) != null)
                    person = group.get(args[2]);
                else {
                    System.out.println("Invalid name");
                    return;
                }
            }
        }
        
        // parse command
        switch(args[0]) {
            case "print":
                if (person != null)
                print(person);
                else if (person == null && group != null)
                    print(group);
                else if (person == null && group == null && args.length == 1)
                    print();
                else
                    System.out.println("Object does not exist");
                break;
            case "goto":
                if (person != null)
                goTo(person);
                else
                    System.out.println("Invalid 'goto' command");
                break;
            case "help":
                printHelp();
                break;
            case "quit":
                running = false;
                break;
            default:
                break;
        }
        
    }
    
    /** Print help function */
    private void printHelp() {
        System.out.printf("|---------------------------------------------------------------------------------|\n");
        System.out.printf("help\n");
        System.out.printf("\t- Prints command help\n\n");
        System.out.printf("quit\n");
        System.out.printf("\t- Exits the FamilyExplorer\n\n");
        System.out.printf("print\n");
        System.out.printf("\t- Prints summary for the current Person\n\n");
        System.out.printf("print [relationship] [identifier]\n");
        System.out.printf("\t- Prints summary for the specified Person\n");
        System.out.printf("\t- Identifier may be name or Group index\n");
        System.out.printf("\t- No identifier necessary for unambiguous relationships (eg spouse)\n");
        System.out.printf("\t- If no identifier provided for ambiguous relationship (eg siblings),\n");
        System.out.printf("\t  the entier Group will be printed\n");
        System.out.printf("\t- No relatiohsip will throw an error\n");
        System.out.printf("\t- Valid relationships:\n");
        System.out.printf("\t\t+ head\n");
        System.out.printf("\t\t+ mom\n");
        System.out.printf("\t\t+ dad\n");
        System.out.printf("\t\t+ spouse\n");
        System.out.printf("\t\t+ siblings\n");
        System.out.printf("\t\t+ children\n");
        System.out.printf("goto [relationship] [identifier]\n");
        System.out.printf("\t- Behaves much like the 'print' command however changes the current Person\n");
        System.out.printf("\t  to the identified Person\n");
        System.out.printf("\t- Identifier may be name or Group index\n");
        System.out.printf("\t- No identifier necessary for unambiguous relationships (eg spouse)\n");
        System.out.printf("\t- No identifier for ambiguous relationship (eg siblings) will throw\n");
        System.out.printf("\t  an error\n");
        System.out.printf("\t- No relatiohsip will throw an error\n");
        System.out.printf("|---------------------------------------------------------------------------------|\n");
    }
    
    /** Loop and take commands */
    public void explore() {
        Scanner sc = new Scanner(System.in);
        running = true;
        while (running) {
            System.out.print(">>> ");
            System.out.flush();
            if (sc.hasNextLine()) 
                parseCommand(sc.nextLine());
            else running = false;
        }
    }
    
}
