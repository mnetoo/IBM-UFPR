import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		
		LampadaLed LL = new LampadaLed(false);
		LampadaFluorescente LF = new LampadaFluorescente(true, 60.0);
		
		System.out.println("1 - Lampada LED (Estado: " + LL.toString() + ")");
		System.out.println("2 - Lampada Lampada Fluorescente (Estado: " + LF.toString() + ")");
		int escolha = sc.nextInt();
		
		Lampada selecionada = null;
		
		if(escolha == 1) selecionada = LL;
		else if(escolha == 2) selecionada = LF;
		else
		{
		    System.out.println("Opção errada, encerrando.");
		    return;
		}
		
		System.out.println("Ligando ou desligando lampada selecionada. Estado: " + selecionada.toString());
		selecionada.alterar();
	    System.out.println("Estado Final: " + selecionada.toString());
	}
}