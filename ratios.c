#include <stdio.h>

int main(void){

    FILE *MyFile;
    MyFile = fopen("counts.dat","r");
    int CountsKPlus[100], CountsKMinus[100], CountsPiPlus[100], CountsPiMinus[100];
    int TotalCountsKPlus = 0, TotalCountsKMinus = 0, TotalCountsPiPlus = 0, TotalCountsPiMinus = 0;

    for(int i = 0; i < 100; i++){
        fscanf(MyFile,"%d %d %d %d", &CountsKPlus[i], &CountsKMinus[i], &CountsPiPlus[i], &CountsPiMinus[i]);
        TotalCountsKPlus += CountsKPlus[i];
        TotalCountsKMinus += CountsKMinus[i];
        TotalCountsPiPlus += CountsPiPlus[i];
        TotalCountsPiMinus += CountsPiMinus[i];
    }

    double RatioPositive, RatioNegative, RatioKaons, RatioPions;

    RatioPositive = (double)TotalCountsKPlus/(double)TotalCountsPiPlus;
    RatioNegative = (double)TotalCountsKMinus/(double)TotalCountsPiMinus;
    RatioKaons = (double)TotalCountsKPlus/(double)TotalCountsKMinus;
    RatioPions = (double)TotalCountsPiPlus/(double)TotalCountsPiMinus;

    printf("The K+/Pi+ ratio is %lf \n", RatioPositive);
    printf("The K-/Pi- ratio is %lf \n", RatioNegative);
    printf("The K+/K- ratio is %lf \n", RatioKaons);
    printf("The Pi+/Pi- ratio is %lf \n", RatioPions);
    
    fclose(MyFile);

    return 0;
}