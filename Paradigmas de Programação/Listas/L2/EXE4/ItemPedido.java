import java.util.*;

public class ItemPedido
{
    //  Atributos
    private String nome;
    private double preco;
    
    //  Construtores
    public ItemPedido(String nome, double preco)
    {
        setNome(nome);
        setPreco(preco);
    }
    
    public ItemPedido(String nome)  { this(nome, 0.0); }
    public ItemPedido(double preco)  { this("", preco); }
    
    // Getters
    public String getNome() { return this.nome; }
    public double getPreco() { return this.preco; }
    
    // Setters
    public void setNome(String nome) { if(nome != null) this.nome = nome; }
    public void setPreco(double preco) { if(preco > 0) this.preco = preco; }
}
