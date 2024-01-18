#include "widget.h"
#include "ui_widget.h"
#include "SerialManager.h"
#include "StyleManager.h"
#include <QDebug>
#include <QThread>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , serialManager(new SerialManager(this))
{
    ui->setupUi(this);
    init_crc8();

    // Pass the ui pointer to the StyleManager.
    styleManager = new StyleManager(ui);
    styleManager->setButtonStyles(this);

    for(int i = 0; i < 10; i++){
        firstKeyboard[i] = '0';
        secondKeyboard[i] = '0';
    }

    QKeyboardAscensor keyboard;
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
        qDebug() << "----------- Found device -----------";
        qDebug() << "Name: " << info.portName();
        qDebug() << "Description: " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "Vendor: " << info.vendorIdentifier();
        qDebug() << "Product: " << info.productIdentifier();
        qDebug() << "------------------------------------";
        ui->comboCOM->addItem(info.portName());
    }

    QTimer::singleShot(TIMEOUT_SCREEN_SAMPLING, this, SLOT(displayDoors()));

    connect(serialManager, &SerialManager::dataReceived, this, &Widget::handleSerialData);
    connect(serialManager, &SerialManager::errorOccurred, this, &Widget::handleSerialError);
}

void Widget::displayDoors()
{
    if(animOne < 11){
        if(displayDoorOne++ == 13){
            displayDoorOne = 0;
            animOne = 11;
        }else {
            ascOne.objects[animOne]->setPixmap(animDoor[displayDoorOne]);
        }
    }
    if(animTwo < 11){
        if(displayDoorTwo++ == 13){
            displayDoorTwo = 0;
            animTwo = 11;
        }
        else{
            ascTwo.objects[animTwo]->setPixmap(animDoor[displayDoorTwo]);
        }
    }
    QTimer::singleShot(TIMEOUT_SCREEN_SAMPLING, this, SLOT(displayDoors()));
}

void Widget::handleSerialData(const QByteArray &data)
{
    const char *pointer = data.constData();
    qDebug() << " Received: "<< data.constData();
    if(pointer[1] == ELEVATOR_ID_A ){
        for(int i = FLOOR_BUTTONS_START_INDEX_A; i < SIZE_PAGE_ASCENSOR; i++){
            if(pointer[i] == '1' ){
                keyboardButtons.first[i-FLOOR_BUTTONS_START_INDEX_A]->setEnabled(true);
            }
        }
        for(int i = FLOOR_BUTTONS_START_INDEX_B; i < SIZE_PAGE_ASCENSOR * NUM_ELEVATORS; i++){
            if(pointer[i] == '1' ){
                keyboardButtons.second[i-FLOOR_BUTTONS_START_INDEX_B]->setEnabled(true);
            }
        }
        if(pointer[BIT_UP_A] == '1'){
            ui->locationOne->setPixmap(QPixmap(":/spanish/up"));
            ui->logReg->append(QString("Ascensor 1 subiendo..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_A; i < SIZE_PAGE_ASCENSOR; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A ,"UP"));
                    animOne = i-FLOOR_BUTTONS_START_INDEX_A;
                }
                else if(pointer[i] == '1'){
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A, "UP"));
                }
                else{
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else if(pointer[BIT_DOWN_A] == '1'){
            ui->locationOne->setPixmap(QPixmap(":/spanish/down"));
            ui->logReg->append(QString("Ascensor 1 bajando..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_A; i < SIZE_PAGE_ASCENSOR; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A, "DOWN"));
                    animOne = i-FLOOR_BUTTONS_START_INDEX_A;
                }
                else if(pointer[i] == '1'){
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A, "DOWN"));
                }
                else{
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else{
            ui->locationOne->setPixmap(QPixmap(":/spanish/stop"));
            ui->logReg->append(QString("Ascensor 1 detenido..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_A; i < SIZE_PAGE_ASCENSOR; i++){
                if(pointer[32] == '1' && pointer[i] == '1'){
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A, "DOWN"));
                    animOne = i-FLOOR_BUTTONS_START_INDEX_A;
                }
                else if(pointer[i] == '1' && animOne == 11){
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asOne_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_A, "DOWN"));
                }
                else if(animOne == 11){
                    ascOne.objects[i-FLOOR_BUTTONS_START_INDEX_A]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
    }
    if(pointer[17] == ELEVATOR_ID_B ){
        if(pointer[BIT_UP_B] == '1'){
            ui->locationTwo->setPixmap(QPixmap(":/spanish/up"));
            ui->logReg->append(QString("Ascensor 2 subiendo..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_B; i < SIZE_PAGE_ASCENSOR * NUM_ELEVATORS; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B ,"UP"));
                    animTwo = i-FLOOR_BUTTONS_START_INDEX_B;
                }
                else if(pointer[i] == '1'){
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B ,"UP"));
                }
                else {
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else if(pointer[BIT_DOWN_B] == '1'){
            ui->locationTwo->setPixmap(QPixmap(":/spanish/down"));
            ui->logReg->append(QString("Ascensor 2 bajando..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_B; i < SIZE_PAGE_ASCENSOR * NUM_ELEVATORS; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B, "DOWN"));
                    animTwo = i-FLOOR_BUTTONS_START_INDEX_B;
                }
                else if(pointer[i] == '1'){
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B, "DOWN"));
                }
                else{
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
        else{
            ui->locationTwo->setPixmap(QPixmap(":/spanish/stop"));
            ui->logReg->append(QString("Ascensor 2 detenido..."));
            for(int i = FLOOR_BUTTONS_START_INDEX_B; i < SIZE_PAGE_ASCENSOR * NUM_ELEVATORS; i++){
                if(pointer[33] == '1' && pointer[i] == '1'){
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B, "DOWN"));
                    animTwo = i-FLOOR_BUTTONS_START_INDEX_B;
                }
                if(pointer[i] == '1' && animTwo == 11){
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/active_closed"));
                    ui->asTwo_indicator->setPixmap(styleManager->getLocationPixmap(i-FLOOR_BUTTONS_START_INDEX_B ,"UP"));
                }
                else if(animTwo == 11){
                    ascTwo.objects[i-FLOOR_BUTTONS_START_INDEX_B]->setPixmap(QPixmap(":/spanish/unused"));
                }
            }
        }
    }
}

void Widget::handleSerialError(const QString &error) {
    // What to do ?
    qCritical() << " ERROR: "<< error.constData();
}

void Widget::on_comButton_clicked()
{
    // If open, then close.
    if(serialManager->isConnected()) {
        serialManager->disconnect();
        ui->comButton->setEnabled(true);
        ui->comboCOM->setEnabled(true);
        qDebug() << "Desconectado";
    } else {
        // Set port and try to connect.
        QString portName = ui->comboCOM->currentText();

        if(serialManager->openSerialPort(portName)) {
            qDebug() << "Conectado";
            ui->comboCOM->setDisabled(true);
            connect(serialManager, &SerialManager::dataReceived, this, &Widget::handleSerialData);
            connect(serialManager, &SerialManager::errorOccurred, this, &Widget::handleSerialError);
        } else {
            QMessageBox::critical(this, tr("ERROR"), serialManager->errorString());
            ui->comButton->setEnabled(true);
        }
    }
}

void Widget::sendElevatorRequest(const QString &requestType, const QString &floor) {
    QString data = QString("AX%1%2").arg(requestType, floor);
    QByteArray sendThis = data.toUtf8();

    // Use QByteArray for the data and then get a pointer to the data for crc8.
    sendThis.append(crc8(reinterpret_cast<unsigned char*>(sendThis.data()), sendThis.size()));

    serialManager->writeData(sendThis);
}


void Widget::on_bajar_8_clicked()
{
    sendElevatorRequest("S0B1", "F9");
}

void Widget::on_subir_7_clicked()
{
    sendElevatorRequest("S1B0", "F8");
}

void Widget::on_bajar_7_clicked()
{
    sendElevatorRequest("S0B1", "F8");
}

void Widget::on_subir_6_clicked()
{
    sendElevatorRequest("S1B0", "F7");
}

void Widget::on_bajar_6_clicked()
{
    sendElevatorRequest("S0B1", "F7");
}

void Widget::on_subir_5_clicked()
{
    sendElevatorRequest("S1B0", "F6");
}

void Widget::on_bajar_5_clicked()
{
    sendElevatorRequest("S0B1", "F6");
}

void Widget::on_subir_4_clicked()
{
    sendElevatorRequest("S1B0", "F5");
}

void Widget::on_bajar_4_clicked()
{
    sendElevatorRequest("S0B1", "F5");
}

void Widget::on_subir_3_clicked()
{
    sendElevatorRequest("S1B0", "F4");
}

void Widget::on_bajar_3_clicked()
{
    sendElevatorRequest("S0B1", "F4");
}

void Widget::on_subir_2_clicked()
{
    sendElevatorRequest("S1B0", "F3");
}

void Widget::on_bajar_2_clicked()
{
    sendElevatorRequest("S0B1", "F3");
}

void Widget::on_subir_1_clicked()
{
    sendElevatorRequest("S1B0", "F2");
}

void Widget::on_bajar_1_clicked()
{
    sendElevatorRequest("S0B1", "F2");
}

void Widget::on_subir_s1_clicked()
{
    sendElevatorRequest("S1B0", "F1");
}

void Widget::on_bajar_s1_clicked()
{
    sendElevatorRequest("S0B1", "F1");
}

void Widget::on_subir_s2_clicked()
{
    sendElevatorRequest("S1B0", "F0");
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

void Widget::on_asOne_send_clicked() {
    sendData("TFS1", firstKeyboard);
}

void Widget::on_asTwo_send_clicked() {
    sendData("TFS2", secondKeyboard);
}

void Widget::sendData(const QString &prefix, unsigned char *keyboard) {
    QByteArray data;
    unsigned char calculateCRC[14];
    QString command = prefix + "0000000000";
    memcpy(calculateCRC, command.toLatin1().data(), 14);

    for(int i = 0; i < 10; i++){
        calculateCRC[i+4] = keyboard[i];
        keyboard[i] = '0';
    }

    data.append(prefix.toLatin1());
    data.append(static_cast<char>(crc8(calculateCRC+4, 10)));
    data.append(crc8(calculateCRC+4, 10));
    serialManager->writeData(data);
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

Widget::~Widget()
{
    delete styleManager;
    delete serialManager;
    delete ui;
}
