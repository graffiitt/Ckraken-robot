#include "icommand.h"

ICommand::ICommand(int indexWidget) : index(indexWidget)
{
}

int ICommand::getIndex()
{
    return index;
}
