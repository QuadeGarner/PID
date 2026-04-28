package Simulator;

public class VirtualMotor {
    private double position = 0;
    private double velocity = 0;

    private final double FRICTION = 0.95;
    private final double POWER_TO_ACCEL = 0.5;

    /**
     *  Method to update the motor
     * @param inputPower power variable
     */
    public void update(double inputPower){
        double acceleration = inputPower * POWER_TO_ACCEL;

        velocity +=(acceleration * FRICTION);

        position += velocity;

    }
    public double getPosition(){return position;}
    public double getVelocity(){return velocity;}

}
