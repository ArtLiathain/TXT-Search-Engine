#include "arraylist.h"
#include <sstream> 
using namespace std;

class serialiseArraylist
{
private:
    /* data */
public:
    serialiseArraylist(/* args */);
    ~serialiseArraylist();
    arraylist<pair<string, float>> deserialiseintoArraylist(string& fileInput);
    string serialiseArraylistIntoString(arraylist<pair<string, float>>& array);
};

