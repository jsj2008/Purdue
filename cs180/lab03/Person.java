/**
 * CS180 - Lab 03 - Person
 *
 * To check Cholesterol levels in people
 *
 * @author krustagi <krustagi@purdue.edu>
 *
 * @lab 806
 *
 * @date 9/17/2014
 */
import java.util.*;
public class Person {
    String id;
    int age,ldl,hdl,other;
    /**
     * Person Class Constructor: Creates a new instance of the person Class;
     * initializes instance variables with the given arguments:
     *
     * @param id - the person's ID
     * @param age - the person's age
     * @param ldl - the person's LDL level
     * @param hdl - the person's HDL level
     * @param other - the person's other lipids level
     */ 
    public Person(String id, int age, int ldl, int hdl, int other) {
        this.id = id;       // initialize this person's ID
        this.age = age;     // initialize this person's age
        this.ldl = ldl;     // initialize this person's LDL level
        this.hdl = hdl;     // initialize this persons's HDL level
        this.other = other; // initialize this persons's other lipids level
    }
    /**
     * computes the sum of this person's LDL, HDL, and other values.
     * @return this person's total cholesterol
     */
    public int getTotalCholesterol() {
        int tc; // the total cholesterol
        // compute the sum of ldl, hdl, and other
        tc = this.ldl + this.hdl + this.other;
        // return the computed sum
        return tc;
    }
    /**
     * @return true if the total cholesterol for this person 
     * is within the healthy range, false otherwise
     * 
     * A healthy TC level for an adult is less than 200 mg/dL.
     * A healthy TC level for a child is less than 170 mg/dL.
     */
    public boolean hasGoodTotalCholesterol() {
        // determine healthy TC level for this person
        int healthy_level; // the healthy TC level for this person
        if (this.isAdult()) {
            healthy_level = 200;
        } 
        else {
            healthy_level = 170;
        }
        // return true if the person's TC is healthy
        if (this.getTotalCholesterol() < healthy_level) {
            return true;
        } 
        else {
            return false;
        }
        
    }
    /**
     * determine if this person is an adult or a child
     * @return true if this person is an adult, false if they are a child
     */
    private boolean isAdult() {
        if (this.age >= 18) {
            return true;  // is an adult
        } else {
            return false; // is a child
        }
    }
    /**
     * @return true if the LDL level is within the healthy range, false otherwise.
     * 
     * A healthy LDL level for an adult is less than or equal to 130 mg/dL.
     * A healthy LDL level for a child is less than or equal to 110 mg/dL. 
     */
    public boolean hasGoodLDL() {
        // determine if person is an adult or child
        if (this.isAdult()) {
            // return true if the person's LDL is healthy for an adult
            if (this.ldl <= 130) {
                return true;
            } else {
                return false;
            }
        } else {
            // return true if the person's LDL is healthy for a child
            if (this.ldl <= 110) {
                return true;
            } else {
                return false;
            }
        }
    }
    /**
     * @return true if the HDL level is within the healthy range, false otherwise.
     * 
     * A healthy range for HDL is greater than or equal to 
     * 40 mg/dL for both adults and children.
     */
    public boolean hasGoodHDL() {
        // return true if person's HDL is >= 40
        return this.hdl >= 40;
    }
    /**
     * pretty print the person's cholesterol report.<br>
     * this method is useful for debugging.
     */
    public void printReport() {
        System.out.println(this.id + "'s Report");
        System.out.println("Age: " + this.age + " (" + (isAdult() ? "Adult" : "Child") + ")");
        System.out.println("Total Cholesterol: " + getTotalCholesterol() + 
                           " ("+(hasGoodTotalCholesterol()?"Good":"Bad")+")");
        System.out.println("LDL: " + this.ldl + " (" + (hasGoodLDL() ? "Good" : "Bad") + ")");
        System.out.println("HDL: " + this.hdl + " (" + (hasGoodHDL() ? "Good" : "Bad") + ")");
    }
}
