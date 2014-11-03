#ifndef SETEGTPATHEVENT_H
#define SETEGTPATHEVENT_H

#include <string>

#include "protocols/event/engineevent.h"

namespace olaf
{

class SetEgtPathEvent : public EngineEvent
{
public:
  explicit SetEgtPathEvent(const std::string& path);

  void execute(EngineState* state) override;

private:
  const std::string m_path;
};

} // namespace olaf

#endif // SETEGTPATHEVENT_H

