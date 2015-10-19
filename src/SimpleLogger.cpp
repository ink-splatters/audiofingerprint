#include "SimpleLogger.h"

SimpleLogger::SimpleLogger():
  _isEnabled(true)
{

}

SimpleLogger &SimpleLogger::instance()
{
  static SimpleLogger logger;

  return logger;
}

void SimpleLogger::enable(bool isEnabled)
{
  _isEnabled = isEnabled;
}

bool SimpleLogger::isEnabled()const
{
  return _isEnabled;
}
