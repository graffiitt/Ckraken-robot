#ifndef PHREI_IO_H
#define PHREI_IO_H

#include <QObject>

#include "statemanager.h"
#include "md_client.h"

#include <QDebug>

class PherephicalIO : public QObject
{
    Q_OBJECT
public:
    PherephicalIO(PherephicalIO const &) = delete;
    PherephicalIO &operator=(PherephicalIO const &) = delete;
    ~PherephicalIO() {

    };

    static PherephicalIO *getInstance()
    {
        static PherephicalIO *inst = new PherephicalIO();
        return inst;
    };

    void startRequesting(bool state) {

    };

    void checkConnection()
    {
        StateManager::getInstance()->setIconState(StateManager::Icon::MCU, true);
        StateManager::getInstance()->setInfo("io module not found");
    };

private:
    

    PherephicalIO()
    {

        
    };
};

#endif