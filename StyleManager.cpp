#include "StyleManager.h"
#include "ui_widget.h"
#include <QPushButton>

StyleManager::StyleManager(Ui::Widget* ui) : ui(ui) {
    // Constructor - sets up displays
    setupDisplays();

    animDoor[0] = QPixmap(":/spanish/just_closed");
    animDoor[1] = QPixmap(":/spanish/opening_one");
    animDoor[2] = QPixmap(":/spanish/opening_one");
    animDoor[3] = QPixmap(":/spanish/opening_two");
    animDoor[4] = QPixmap(":/spanish/opening_two");
    animDoor[5] = QPixmap(":/spanish/opening_three");
    animDoor[6] = QPixmap(":/spanish/opening_three");
    animDoor[7] = QPixmap(":/spanish/opening_three");
    animDoor[8] = QPixmap(":/spanish/opening_three");
    animDoor[9] = QPixmap(":/spanish/opening_two");
    animDoor[10] = QPixmap(":/spanish/opening_two");
    animDoor[11] = QPixmap(":/spanish/opening_one");
    animDoor[12] = QPixmap(":/spanish/opening_one");
    animDoor[13] = QPixmap(":/spanish/just_closed");
}

void StyleManager::setupDisplays() {
    ui->floor_s2->display(-2);
    ui->floor_s1->display(-1);
    ui->floor_1->display(1);
    ui->floor_2->display(2);
    ui->floor_3->display(3);
    ui->floor_4->display(4);
    ui->floor_5->display(5);
    ui->floor_6->display(6);
    ui->floor_7->display(7);
    ui->floor_8->display(8);

    QLCD display;
    display.up[0] = QPixmap(":/spanish/s2_up");
    display.up[1] = QPixmap(":/spanish/s1_up");
    display.up[2] = QPixmap(":/spanish/1_up");
    display.up[3] = QPixmap(":/spanish/2_up");
    display.up[4] = QPixmap(":/spanish/3_up");
    display.up[5] = QPixmap(":/spanish/4_up");
    display.up[6] = QPixmap(":/spanish/5_up");
    display.up[7] = QPixmap(":/spanish/6_up");
    display.up[8] = QPixmap(":/spanish/7_up");
    display.up[9] = QPixmap(":/spanish/8_up");
    display.down[0] = QPixmap(":/spanish/s2_up");
    display.down[1] = QPixmap(":/spanish/s1_down");
    display.down[2] = QPixmap(":/spanish/1_down");
    display.down[3] = QPixmap(":/spanish/2_down");
    display.down[4] = QPixmap(":/spanish/3_down");
    display.down[5] = QPixmap(":/spanish/4_down");
    display.down[6] = QPixmap(":/spanish/5_down");
    display.down[7] = QPixmap(":/spanish/6_down");
    display.down[8] = QPixmap(":/spanish/7_down");
    display.down[9] = QPixmap(":/spanish/8_down");

    locationlDisplay = display;
}

QPixmap StyleManager::getLocationPixmap(int floor, char *direction){
    // if direction is up
    if(strcmp(direction, "UP") == 0){
        return this->locationlDisplay.up[floor];
    }
    else if(strcmp(direction, "DOWN") == 0){
        return this->locationlDisplay.down[floor];
    }
    else {
        return this->locationlDisplay.stable[floor];
    }
}

void StyleManager::setButtonStyles(QWidget *widget) {
    // Apply styles to "bajar_" buttons
    for (int i = 1; i <= 8; ++i) {
        QPushButton* bajarBtn = widget->findChild<QPushButton*>(QString("bajar_%1").arg(i));
        if (bajarBtn) {
            bajarBtn->setStyleSheet(
                "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
                "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
                "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}"
                );
        }
    }

    // Apply styles to "subir_" buttons
    for (int i = 1; i <= 7; ++i) {
        QPushButton* subirBtn = widget->findChild<QPushButton*>(QString("subir_%1").arg(i));
        if (subirBtn) {
            subirBtn->setStyleSheet(
                "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
                "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
                "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}"
                );
        }
    }

    // Apply styles to "subir_s1" and "subir_s2" buttons separately if they have unique styles
    QPushButton* subirS1Btn = widget->findChild<QPushButton*>("subir_s1");
    if (subirS1Btn) {
        subirS1Btn->setStyleSheet(
            "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
            "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
            "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}"
            );
    }

    QPushButton* subirS2Btn = widget->findChild<QPushButton*>("subir_s2");
    if (subirS2Btn) {
        subirS2Btn->setStyleSheet(
            "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
            "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
            "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}"
            );
    }

    QPushButton* bajarS1Btn = widget->findChild<QPushButton*>("bajar_s1");
    if (bajarS1Btn) {
        bajarS1Btn->setStyleSheet(
            "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
            "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
            "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}"
            );
    }

    // Apply styles to "asOne_" and "asTwo_" buttons
    for (const QString &prefix : { "asOne_", "asTwo_" }) {
        for (int i = 1; i <= 8; ++i) {
            QPushButton* asBtn = widget->findChild<QPushButton*>(QString("%1%2").arg(prefix).arg(i));
            if (asBtn) {
                QString url = QString(":/spanish/%1_no_active").arg(i);
                QString hoverUrl = QString(":/spanish/%1_active").arg(i);
                QString disabledUrl = QString(":/spanish/%1_keep").arg(i);

                QString stylesheet = QString(
                                         "QPushButton{border-image: url(%1) ;}"
                                         "QPushButton:hover{border-image: url(%2) ;}"
                                         "QPushButton:disabled{border-image: url(%3) ;}"
                                         ).arg(url).arg(hoverUrl).arg(disabledUrl);

                asBtn->setStyleSheet(stylesheet);
            }
        }

        // Apply styles to "s1" and "s2" buttons for each "asOne_" and "asTwo_"
        QPushButton* asS1Btn = widget->findChild<QPushButton*>(QString("%1s1").arg(prefix));
        if (asS1Btn) {
            // Add styles for "s1" button
            asS1Btn->setStyleSheet(
                "QPushButton{border-image: url(:/spanish/s1_no_active) ;}"
                "QPushButton:hover{border-image: url(:/spanish/s1_active) ;}"
                "QPushButton:disabled{border-image: url(:/spanish/s1_keep) ;}"
                );
        }

        QPushButton* asS2Btn = widget->findChild<QPushButton*>(QString("%1s2").arg(prefix));
        if (asS2Btn) {
            // Add styles for "s2" button
            asS2Btn->setStyleSheet(
                "QPushButton{border-image: url(:/spanish/s2_no_active) ;}"
                "QPushButton:hover{border-image: url(:/spanish/s2_active) ;}"
                "QPushButton:disabled{border-image: url(:/spanish/s2_keep) ;}"
                );
        }
    }

    const QStringList sendButtonNames = { "asOne_send", "asTwo_send" };
    QString sendButtonStyle =
        "QPushButton{border-image: url(:/spanish/close_doors_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/close_doors_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/close_doors_pressed) ;}";

    for (const QString &buttonName : sendButtonNames) {
        QPushButton* sendBtn = widget->findChild<QPushButton*>(buttonName);
        if (sendBtn) {
            sendBtn->setStyleSheet(sendButtonStyle);
        }
    }
}

