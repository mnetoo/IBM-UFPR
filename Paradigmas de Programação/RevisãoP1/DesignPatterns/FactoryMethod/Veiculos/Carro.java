public class Carro extends Automovel
{
    public Carro(String modelo)     { super(modelo); }

    public void buscar(String nomeC)    { System.out.println(getModelo() + " buscando " + nomeC); }
    public void parar()     {System.out.println(getModelo() + " parado"); }
}