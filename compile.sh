
if [ $# -eq 0 ]
then
 mkdir -p build
 cd build
 qmake -makefile ../src/project.pro
 make
elif [ $1 == "run" ]
then
 ./build/project
elif [ $1 == "test" ] 
then  
 mkdir -p build
 cd build
 qmake -makefile ../src/project.pro
 make
 if [ $? -gt 0 ] 
 then echo "erreur de compilation" 
 else

  ./project
 fi

fi
