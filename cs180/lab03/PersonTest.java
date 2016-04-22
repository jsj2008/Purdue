import junit.framework.TestCase;
/**
 * CS180 - Lab 03 - PersonTest.java
 *
 * A JUnit test case class to test 
 * the methodality of the Person class.
 *
 * @author (krustagi) <krustagi@purdue.edu>
 *
 * @lab 806
 *
 * @date 09/17/2014
 */

/**
 * A JUnit test case class.
 * Every method starting with the word "test" will be called when running
 * the test with JUnit.
 */
public class PersonTest extends TestCase {
    // declare instance variables
    private Person adult_badTC;
    private Person adult_badLDL;
    private Person adult_badHDL;
    private Person adult_goodTC;
    private Person adult_goodLDL;
    private Person adult_goodHDL;
    private Person child_badTC;
    private Person child_badLDL;
    private Person child_badHDL;
    private Person child_goodTC;
    private Person child_goodHDL;
    private Person child_goodLDL;
    
    
    /**
     * set up the test case, called before each test
     */
    protected void setUp() throws Exception {
        super.setUp();
        // initialize test people
        adult_badTC = new Person("0022212341",21,100,100,100);
        adult_badLDL = new Person("0022212342",18,131,100,100);
        adult_badHDL = new Person("0022212343",45,100,39,100);
        adult_goodTC = new Person("0022212344",60,100,50,49);
        adult_goodLDL = new Person("0022212345",19,130,100,4);
        adult_goodHDL = new Person("0022212346",20,130,40,100);
        child_badTC = new Person("0022212347",13,100,100,100);
        child_badLDL = new Person("0022212348",17,200,100,100);
        child_badHDL = new Person("0022212349",12,100,10,100);
        child_goodTC = new Person("0022212350",15,100,60,9);
        child_goodLDL = new Person("0022212351",10,110,100,100);
        child_goodHDL = new Person("0022212352",17,100,40,100);
    }
    /**
     * A test method.
     * (Replace "X" with a name describing the test.  You may write as
     * many "testSomething" methods in this class as you wish, and each
     * one will be called when running JUnit over this class.)
     */
    // test methods  
    /**
     * Tests the getTotalCholesterol method.
     */
    public void testGetTotalCholesterol() {
        // write code to test the getTotalCholesterol() method here
        //Example
        assertEquals(300, adult_badTC.getTotalCholesterol());
    }
    
    /**
     * Tests the hasGoodTotalCholesterol method.
     */
    public void testHasGoodTotalCholesterol() {
        // write code to test the hasGoodTotalCholesterol method here
        assertEquals(true,adult_goodTC.hasGoodTotalCholesterol());
        assertEquals(false,adult_badTC.hasGoodTotalCholesterol());
        assertEquals(false,child_badTC.hasGoodTotalCholesterol());
        assertEquals(true,child_goodTC.hasGoodTotalCholesterol());
        //Example
        assertFalse(adult_badTC.hasGoodTotalCholesterol()); 
    }
    
    /**
     * Tests the hasGoodLDL method.
     */
    public void testHasGoodLDL() {
        // write code to test the hasGoodLDL() method here
        assertEquals(true,adult_goodLDL.hasGoodLDL());
        assertEquals(false,adult_badLDL.hasGoodLDL());
        assertEquals(false,child_badLDL.hasGoodLDL());
        assertEquals(true,child_goodLDL.hasGoodLDL());
        assertTrue(adult_badTC.hasGoodLDL()); 
    }
    
    /**
     * Tests the hasGoodHDL method.
     */
    public void testHasGoodHDL() {
        // write code to test the hasGoodHDL() method here
        assertEquals(true,adult_goodHDL.hasGoodHDL());
        assertEquals(false,adult_badHDL.hasGoodHDL());
        assertEquals(false,child_badHDL.hasGoodHDL());
        assertEquals(true,child_goodHDL.hasGoodHDL());
        assertTrue(adult_badTC.hasGoodHDL()); 
    }
}