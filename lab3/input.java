int factorial(int number){

    if(number < 0){
        return 0;
    }
    else if(number==0){
        return 1;
    }

    switch(number){
        case 99:
            return 5;
            break;
    }

    return number * factorial(number-1);
}