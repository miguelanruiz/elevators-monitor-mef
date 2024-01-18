#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    init_crc8();
    for(int i = 0; i < 10; i++){
        firstKeyboard[i] = '0';
        secondKeyboard[i] = '0';
    }
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
    classDoors[0] = QPixmap(":/spanish/just_closed");
    classDoors[1] = QPixmap(":/spanish/opening_one");
    classDoors[2] = QPixmap(":/spanish/opening_one");
    classDoors[3] = QPixmap(":/spanish/opening_two");
    classDoors[4] = QPixmap(":/spanish/opening_two");
    classDoors[5] = QPixmap(":/spanish/opening_three");
    classDoors[6] = QPixmap(":/spanish/opening_three");
    classDoors[7] = QPixmap(":/spanish/opening_three");
    classDoors[8] = QPixmap(":/spanish/opening_three");
    classDoors[9] = QPixmap(":/spanish/opening_two");
    classDoors[10] = QPixmap(":/spanish/opening_two");
    classDoors[11] = QPixmap(":/spanish/opening_one");
    classDoors[12] = QPixmap(":/spanish/opening_one");
    classDoors[13] = QPixmap(":/spanish/just_closed");

    QKeyboadAscensor keyboard;
    keyboard.first[0] = ui->asOne_s2;
    keyboard.first[1] = ui->asOne_s1;
    keyboard.first[2] = ui->asOne_1;
    keyboard.first[3] = ui->asOne_2;
    keyboard.first[4] = ui->asOne_3;
    keyboard.first[5] = ui->asOne_4;
    keyboard.first[6] = ui->asOne_5;
    keyboard.first[7] = ui->asOne_6;
    keyboard.first[8] = ui->asOne_7;
    keyboard.first[9] = ui->asOne_8;
    keyboard.second[0] = ui->asTwo_s2;
    keyboard.second[1] = ui->asTwo_s1;
    keyboard.second[2] = ui->asTwo_1;
    keyboard.second[3] = ui->asTwo_2;
    keyboard.second[4] = ui->asTwo_3;
    keyboard.second[5] = ui->asTwo_4;
    keyboard.second[6] = ui->asTwo_5;
    keyboard.second[7] = ui->asTwo_6;
    keyboard.second[8] = ui->asTwo_7;
    keyboard.second[9] = ui->asTwo_8;

    keyboardButtons = keyboard;

    QPositionLabels ascensor;
    ascensor.objects[0] = ui->a1_s2;
    ascensor.objects[1] = ui->a1_s1;
    ascensor.objects[2] = ui->a1_1;
    ascensor.objects[3] = ui->a1_2;
    ascensor.objects[4] = ui->a1_3;
    ascensor.objects[5] = ui->a1_4;
    ascensor.objects[6] = ui->a1_5;
    ascensor.objects[7] = ui->a1_6;
    ascensor.objects[8] = ui->a1_7;
    ascensor.objects[9] = ui->a1_8;
    ascOne = ascensor;
    QPositionLabels ascensorNew;
    ascensorNew.objects[0] = ui->a2_s2;
    ascensorNew.objects[1] = ui->a2_s1;
    ascensorNew.objects[2] = ui->a2_1;
    ascensorNew.objects[3] = ui->a2_2;
    ascensorNew.objects[4] = ui->a2_3;
    ascensorNew.objects[5] = ui->a2_4;
    ascensorNew.objects[6] = ui->a2_5;
    ascensorNew.objects[7] = ui->a2_6;
    ascensorNew.objects[8] = ui->a2_7;
    ascensorNew.objects[9] = ui->a2_8;
    ascTwo = ascensorNew;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        qDebug() << "Name: " << info.portName();
        qDebug() << "Description: " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Vendor: " << info.vendorIdentifier();
        qDebug() << "Product: " << info.productIdentifier();
        ui->comboCOM->addItem(info.portName());
    }
    //ui->bajar_8->setIcon(QIcon(QPixmap(":/spanish/go_down_no_active")));
    setButtonsStyle();
    QTimer::singleShot(600, this, SLOT(displayDoors()));
    modem_STM = new QSerialPort(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::displayDoors()
{
    if(animOne < 11){
        if(displayDoorOne++ == 13){
            displayDoorOne = 0;
            animOne = 11;
        }else {
            ascOne.objects[animOne]->setPixmap(classDoors[displayDoorOne]);
        }
    }
    if(animTwo < 11){
        if(displayDoorTwo++ == 13){
            displayDoorTwo = 0;
            animTwo = 11;
        }
        else{
            ascTwo.objects[animTwo]->setPixmap(classDoors[displayDoorTwo]);
        }
    }
    QTimer::singleShot(600, this, SLOT(displayDoors()));
}

void Widget::readSerial()
{
    QByteArray serialData = modem_STM->readAll();
    const char *pointer = serialData.constData();
    qDebug()<<"readed"<<serialData.constData();
    if(pointer[1] == '1'){
        for(int i = 6 ; i < 16; i++){
            if(pointer[i] == '1' ){
                keyboardButtons.first[i-6]->setEnabled(true);
            }
        }
        for(int i = 22 ; i < 32; i++){
            if(pointer[i] == '1' ){
                keyboardButtons.second[i-22]->setEnabled(true);
            }
        }
        if(pointer[3] == '1'){
            ui->locationOne->setPixmap(QPixmap(":/spanish/up"));
            ui->logReg->append(QString("Ascensor 1 subiendo..."));
            for(int i = 6; i < 16; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    //ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.up[i-6]);
                    animOne = i-6;
                }
                else if(pointer[i] == '1'){
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.up[i-6]);
                }
                else{
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else if(pointer[5] == '1'){
            ui->locationOne->setPixmap(QPixmap(":/spanish/down"));
            ui->logReg->append(QString("Ascensor 1 bajando..."));
            for(int i = 6; i < 16; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    //ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.down[i-6]);
                    animOne = i-6;
                }
                else if(pointer[i] == '1'){
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.down[i-6]);
                }
                else{
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else{
            ui->locationOne->setPixmap(QPixmap(":/spanish/stop"));
            ui->logReg->append(QString("Ascensor 1 detenido..."));
            for(int i = 6; i < 16; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    //ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.down[i-6]);
                    animOne = i-6;
                }
                else if(pointer[i] == '1' && animOne == 11){
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(locationlDisplay.down[i-6]);
                }
                else if(animOne == 11){
                    ascOne.objects[i-6]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        /*for(int i = 0; i < serialData.size(); i++){
            qDebug()<<pointer[i];
        }*/
    }
    if(pointer[17] == '2'){
        if(pointer[19] == '1'){
            ui->locationTwo->setPixmap(QPixmap(":/spanish/up"));
            ui->logReg->append(QString("Ascensor 2 subiendo..."));
            for(int i = 22; i < 32; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    //ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asTwo_indicator->setPixmap(locationlDisplay.up[i-22]);
                    animTwo = i-22;
                }
                else if(pointer[i] == '1'){
                    ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asTwo_indicator->setPixmap(locationlDisplay.up[i-22]);
                }
                else {
                    ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else if(pointer[21] == '1'){
            ui->locationTwo->setPixmap(QPixmap(":/spanish/down"));
            ui->logReg->append(QString("Ascensor 2 bajando..."));
            for(int i = 22; i < 32; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    //ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asTwo_indicator->setPixmap(locationlDisplay.down[i-22]);
                    animTwo = i-22;
                }
                else if(pointer[i] == '1'){
                   ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/active_closed"));
                   ui->asTwo_indicator->setPixmap(locationlDisplay.down[i-22]);
                }
                else{
                    ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else{
            ui->locationTwo->setPixmap(QPixmap(":/spanish/stop"));
            ui->logReg->append(QString("Ascensor 2 detenido..."));
            for(int i = 22; i < 32; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    //ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/opening_three"));
                    ui->asTwo_indicator->setPixmap(locationlDisplay.down[i-22]);
                    animTwo = i-22;
                }
                if(pointer[i] == '1' && animTwo == 11){
                    ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asTwo_indicator->setPixmap(locationlDisplay.up[i-22]);
                }
                else if(animTwo == 11){
                    ascTwo.objects[i-22]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
    }
}

void Widget::on_comButton_clicked()
{
    ui->comButton->setDisabled(true);
    modem_STM->setPortName(ui->comboCOM->currentText());
    modem_STM->setBaudRate(QSerialPort::Baud115200);
    modem_STM->setDataBits(QSerialPort::Data8);
    modem_STM->setParity(QSerialPort::NoParity);
    modem_STM->setStopBits(QSerialPort::OneStop);
    modem_STM->setFlowControl(QSerialPort::NoFlowControl);
    modem_STM->setReadBufferSize(34);
    connect(modem_STM, SIGNAL(readyRead()),this, SLOT(readSerial()));

    if(modem_STM->isOpen()){
          modem_STM->close();
          ui->comButton->setEnabled(true);
          qDebug()<< "Desconectado";
          disconnect(modem_STM, SIGNAL(readyRead()),this, SLOT(readSerial()));
    }
    else {
    if(modem_STM->open(QIODevice::ReadWrite)){
        qDebug() << "Conected";
        ui->comboCOM->setDisabled(true);
        connect(modem_STM, SIGNAL(readyRead()),this, SLOT(readSerial()));
    }else{
        QMessageBox::critical(this,tr("Error"), modem_STM->errorString());
    }
    }
}

void Widget::on_bajar_8_clicked()
{
    QString data("A1S0B1F9");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F9";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_7_clicked()
{
    QString data("A1S1B0F8");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F8";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_7_clicked()
{
    QString data("A1S0B1F8");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F8";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_6_clicked()
{
    QString data("A1S1B0F7");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F7";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_6_clicked()
{
    QString data("A1S0B1F7");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F7";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_5_clicked()
{
    QString data("A1S1B0F6");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F6";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_5_clicked()
{
    QString data("A1S0B1F6");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F6";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_4_clicked()
{
    QString data("A1S1B0F5");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F5";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_4_clicked()
{
    QString data("A1S0B1F5");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F5";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_3_clicked()
{
    QString data("A1S1B0F4");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F4";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_3_clicked()
{
    QString data("A1S0B1F4");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F4";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_2_clicked()
{
    QString data("A1S1B0F3");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F3";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_2_clicked()
{
    QString data("A1S0B1F3");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F3";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_1_clicked()
{
    QString data("A1S1B0F2");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F2";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_1_clicked()
{
    QString data("A1S0B1F2");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F2";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_s1_clicked()
{
    QString data("A1S1B0F1");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F1";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_bajar_s1_clicked()
{
    QString data("A1S0B1F1");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S0B1F1";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::on_subir_s2_clicked()
{
    QString data("A1S1B0F0");
    QByteArray sendThis;
    unsigned char calculateCRC[] = "A1S1B0F0";
    sendThis.append(data);
    sendThis.append(crc8(calculateCRC, 8));
    modem_STM->write(sendThis);
}

void Widget::setButtonsStyle(){
    ui->bajar_8->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_7->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_7->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_6->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_6->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_5->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_5->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_4->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_4->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_3->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_3->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->bajar_s1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_down_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_down_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_s1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->subir_s2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/go_up_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/go_up_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/go_up_active) ;}");
    ui->asOne_1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/1_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/1_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/1_keep) ;}");
    ui->asOne_2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/2_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/2_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/2_keep) ;}");
    ui->asOne_3->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/3_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/3_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/3_keep) ;}");
    ui->asOne_4->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/4_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/4_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/4_keep) ;}");
    ui->asOne_5->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/5_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/5_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/5_keep) ;}");
    ui->asOne_6->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/6_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/6_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/6_keep) ;}");
    ui->asOne_7->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/7_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/7_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/7_keep) ;}");
    ui->asOne_8->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/8_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/8_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/8_keep) ;}");
    ui->asOne_s1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/s1_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/s1_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/s1_keep) ;}");
    ui->asOne_s2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/s2_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/s2_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/s2_keep) ;}");
    ui->asTwo_1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/1_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/1_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/1_keep) ;}");
    ui->asTwo_2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/2_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/2_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/2_keep) ;}");
    ui->asTwo_3->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/3_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/3_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/3_keep) ;}");
    ui->asTwo_4->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/4_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/4_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/4_keep) ;}");
    ui->asTwo_5->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/5_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/5_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/5_keep) ;}");
    ui->asTwo_6->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/6_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/6_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/6_keep) ;}");
    ui->asTwo_7->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/7_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/7_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/7_keep) ;}");
    ui->asTwo_8->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/8_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/8_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/8_keep) ;}");
    ui->asTwo_s1->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/s1_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/s1_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/s1_keep) ;}");
    ui->asTwo_s2->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/s2_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/s2_active) ;}"
        "QPushButton:disabled{border-image: url(:/spanish/s2_keep) ;}");
    ui->asOne_send->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/close_doors_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/close_doors_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/close_doors_pressed) ;}");
    ui->asTwo_send->setStyleSheet(
        "QPushButton{border-image: url(:/spanish/close_doors_no_active) ;}"
        "QPushButton:hover{border-image: url(:/spanish/close_doors_active) ;}"
        "QPushButton:pressed{border-image: url(:/spanish/close_doors_pressed) ;}");
}

void Widget::on_asOne_1_clicked()
{
    firstKeyboard[2] = '1';
    keyboardButtons.first[2]->setDisabled(true);
}

void Widget::on_asOne_2_clicked()
{
    firstKeyboard[3] = '1';
    keyboardButtons.first[3]->setDisabled(true);
}

void Widget::on_asOne_3_clicked()
{
    firstKeyboard[4] = '1';
    keyboardButtons.first[4]->setDisabled(true);
}

void Widget::on_asOne_4_clicked()
{
    firstKeyboard[5] = '1';
    keyboardButtons.first[5]->setDisabled(true);
}

void Widget::on_asOne_5_clicked()
{
    firstKeyboard[6] = '1';
    keyboardButtons.first[6]->setDisabled(true);
}

void Widget::on_asOne_6_clicked()
{
    firstKeyboard[7] = '1';
    keyboardButtons.first[7]->setDisabled(true);
}

void Widget::on_asOne_7_clicked()
{
    firstKeyboard[8] = '1';
    keyboardButtons.first[8]->setDisabled(true);
}

void Widget::on_asOne_8_clicked()
{
    firstKeyboard[9] = '1';
    keyboardButtons.first[9]->setDisabled(true);
}

void Widget::on_asOne_s1_clicked()
{
    firstKeyboard[1] = '1';
    keyboardButtons.first[1]->setDisabled(true);
}

void Widget::on_asOne_s2_clicked()
{
    firstKeyboard[0] = '1';
    keyboardButtons.first[0]->setDisabled(true);
}

void Widget::on_asTwo_1_clicked()
{
    secondKeyboard[2] = '1';
    keyboardButtons.second[2]->setDisabled(true);
}

void Widget::on_asTwo_2_clicked()
{
    secondKeyboard[3] = '1';
    keyboardButtons.second[3]->setDisabled(true);
}

void Widget::on_asTwo_3_clicked()
{
    secondKeyboard[4] = '1';
    keyboardButtons.second[4]->setDisabled(true);
}

void Widget::on_asTwo_4_clicked()
{
    secondKeyboard[5] = '1';
    keyboardButtons.second[5]->setDisabled(true);
}

void Widget::on_asTwo_5_clicked()
{
    secondKeyboard[6] = '1';
    keyboardButtons.second[6]->setDisabled(true);
}

void Widget::on_asTwo_6_clicked()
{
    secondKeyboard[7] = '1';
    keyboardButtons.second[7]->setDisabled(true);
}

void Widget::on_asTwo_7_clicked()
{
    secondKeyboard[8] = '1';
    keyboardButtons.second[8]->setDisabled(true);
}

void Widget::on_asTwo_8_clicked()
{
    secondKeyboard[9] = '1';
    keyboardButtons.second[9]->setDisabled(true);
}

void Widget::on_asTwo_s1_clicked()
{
    secondKeyboard[1] = '1';
    keyboardButtons.second[1]->setDisabled(true);
}

void Widget::on_asTwo_s2_clicked()
{
    secondKeyboard[0] = '1';
    keyboardButtons.second[0]->setDisabled(true);
}

void Widget::on_asOne_send_clicked()
{
    QByteArray data;
    unsigned char calculateCRC[] = "TFS10000000000";
    QString prefix("TFS1");
    data.append(QByteArray::fromHex(prefix.toLatin1().toHex()));
    for(int i = 0; i < 10; i++){
        data.append(firstKeyboard[i]);
        calculateCRC[i+4] = firstKeyboard[i];
        firstKeyboard[i] = '0';
        //keyboardButtons.first[i]->setEnabled(true);
    }
    data.append(crc8(calculateCRC+4, 10));
    modem_STM->write(data);
}

void Widget::on_asTwo_send_clicked()
{
    QByteArray data;
    unsigned char calculateCRC[] = "TFS20000000000";
    QString prefix("TFS2");
    data.append(QByteArray::fromHex(prefix.toLatin1().toHex()));
    for(int i = 0; i < 10; i++){
        data.append(secondKeyboard[i]);
        calculateCRC[i+4] = secondKeyboard[i];
        secondKeyboard[i] = '0';
        //keyboardButtons.second[i]->setEnabled(true);
    }
    data.append(crc8(calculateCRC+4, 10));
    modem_STM->write(data);
}

void Widget::init_crc8()
{
    int i,j;
    unsigned char crc;
    if (!made_table) {
    for (i=0; i<256; i++) {
        crc = i;
        for (j=0; j<8; j++)
            crc = (crc << 1) ^ ((crc & 0x80) ? DI : 0);
        crc8_table[i] = crc & 0xFF;
             /* printf("table[%d] = %d (0x%X)\n", i, crc, crc); */
        }
        made_table=1;
    }
}

unsigned char Widget::crc8(unsigned char *message, unsigned char length)
{
      unsigned char i, j, crc = 0;

      for (i = 0; i < length; i++)
      {
        crc ^= message[i];
        for (j = 0; j < 8; j++)
        {
          if (crc & 1)
            crc ^= GP;
          crc >>= 1;
        }
      }
    return crc;
}
