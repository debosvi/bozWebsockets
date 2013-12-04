
#include <unistd.h>
#include <QCoreApplication>
#include "main.h"

TestWs::TestWs() : QObject(0), _client(Q_NULLPTR) {
        _client = new BOZ::bozWebsocketClient(this);
        connect(_client, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(_client, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
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

int main(int ac, char **av) {
    QCoreApplication app(ac, av);
    TestWs ws;

    ws.connection();
    sleep(1);
    ws.disconnection();
    sleep(1);
    
    return app.exec();
}
