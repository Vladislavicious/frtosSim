#ifndef INITIALIZABLE_H_
#define INITIALIZABLE_H_

//---------------------------------------------------------------
//       Initialazable interface definition:
//---------------------------------------------------------------
class Initialazable
{
public:
  bool Init();
  bool DeInit();
  bool IsInit();
protected:
  virtual bool _Init() = 0;
  virtual bool _DeInit() = 0;
private:
  bool initialized{ false };
};
//---------------------------------------------------------------
#endif // INITIALIZABLE_H_