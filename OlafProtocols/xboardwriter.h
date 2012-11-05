#ifndef XBOARDWRITER_H
#define XBOARDWRITER_H

#include "protocolwriter.h"
#include "result.h"
#include "OlafRules/move.h"
#include <string>
#include <mutex>
#include <vector>

class XBoardWriter : public ProtocolWriter
{
public:
  void newline();

  void unknown_command(const std::string&);

  void feature(const std::string& name, bool value);

  void feature(const std::string& name, int value);

  void feature(const std::string& name, const std::string& value);

  void move(const Move &);

  void error(const std::string& type, const std::string& message);

  void resign();

  void offer_draw();

  void result(Result, const std::string&);

  void tell_opponent(const std::string&);

  void tell_others(const std::string&);

  void tell_all(const std::string&);

  void tell_user(const std::string&);

  void tell_user_error(const std::string&);

  void askuser(const std::string &rep_tag, const std::string &question);

  void tell_ics(const std::string&);

  void tell_ics_noalias(const std::string&);

  void comment(const std::string&);

  void pong(int number);

  void illegal_move(const std::string& move);

  void illegal_move(const std::string& reason, const std::string& move);

  void thinking_output(int ply, int score, int centiseconds, int nodes, const std::string &moves);

private:
  std::mutex m_mutex;

};

#endif // XBOARDWRITER_H
