#include "../include/serialiseArraylist.h"

serialiseArraylist::serialiseArraylist(/* args */)
{
}

serialiseArraylist::~serialiseArraylist()
{
}

arraylist<pair<string, float>> serialiseArraylist::deserialiseintoArraylist(string &fileInput)
{
    arraylist<pair<string, float>> arr;
    // Create a stream to psuh string values into
    stringstream streamstring(fileInput);  
    string pairStr;
    // read the streamstring until ; store the string into pairStr for processing
    while (getline(streamstring, pairStr, ';')) {  
        // Find the comma seperator for the pair
        size_t commaPos = pairStr.find(',');
        // if the comma position exists
        if (commaPos != string::npos) {
            // create the pair from the two substrings
            // read from 0 to the comma
            string first = pairStr.substr(0, commaPos);  
            // Read from after the comma to the end of the string
            float second = stof(pairStr.substr(commaPos + 1));  
            arr.insert(pair(first, second));  
        }
    }
    return arr; 
}

string serialiseArraylist::serialiseArraylistIntoString(arraylist<pair<string, float>> &array)
{
    stringstream streamstring;
    for (size_t i = 0; i < array.length; ++i)
    {
        //convert array into string , between pairs and ; between values
        streamstring << array.get(i).first << "," << array.get(i).second;
        if (i < array.length - 1)
        {
            streamstring << ";"; 
        }
    }
    return streamstring.str();
}