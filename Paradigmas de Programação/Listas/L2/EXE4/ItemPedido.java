import java.util.*;

public class ItemPedido
{
    private String nome;
    private double preco;
    
    public ItemPedido(String nome)
    {
        setNome(nome);
        this.preco = 0.0;
    }
    
    public ItemPedido(String nome, double preco)
    {
        setNome(nome);
        setPreco(preco);
    }
    
    // Getters
    public String getNome() { return this.nome; }
    public double getPreco() { return this.preco; }
    
    // Setters
    public void setNome(String nome) { if(nome != null) this.nome = nome; }
    public void setPreco(double preco) { if(preco > 0) this.preco = preco; }
}