package Simulator;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

public class TelemetryDashboard extends Application {
    VirtualMotor vm = new VirtualMotor();
    private double scale  = 0;
    private double offset = 0;
    private double target;
    private double kP = 0.01; // Gain - sensitivity of the motor
    private double kD = 0.1;
    private double lastError = 500;
    double currentPos;
    double error;
    double derivative;
    double power;
    @Override
    public void start(Stage primaryStage){
        Pane root = new Pane();
        Scene scene = new Scene(root, 800, 600);
        Circle robot = new Circle(10, Color.BLUE);
        robot.setCenterY(300);
        robot.setCenterX(50);
        root.getChildren().add(robot);
        Slider slider = new Slider();
        slider.setLayoutX(100);
        slider.setLayoutY(500);
        slider.adjustValue(10);
        slider.setMax(600);
        slider.setMin(100);
        slider.setPrefWidth(500);
        target = slider.getValue();
        root.getChildren().add(slider);
        TextArea ta = new TextArea();
        root.getChildren().add(ta);
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long l) {
                setTarget(slider.getValue());
                currentPos = vm.getPosition();
                error = target - currentPos;
                derivative = error - lastError;
                power = (error * kP) + (derivative * kD);
                lastError = error;

                if(power > 1.0 ){
                    power = 1.0;
                }
                if(power < -1.0){
                    power = -1.0;
                }
                vm.update(power);
                robot.setCenterX(vm.getPosition());

                if(Math.abs(error) < 0.1 && Math.abs(vm.getVelocity())< 0.1){
                    return;
                }
                String values = "Pos: %.2f"+currentPos +" | Error: %.2f "+ error +"| Power: %.2f%n" + power;
                ta.setText(values);
            }
        };
        primaryStage.setTitle("Motor Firmware Telemetry");
        primaryStage.setScene(scene);
        primaryStage.show();
        timer.start();
    }
    private double scaleFactor(){
        return (vm.getPosition() * scale) + offset;
    }
    public static void main(String[] args) {
        launch(args);

    }

    private double getTarget(){
        return target;
    }
    private void setTarget(double n){
        this.target = n;
    }

}
