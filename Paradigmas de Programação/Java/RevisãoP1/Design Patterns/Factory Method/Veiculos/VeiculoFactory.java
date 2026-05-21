public abstract class VeiculoFactory
{
    public abstract Veiculo criarVeiculo (String tipo, String modelo);

    public Veiculo buscar(String nomeC, String tipo, String modelo)
    {
        Veiculo v = this.criarVeiculo(tipo, modelo);
        v.buscar(nomeC);
        return v;
    }
} 