
#include <QCoreApplication>
#include "bozWebsocketClient.h"

int main(int ac, char **av) {
    QCoreApplication app(ac, av);
    quint16 port=7681;
    QString s("127.0.0.1");
    QHostAddress address(s);
    
    BOZ::bozWebsocketClient client(0);
    client.connectToHost(address, port);    
    
    return app.exec();
}
