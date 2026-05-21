public final class BoloBaseFactory extends BoloFactory
{
    public Bolo criarBolo(String tipo, String tamanho)
    {
        if (tipo == null || tamanho == null)
            return null;

        if (tipo.equalsIgnoreCase("chocolate"))
            return new BoloChocolate(tamanho);
        else if (tipo.equalsIgnoreCase("fruta"))
            return new BoloFruta(tamanho);
        else if (tipo.equalsIgnoreCase("vegano"))
            return new BoloVegano(tamanho);
        else
            return null;
    }
}