#include "compositestopper.h"

using namespace std;

CompositeStopper::CompositeStopper(const vector<const Stopper*>& sub_stoppers):
  m_sub_stoppers(sub_stoppers)
{}

CompositeStopper::CompositeStopper(const initializer_list<const Stopper*>& sub_stoppers):
  m_sub_stoppers(sub_stoppers)
{}


bool CompositeStopper::should_stop() const
{
  for (const Stopper* const stopper : m_sub_stoppers) {
    if (stopper->should_stop()) {
      return true;
    }
  }
  return false;
}
