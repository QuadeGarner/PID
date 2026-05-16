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
    private double kP, kD,kI,overShoot, riseTime, settlingTime;

    public DataDTO toDTO(DataCalculations data){
        setKD(data.getKD());
        setKI(data.getKI());
        setKP(data.getKP());
        setOverShoot(data.getOverShoot());
        setSettlingTime(data.getSettlingTime());
        setRiseTime(data.getRiseTime());
    }

}
