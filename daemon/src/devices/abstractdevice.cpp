#include "abstractdevice.h"

#include <QString>
    
AbstractDevice::AbstractDevice(QObject *parent) : QBLEDevice(parent)
{
    setConnectionState("disconnected");
    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setInterval(60000);
    connect(m_reconnectTimer, &QTimer::timeout, this, &AbstractDevice::reconnectionTimer);
}

QString AbstractDevice::pair()
{
    qDebug() << "AbstractDevice::pair";

    m_needsAuth = true;
    m_pairing = true;
    m_autoreconnect = true;
    //disconnectFromDevice();
    setConnectionState("pairing");
    emit connectionStateChanged();

    return QBLEDevice::pair();
}

void AbstractDevice::pairAsync()
{
    qDebug() << "AbstractDevice::pairAsync";

    m_needsAuth = true;
    m_pairing = true;
    m_autoreconnect = true;
    //disconnectFromDevice();
    setConnectionState("pairing");
    emit connectionStateChanged();

    QBLEDevice::pairAsync();
}

void AbstractDevice::connectToDevice()
{
    qDebug() << "AbstractDevice::connectToDevice";

    m_pairing = false;
    m_autoreconnect = true;
    QBLEDevice::disconnectFromDevice();
    setConnectionState("connecting");
    QBLEDevice::connectToDevice();
    m_reconnectTimer->start(); //Start timer to attempt to reconnect every 60 seconds
}

void AbstractDevice::disconnectFromDevice()
{
    qDebug() << "AbstractDevice::disconnectFromDevice";

    m_autoreconnect = false;
    setConnectionState("disconnected");

    QBLEDevice::disconnectFromDevice();
}

void AbstractDevice::reconnectionTimer()
{
    qDebug() << "AbstractDevice::reconnectionTimer";
    if ((!deviceProperty("Connected").toBool() && m_autoreconnect) || connectionState() == "authfailed") {
        qDebug() << "Lost connection";
        QBLEDevice::disconnectFromDevice();
        QBLEDevice::connectToDevice();
    }
}

void AbstractDevice::setConnectionState(const QString &state)
{
    if (state != m_connectionState) {
        m_connectionState = state;
        emit connectionStateChanged();
    }
}

QString AbstractDevice::connectionState() const
{
    return m_connectionState;
}

QString AbstractDevice::prepareFirmwareDownload(const QString &path)
{
   Q_UNUSED(path)
   return "";
}

void AbstractDevice::startDownload()
{
    
}

void AbstractDevice::downloadSportsData()
{
    
}

void AbstractDevice::sendWeather(CurrentWeather *weather)
{
    Q_UNUSED(weather)
}

void AbstractDevice::refreshInformation()
{
    
}

QString AbstractDevice::information(Info i)
{
    Q_UNUSED(i)
}

void AbstractDevice::applyDeviceSetting(Settings s)
{
    Q_UNUSED(s)
    emit message(tr("Device doen not support settings"));
}

void AbstractDevice::rebootWatch()
{

}
