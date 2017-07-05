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
public abstract class Jogador implements PuxaCarta{
    protected Carta[] mao;
    protected int cartas;
    
    public Jogador(){
        cartas = 0;
        mao = new Carta[3];
    }
    
    public void darCarta(Carta c){
        this.mao[this.cartas]=c;
        this.cartas++;
    }
    
    public void esvaziarMao(){
        this.cartas = 0;
    }
    
    protected void organizaMao(){
        if(this.mao[0]==null){
            if(this.mao[2]!=null){
                this.mao[0]=this.mao[2];
                this.mao[2]=null;
            }
            else if(this.mao[1]!=null){
                this.mao[0]=this.mao[1];
                this.mao[1]=null;
            }
        }
        else if(this.mao[1]==null){
            if(this.mao[2]!=null){
                this.mao[1]=this.mao[2];
                this.mao[2]=null;
            }
        }
    }

    @Override
    public abstract Carta obterCarta();
    
}
