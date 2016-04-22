import junit.framework.TestCase;

/**
 * A JUnit test case class.
 * Every method starting with the word "test" will be called when running
 * the test with JUnit.
 */
public class CarLotTest extends TestCase {
    
    /**
     * A test method.
     * (Replace "X" with a name describing the test.  You may write as
     * many "testSomething" methods in this class as you wish, and each
     * one will be called when running JUnit over this class.)
     */
    public void testCapacity() {
       CarLot carLot = new CarLot(10);
        assertEquals(10,carLot.capacity());
    }
    public void testNumVehicles() {
        CarLot carLot = new CarLot(10);
        carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        assertEquals(2,carLot.numVehicles());
    }
    public void testAddFail() {
        CarLot carLot = new CarLot(2);
        carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        assertEquals(false,carLot.add(new Car("red", "chevy")));
    }
    public void testAddSucess() {
        CarLot carLot = new CarLot(3);
        carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        assertEquals(true,carLot.add(new Car("red", "chevy")));
    }
    public void testRemoveSucess() {
        CarLot carLot = new CarLot(3);
        carLot.add(new Car("red", "ford"));
        Car a = new Car("blue", "gm");
        carLot.add(a);
        carLot.add(new Car("red", "chevy"));
        assertEquals(a,carLot.remove(1));
    }
    public void testRemoveFail() {
        CarLot carLot = new CarLot(3);
        carLot.add(new Car("red", "ford"));
        assertEquals(null,carLot.remove(1));
    }
    public void testGetSuccess() {
        CarLot carLot = new CarLot(3);
        Car a = new Car("red", "ford");
        carLot.add(a);
        carLot.add(new Car("blue", "gm"));
        assertEquals(a,carLot.get(0));
    }
    public void testGetFail() {
        CarLot carLot = new CarLot(2);
        carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        assertEquals(false,carLot.add(new Car("red", "chevy")));
    }
    public void testSearchFail() {
        CarLot carLot = new CarLot(2);
        carLot.add(new Car("red", "ford"));
        carLot.add(new Car("blue", "gm"));
        assertEquals(false,carLot.add(new Car("red", "chevy")));
    }
}
