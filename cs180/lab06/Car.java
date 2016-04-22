class Car implements Vehicle {
    String make;
    String color;
    public Car(String a, String b) {
        color = a;
        make = b;
    }
    public String getMake() {
        return make;
    }
    public String getColor() {
        return color;
    }
}