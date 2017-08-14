#!/bin/bash
# Compilando modelo Java
mkdir -p build
cd build
javac -d ./ ../src/javatruco/*.java
jar cfe truco.jar javatruco.JavaTruco ./javatruco/*.class
cd ..
# Compilando modelo C-POO
cd src/ctruco
gcc truco.c -o ../../build/truco
cd ../..
# Criando executável
echo "#!/bin/bash
TOEXECUTE=\$1

if [ \"\$TOEXECUTE\" = \"-j\" ] || [ \"\$TOEXECUTE\" = \"--java\" ]; then
	java -jar ./build/truco.jar
elif [ \"\$TOEXECUTE\" = \"-c\" ] || [ \"\$TOEXECUTE\" = \"--cpoo\" ]; then
	./build/truco
else
	echo \"Uso: Truco [OPÇÃO]
Pequeno jogo de truco para ser jogado via terminal.

	-c, --cpoo		Executa o modelo desenvolvido em C com a biblioteca 'oo.h'
	-j, --java		Executa o modelo desenvolvido em Java.
\"
fi" > Truco.sh
chmod +x Truco.sh
