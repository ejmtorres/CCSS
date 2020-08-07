echo "####################"
echo "# Inicializando ...#"
echo "####################"
rm -v *.o
rm -v ccss
rm -v testar_al
cd fontes
rm -v *.o
echo "###################################################"
echo "# Gerando o CCSS - Compilador C Super Simples ... #"
echo "###################################################"
make -f ../gerarccss.mak
make -f ../gerartestar_al.mak
mv ccss ..
mv testar_al ..
rm -v *.o
echo "#####################################"
echo "# Gerando as bibliotecas do CCS ... #"
echo "#####################################"
make -f ../gerarlib.mak
mv lib_es.o ..
mv lib_cad.o ..
cd ..
