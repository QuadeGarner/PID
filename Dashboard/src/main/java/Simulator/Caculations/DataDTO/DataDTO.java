package Simulator.Caculations.DataDTO;

import Simulator.Caculations.DataCalculations;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@Setter
@Getter
@AllArgsConstructor
@NoArgsConstructor
public class DataDTO {
    private double kP, kD,kI,overShoot, riseTime, settlingTime , power, targetMap, posMap;

}
