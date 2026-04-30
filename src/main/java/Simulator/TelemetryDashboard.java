package Simulator;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Slider;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polyline;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

public class TelemetryDashboard extends Application {
    VirtualMotor vm = new VirtualMotor();
//    private double scale  = 0;
//    private double offset = 0;
    private double target;
    private double kP = 0.008; // Gain - sensitivity of the motor
    private double kD = 0.03; //
    private double kI = 0.0001;
    private double lastError = 500;
    double currentPos;
    double error;
    double derivative;
    double power;
    double intergalSum = 0;
    double timeX = 0;
    @Override
    public void start(Stage primaryStage){
        Pane root = new Pane();
        Pane graph = new Pane();
        Polyline targetLine = new Polyline();
        targetLine.setLayoutX(50);
        targetLine.setStroke(Color.GREEN);
        targetLine.setStrokeWidth(2);
        Polyline motorLine = new Polyline();
        motorLine.setLayoutX(50);
        motorLine.setStroke(Color.YELLOW);
        motorLine.setStrokeWidth(2);
        Polyline powerLine = new Polyline();
        powerLine.setStrokeWidth(2);
        powerLine.setStroke(Color.WHITE);
        powerLine.setLayoutX(50);
        Rectangle rect = new Rectangle(800,400, Color.LIGHTGRAY);
        rect.setLayoutX(50);
        Scene scene = new Scene(root, 1200, 600);
        Circle robot = new Circle(10, Color.BLUE);
        robot.setCenterY(450);
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
        root.getChildren().add(graph);
        root.getChildren().add(rect);
        root.getChildren().add(motorLine);
        root.getChildren().add(targetLine);
        root.getChildren().add(powerLine);
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long l) {
                timeX += 0.5;
                if(target != slider.getValue()){
                    intergalSum = 0;
                }
                setTarget(slider.getValue());
                currentPos = vm.getPosition();
                error = target - currentPos;
                intergalSum += error;
                if(intergalSum > 100){
                    intergalSum = 100;
                }
                if(intergalSum < -100) {
                    intergalSum = -100;
                }
                derivative = error - lastError;
                power = (error * kP)+ (kI * intergalSum) + (derivative * kD);
                lastError = error;

                if(power > 1.0 ){
                    power = 1.0;
                }
                if(power < -1.0){
                    power = -1.0;
                }
                if( power < 0.05 && power > 0) {
                    power = 0.05;
                }else if( power > -0.05 && power < 0){
                    power = -.05;
                }

                double posMap = (currentPos - 100) * (200.0 / 500.0);
                double targetMap = (target - 100) * (200.0 / 500.0);
                motorLine.getPoints().addAll(timeX, 200 - posMap);
                targetLine.getPoints().addAll(timeX, 200 - targetMap);
                powerLine.getPoints().addAll(timeX, 300- (power *80));

                if(timeX > 800){
                    motorLine.getPoints().clear();
                    targetLine.getPoints().clear();
                    powerLine.getPoints().clear();
                    timeX = 0;
                }


                if(Math.abs(error) < 0.1 && Math.abs(vm.getVelocity())< 0.1){
                    return;
                }
                vm.update(power);
                robot.setCenterX(vm.getPosition());
            }
        };
        primaryStage.setTitle("Motor Firmware Telemetry");
        primaryStage.setScene(scene);
        primaryStage.show();
        timer.start();
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
