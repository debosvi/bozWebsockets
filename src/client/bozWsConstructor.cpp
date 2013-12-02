
#include "bozWebsocketClient.h"

namespace BOZ {
    
bozWebsocketClient::bozWebsocketClient(QObject *parent) : 
    QObject(parent), _fd(-1) {
        
    }
    
bozWebsocketClient::~bozWebsocketClient() {
    
}

} // NAMESPACE
