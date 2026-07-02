public class Jogo
{
    // Atributos
    private int turno;
    private Jogador[] jogadores;
    private FakeNews[] fakeNews;
    private Item[] itens;

    // Construtores
    public Jogo(){};
    public Jogo(int turno, Jogador[] jogadores, FakeNews[] fakeNews, Item[] itens){
        setTurno(turno);
        setJogadores(jogadores);
        setFakeNews(fakeNews);
        setItens(itens);
    }

    // Getters and Setters
    public int getTurno(){
        return this.turno;
    }

    public void setTurno(){
        if (turno > 0 & turno < 21)
            this.turno = turno;
    }

    public Jogador[] getJogadores(){
        return this.jogadores;
    }

    public void setJogadores(Jogador[] jogadores){
        if //
            this.jogadores = jogadores;
    }

    public FakeNews[] getFakeNews(){
        return this.fakeNews;
    }

    public void setFakeNews(FakeNews[] fakeNews){
        if //
            this.fakeNews = fakeNews
    }

    public Item[] getItens(){
        return this.itens;
    }

    public void setItens(Item[] itens){
        if //
            this.itens = itens;
    }

    // Métodos
    public void iniciarJogo() {}
    public void atualizarTurno() {}
}