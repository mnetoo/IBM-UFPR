public abstract class Imovel
{
    //  Atributos
    private Endereco endereco;
    private double preco;

    //  Construtor
    public Imovel(Endereco endereco, double preco)
    {
        setEndereco(endereco);
        setPreco(preco);
    }

    //  Getters
    public Endereco getEndereco()   { return this.endereco; }
    public double getPreco()    { return this.preco; }

    //  Setters
    public void setEndereco(Endereco endereco)   { if(endereco != null) this.endereco = endereco; }
    public void setPreco(double preco)  { if(preco > 0.0) this.preco = preco; }

    //  Métodos Abstratos
    public abstract double calcularValorImovel();
}