arg="$#"
if [ "$arg" -eq "1" ]
then clear ; cat -n $1.c ; ./ccss $1.c ; cat $1.s
else echo "Por favor, passe o nome do \"arquivo.c\" a ser testado (sem o \".c\")."
fi
