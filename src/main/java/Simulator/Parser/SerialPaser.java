package Simulator.Parser;

import com.fazecast.jSerialComm.SerialPort;

import java.util.Scanner;

public class SerialPaser {
    SerialPort port = SerialPort.getCommPort("COM7");
    Scanner scanner = new Scanner(port.getInputStream());
    public boolean startPort(){
        boolean open = port.openPort();
        port.setBaudRate(115200);
        if (!open) {
            return false;
        }
        return true;
    }
    /*
    Serial.print(String(controller.getTarget()) +","); target
    Serial.print(String(controller.computeError()) +",");  error
    Serial.print(String(controller.getLastError())+","); lastError
    Serial.print(String(vm.getPosition())+","); currentPos
    Serial.print(String(controller.getKp())+","); kP
    Serial.print(String(controller.getKd())+","); KD
    Serial.print(String(percentComplete)+"\n"); percentComplete
     */
    public String[] scanData(){
        while(startPort()){
            String s = scanner.nextLine();
            String[] stringSplit = s.split(",");
            if(!(stringSplit.length != 7 || stringSplit[0].isEmpty()|| stringSplit[1].isEmpty() ||
                    stringSplit[2].isEmpty()||stringSplit[3].isEmpty()||stringSplit[4].isEmpty()||stringSplit[5].isEmpty()
            ||stringSplit[6].isEmpty()))  {
                setTarget(Double.parseDouble(stringSplit[0]));
                setError(Double.parseDouble(stringSplit[1]));
                setLastError(Double.parseDouble(stringSplit[2]));
                setCurrentPos(Double.parseDouble(stringSplit[3]));
                setKP(Double.parseDouble(stringSplit[4]));
                setKD(Double.parseDouble((stringSplit[5])));
                setPercentComplete(Double.parseDouble(stringSplit[6]));
            }
        }
    }

}
