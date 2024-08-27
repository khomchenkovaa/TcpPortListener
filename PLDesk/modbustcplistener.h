#ifndef MODBUSTCPLISTENER_H
#define MODBUSTCPLISTENER_H

#include "listenerwidget.h"

#include <QModbusTcpServer>
#include <QBitArray>

#define REG_MAX 2000

namespace Ui {
class ModbusTcpListener;
}

class ModbusTcpListener : public ListenerWidget
{
    Q_OBJECT

public:
    explicit ModbusTcpListener(QWidget *parent = nullptr);
    ~ModbusTcpListener();

signals:
    void tabText(const QString &label);

public slots:
    void onDataUpdated(QModbusDataUnit::RegisterType table, int address, int size);
    void handleDeviceError(QModbusDevice::Error newError);

private slots:
    void doConnect();
    void doDisconnect();
    void changeHandler(int index);

private:
    void updateStatus();
    void onCoilsUpdated(int address, int size);
    void onHoldingRegistersUpdated(int address, int size);
    void processCoils(int address, int size, const QBitArray &data);
    void processHoldingRegisters(int address, int size, const QList<quint16> &data);

private:
    Ui::ModbusTcpListener *ui;
    QModbusTcpServer m_ModbusDevice;
};

#endif // MODBUSTCPLISTENER_H
