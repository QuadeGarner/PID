module Simulator {
    requires javafx.controls;
    requires javafx.fxml;

    opens Simulator to javafx.graphics;

}