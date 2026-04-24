public class Lampada
{
    // Atributos
    protected boolean estado;
    
    // Construtor
    public Lampada(boolean estado) { setEstado(estado); }

    // Getters
    public boolean isEstado() { return this.estado; }
    
    // Setters
    public void setEstado(boolean estado) { this.estado = estado; }
    
    // Métodos
    public void ligar() { this.estado = true; }
    public void desligar()  { this.estado = false; }
    
    @Override
    public String toString() { return this.estado ? "Ligada" : "Desligada"; }
}
