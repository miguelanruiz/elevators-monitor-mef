#ifndef WIDGET_H
#define WIDGET_H

#include "SerialManager.h"
#include "StyleManager.h"
#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QPixmap>

#define GP  0x107   /* x^8 + x^2 + x + 1 */
#define FLOOR_BUTTONS_START_INDEX_A 6
#define FLOOR_BUTTONS_START_INDEX_B 22
#define ELEVATOR_ID_A '1'
#define ELEVATOR_ID_B '2'
#define BIT_UP_A 3
#define BIT_DOWN_A 5
#define BIT_UP_B 19
#define BIT_DOWN_B 21
#define SIZE_PAGE_ASCENSOR 16
#define NUM_ELEVATORS 2
#define TIMEOUT_SCREEN_SAMPLING 600
#define DI  0x07

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void handleSerialData(const QByteArray &data);
    void handleSerialError(const QString &error);
    void displayDoors();
    void on_comButton_clicked();
    void sendElevatorRequest(const QString &requestType, const QString &floor);

    // Floor button slots
    void on_bajar_8_clicked();
    void on_subir_7_clicked();
    void on_bajar_7_clicked();
    void on_subir_6_clicked();
    void on_bajar_6_clicked();
    void on_subir_5_clicked();
    void on_bajar_5_clicked();
    void on_subir_4_clicked();
    void on_bajar_4_clicked();
    void on_subir_3_clicked();
    void on_bajar_3_clicked();
    void on_subir_2_clicked();
    void on_bajar_2_clicked();
    void on_subir_1_clicked();
    void on_bajar_1_clicked();
    void on_subir_s1_clicked();
    void on_bajar_s1_clicked();
    void on_subir_s2_clicked();

    // Keyboard input slots for the first elevator
    void on_asOne_1_clicked();
    void on_asOne_2_clicked();
    void on_asOne_3_clicked();
    void on_asOne_4_clicked();
    void on_asOne_5_clicked();
    void on_asOne_6_clicked();
    void on_asOne_7_clicked();
    void on_asOne_8_clicked();
    void on_asOne_s1_clicked();
    void on_asOne_s2_clicked();

    // Keyboard input slots for the second elevator
    void on_asTwo_1_clicked();
    void on_asTwo_2_clicked();
    void on_asTwo_3_clicked();
    void on_asTwo_4_clicked();
    void on_asTwo_5_clicked();
    void on_asTwo_6_clicked();
    void on_asTwo_7_clicked();
    void on_asTwo_8_clicked();
    void on_asTwo_s1_clicked();
    void on_asTwo_s2_clicked();

    // Send button slots for each elevator
    void on_asOne_send_clicked();
    void on_asTwo_send_clicked();

private:
    Ui::Widget *ui;
    SerialManager *serialManager;
    StyleManager *styleManager;

    struct QPositionLabels {
        QLabel *objects[10];
    };
    struct QKeyboardAscensor {
        QPushButton *first[10];
        QPushButton *second[10];
    };

    char serialBuffer[34];
    QKeyboardAscensor keyboardButtons;
    QPositionLabels ascOne;
    QPositionLabels ascTwo;
    unsigned char firstKeyboard[10];
    unsigned char secondKeyboard[10];

    QPixmap animDoor[14];
    quint8 displayDoorOne = 0;
    quint8 displayDoorTwo = 0;
    quint8 animOne = 11;
    quint8 animTwo = 11;
    quint8 freeRunAnim = 0;

    void init_crc8();
    unsigned char crc8(unsigned char *message, unsigned char length);
    void sendData(const QString &prefix, unsigned char *keyboard);
    char crc8_table[256];     /* 8-bit table */
    bool made_table = false;
};

#endif // WIDGET_H
