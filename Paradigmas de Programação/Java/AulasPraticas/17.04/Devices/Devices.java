public abstract class Devices implements Offline
{
    protected boolean estado;

    public Devices(boolean estado)  { isEstado(estado); }

    public boolean getEstado()  { return this.estado; }
    public void isEstado(boolean estado)    { this.estado = estado; }
}