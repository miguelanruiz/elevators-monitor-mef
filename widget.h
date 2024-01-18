#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QPixmap>

#define GP  0x107   /* x^8 + x^2 + x + 1 */
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

    void readSerial();
    void displayDoors();
    void on_comButton_clicked();
    void on_subir_7_clicked();
    void on_bajar_8_clicked();

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
    void setButtonsStyle();

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

    void on_asOne_send_clicked();

    void on_asTwo_send_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *modem_STM;

    struct QPositionLabels{
        QLabel *objects[10];
    };
    struct QKeyboadAscensor{
        QPushButton *first[10];
        QPushButton *second[10];
    };
    struct QLCD{
        QPixmap up[10];
        QPixmap down[10];
        QPixmap stable[10];
    };

    char serialBuffer[34];
    QLCD locationlDisplay;
    QKeyboadAscensor keyboardButtons;
    QPositionLabels ascOne;
    QPositionLabels ascTwo;
    unsigned char firstKeyboard[10];
    unsigned char secondKeyboard[10];

    QPixmap classDoors[14];
    quint8 displayDoorOne = 0;
    quint8 displayDoorTwo = 0;
    quint8 animOne = 11;
    quint8 animTwo = 11;
    quint8 freeRunAnim = 0;

    void init_crc8();
    unsigned char crc8(unsigned char *message, unsigned char length);
    char crc8_table[256];     /* 8-bit table */
    int made_table=0;
};

#endif // WIDGET_H
