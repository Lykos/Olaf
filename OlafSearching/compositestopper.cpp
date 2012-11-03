#include "compositestopper.h"

using namespace std;
using namespace boost;

CompositeStopper::CompositeStopper(const vector<shared_ptr<Stopper>> &sub_stoppers):
  m_sub_stoppers (sub_stoppers)
{}

CompositeStopper::CompositeStopper(const initializer_list<shared_ptr<Stopper>> &sub_stoppers):
  m_sub_stoppers (sub_stoppers)
{}


bool CompositeStopper::should_stop(int nodes_searched) const
{
  for (const shared_ptr<Stopper>& stopper : m_sub_stoppers) {
    if (stopper->should_stop(nodes_searched)) {
      return true;
    }
  }
  return false;
}
