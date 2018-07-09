#creat dir build if not exist
if [ -d ./build ]; then
	rm -Rfv build;
fi
mkdir ./build && cd ./build

#create makefile and build project
cmake .. && make

#print dependensies in file
ldd ocv > dependensies.txt

#replace exec file
mkdir bin && mv ocv bin
