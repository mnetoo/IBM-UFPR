public class Posicao
{
    // Atributos
    private int x;
    private int y;

    // Construtores
    public Posicao(){}
    public Posicao(int x, int y) {
        setX(x);
        setY(y);
    }

    // Getters and Setters
    public int getX(){
        return this.x;
    }

    public void setX(int x){
        if (x > 0 & x <= 9)
            this.x = x;
    }

    public int getY(){
        return this.y;
    }

    public void setY(int y){
        if (y > 0 & y <= 9)
            this.y = y
    }

    // Métodos
}