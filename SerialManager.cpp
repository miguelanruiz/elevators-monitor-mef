#include "SerialManager.h"
#include <QSerialPortInfo>

SerialManager::SerialManager(QObject *parent) : QObject(parent), serialPort(new QSerialPort(this)) {
    connect(serialPort, &QSerialPort::readyRead, this, &SerialManager::readData);
    connect(serialPort, &QSerialPort::errorOccurred, [this](QSerialPort::SerialPortError error) {
        if (error == QSerialPort::ReadError) {
            emit errorOccurred(serialPort->errorString());
        }
    });
}

SerialManager::~SerialManager() {
    closeSerialPort();
}

bool SerialManager::openSerialPort(const QString &portName) {
    serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    return serialPort->open(QIODevice::ReadWrite);
}

void SerialManager::closeSerialPort() {
    if (serialPort->isOpen())
        serialPort->close();
}

bool SerialManager::writeData(const QByteArray &data) {
    if (serialPort->isOpen()) {
        return serialPort->write(data) != -1;
    }
    return false;
}

QString SerialManager::errorString() const {
    // Retorna una descripción del último error.
    return serialPort->errorString();
}

bool SerialManager::isConnected() const {
    return serialPort->isOpen();
}

void SerialManager::readData() {
    const QByteArray data = serialPort->readAll();
    emit dataReceived(data);
}
