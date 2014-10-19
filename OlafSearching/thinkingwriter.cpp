#include "thinkingwriter.h"

namespace olaf
{

ThinkingWriter::ThinkingWriter():
  m_post (true)
{}

ThinkingWriter::~ThinkingWriter() {}

void ThinkingWriter::post(const bool value)
{
  m_post = value;
}

bool ThinkingWriter::post() const
{
  return m_post;

} // namespace olaf
}
