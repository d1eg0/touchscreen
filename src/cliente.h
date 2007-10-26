#include <SolarSockets/SolarSockets++.h>
#include <fstream>

class Cliente : public ssPPClient
{
private:
  void onConnect();
  void onDataArrival(string Data);
  void onError(int ssError);
};


