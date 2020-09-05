arg="$#"
if [ "$arg" -eq "1" ]
then ./ccss $1.c ; clear ; cat $1.c $1.s | less
else echo "Por favor, passe o nome do \"arquivo.c\" a ser testado (sem o \".c\")."
fi
