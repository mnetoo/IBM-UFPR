public class Lampada
{
    // Atributos
    protected boolean estado;
    
    // Construtor
    public Lampada(boolean estado) { setEstado(estado); }

    // Getters
    public boolean isAtivo() { return this.estado; }
    
    // Setters
    public void setEstado(boolean estado) { this.estado = estado; }
    
    // Métodos
    public void alterar() { this.estado = !this.estado; }
    
    @Override
    public String toString() { return this.estado ? "Ligada" : "Desligada"; }
}