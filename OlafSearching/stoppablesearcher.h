#ifndef STOPPABLESEARCHER_H
#define STOPPABLESEARCHER_H

class StoppableSearcher
{
public:

  void request_stop();

  virtual ~StoppableSearcher() {}

protected:
  bool stop_requested() const;

  void stopped();

private:
  volatile bool m_should_stop = false;

};

#endif // STOPPABLESEARCHER_H
