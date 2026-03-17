import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
        Pedido p = new Pedido(101);
        ItemPedido pizza = new ItemPedido("Pizza", 35.00);
        ItemPedido suco = new ItemPedido("Suco", 8.00);
        
        p.adicionarItem(pizza);
        p.adicionarItem(suco);
        p.imprimirPedido();
	}
}