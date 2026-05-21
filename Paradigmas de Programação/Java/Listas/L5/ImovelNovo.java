public class ImovelNovo extends Imovel
{
    // Atributos

    //  Construtor
    public ImovelNovo(Endereco endereco, double preco) { super(endereco, preco); }

    //  Getters e Setters

    @Override
    public double calcularValorImovel() { return getPreco() * 1.5; }
}