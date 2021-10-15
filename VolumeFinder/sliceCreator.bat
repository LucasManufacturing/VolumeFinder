@ECHO OFF
cd /d C:\\Users\\Lucas Stacey\\Downloads\\Slic3r-1.3.0.64bit 
slic3r-console.exe --info D:\Apache\xampp\htdocs\uploads\555569349\555569349.stl > printingInfo.txt 
slic3r-console.exe --load D:\\Documents\\CodeProjects\\SlicingStuff\\100PETG.ini --fill-density 50 --gcode-comments D:\Apache\xampp\htdocs\uploads\555569349\555569349.stl > geometricInfo.txt 
echo Bat has ran
