#include <iostream>
#include <stdexcept>
#include <filesystem>

#include "DocumentScanner.h"

using namespace std;
using namespace cv;
namespace fs = __fs::filesystem;

/******************************************************************************/
int main(int argc, char* argv[])
{
  string filename;
  if (argc == 2)
    filename = string(argv[1]);
  else if (argc == 1)
    //filename = "../images/scanned-form.jpg";
    filename = "../images/scanned-form.jpg";
  else
  {
    cout << "USAGE:" << endl
         << "./documentScanner <filename>" << endl
         << "-OR-" << endl
         << "./documentScanner" << endl;
    return EXIT_FAILURE;
  }

  DocumentScanner ds(filename, "Detection");
  ds.run();

	return 0;
}
/******************************************************************************/

