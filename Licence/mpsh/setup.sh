cd src
echo Cleaning flex files.
rm scan.h scan.c vars_scan.h vars_scan.c
echo Building flex files.
flex scan.l
flex vars_scan.l
cd ..
echo Make
make
# Add directory to path.
echo Checking path.
which mpsh >& /dev/null
if [ "$?" != "0" ]
then
    echo Adding MPSH to path.
    export PATH=$PATH:$PWD
fi
