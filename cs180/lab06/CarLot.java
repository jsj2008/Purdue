import java.util.*;
class CarLot implements Inventory<Car> {
    int cap;
    int num = 0;
    ArrayList<Car> pos = new ArrayList<Car>();
    public CarLot(int a) {
        cap = a;
        //Car car = new Car("","")[cap];
    }
    public int capacity() {
        return cap;
    }
    public int numVehicles() {
        return num;
    }
    public boolean add(Car vehicle) {
        try {
            if((num + 1) <= cap) {
                num++;
                pos.add(vehicle);
                return true;
            }
            else return false;
        }
        catch (Exception e) {
            System.out.println(" Error. ");
            return false;
        }
    }
    public Car get(int location) {
        try {
            return pos.get(location);
        }
        catch (Exception e) {
            return null;
        }
    }
    public Car remove(int location) {
        if ((num - 1) > 0) {
            num--;
            Car a = pos.get(location);
            pos.set(location,null);
            return a;
        }
        else return null;
    }
    public boolean[] searchByMake(String make) {
        boolean b[] = new boolean[pos.size()];
        for (int i = 0;i < pos.size(); i++) 
        {
            Car a = pos.get(i);
            if(a.getMake().equals(make))
                b[i] = true;
            else b[i] = false;
        }
        return b;
    }
}