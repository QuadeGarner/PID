package Simulator.Caculations;

import Simulator.Caculations.DataDTO.DataDTO;
import Simulator.Caculations.DataDTO.SerialParserDTO;
import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class DataCalculations {
    /*
    Serial.print(String(controller.getTarget()) +","); target
    Serial.print(String(controller.computeError()) +",");  error
    Serial.print(String(controller.getLastError())+","); lastError
    Serial.print(String(vm.getPosition())+","); currentPos
    Serial.print(String(controller.getKp())+","); kP
    Serial.print(String(controller.getKd())+","); KD
    Serial.print(String(percentComplete)+"\n"); percentComplete
     */
    // calculation data
    private double overShoot,settlingTime, riseTime, posMap, targetMap;
    // needed data to calculate
    double target, lastError, error,currentPos, percentComplete, startTime, kP, kD, power, kI;
    int framesInBand = 0;
    double maxPosDuringStep = 0;
    public DataDTO computeMetrics() {
        computeOverShoot();
        computeRiseTime();
        computeSettlingTime();
        posMap = (currentPos - 100) * (200.0 / 500.0);
        targetMap = (target - 100) * (200.0 / 500.0);
        return toDTO();


    }
    void computeOverShoot(){
        overShoot = ((maxPosDuringStep - target) / target) * 100;
        if (overShoot < 0) overShoot = 0;
    }
    void computeRiseTime(){
        if (percentComplete >= 0.10 && startTime == 0) {
            startTime = System.currentTimeMillis(); // Start the timer at 10%
        }
        if (percentComplete >= 0.90 && riseTime == 0 && startTime != 0) {
            riseTime = (System.currentTimeMillis() - startTime) / 1000.0; // Stop at 90%
        }
    }
    void computeSettlingTime(){
        double tolerance = target * 0.02; // 2% band

        if (Math.abs(error) < tolerance) {
            framesInBand++;
        }else{
            framesInBand = 0;
        }
        // If it stays in the band for 60 consecutive frames (approx 1 second)
        if (framesInBand > 60 && settlingTime == 0 && startTime != 0) {
            settlingTime = (System.currentTimeMillis() - startTime) / 1000.0;
        }
    }
    public void fromDTO(SerialParserDTO dto){
        setTarget(dto.getTarget());
        setError(dto.getError());
        setCurrentPos(dto.getCurrentPos());
        setLastError(dto.getLastError());
        setPercentComplete(dto.getPercentComplete());
        setKD(dto.getKD());
        setKP(dto.getKP());
        setKI(dto.getKI());
        setPower(dto.getPower());
    }
    public DataDTO toDTO(){
        DataDTO dto = new DataDTO();
        dto.setKD(getKD());
        dto.setKI(getKI());
        dto.setKP(getKP());
        dto.setOverShoot(getOverShoot());
        dto.setSettlingTime(getSettlingTime());
        dto.setRiseTime(getRiseTime());
        dto.setPower(getPower());
        dto.setPosMap(getPosMap());
        dto.setTargetMap(getTargetMap());

        return dto;
    }
}
