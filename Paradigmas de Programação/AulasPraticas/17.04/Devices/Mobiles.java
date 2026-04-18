public class Mobiles extends SmartDevices
{
    public Mobiles(boolean estado, boolean conexao) { super(estado, conexao); }

    @Override
    public void ligar()
    {
        System.out.println("Ligando celular...");
        this.estado = true;
    }

    @Override
    public void desligar()
    {
        System.out.println("Desligando celular...");
        this.estado = false;  
    }

    @Override
    public void conectarWifi()
    {
        System.out.println("Conectando wifi...");
        this.conexao = true;    
    }
}