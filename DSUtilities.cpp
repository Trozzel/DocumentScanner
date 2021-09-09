//
// Created by George Ford on 8/27/21.
//
#include "DSUtilities.h"

using namespace std;

static char waitBar[] = {'|', '/', '-', '\\'};

void spinWaiting(int ms, const bool& stop, string& message)
{
  if (!message.empty())
  {
    cout << message << "... ";
    message = "";
  }
  while (true)
  {
    for(char bar : waitBar)
    {
      if (!stop)
      {
        cout << bar;
        this_thread::sleep_for(chrono::milliseconds(ms));
        cout << '\b';
      }
      else
      {
        cout << endl;
        if (!message.empty())
          cout << message << endl;
        return;
      }
    }
  }
}