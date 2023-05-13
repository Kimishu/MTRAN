public class test {

    public static int factorial(int number) {

        if(number == 0){
            return 1;
        }

        return number * factorial(number-1);
    }

    public static void main(String[] args){

        int a = 5;
        int f = factorial(a);

        System.out.println(f);

    }
}