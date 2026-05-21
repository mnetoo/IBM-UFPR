public class ImovelVelho extends Imovel
{
    // Atributos

    //  Construtor
    public ImovelVelho(Endereco endereco, double preco) { super(endereco, preco); }

    //  Getters e Setters

    @Override
    public double calcularValorImovel() { return getPreco() * 0.2; }
}