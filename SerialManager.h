#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>
#include <QSerialPort>

class SerialManager : public QObject {
    Q_OBJECT

public:
    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    bool openSerialPort(const QString &portName);
    void closeSerialPort();
    bool writeData(const QByteArray &data);
    bool isConnected() const;
    QString errorString() const;

    struct Settings {
        QString name;
        qint32 baudRate;
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
        QSerialPort::FlowControl flowControl;
    };

signals:
    void dataReceived(const QByteArray &data);
    void errorOccurred(const QString &error);

private slots:
    void readData();

private:
    QSerialPort *serialPort;
};

#endif // SERIALMANAGER_H
