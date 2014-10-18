#ifndef XBOARDWRITER_H
#define XBOARDWRITER_H

#include <string>
#include <mutex>
#include <vector>
#include <ostream>

#include "protocolwriter.h"
#include "result.h"
#include "OlafSearching/move.h"

/**
 * @brief The XBoardWriter class sends answers to the chess interface program
 *        using the XBoard protocol.
 */
class XBoardWriter : public ProtocolWriter
{
public:
  enum class ErrorType {
    UNKNOWN_COMMAND,
    NOT_ENOUGH_ARGUMENTS,
    INVALID_FEN
  };

  /**
   * @brief XBoardWriter does not take ownership of out.
   * @param out the output stream to which the result should be written.
   */
  XBoardWriter(std::ostream* out);

  ~XBoardWriter();

  void newline();

  void unknown_command(const std::string&);

  void feature(const std::string& name, bool value);

  void feature(const std::string& name, int value);

  void feature(const std::string& name, const std::string& value);

  void move(const Move& mov) override;

  void error(const ErrorType type, const std::string& message);

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

  void comment(const std::string&) override;

  void pong(int number) override;

  void illegal_move(const std::string& move);

  void illegal_move(const std::string& reason, const std::string& move);

  void thinking_output(int ply,
                       int score,
                       int centiseconds,
                       int nodes,
                       const std::string& moves) override;

private:
  std::string error_name(ErrorType type) const;

  std::mutex m_mutex;

  std::ostream* const m_out;
};

#endif // XBOARDWRITER_H
