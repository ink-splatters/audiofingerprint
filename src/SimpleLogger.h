#include <iostream>

class SimpleLogger
{
public:
  static SimpleLogger &instance();
  void enable(bool isEnabled);
  bool isEnabled()const;

  template<typename T>
  SimpleLogger& operator << ( T object)
  {
      if (_isEnabled)
      {
          std::cout << object;
      }
      return *this;
  }

private:
  SimpleLogger();
  bool _isEnabled;
};