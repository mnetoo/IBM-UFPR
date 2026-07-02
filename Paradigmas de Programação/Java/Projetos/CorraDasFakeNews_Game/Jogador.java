public class Jogador extends ElementoDoJogo
{
    // Atributos
    private Item[] itens;

    // Construtores
    public Jogador(){}
    public Jogador(int tipo, Item[] itens, boolean estado) {
        ElementoDoJogo(tipo, estado);
        setItens(itens);
    }

    // Getters and Setters
    public Item[] getItens(){
        return this.itens;
    }

    public void setItens(Item[] itens){
        if //
            this.itens = itens;
    }

    // Métodos
    public void usarItem(Jogador[] jogadores, int id) {}
}