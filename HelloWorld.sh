#PBS -l nodes=1:ppn=5,mem=1gb,walltime=00:10:00
#PBS -m abe
#PBS -N ejercicio29

cd $PBS_O_WORKDIR # este es el directorio desde donde se ejecuto qsub
gcc -fopenmp HelloWorld.c -o HelloWorld_c
./HelloWorld_c

