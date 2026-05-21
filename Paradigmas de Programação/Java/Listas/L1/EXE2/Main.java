import java.util.Scanner;

public class Main
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		System.out.print("Digite a primeira hora: ");
		int h1 = sc.nextInt();
		int m1 = sc.nextInt();

		System.out.print("Digite a segunda hora: ");
		int h2 = sc.nextInt();
		int m2 = sc.nextInt();

		Time t1 = new Time(h1, m1);
		Time t2 = new Time(h2, m2);

		System.out.println("Primeira hora: " + t1.toString());
		System.out.println("Segunda hora: " + t2.toString());

		if(t1.anterior(h2, m2))
			System.out.println("Primeira hora é anterior!");
		else if(t1.posterior(h2, m2))
				System.out.println("Primeira hora é posterior!");
		else
			System.out.println("AS duas horas são iguai!");

		sc.close();
	}
}
