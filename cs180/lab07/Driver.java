public class Driver {
    public static void main(String[] args) {
        Thread t = new A();
        t.start();
        Runnable r = new B();
        Thread s = new Thread(r);
        s.start();
    }
}