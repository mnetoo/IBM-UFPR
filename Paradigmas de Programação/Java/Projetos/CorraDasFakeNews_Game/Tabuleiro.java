public class Tabuleiro
{
    //Atributos
    private Posicao[] setorNormal;
    private Posicao[] setorRestrito;
    private Posicao[] posicaoJogadores;
    private Posicao[] posicaoItens;
    private Posicao[] posicaoFakeNews;

    // Construtores
    public Tabuleiro(){}
    public Tabuleiro(Posicao[] setorNormal, Posicao[] setorRestrito, 
                    Posicao[] posicaoJogadores, Posicao[] posicaoItens, 
                    Posicao[] posicaoFakeNews){
        setSetorNormal(setorNormal);
        setSetorRestrito(setorRestrito);
        setPosicaoJogadores(posicaoJogadores);
        setPosicaoItens(posicaoItens);
        setPosicaoFakeNews(posicaoFakeNews);
    }

    // Getters and Setters
    public Posicao[] getSetorNormal(){
        return this.setorNormal;
    }

    public void setSetorNormal(Posicao[] setorNormal){
        if //
            this.setorNormal = setorNormal;
    }

    public Posicao[] getSetorRestrito(){
        return this.setorRestrito;
    }

    public void setSetorRestrito(Posicao[] setorRestrito){
        if //
            this.setorRestrito = setorRestrito;
    }

    public Posicao[] getPosicaoJogadores(){
        return this.posicaoJogadores;
    }

    public void setPosicaoJogadores(Posicao[] posicaoJogadores){
        if //
            this.posicaoJogadores = posicaoJogadores;
    }

    public Posicao[] getPosicaoItens(){
        return this.posicaoItens;
    }

    public void setPosicaoItens(Posicao[] posicaoItens){
        if //
            this.posicaoItens = posicaoItens;
    }

    public Posicao[] getPosicaoFakeNews(){
        return this.posicaoFakeNews;
    }

    public void setPosicaoFakeNews(Posicao[] posicaoFakeNews){
        if //
            this.posicaoFakeNews = posicaoFakeNews;
    }

    // Métodos
    public void moverJogador(Jogador[] jogadores, int id, int novo_x, int novo_y) {}
    public void posicionarItens(Item[] itens) {}
    public void posicionarFakeNews( FakeNews[] fakeNews) {}
}