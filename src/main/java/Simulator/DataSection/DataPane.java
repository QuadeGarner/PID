package Simulator.DataSection;

import Simulator.Caculations.DataDTO.DataDTO;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class DataPane extends Pane {
    Rectangle rect = new Rectangle(250, 300, Color.DARKGRAY);

    Label pLabel, dLabel, iLabel, overShootLabel, riseTimeLabel, settlingTimeLabel;
    DataDTO dto;

    public void setDataPane(){
        rect.setLayoutX(880);
        rect.setLayoutY(20);
        getChildren().addAll(rect, createPLabel(),createDLabel(), createILabel(), createOverShootLabel(), createRiseTimeLabel(),createSettlingTimeLabel() );
    }
    public void updateLabels(DataDTO dto){
        updatePLabel(dto.getKP());
        updateILabel(dto.getKI());
        updateDLabel(dto.getKD());
        updateOverShootLabel(dto.getOverShoot());
        updateRisetimeLabel(dto.getRiseTime());
        updateSettlingLabel(dto.getSettlingTime());

    }



    private Label createILabel() {
        iLabel = new Label();
        iLabel.setLayoutX(900);
        iLabel.setLayoutY(100);
        iLabel.setTextFill(Color.BLACK);
        iLabel.setText("kI (Integral): ");
        return iLabel;
    }

    private Label createDLabel() {
        dLabel = new Label();
        dLabel.setLayoutX(900);
        dLabel.setLayoutY(170);
        dLabel.setTextFill(Color.BLACK);
        dLabel.setText("kD (Derivative): %.4f");
        return dLabel;
    }

    private Label createPLabel() {
        pLabel = new Label();
        pLabel.setLayoutX(900);
        pLabel.setLayoutY(30);
        pLabel.setTextFill(Color.BLACK);
        pLabel.setText("kP (Proportional): ");
        return pLabel;
    }
    private Label createOverShootLabel() {
        overShootLabel = new Label();
        overShootLabel.setLayoutX(900);
        overShootLabel.setLayoutY(230);
        overShootLabel.setTextFill(Color.BLACK);
        return overShootLabel;
    }
    private Label createRiseTimeLabel() {
        riseTimeLabel = new Label();
        riseTimeLabel.setLayoutX(900);
        riseTimeLabel.setLayoutY(250);
        riseTimeLabel.setTextFill(Color.BLACK);
        return riseTimeLabel;
    }
    private Label createSettlingTimeLabel() {
        settlingTimeLabel = new Label();
        settlingTimeLabel.setLayoutX(900);
        settlingTimeLabel.setLayoutY(270);
        settlingTimeLabel.setTextFill(Color.BLACK);
        return settlingTimeLabel;
    }
    private void updateDLabel(double kD) {
        dLabel.setText(String.format("kD (Derivative): %.4f", kD));
    }

    private void updateILabel(double kI) {
        iLabel.setText(String.format("kI (Integral): %.6f", kI));
    }

    private void updatePLabel(double kP) {
        pLabel.setText(String.format("kP (Proportional): %.4f", kP));
    }
    private void updateOverShootLabel(double overshoot){
        overShootLabel.setText(String.format("Overshoot: %.1f%%",
                overshoot));
    }
    private void updateRisetimeLabel(double riseTime){
        riseTimeLabel.setText(String.format("Rise Time: %.2fs",
                riseTime));
    }
    private void updateSettlingLabel(double settlingTime){
        settlingTimeLabel.setText(String.format("Settling Time: %.2fs",
                settlingTime));
    }
}
