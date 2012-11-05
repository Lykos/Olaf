#include "thinkingwriter.h"

ThinkingWriter::~ThinkingWriter() {}

void ThinkingWriter::post(bool value)
{
  m_post = value;
}

bool ThinkingWriter::post() const
{
  return m_post;
}
