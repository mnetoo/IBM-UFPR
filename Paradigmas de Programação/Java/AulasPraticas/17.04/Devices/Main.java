public class Main 
{
    public static void main(String[] args) 
    {
        Offline celular = new Mobiles(false, false);
        Offline tv = new Eletrodomestico(false);

        celular.ligar(); 
        tv.ligar();

        if (celular instanceof Online) 
            ((Online) celular).conectarWifi();

        if(tv instanceof Online)
            ((Online) tv).conectarWifi();
        else
            System.out.println("TV é dispositivo OFFLINE!");

        celular.desligar();
        tv.desligar();
    }
}