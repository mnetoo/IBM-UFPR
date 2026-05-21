import java.util.Observable;
import java.util.Observer;


public class Assinante implements Observer
{
    private Observable revistaInf;
    private int edicaoNovaRevista;

    public Assinante(Observable revistaInf)
    {
        setRevistaInf(revistaInf);
        revistaInf.addObserver(this); // método correto
    }

    // Getters
    public Observable getRevistaInf() { return this.revistaInf; }
    public int getEdicaoNovaRevista() { return this.edicaoNovaRevista; }

    // Setter
    public void setRevistaInf(Observable revistaInf)
    {
        if(revistaInf != null)
            this.revistaInf = revistaInf;
    }

    @Override
    public void update(Observable o, Object arg)
    {       
        if(o instanceof RevistaInformatica)
        {
            RevistaInformatica rev = (RevistaInformatica) o;
            this.edicaoNovaRevista = rev.getEdicao();

            System.out.println("Atenção! Edição " + edicaoNovaRevista + " disponível");
        }
    }
}