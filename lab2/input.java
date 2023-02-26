int factorial(int number){
    int b;
    int f = 5;
    if(number < 0){
        return 0;
    }
    else if(number == 0){
        return 1;
    }
    return number * factorial(number-1);
}
