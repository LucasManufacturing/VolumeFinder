#pragma once
#include <string> 
#include <fstream>

using namespace std;
class programSettings {
public:
    string path; //Path for the settings file
    string setting; //used as a specifier for which setting to return


    string find(string setting);

private:
};