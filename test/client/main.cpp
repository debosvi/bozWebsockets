
#include <unistd.h>
#include <QCoreApplication>
#include "main.h"

TestWs::TestWs() : QObject(0), _client(Q_NULLPTR) {
    QString prot = "dumb-increment-protocol";
    _client = new BOZ::bozWebsocketClient(prot, this);
    connect(_client, SIGNAL(connected()), this, SLOT(onConnected()), Qt::DirectConnection);
    connect(_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    connect(_client, SIGNAL(readyRead()), this, SLOT(onData()), Qt::DirectConnection);
    }

TestWs::~TestWs() {
    delete _client;
    }

void TestWs::connection() {
    quint16 port=1234;
    QString s("127.0.0.1");
    QHostAddress address(s);
    
    _client->connectToHost(address, port);    
}

void TestWs::disconnection() {
    _client->disconnectFromHost();    
}

void TestWs::onConnected() {
    qDebug("%s", __PRETTY_FUNCTION__);
}

void TestWs::onDisconnected() {
    qDebug("%s", __PRETTY_FUNCTION__);
}

void TestWs::onData() {
//    qDebug("%s", __PRETTY_FUNCTION__);
    QByteArray data=_client->read();
    qDebug("%s: rx %d '%s'", __PRETTY_FUNCTION__, data.size(), data.constData());

    if(!strncmp(data.constData(), "7", 1)) {
        qDebug("%s: send reset", __PRETTY_FUNCTION__);
        _client->write("reset\n", 6);
    }

}

int main(int ac, char **av) {
    QCoreApplication app(ac, av);
    TestWs ws;

    ws.connection();
    sleep(1);
    ws.connection();
    sleep(1);
    ws.disconnection();
    sleep(1);
    ws.disconnection();
    sleep(1);
    ws.connection();
    sleep(1);
    ws.disconnection();
    sleep(1);
    ws.disconnection();
    sleep(1);

    QTimer t;
    t.setInterval(6);
    QObject::connect(&t, SIGNAL(timeout()), &app, SLOT(quit()));
    t.setSingleShot(true);
    t.start();
    
    return app.exec();
}
