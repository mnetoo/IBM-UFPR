public class Eletrodomestico extends Devices
{
    public Eletrodomestico(boolean estado)  { super(estado); }

    @Override
    public void ligar()
    {
        System.out.println("Ligando eletrodoméstico...");
        this.estado = true;
    }

    @Override
    public void desligar()
    {
        System.out.println("Desligando eletrodoméstico...");
        this.estado = false;   
    }
}