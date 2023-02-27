int factorial(int number){
    int b;
    double v;
    float c = 4;
    int f= c++;
    float zaza=c+f;
    if(number < 0){
        return 0;
    }
    else if(number==0){
        return 1;
    }
    return number * factorial(number-1);
}