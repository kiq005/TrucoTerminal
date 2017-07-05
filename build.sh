#!/bin/bash
mkdir -p build
cd build
javac -d ./ ../src/javatruco/*.java
jar cfe truco.jar javatruco.JavaTruco ./javatruco/*.class
cd ..
echo "#!/bin/bash
java -jar ./build/truco.jar" > Truco.sh
chmod +x Truco.sh
