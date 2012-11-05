#ifndef XBOARDWRITER_H
#define XBOARDWRITER_H

#include "protocolwriter.h"
#include "result.h"
#include "OlafRules/move.h"
#include <string>

class XBoardWriter : public ProtocolWriter
{
public:
  void newline() const;

  void unknown_command(const std::string&) const;

  void feature(const std::string& name, bool value) const;

  void feature(const std::string& name, int value) const;

  void feature(const std::string& name, const std::string& value) const;

  void move(const Move &) const;

  void error(const std::string& type, const std::string& message) const;

  void resign() const;

  void offer_draw() const;

  void result(Result, const std::string&) const;

  void tell_opponent(const std::string&) const;

  void tell_others(const std::string&) const;

  void tell_all(const std::string&) const;

  void tell_user(const std::string&) const;

  void tell_user_error(const std::string&) const;

  void askuser(const std::string &rep_tag, const std::string &question) const;

  void tell_ics(const std::string&) const;

  void tell_ics_noalias(const std::string&) const;

  void comment(const std::string&) const;

  void pong(int number) const;

  void illegal_move(const std::string& move) const;

  void illegal_move(const std::string& reason, const std::string& move) const;

};

#endif // XBOARDWRITER_H
