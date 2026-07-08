package Simulator;

public class VirtualMotor {
    private double position = 100;
    private double velocity = 0;
    private double acceleration = 0;
    private double  MASS = 1.0;
    private final double DAMPING = 0.1; // FRICTION: amount of resistance
    private final double POWER_SCALING = 5.0 ;// motor strength
    private final double DELTA_T = 0.016; // 60 frames per second

    /**
     *  Method to update the motor
     * @param inputPower power variable
     */
    public void update(double inputPower){
        double force = (inputPower * POWER_SCALING) - (velocity * DAMPING);
        acceleration = force / MASS;
        velocity +=(acceleration * DELTA_T);  // velocity = acceleration time the amount of time

        position += velocity * DELTA_T ; // update the posistion based on the velocity and how much time has passed

    }
    public double getPosition(){return position;}
    public double getVelocity(){return velocity;}
    public void setMASS(double mass){
        this.MASS = mass;
    }

}
