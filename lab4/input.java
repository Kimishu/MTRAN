void f(){
    int s;
}

int factorial(int number){

    s = 5;
    if(number < 0){
        return 0;
    }
    else if(number==0){
        int b;
        return 1;
    }

    switch(number){
        case 99:
            return 5;
            break;
    }

    return number * factorial(number-1);
}