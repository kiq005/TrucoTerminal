/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javatruco;

/**
 *
 * @author kaique
 */
public class Carta {
    public static final int 
            C4 = 0, C5 = 1, C6 = 2, C7 = 3,
            Q = 4, J = 5, K = 6, A = 7, C2 = 8, C3 = 9;
    
    public static final int OURO = 0;
    public static final int ESPADAS = 1;
    public static final int COPAS = 2;
    public static final int PAUS = 3;
    
    public static final int PERDE = -1;
    public static final int EMPATA = 0;
    public static final int GANHA = 1;
    
    
    protected int valor;
    protected int naipe;
    
    public Carta(int valor, int naipe){
        this.valor = valor;
        this.naipe = naipe;
    }
    
    /**
     * Obtém o "desenho" da carta
     * @return String com valor e naipe da carta
     */
    public String Desenho(){
        String carta = "";
        switch(this.getValor()){
            case C4:
                carta += "4";
                break;
            case C5:
                carta += "5";
                break;
            case C6:
                carta += "6";
                break;
            case C7:
                carta += "7";
                break;
            case Q:
                carta += "Q";
                break;
            case J:
                carta += "J";
                break;
            case K:
                carta += "K";
                break;
            case A:
                carta += "A";
                break;
            case C2:
                carta += "2";
                break;
            case C3:
                carta += "3";
                break;
        }
        switch(getNaipe()){
            case OURO:
                carta += "♦";
                break;
            case COPAS:
                carta += "♥";
                break;
            case ESPADAS:
                carta += "♠";
                break;
            case PAUS:
                carta += "♣";
                break;
        }
        return carta;
    }
    
    /**
     * Verifica se a carta é manilha
     * @return Retorna TRUE se a carta for manilha
     */
    private boolean Manilha(Carta c, Carta vira){
        return c.getValor() == (vira.getValor()+1) || 
                (c.getValor()==C4 && vira.getValor()==C3);
    }
    
    /**
     * Verifica se a carta ganha
     * @return Retorna GANHA, EMPATA ou PERDE, dependendo das condições
     */
    public int Ganha(Carta outra, Carta vira){
        if(Manilha(this, vira)){
            if(Manilha(outra, vira) && this.getNaipe() < outra.getNaipe()){
                return PERDE;
            }
            return GANHA;
        }
        else{
            if(Manilha(outra, vira) || this.getValor() < outra.getValor()){
                return PERDE;
            }
            if(this.getValor() > outra.getValor())
                return GANHA;
        }
            
        return EMPATA;
    }

    /**
     * @return o valor
     */
    public int getValor() {
        return valor;
    }

    /**
     * @param valor o valor para definir
     */
    public void setValor(int valor) {
        this.valor = valor;
    }

    /**
     * @return o naipe
     */
    public int getNaipe() {
        return naipe;
    }

    /**
     * @param naipe o naipe para definir
     */
    public void setNaipe(int naipe) {
        this.naipe = naipe;
    }
}
