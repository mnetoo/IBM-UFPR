public class AutomovelFactory extends VeiculoFactory
{
    public Veiculo criarVeiculo (String tipo, String modelo)
    {
        if(tipo == "carro")
            return new Carro(modelo);
        else if(tipo == "moto")
            return new Moto(modelo);
        else
            return null;
    }
}