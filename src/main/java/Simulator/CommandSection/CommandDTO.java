package Simulator.CommandSection;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class CommandDTO {
    private double kP;
    private double kI;
    private double kD;


    @Override
    public String toString() {
        return getKP() +","+getKI()+"," + getKD()+"\n";
    }
}
