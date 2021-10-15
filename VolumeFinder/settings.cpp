#include "settings.h"




    string programSettings::find(string setting)
    {
        string line;
        ifstream settingFile(programSettings::path);
        while (getline(settingFile, line))
        {
            if (line[0] == '#')
            {
                if (line.find(setting) != string::npos)
                {
                    size_t startOfSetting = line.find(setting) + setting.length() + 2;
                    //cout << line.substr(startOfSetting);
                    return line.substr(startOfSetting);
                }
            }
        }
        settingFile.close();
    }
