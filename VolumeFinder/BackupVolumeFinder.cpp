#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <windows.h>
#include <tchar.h>
#include <atlstr.h>
#include <vector>
#include <slicerArgs.h>
#include <filesystem>
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


double line_double(string _string) //Finds all the numbers in a string and converts it to a double 
    {
    int it = 0;
    string doubleFromString = "";
    while (it != _string.size())
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


    return stod(doubleFromString);
}



string findLine(string fileDir, int line) //Searchs a slicer output file and returns dimensions and volume of print. 
{
    // Create a text string, which is used to output the text file
    string text;
    // Read from the text file
    ifstream file(fileDir);

    int fileReaderIterator = 0;
    while (getline(file, text)) {
        if (fileReaderIterator == line)
        {
            file.close();
            return text;
        }
        fileReaderIterator++;
    }
    file.close();
    return "*NULL*";
}

vector<string> findLines(string fileDir, vector<int> lines)
{
    vector<string> output;
    for (int i = 0; i < lines.size(); i++)
    {
        output.push_back(findLine(fileDir, lines[i]));
    }
    return output;
}

bool executeBat(string _batFilePath)
{
    //This chunk of code brought me to tears so i repurposed someone elses 
    cout << "\nExecuting Bat\n"; 
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
    doubleSize_x = line_double(strSize_x);
    doubleSize_y = line_double(strSize_y);
    doubleSize_z = line_double(strSize_z);
    doubleVolume = line_double(strVolume);

    return make_tuple(doubleSize_x, doubleSize_y, doubleSize_z, doubleVolume);

}

void createBat(vector<string> _batArgs, string _batFilePath, bool execute = false)
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

tuple<double, double, double, double> findModelInfo(string modelDir, string modelName) {
   double size_x, size_y, size_z, volume;
   string slicerDir = "C:\\Users\\Lucas Stacey\\Downloads\\Slic3r-1.3.0.64bit"; //This has to point towards the dir the slicercmd.exe lays 
   string batFilePath = modelDir + modelName + ".bat"; 
   string sliceInfoPath = modelDir + modelName + "Info.txt";
   string modelPath = modelDir + modelName + ".stl";
   string configFile = "D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini";
   string gCodeOutputPath = modelDir + modelName + "GCodeInfo.txt";
   string gCodeOutputDir = modelDir; 


   //Sets the options to be used in future arguments and file paths, these are really just testers
   /* 
   string batRanMsg = "Bat has ran";
   string batFilePath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\sliceCreator.bat";
   string sliceInfoPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\geometricInfo.txt";
   string modelPath = "D:\\3dModels\\GunClub\\Revolver\\ThickSpeedLoaderHolster.stl";
   string configFile = "D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini";
   string gCodeOutputPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\printingInfo.txt";
   string gCodeOutputDir = "D:\\Documents\\CodeProjects\\SlicingOutputs\\";
   */ 
   //-------------------------------------------------------------------------------------------------
    vector<string> batArgs; //Stores each line of argument to be sequentially executed in a .bat file
    batArgs.push_back(changeDir(slicerDir));
    batArgs.push_back(slicer() + info(modelPath) + cmdOutTo(sliceInfoPath));
    batArgs.push_back(slicer() + loadFile(configFile) + sliceGcode(modelPath, gCodeOutputDir) + cmdOutTo(gCodeOutputPath));
    batArgs.push_back(echo(batRanMsg));

    createBat(batArgs, batFilePath, true); //Creates .bat file using the above arguments and paths, and then executing it

    tie(size_x, size_y, size_z, volume) = slicerInfoOutput(sliceInfoPath); //Takes the tuple from slicerInfoOutput which originates from the info() arg.

   string materialInfo = findLine(gCodeOutputPath, 7); //Takes the Length found from the sliceGcode file. 

  //  cout << endl << "Size X: " << size_x << endl << "Size Y: " << size_y << endl << "Size Z: " << size_z << endl << "Volume: " << volume << endl << "Length: " << length;
    return make_tuple(size_x, size_y, size_z, volume) 
}

int main()
{
    cout << "Running";
    string targetDir = "D:\\Apache\\xampp\\htdocs\\uploads"
    bool running = true 
        while (running)
        {
            for (auto const& dir_entry : filesystem::directory_iterator{targetDir})
                cout << dir_entry << '\n';
    }




    int a; 
    cin >> a
        return a; 
}

/* 
int main() {
    double size_x, size_y, size_z, volume;
    string slicerDir = "C:\\Users\\Lucas Stacey\\Downloads\\Slic3r-1.3.0.64bit"; //This has to point towards the dir the slicercmd.exe lays 
    string outputLocation = "D:\\Documents\\CodeProjects\\SlicingOutputs\\";
    string batFilePath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\sliceCreator.bat";
    string sliceInfoPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\geometricInfo.txt";
    string modelPath = "D:\\3dModels\\GunClub\\Revolver\\ThickSpeedLoaderHolster.stl";
    string configFile = "D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini";
    string gCodeOutputPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\printingInfo.txt";
    string gCodeOutputDir = "D:\\Documents\\CodeProjects\\SlicingOutputs\\";


    //Sets the options to be used in future arguments and file paths, these are really just testers
    string batRanMsg = "Bat has ran";
    string batFilePath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\sliceCreator.bat";
    string sliceInfoPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\geometricInfo.txt";
    string modelPath = "D:\\3dModels\\GunClub\\Revolver\\ThickSpeedLoaderHolster.stl";
    string configFile = "D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini";
    string gCodeOutputPath = "D:\\Documents\\CodeProjects\\SlicingOutputs\\printingInfo.txt";
    string gCodeOutputDir = "D:\\Documents\\CodeProjects\\SlicingOutputs\\";
    //-------------------------------------------------------------------------------------------------
    vector<string> batArgs; //Stores each line of argument to be sequentially executed in a .bat file
    batArgs.push_back(changeDir(slicerDir));
    batArgs.push_back(slicer() + info(modelPath) + cmdOutTo(sliceInfoPath));
    batArgs.push_back(slicer() + loadFile(configFile) + sliceGcode(modelPath, gCodeOutputDir) + cmdOutTo(gCodeOutputPath));
    batArgs.push_back(echo(batRanMsg));

    createBat(batArgs, batFilePath, true); //Creates .bat file using the above arguments and paths, and then executing it

    tie(size_x, size_y, size_z, volume) = slicerInfoOutput(sliceInfoPath); //Takes the tuple from slicerInfoOutput which originates from the info() arg.

    string materialInfo = findLine(gCodeOutputPath, 7); //Takes the Length found from the sliceGcode file. 

   //  cout << endl << "Size X: " << size_x << endl << "Size Y: " << size_y << endl << "Size Z: " << size_z << endl << "Volume: " << volume << endl << "Length: " << length;
    int a;
    cin >> a;
    return a;
}*/ 








































