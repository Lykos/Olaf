#ifndef COMPOSITESTOPPER_H
#define COMPOSITESTOPPER_H

#include <vector>
#include <initializer_list>
#include <memory>

#include "olaf/search/stopper.h"

namespace olaf
{

class CompositeStopper : public Stopper
{
public:
  /**
   * @brief CompositeStopper does not take ownership of any of the sub_stoppers
   */
  CompositeStopper(const std::vector<const Stopper*>& sub_stoppers);

  /**
   * @brief CompositeStopper does not take ownership of any of the sub_stoppers
   */
  CompositeStopper(const std::initializer_list<const Stopper*>& sub_stoppers);

  bool should_stop() const override;

private:
  std::vector<const Stopper*> m_sub_stoppers;

};

} // namespace olaf

#endif // COMPOSITESTOPPER_H
