//public class Main {
//
//        Simulator.VirtualMotor vm = new Simulator.VirtualMotor();
//        double target = 500.0;
//        double kP = 0.01; // Gain - sensitivity of the motor
//        double kD = 0.04;
//        double lastError = 0;
//        //while(true){
//            double currentPos = vm.getPosition();
//            double error = target - currentPos;
//
//            double derivative = error - lastError;
//            // set the power based of how big the error is
//            double power = (error * kP) + (derivative * kD);
//
//            lastError = error;
//
//            if(power > 1.0 ){
//                power = 1.0;
//            }
//            if(power < -1.0){
//                power = -1.0;
//            }
//            vm.update(power);
//
//            System.out.printf("Pos: %.2f | Error: %.2f | Power: %.2f%n",currentPos, error, power);
//
//            if(Math.abs(error) < 0.1 && Math.abs(vm.getVelocity())< 0.1){
//                break;
//            }
//            try {
//                Thread.sleep(20);
//            }catch (InterruptedException e){
//                break;
//            }
//        //}
//}
