
#include <QCoreApplication>
#include "bozWebsocketClient.h"

int main(int ac, char **av) {
    QCoreApplication app(ac, av);
    quint16 port=1234;
    QHostAddress address("localhost");
    
    BOZ::bozWebsocketClient client(0);
    client.connectToHost(address, port);    
    
    return app.exec();
}