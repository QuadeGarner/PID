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
        return "$"+getTarget() +"," +getKP() +","+getKI()+"," + getKD()+"\n";
    }
}
