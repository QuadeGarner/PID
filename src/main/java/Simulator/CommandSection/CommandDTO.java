package Simulator.CommandSection;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class CommandDTO {
    private double target;
    private double kP;
    private double kI;
    private double kD;


    @Override
    public String toString() {
        String target = String.format("%.2f", getTarget());
        String kp = String.format("%.2f", getKP());
        String ki = String.format("%.2f", getKI());
        String kd = String.format("%.2f", getKD());
        return "$"+target +"," +kp +","+ki+"," + kd+"\n";
    }
}
