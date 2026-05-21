import java.util.ArrayList;
import java.util.List;

public class TickerCripto 
{
    private List<PrecoObserver> observers = new ArrayList<>();
    private double preco;
    private String nomeMoeda;

    public TickerCripto(String nomeMoeda) {this.nomeMoeda = nomeMoeda; }
    public void registrarObserver(PrecoObserver observer) { observers.add(observer); }
    public void removerObserver(PrecoObserver observer) {observers.remove(observer); }

    public void setPreco(double novoPreco) 
    {
        this.preco = novoPreco;
        System.out.println("\n--- Ticker " + nomeMoeda + ": Novo preço registrado: $" + novoPreco + " ---");
        notificarTodos();
    }

    private void notificarTodos() 
    {
        // O Subject apenas percorre a lista e chama o método do contrato
        for (PrecoObserver observer : observers)
            observer.atualizar(this.preco);
    }
}