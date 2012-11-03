#ifndef ENGINEFACTORY_H
#define ENGINEFACTORY_H

#include "engine.h"
#include "protocolwriter.h"

class EngineFactory
{
public:
  EngineFactory();

  Engine create_engine(ProtocolWriter *writer) const;

};

#endif // ENGINEFACTORY_H
