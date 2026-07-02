public class ElementoDoJogo{
    // Atributos
    protected int tipo;
    protected boolean estado;

    // Construtores
    public ElementoDoJogo(){}
    public ElementoDoJogo(int tipo, boolean estado){
        setTipo(tipo);
        setEstado(estado);
    }

    //Getters and Setters
    public void setTipo(int tipo){
        if (tipo >= 0 & tipo < 4)
            this.tipo = tipo;
    }

    public int getTipo(){
        return this.tipo;
    }

    public void setEstado(boolean estado){
        this.estado = estado;
    }

    public boolean isEstado(){
        return this.estado;
    }

    // Métodos
}