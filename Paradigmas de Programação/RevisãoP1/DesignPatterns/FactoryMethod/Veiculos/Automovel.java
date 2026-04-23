public abstract class Automovel implements Veiculo
{
    protected String modelo;

    public Automovel(String modelo) { setModelo(modelo); }
    public String getModelo() { return modelo; }
    public void setModelo(String modelo) { this.modelo = modelo; }
} 