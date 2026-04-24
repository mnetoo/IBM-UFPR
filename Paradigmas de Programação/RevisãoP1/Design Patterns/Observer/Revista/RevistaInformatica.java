import java.util.Observable;
import java.util.Observer;

public class RevistaInformatica extends Observable
{
    private int edicao;

    public RevistaInformatica(int edicao)
    {
        setEdicao(edicao);
    }
    
    public int getEdicao() { return this.edicao; }

    public void setEdicao(int novaEdicao)
    {
        if(novaEdicao > 0)
        {
            this.edicao = novaEdicao;

            setChanged();
            notifyObservers();
        }
    }
}