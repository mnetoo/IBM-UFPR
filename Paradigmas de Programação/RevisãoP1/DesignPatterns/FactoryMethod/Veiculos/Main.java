public class Main
{
    public static void main(String[] args)
    {
        VeiculoFactory factory = new AutomovelFactory();
        Veiculo v1 = factory.criarVeiculo("carro", "Fusca");
        Veiculo v2 = factory.criarVeiculo("moto", "Honda CG");

        v1.buscar("Maria");
        v2.buscar("João");
        v1.parar();
        v2.parar();

        Veiculo v3 = factory.buscar("Carlos", "carro", "Gol");
        v3.parar();
    }
}