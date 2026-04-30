package Simulator;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polyline;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

public class TelemetryDashboard extends Application {
    VirtualMotor vm = new VirtualMotor();
    private double target;
    private double kP;// Gain - sensitivity of the motor
    private double kD; //
    private double kI;
    private double lastError = 500;
    double currentPos;
    double error;
    double derivative;
    double power;
    double intergalSum = 0;
    double timeX = 0;
    private Slider slider, pSlider, iSlider, dSlider, massSlider;
    private Label pLabel, iLabel, dLabel, statsLabel, massLabel;
    private double maxPosDuringStep =0;
    private Polyline targetLine, motorLine, powerLine;
    private int settleFrames = 0;
    private  long startTime =0;
    private double riseTime =0;
    private  double settlingTime =0;
    private  boolean rising = false;
    private int framesInBand = 0;
    @Override
    public void start(Stage primaryStage){
        Pane root = new Pane();
        Pane graph = new Pane();
        targetLine = new Polyline();
        targetLine.setLayoutX(50);
        targetLine.setStroke(Color.GREEN);
        targetLine.setStrokeWidth(2);
        motorLine = new Polyline();
        motorLine.setLayoutX(50);
        motorLine.setStroke(Color.YELLOW);
        motorLine.setStrokeWidth(2);
        powerLine = new Polyline();
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
        slider = new Slider();
        slider.setLayoutX(100);
        slider.setLayoutY(500);
        slider.adjustValue(10);
        slider.setMax(600);
        slider.setMin(100);
        slider.setPrefWidth(500);
        Button trigger = new Button(" Trigger Step");
        trigger.setOnAction( event -> {
            setTrigger();
        });
        trigger.setLayoutX(100);
        trigger.setLayoutY(550);
        root.getChildren().add(trigger);
        target = slider.getValue();
        pSlider = new Slider(0, 0.05, kP);
        pSlider.setLayoutX(900); pSlider.setLayoutY(50);
        pSlider.setPrefWidth(200);
        pLabel = new Label();
        pLabel.setLayoutX(900); pLabel.setLayoutY(30);
        pLabel.setTextFill(Color.BLACK);
        iSlider = new Slider(0, 0.001, kI);
        iSlider.setLayoutX(900); iSlider.setLayoutY(120);
        iSlider.setPrefWidth(200);
        iLabel = new Label();
        iLabel.setLayoutX(900); iLabel.setLayoutY(100);
        iLabel.setTextFill(Color.BLACK);
        dSlider = new Slider(0, 1, kD);
        dSlider.setLayoutX(900); dSlider.setLayoutY(190);
        dSlider.setPrefWidth(200);
        dLabel = new Label();
        dLabel.setLayoutX(900); dLabel.setLayoutY(170);
        dLabel.setTextFill(Color.BLACK);
        statsLabel = new Label();
        statsLabel.setLayoutX(900); statsLabel.setLayoutY(230);
        statsLabel.setTextFill(Color.BLACK);
        massSlider = new Slider();
        massSlider.setMin(1.0);
        massSlider.setMax(5.0);
        massSlider.setLayoutX(900); massSlider.setLayoutY(210);
        massLabel = new Label("Mass");
        massLabel.setLayoutX(900);massLabel.setLayoutY(200);
        Rectangle controlBg = new Rectangle(250, 250, Color.DARKGRAY);
        controlBg.setLayoutX(880);
        controlBg.setLayoutY(20);
        controlBg.setArcWidth(10); // Rounded corners look professional
        controlBg.setArcHeight(10);
        root.getChildren().add(controlBg);
        root.getChildren().addAll(pSlider, iSlider, dSlider, pLabel, iLabel, dLabel, statsLabel, massLabel, massSlider);
        root.getChildren().add(slider);
        root.getChildren().add(graph);
        root.getChildren().add(rect);
        root.getChildren().add(motorLine);
        root.getChildren().add(targetLine);
        root.getChildren().add(powerLine);
        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long l) {
                kP = pSlider.getValue();
                kI = iSlider.getValue();
                kD = dSlider.getValue();
                vm.setMASS(massSlider.getValue());
                pLabel.setText(String.format("kP (Proportional): %.4f", kP));
                iLabel.setText(String.format("kI (Integral): %.6f", kI));
                dLabel.setText(String.format("kD (Derivative): %.4f", kD));
                massLabel.setText(String.format("Mass : %.2f", massSlider.getValue()));
                timeX += 0.5;
                if(target != slider.getValue()){
                    intergalSum = 0;
                }
                setTarget(slider.getValue());
                currentPos = vm.getPosition();
                error = target - currentPos;
                intergalSum += error;
                // capping the sum to 100 to prevent spiralling of the sum
                if(intergalSum > 100){
                    intergalSum = 100;
                }
                if(intergalSum < -100) {
                    intergalSum = -100;
                }
                if(Math.abs(error) > 5){
                    if(currentPos > maxPosDuringStep && target > 100){
                        maxPosDuringStep = currentPos;
                    }
                }
                double overshoot = ((maxPosDuringStep - target)/ target) *100;
                if(overshoot < 0) overshoot = 0;

                double percentComplete = (currentPos - 100) / (target - 100);

                if (percentComplete >= 0.10 && startTime == 0) {
                    startTime = System.currentTimeMillis(); // Start the timer at 10%
                }
                if (percentComplete >= 0.90 && riseTime == 0 && startTime != 0) {
                    riseTime = (System.currentTimeMillis() - startTime) / 1000.0; // Stop at 90%
                }
                statsLabel.setText(String.format("Overshoot: %.1f%%\n" + "Rise Time: %.2fs\n" + "Settling Time: %.2fs",
                        overshoot, riseTime, settlingTime
                ));
                double rawDerivative = error - lastError;
                // smoothing factor
                derivative = (0.1 * rawDerivative) + (0.9 * derivative);
                power = (error * kP)+ (kI * intergalSum) + (derivative * kD);
                lastError = error;
                double tolerance = target * 0.02; // 2% band
                if (Math.abs(error) < tolerance) {
                    framesInBand++;
                } else {
                    framesInBand = 0; // Reset if it bounces back out
                }

                // If it stays in the band for 60 consecutive frames (approx 1 second)
                if (framesInBand > 60 && settlingTime == 0 && startTime != 0) {
                    settlingTime = (System.currentTimeMillis() - startTime) / 1000.0;
                }
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
    private void setTrigger(){
        slider.setValue(500);
        pSlider.setValue(0.001);
        dSlider.setValue(0.0);
        iSlider.setValue(0.0);
        targetLine.getPoints().clear();
        powerLine.getPoints().clear();
        motorLine.getPoints().clear();
        timeX =0;
        settleFrames = 0;
        startTime =0;
        riseTime =0;
        settlingTime =0;
        rising = false;
        framesInBand = 0;
    }
}
