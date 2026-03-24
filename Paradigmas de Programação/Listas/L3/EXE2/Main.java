import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
	    IngressoNormal N = new IngressoNormal(30.0);
	    IngressoVip V = new IngressoVip(30.0, 50.0);
	    IngressoCamarote C = new IngressoCamarote(30.0, 50.0, 100.0);
	    
	    N.imprimir();
	    V.imprimir();
	    C.imprimir();
	    
	    
	    
	    IngressoNormal[] vN = new IngressoNormal[25];
	    IngressoVip[] vV = new IngressoVip[25];
	    IngressoCamarote[] vC = new IngressoCamarote[25];
	    
	    for(int i = 0; i < 25; i++)
	    {
	        vN[i] = new IngressoNormal(30.0);
	        vV[i] = new IngressoVip(30.0, 50.0);
	        vC[i] = new IngressoCamarote(30.0, 50.0, 100.0);
	        
	        vN[i].imprimir();
	        vV[i].imprimir();
	        vC[i].imprimir();
	    }
	}
}