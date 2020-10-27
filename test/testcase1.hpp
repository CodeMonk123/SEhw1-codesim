class MyClass
{
public:
  int field;
  virtual void method() const = 0;

  static const int static_field;
  static int static_method();
};

class YourClass
{
  public:
    int f(int a, int b) {
      return a+b;
    }
};