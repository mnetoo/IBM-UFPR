import java.util.*;

public class Pedido
{
    // Atributos
    private int numPedido;
    private List<ItemPedido> itensPedido;
    
    // Construtores
    public Pedido(int numPedido, List<ItemPedido> itensPedido)
    {
        setNumPedido(numPedido);
        setItensPedido(itensPedido);
    }
    
    public Pedido(int numPedido)    { this(numPedido, new ArrayList<>()); }
    public Pedido(List<ItemPedido> itensPedido)    { this(0, itensPedido); }
    
    // Getters
    public int getNumPedido() { return this.numPedido; }
    public List<ItemPedido> getItensPedido() { return this.itensPedido; }
    
    // Setters
    public void setNumPedido(int numPedido) { if(numPedido > 0) this.numPedido = numPedido; }
    public void setItensPedido(List<ItemPedido> itensPedido) 
    { 
        if(itensPedido != null) this.itensPedido = itensPedido;
        else this.itensPedido = new ArrayList<>();
    }
    
    // Métodos
    public void adicionarItem(ItemPedido item) { if(item != null) this.itensPedido.add(item); }
    
    public double calcularTotal()
    {
        double total = 0.0;
        for(ItemPedido i : itensPedido) { total += i.getPreco(); }
        return total;
    }
    
    public void imprimirPedido()
    {
        System.out.println("Pedido #" + getNumPedido());
        int i = 1;
        for(ItemPedido item : itensPedido) 
        { 
            System.out.println(i + " - " + item.getNome() + " (R$" + item.getPreco() + ")");
            i++;
        }
        System.out.println("Total: R$" + calcularTotal());
    }
}
