#include "icommand.h"

ICommand::ICommand(int indexWidget) : index(indexWidget)
{
}

ICommand::~ICommand()
{
}

int ICommand::getIndex()
{
    return index;
}
