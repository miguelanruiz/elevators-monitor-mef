#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "ui_widget.h"
#include <QWidget>
#include <QLCDNumber>
#include <QPixmap>
#include <QMap>
#include <QString>

class StyleManager {
public:
    explicit StyleManager(Ui::Widget* ui);
    void setButtonStyles(QWidget *widget);
    void setupDisplays();
    QPixmap getLocationPixmap(int floor, char *direction);

private:
    Ui::Widget* ui;

    struct QLCD{
        QPixmap up[10];
        QPixmap down[10];
        QPixmap stable[10];
    };

    QLCD locationlDisplay;
    QPixmap animDoor[14];
};

#endif // STYLEMANAGER_H
