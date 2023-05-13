public class test {

    public static int factorial(int number) {

        if(number == 0){
            return 1;
        }

        return number * factorial(number-1);
    }

    public static void main(String[] args){

        int f = factorial(5);

        System.out.println(f);
    }
}