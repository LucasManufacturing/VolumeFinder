#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <windows.h>
#include <tchar.h>
#include <atlstr.h>
#include <stdio.h>
#include <vector>
#include "slicerArguments.h"
#include "settings.h"
#include <filesystem>
#include <regex>
#include <ctime>
#include <lucasMaths.h>
/*
#include <iostream>
#include <algorithm>
#include <list>

#include <stdlib.h>
#include <math.h>  
#include <time.h> 
#include <charconv>
#include <vector>*/
using namespace std;
using filesystem::directory_iterator;

//Some dangerous global variables because im lazy and live life on the edge
bool debug = true;

void b_cout(string msg = "", string _string = "", int _int = 9999)
{
    if (debug)
    {
        cout << msg << " " << _string << endl;
    }
}

double line_double(string _string) //Finds all the numbers in a string and converts it to a double 
    {
    int it = 0;
    string doubleFromString = "";
    while (it != _string.size())//this should've been written with a isDigit type loop like stringToOnlyDigits() smh
    {
        switch (_string[it]) {
        case '0':
            doubleFromString += _string[it];
            break;
        case '1':
            doubleFromString += _string[it];
            break;
        case '2':
            doubleFromString += _string[it];
            break;
        case '3':
            doubleFromString += _string[it];
            break;
        case '4':
            doubleFromString += _string[it];
            break;
        case '5':
            doubleFromString += _string[it];
            break;
        case '6':
            doubleFromString += _string[it];
            break;
        case '7':
            doubleFromString += _string[it];
            break;
        case '8':
            doubleFromString += _string[it];
            break;
        case '9':
            doubleFromString += _string[it];
            break;
        case '.':
            doubleFromString += _string[it];
            break;
        default: break;
        }
        it++;
   }

   // cout << "\nString " << _string << " DoubleString " << doubleFromString << endl; 
    return stod(doubleFromString);
}

void printStringVect(vector<string> input)//it little but it clean 
{
    for (int i = 0; i < input.size(); i++) {
        cout << input.at(i) << endl;
    }
}

string findLine(string fileDir, int line) //Searchs a slicer output file and returns dimensions and volume of print. 
{
    b_cout("findLine() Started with", fileDir);
    // Create a text string, which is used to output the text file
    string text;
    // Read from the text file
    ifstream file(fileDir);

    int fileReaderIterator = 0;
    while (getline(file, text)) {
        if (fileReaderIterator == line)
        {
            file.close();
            b_cout("findLine() Ended wtih text");
            return text;
        }
        fileReaderIterator++;
    }
    file.close();
    b_cout("findLine() Ended without text"); 
    return "*NULL*";
}

vector<string> findLines(string fileDir, vector<int> lines)//Bassically just finds several lines using the findLine()
{
    b_cout("findLines() Started with ", fileDir);
    vector<string> output;
    for (int i = 0; i < lines.size(); i++)
    {
        output.push_back(findLine(fileDir, lines[i]));
    }
    b_cout("findLines() Ended");
    return output;
}

vector<string> allLines(string fileDir)//returns all the lines of a file as an array with each indivdiual line being stored as a string
{
    // Create a text string, which is used to output the text file
    vector<string> output;
    string text; 
    // Read from the text file
    ifstream file(fileDir);

    int fileReaderIterator = 0;
    while (getline(file, text))
        {
        output.push_back(text);
        }
    return output; 
    file.close();

}

bool executeBat(string _batFilePath) //executes a bat using some witch craft
{
    //This chunk of code brought me to tears so i repurposed someone elses 
   // cout << "\nExecuting Bat\n"; 
    string _string = _batFilePath; //Mine
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    TCHAR tcsCommandLine[256];
    _tcscpy_s(tcsCommandLine, CA2T(_batFilePath.c_str())); //Mine
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    if (!CreateProcess(NULL, tcsCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        printf("CreateProcess failed (%d)\n", GetLastError());
        return FALSE;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

tuple<double, double, double, double> slicerInfoOutput(string fileDir) //Opens the file opened by the info() arg and makes a tuple containing the XYZ and volume info.
{

    
    vector<int> sliceInfoLines = { 2, 3, 4, 14 };
    double doubleSize_x = 0, doubleSize_y = 0, doubleSize_z = 0, doubleVolume = 0;
    vector<string> sliceInfoXYZV = findLines(fileDir, sliceInfoLines);
    string strSize_x = sliceInfoXYZV[0], strSize_y = sliceInfoXYZV[1], strSize_z = sliceInfoXYZV[2], strVolume = sliceInfoXYZV[3];
   // cout << "\nStartingsliceInfoDub\n";
    doubleSize_x = line_double(strSize_x);
    doubleSize_y = line_double(strSize_y);
    doubleSize_z = line_double(strSize_z);
    doubleVolume = line_double(strVolume);
   // cout << "\nEndedSliceInfoDub\n";

    return make_tuple(doubleSize_x, doubleSize_y, doubleSize_z, doubleVolume);

}

void createBat(vector<string> _batArgs, string _batFilePath, bool execute = false) //creates a bat file and can execute it
{
    int it = 0;
    ofstream myfile;
    myfile.open(_batFilePath);
    myfile << "@ECHO OFF\n";
    while (it != _batArgs.size())
    {
        myfile << _batArgs[it] << endl;
        it++;
    }

    myfile.close();

    if (execute)
    {
        executeBat(_batFilePath); 
    }
}

tuple<double, double, double, double> findModelInfo(string modelPath, vector<string> userConfigs, vector<string> settings) {
    b_cout("findModelInfo() Started");
   double size_x, size_y, size_z, volume;
   string slicerDir = settings[0]; //This has to point towards the dir the slicercmd.exe lays 
   string batFilePath = settings[1];
   string sliceInfoPath = settings[2];
   string configFile = settings[3];
   string gCodeOutputPath = settings[4];
   string gCodeOutputDir = settings[5];
   string batRanMsg = "Bat has ran";

   printStringVect(userConfigs);
   string infilDensity = userConfigs[0]; //This chunk of declarations come from the options the user selects on the website. see findUserConfigs() for more info


    vector<string> batArgs; //Stores each line of argument to be sequentially executed in a .bat file
    batArgs.push_back(changeDir(slicerDir));
    batArgs.push_back(slicer() + info(modelPath) + cmdOutTo(sliceInfoPath));
    batArgs.push_back(slicer() + loadFile(configFile) + infil(infilDensity) + sliceGcode(modelPath) + cmdOutTo(gCodeOutputPath));
    batArgs.push_back(echo(batRanMsg));

    createBat(batArgs, batFilePath, true); //Creates .bat file using the above arguments and paths, and then executing it

    tie(size_x, size_y, size_z, volume) = slicerInfoOutput(sliceInfoPath); //Takes the tuple from slicerInfoOutput which originates from the info() arg.

   string materialInfo = findLine(gCodeOutputPath, 7); //Takes the Length found from the sliceGcode file. 
   string printVolumeDirty = materialInfo.substr(materialInfo.find("(")); 
   float printVolume = line_double(printVolumeDirty);
  //  cout << endl << "Size X: " << size_x << endl << "Size Y: " << size_y << endl << "Size Z: " << size_z << endl << "Volume: " << volume << endl << "Length: " << length;
   b_cout("findModelInfo() Ended");
   return make_tuple(size_x, size_y, size_z, printVolume);
}



string eraseFirstCharAndLastChar(string _string)//digusting but needed and very simple
{
    string targetString = _string; 
    targetString.erase(targetString.begin());//These 2 lines will erase the first character and last character since the string contains " "quotes
    targetString.erase(targetString.end() - 1);
    return targetString;
}

string replaceAll(string _string, string searchFor, string replaceWith)//Searches a string for a target and replaces it for the entire string, it's like the replace() but with steroids 
{
    b_cout("replaceAll() Started");
    string searchIn = _string;
    size_t foundPos = searchIn.find(searchFor);////npos is the "cant find it" thingo for the find function, if it does find the problem string then it will return a position 
    while (foundPos != string::npos)
    {
        if (foundPos != string::npos)
        {
            searchIn.replace(foundPos, searchFor.length(), replaceWith);
        }
        foundPos = searchIn.find(searchFor);
        
    }
    b_cout("replaceAll() Ended");
    return searchIn; 
}


vector<string> findSubDirs(string _targetDir, string subDirDepositPath)//uh finds the directory's including file paths inside a directory
{
    b_cout("findSubDirs() Started");
    string firstPath;
    string secondPath;
    vector<string> subDirPaths; 
    vector<string> stlPathtxtPath; 
    ofstream subDirDeposit(subDirDepositPath);
    for (const auto& fileIt : directory_iterator(_targetDir))//Finds the subfiles in _targetDir and writes to the subDirDeposit.txt
        subDirDeposit << fileIt.path() << endl;


    subDirPaths = allLines(subDirDepositPath);//assigns the array all the lines indvidually as strings 
    b_cout("findSubDirs() subDirPaths = allLines");
    firstPath = subDirPaths[0];
    secondPath = subDirPaths[1];
    b_cout("FindSubDirs() Assgin paths to sub vect");
    firstPath = replaceAll(firstPath, "\\\\", "\\");// For some reason the paths in the subDirPaths have quadruple backslashes so i replace them with double
    secondPath = replaceAll(secondPath, "\\\\", "\\");
    b_cout("FindSubDirs() replaceAll");
    //P.S im also pretty sure this doesn't work as i intended as "\\\\" is tried as \\ and "\\" is \ 
    //so i think it just keeps passing through my func until it gets them to \ but the rest of the code doesn't have problems with that so uh it works no touchies <3

    string stlPath;
    string txtPath;
    if (firstPath.find(".txt") == string::npos)
    {
        stlPath = firstPath;
        txtPath = secondPath;
    }
    else
    {
        stlPath = secondPath;
        txtPath = firstPath;
    }
    b_cout("FindSubDirs() start eraseFCALC");
    stlPathtxtPath.push_back(eraseFirstCharAndLastChar(stlPath));
    stlPathtxtPath.push_back(eraseFirstCharAndLastChar(txtPath));
    

    subDirDeposit.close();
    b_cout("FindSubDirs() Ended");
    return stlPathtxtPath; 
    
}

tuple<bool, string, vector<string>> checkForNewDir(string targetDir, vector<string> _dirs, string dirDepositPath)//This checks to see if any new dirs have been created
{
    b_cout("checkFOrNewDir() Started");
    vector<string> newDirs; 
    vector<string> returnDirs; 
    string newDir;
    returnDirs = _dirs; 
    bool boolNewDir = false;
    ofstream dirDeposit(dirDepositPath);
    for (const auto& fileIt : directory_iterator(targetDir))
        dirDeposit << fileIt.path() << endl;
    b_cout("Iteration Done");
    newDirs = allLines(dirDepositPath);//Stores the lines of the text in vector string

    if (newDirs.size() != _dirs.size())//Checks to see if a new dir has been added (file uploaded) 
    {
        

        //This stuff finds the dir of the new one and creates a file with the dir's sub files vvv
        
        for (int i = 0; i < newDirs.size(); i++) //This will check each newPath string to see if it is in the oldPath vector. Hence figures out which the new dir is since dir is listen in alphabetical order smh
        {
            boolNewDir = true;
            for (int it = 0; it < _dirs.size(); it++)
            {

                if (newDirs[i] == _dirs[it])
                {
                    boolNewDir = false;
                }
            }
            if (boolNewDir == true) //So if it's a new dir assign the newDirs string to newDir
            {
                newDir = newDirs[i];
                newDir = eraseFirstCharAndLastChar(newDir);


                returnDirs = newDirs; 
                dirDeposit.close();
                b_cout("checkFOrNewDir() Ended");
                return make_tuple(boolNewDir, newDir, returnDirs);

            }
        }
    }

    dirDeposit.close();
    b_cout("checkFOrNewDir() Ended");
    return make_tuple(boolNewDir, newDir, returnDirs);
    
}

string stringToOnlyDigits(string _string)
{
    b_cout("stringToOnlyDigits() Started");
    string output; 
    for (int i = 0; i < _string.size(); i++)
    {
        if (isdigit(_string[i]) == 4)//returns 4 for true and 0 for false, i dunno im pretty sure cplusplus.com says it returns true and false
        {
            output.push_back(_string[i]); 
        }
    }
    b_cout("stringToOnlyDigits() Ended");
    return output; 
}

vector<string> findUserConfigs(string path)
{
    b_cout("findUserConfigs() Started");
    vector<string> output; 
    vector<string> pathLines = allLines(path);
    for (int i = 0; i < pathLines.size(); i++)
    {
        output.push_back(stringToOnlyDigits(pathLines[i])); 
    }
    /*
    output[0] contains infil%
    
    */
    b_cout("findUserConfigs() Ended");
    return output;
}

int main()
{
    programSettings defaultSettings;
    defaultSettings.path = "settings.txt";
    cout << "Running\n";
    cout << time(0); 
    float markup = 7.5; //Multiplier| markup * cost = price 
    float costOfPETG = 39.95 / 1000; //Price per gram 
    float densityOfPETG = 1.27; //g/cm3
    string slicerDir = defaultSettings.find("slicerDir"); 
    string gcodeOutputDir = defaultSettings.find("gcodeOutputDir");
    string targetDir = defaultSettings.find("modelDir");
  //  string targetDir = "D:\\Apache\\xampp\\htdocs\\uploads";
    string dirDepositPath = defaultSettings.find("dirDepositPath");
  //  string dirDepositPath = "D:\\Documents\\CodeProjects\\SlicingStuff\\dirDeposit.txt";
    string subDirDepositPath = defaultSettings.find("subDirDepositPath");
    string batFilePath = defaultSettings.find("batFilePath");
    string sliceInfoPath = defaultSettings.find("sliceInfoPath");
    string slicingConfigPath = defaultSettings.find("slicingConfigPath");
    string gcodeOutputPath = defaultSettings.find("gcodeOutputPath");

    cout << endl << slicerDir << endl << gcodeOutputDir << endl << targetDir << endl << dirDepositPath << endl << subDirDepositPath << endl << batFilePath << endl << sliceInfoPath << endl << slicingConfigPath << endl << gcodeOutputPath << endl; 
    vector<string> findModelInfoSettings; 
    
    findModelInfoSettings.push_back(slicerDir);
    findModelInfoSettings.push_back(batFilePath);
    findModelInfoSettings.push_back(sliceInfoPath);
    findModelInfoSettings.push_back(slicingConfigPath);
    findModelInfoSettings.push_back(gcodeOutputPath);
    findModelInfoSettings.push_back(gcodeOutputDir);

    string dirRead = ""; 
    vector<string> oldDirs;
    time_t nullPointer = NULL; 
     

    bool running = true;

    //This logs what sub dirs are present in targert dir. 
    ofstream dirDeposit(dirDepositPath);
    for (const auto& fileIt : directory_iterator(targetDir))
        dirDeposit << fileIt.path() << endl;

    oldDirs = allLines(dirDepositPath);//Stores the lines of the text in vector string
   //------------------
        while (running)
        {
            b_cout("running"); 
            time_t startTime = time(0); 
           // b_cout("whileRunning");
            bool hasNewDirBeenFound; 
            string newDir;
            tie(hasNewDirBeenFound, newDir, oldDirs) = checkForNewDir(targetDir, oldDirs, dirDepositPath);//sets oldDirs which if no new dir has been found will just set it as it was parsed, or if a new dir was found will be set to include it
           
            if (hasNewDirBeenFound)
            {
                b_cout("newDirFound");
                vector<string> txtStlVector = findSubDirs(newDir, subDirDepositPath);
                b_cout("FoundSubDirs");
                string stlPath = txtStlVector[0];
                string txtPath = txtStlVector[1]; 
                b_cout("STL Path ", stlPath);
                vector<string> userConfigurations;
                userConfigurations = findUserConfigs(txtPath); 

                float sizeX, sizeY, sizeZ, printVolume;
                tie(sizeX, sizeY, sizeZ, printVolume) = findModelInfo(stlPath, userConfigurations, findModelInfoSettings);
                float cost = costOfPETG * densityOfPETG * printVolume; //Finds material cost
                float price = cost * markup; //Finds posted price without shipping
                ofstream costTxt(newDir + "\\cost.txt");
                costTxt << stlPath << endl;
                costTxt << price;
                costTxt.close();
                cout << "\nNew Model " << stlPath << "\nPrice: $" << price; 
                time_t endTime = time(0);
                cout << "\nTime Taken: " << difftime(endTime, startTime);

            }

        }
    
    int a; 
    cin >> a;
    return a; 
}

/*
                              Known Problems and things to add
#Can't handle if more than one files are uploaded at a time, don't really know what would happen, 
    best case scenario it forgets about the rest and fills one if not uh bad shit i guess

#Not really a problem more so a philospohical question, security? 

#Some sort of config file so i dont have to adjust prices and dirs in here 

#Really got to add some infil config to the slicer args and other args such as quality 

#the ideal scope of this is to find the overal cost so uh i should seperate the projects into the constantly running main()
    to it own file and seperate most of this as like a material cost type thing

#Deal with the warnings 

#More so an entire project issue, work out what is causing the slowness, im pretty sure its equal amongst everywhere but together it's 

#Add some class for the settings. so i can do things like settings.getDirDeposit() 

#Add some folder creator to store the slicer software
*/






//Sets the options to be used in future arguments and file paths, these are really just testers | Throw in findModelInfo()
/*

string batFilePath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\sliceCreator.bat";
string sliceInfoPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\geometricInfo.txt";
string modelPath = "D:\\3dModels\\GunClub\\Revolver\\ThickSpeedLoaderHolster.stl";
string configFile = "D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini";
string gCodeOutputPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\printingInfo.txt";
string gCodeOutputDir = "D:\\Documents\\CodeProjects\\SlicingOutputs\\";
*/
//-------------------------------------------------------------------------------------------------






























